/*
    tcbasic - a small BASIC Interpreter written in C.
    Copyright (C) 2015, 2016, 2017, 2018  Thomas Cort <linuxgeek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

#include "sqr.h"
#include "expression.h"
#include "number.h"

struct sqr *new_sqr(struct expression *e) {

	struct sqr *s;

	s = (struct sqr *) malloc(sizeof(struct sqr));
	if (s == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memset(s, '\0', sizeof(struct sqr));

	s->e = e;

	return s;
}

struct sqr *parse_sqr(struct tokenizer *t) {

	struct expression *e;

	token_get(t);
	if (t->token.type != SQR) {
		token_unget(t);
		return NULL;
	}

	token_get(t);
	if (t->token.type != OPAREN) {
		token_unget(t);
		return NULL;
	}

	e = parse_expression(t);
	if (e == NULL) {
		return NULL;
	}

	token_get(t);
	if (t->token.type != CPAREN) {
		token_unget(t);
		free_expression(e);
		return NULL;
	}

	return new_sqr(e);
}

struct number *eval_sqr(struct sqr *s) {
	struct number *n;

	n = eval_expression(s->e);
	if (n->type == INT) {
		float f;
		f = sqrtf((1.0f) * n->value.ival);
		n->type = FLOAT;
		n->value.fval = f;
	} else { /* float */
		n->value.fval = sqrtf(n->value.fval);
	}

	return n;
}

void print_sqr(struct sqr *s) {
	if (s == NULL) {
		return;
	}

	printf("SQR (");
	print_expression(s->e);
	printf(")");
}

void free_sqr(struct sqr *s) {

	if (s != NULL) {
		if (s->e != NULL) {
			free_expression(s->e);
			s->e = NULL;
		}
		free(s);
	}
}
