"""
The script is used to convert the DFA transition table and/or SLR(1) 
table into arrays used in  the DFA-based lexical analyzer or SLR(1) 
parser.

Authors:
    Bohui WU, Rui LIU, Xuchen YAO
"""

import sys
import argparse
import pandas as pd


def to_escape_valid(data):
    data = str(data)
    data = data.replace("'", "\\'")
    data = data.replace("\"", '\\"')
    return data


def to_c_array_1d(data, array_type='int'):
    array_types = ['int', 'char', 'str']

    # Convert to int representation
    array_type = array_types.index(array_type)
    code = '{'
    for c in data:
        if array_type == 0:
            code += str(int(c)) + ", "
        elif array_type == 1:
            code += "'" + to_escape_valid(c) + "', "
        elif array_type == 2:
            code += '"' + to_escape_valid(c) + '", '
        else:
            code += f"'{c}', "
    code = code[0:-2]
    code += '}'
    return code


def to_c_array_2d(data, array_type='int'):
    array_types = ['int', 'char', 'str']

    # Convert to int representation
    array_type = array_types.index(array_type)
    code = '{'
    for idx, row in data.iterrows():
        row_list = list(row)
        code += "\n\t{"
        for c in row_list[1:]:
            if array_type == 0:
                code += str(int(c)) + ", "
            elif array_type == 1:
                code += "'" + to_escape_valid(c) + "', "
            elif array_type == 2:
                code += '"' + to_escape_valid(c) + '", '
            else:
                code += f"'{c}', "
        code = code[0:-2]
        code += "},"
    code = code[0:-1]
    code += '}'
    return code


def to_dfa_trans_tbl(dfa_filename):
    xlsx_file = pd.ExcelFile(dfa_filename)

    # Read the transition table
    tt = pd.read_excel(xlsx_file, 'TransitionTable').fillna(-1)

    # Read the accepted states
    acs = pd.read_excel(xlsx_file, 'AcceptedStates')

    # Get the alphabets (the first row of tt)
    alphabet = [str(x) for x in list(tt.columns)[1:]]
    
    # The the array of alphabets
    alphabet_c = f"static const int alphabet_len = {len(alphabet)};\n"
    alphabet_c += f"static const char alphabet[alphabet_len] = {to_c_array_1d(alphabet, 'char')};\n"

    # The transition table
    trans_table_c = f"static const int max_state = {tt.shape[0]-1};\n"
    trans_table_c += f"static const int trans_table[{tt.shape[0]}][{tt.shape[1]-1}] = {to_c_array_2d(tt, 'int')};\n\n"

    acs_c = f"static const int num_accepted_states = {acs.shape[0]};\n"
    acs_c += f"static const int accepted_states[num_accepted_states] = {to_c_array_1d(list(acs.loc[:, 'StateId']), 'int')};\n\n"

    acs_c += f"static const char* lexemes[] = {to_c_array_1d(list(acs.loc[:, 'Token']), 'str')};\n\n"

    show_tk_idx = list(acs.index[acs['ShowToken'] == 1])
    acs_c += f"static const int show_sym_name_len = {len(show_tk_idx)};\n"
    acs_c += f"static const int show_sym_name[{len(show_tk_idx)}] = {to_c_array_1d(show_tk_idx, 'int')};\n"

    with open('dfa.h', 'w') as f:
        f.write('#pragma once\n\n')
        f.write(alphabet_c + '\n')
        f.write(trans_table_c + '\n')
        f.write(acs_c + '\n')
        print('Successfully saved in dfa.h')

