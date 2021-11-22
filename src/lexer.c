
#include "lexer.h"

// transforms a mathematical expression into a simple start to finish array of tokens that 
// can then be executed by the parser
svector *generate_tokens(cstr *m_expression) {
	svector *tokens = generate_svec();
	int i = 0; 
	while (i < cstr_len(m_expression)) {
		char current_char = cstr_getc(m_expression, i);
		if (is_bracket(current_char)) {
			cstr *token = get_bracket_token(current_char);
			svec_append(tokens, token);
			del_cstr(token);
		}
		else if (is_operator(current_char)) {
			// '-' is a special case as it can be both an operator and both part of a number
			// which can cause compilcations in long expressions
			
			if (current_char != '-') {
				cstr *operator_token = get_op_token(current_char);
				svec_append(tokens, operator_token);
				del_cstr(operator_token);
			}
			else {
				cstr *operator_token = get_op_token('+'); // replace - with + and make the next number be negative
				svec_append(tokens, operator_token);
				del_cstr(operator_token);
			}
			
		}
		if (isdigit(current_char) || current_char == '-'){
			// create number
			number *num = get_number(i, m_expression);
			i = num->pos->y;
			// get token
			cstr *token = num_to_token(num);
			svec_append(tokens, token);
			del_cstr(token);
			del_number(num);
			if (i >= cstr_len(m_expression)) {break;} 
		}
		i++;
	}
	return tokens;
}


cstr *num_to_token(number *num) {
	switch (num->type) {
		case Int_t:
			return get_int_token(num->str_num);
		case Float_t:
			return get_float_token(num->str_num);
		case Nan_t:
			return get_cstr(NAN_TOKEN);
		default:
			return NULL;
			break;
	}
}

number *get_number(int start_pos, cstr *expression) {
	number *num = alloc_number();
	cstr *str_num = get_cstr("");
	num_type type_ = Int_t;
	for (int i = start_pos; i < cstr_len(expression); i++) {
		char c = cstr_getc(expression, i);
		if (isdigit(c) || c == '.' || c == ',' || (i == start_pos)) {
			if (c == '.' || c == ',') {
				type_ = Float_t;
			}
			cstr_appendc(str_num, c);
		}
		else {
			break;
		}
	}
	if (cstr_len(str_num) == 0) {type_ = Nan_t;}
	num->pos = get_point(start_pos, start_pos+cstr_len(str_num)-1);
	num->type = type_;
	num->str_num = str_num;
	return num;
}	

bool is_operator(char c) {
	char operators[] = USED_OPERATORS;
	for (int i = 0; i < strlen(operators); i++) {
		if (operators[i] == c) return true;
	}
	return false;
}


//XXX: add more brackets later like [] {} etc
bool is_bracket(char c) { return (is_rbracket(c) || is_lbracket(c)); }
bool is_lbracket(char c) { return c == '('; }
bool is_rbracket(char c) { return c == ')'; }