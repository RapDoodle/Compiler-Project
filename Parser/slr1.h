#pragma once

static const int num_slr_states = 25;
static const char actn_shft_tbl[25][10] = {
	{2, -1, -1, 4, 5, -1, -1, -1, -1, -1},
	{-1, -1, 6, -1, -1, -1, -1, -1, -1, -1},
	{-1, 7, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, -1, -1, 4, 5, -1, -1, -1, -1, -1},
	{-1, -1, -1, 4, 5, -1, -1, -1, -1, -1},
	{-1, -1, -1, 15, 13, -1, -1, -1, 16, -1},
	{-1, -1, 6, -1, -1, 17, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 4, 5, -1, 19, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 15, 13, -1, -1, -1, 16, -1},
	{-1, -1, -1, -1, -1, -1, -1, 21, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 15, 13, -1, -1, -1, 16, -1},
	{-1, -1, -1, -1, -1, 23, 19, -1, -1, -1},
	{-1, -1, -1, 15, -1, -1, -1, -1, 16, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1} };
static const char actn_rdc_tbl[25][10] = {
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, 3, -1, -1, 3, -1, -1, -1, 3},
	{-1, -1, 4, -1, -1, 4, -1, -1, -1, 4},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, 2, -1, -1, 2, -1, -1, -1, 2},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 7, 7, 7, 7, -1, -1, -1},
	{-1, -1, -1, 8, 8, 8, 8, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 11, 11, 11, 11, 11, -1, -1},
	{-1, -1, -1, 12, 12, 12, 12, 12, -1, -1},
	{-1, -1, 5, -1, -1, 5, -1, -1, -1, 5},
	{-1, -1, 1, -1, -1, 1, -1, -1, -1, 1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 6, 6, 6, 6, -1, -1, -1},
	{-1, -1, -1, 9, 9, 9, 9, -1, -1, -1},
	{-1, -1, -1, 10, 10, 10, 10, -1, -1, -1} };
static const char actn_acc_tbl[25][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
static const char goto_tbl[25][7] = {
	{-1, 1, 3, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, 8, 3, -1, -1, -1, -1},
	{-1, -1, 9, -1, -1, -1, -1},
	{-1, -1, -1, 10, 11, 12, 14},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, 18, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 20, 11, 12, 14},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, 22, 12, 14},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, 24},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1} };

static const int num_rules = 13;
static const char* rules[] = { "E\'->E", "E->sig_PT", "E->E*T", "E->T", "T->id", "T->(E)", "P->PorQ", "P->Q", "Q->R", "Q->(P)", "R->N==N", "N->id", "N->text" };

const static int rules_tk_count[] = { 1, 4, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1 };
const static int rules_lhs_idx[] = { 0, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 6 };
const static char* rules_lhs_sym[] = { "E\'", "E", "E", "E", "T", "T", "P", "P", "Q", "Q", "R", "N", "N" };
const static char* parser_tks[] = { "sig", "_", "*", "id", "(", ")", "or", "==", "text", "$" };
static const int stack_rule_offset = num_slr_states + 1;

static const int dfa2tkid_tbl_len = 37;
static const int dfa2tkid_tbl[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 8, 4, 5, 2, -1, -1, 7, 1, -1, 6, -1, -1, 0, -1, -1, -1, -1, -1 };