def to_slr1_tbl(slr1_filename, dfa_filename):
    dfa_xlsx_file = pd.ExcelFile(dfa_filename)
    tt = pd.read_excel(dfa_xlsx_file, 'TransitionTable').fillna(-1)
    acs = pd.read_excel(dfa_xlsx_file, 'AcceptedStates')

    slr1_xlsx_file = pd.ExcelFile(slr1_filename)
    rules = pd.read_excel(slr1_xlsx_file, 'rules')
    dfa2tkid_tbl = pd.read_excel(slr1_xlsx_file, 'dfa2tkid_tbl').fillna(-1)
    actn_shft_tbl = pd.read_excel(slr1_xlsx_file, 'actn_shft_tbl').fillna(-1)
    actn_rdc_tbl = pd.read_excel(slr1_xlsx_file, 'actn_rdc_tbl').fillna(-1)
    actn_acc_tbl = pd.read_excel(slr1_xlsx_file, 'actn_acc_tbl').fillna(0)
    goto_tbl = pd.read_excel(slr1_xlsx_file, 'goto_tbl').fillna(-1)

    # Assertions
    actn_shft_tbl_col_len = len(actn_shft_tbl.columns[1:])
    actn_rdc_tbl_col_len = len(actn_rdc_tbl.columns[1:])
    actn_acc_tbl_col_len = len(actn_acc_tbl.columns[1:])
    if actn_shft_tbl_col_len != actn_rdc_tbl_col_len or actn_rdc_tbl_col_len != actn_acc_tbl_col_len:
        raise Exception('the number of tokens in actn_shft_tbl, actn_rdc_tbl, and actn_acc_tbl does not match.')

    if not (all(actn_shft_tbl.columns[1:] == actn_rdc_tbl.columns[1:]) and all(actn_rdc_tbl.columns[1:] == actn_acc_tbl.columns[1:])):
        raise Exception('Token name in actn_shft_tbl, actn_rdc_tbl, and actn_acc_tbl does not match.')

    # Conversions
    tbls_str_c = f'static const int num_slr_states = {actn_shft_tbl.shape[0]};\n'
    # Convert the tables
    tbls = {
        'actn_shft_tbl': actn_shft_tbl,
        'actn_rdc_tbl': actn_rdc_tbl,
        'actn_acc_tbl': actn_acc_tbl, 
        'goto_tbl': goto_tbl
    }
    
    for tbl_name, tbl in tbls.items():
        tbls_str_c += f"static const char {tbl_name}[{tbl.shape[0]}][{tbl.shape[1]-1}] = {to_c_array_2d(tbl, 'int')};\n"

    rule_max_id = 0
    rules_str = []
    rules_tk_count = []
    rules_lhs_idx = []
    rules_lhs_sym = []
    parser_tks = []
    parser_tks = [str(x) for x in list(actn_shft_tbl.columns)[1:]]
    rule_id_dict = {}

    for idx, row in rules.iterrows():
        rule_tks = row['Rule RHS'].split(' ')
        lhs = row['Rule LHS']
        rhs = ''.join(rule_tks)
        if lhs not in rules_lhs_sym:
            # The first occurence
            rule_id_dict[lhs] = rule_max_id
            rule_max_id = rule_max_id + 1
        rules_lhs_sym.append(lhs)
        rules_lhs_idx.append(rule_id_dict[lhs])
        rules_tk_count.append(len(rule_tks))
        rules_str.append(f"{lhs}->{rhs}")

    rules_str_c = f"static const int num_rules = {len(rules)};\n"
    rules_str_c += f"static const char* rules[] = {to_c_array_1d(rules_str, 'str')};\n"

    stack_related_c = f"const static int rules_tk_count[] = {to_c_array_1d(rules_tk_count, 'int')};\n"
    stack_related_c += f"const static int rules_lhs_idx[] = {to_c_array_1d(rules_lhs_idx, 'int')};\n"
    stack_related_c += f"const static char* rules_lhs_sym[] = {to_c_array_1d(rules_lhs_sym, 'str')};\n"
    stack_related_c += f"const static char* parser_tks[] = {to_c_array_1d(parser_tks, 'str')};\n"
    stack_related_c += "static const int stack_rule_offset = num_slr_states + 1;\n"

    # dfa2tkid_tbl
    dfa2tkid_tbl_len = len(tt)-1
    dfa2tkid = [-1] * dfa2tkid_tbl_len
    for idx, row in acs.iterrows():
        try:
            dfa2tkid[int(row['StateId'])] = parser_tks.index(row['Token'])
        except ValueError:
            pass

    dfa2tkid_tbl_c = f"static const int dfa2tkid_tbl_len = {dfa2tkid_tbl_len};\n"
    dfa2tkid_tbl_c += f"static const int dfa2tkid_tbl[] = {to_c_array_1d(dfa2tkid, 'int')};\n"

    with open('slr1.h', 'w') as f:
        f.write('#pragma once\n\n')
        f.write(tbls_str_c + '\n')
        f.write(rules_str_c + '\n')
        f.write(stack_related_c + '\n')
        f.write(dfa2tkid_tbl_c + '\n')
        print('Successfully saved in slr1.h')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-d', 
        '--dfa', 
        metavar='FILE', 
        required=False, 
        default='dfa_trans_tbl.xlsx',
        help='specify the excel file containing DFA\'s transition table.')    
    parser.add_argument(
        '-s', 
        '--slr', 
        metavar='FILE', 
        required=False, 
        default='slr1_tbl.xlsx',
        help='specify the excel file containing DFA\'s transition table.')
    args = parser.parse_args()

    to_dfa_trans_tbl(args.dfa)
    to_slr1_tbl(args.slr, args.dfa)
