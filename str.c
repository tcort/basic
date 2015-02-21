/*
    tcb - a small BASIC Interpreter written in C.
    Copyright (C) 2015  Thomas Cort <linuxgeek@gmail.com>

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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "str.h"

struct str *new_str(char *value) {

	struct str *s = NULL;

	s = (struct str *) malloc(sizeof(struct str));
	if (s == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memset(s, '\0', sizeof(struct str));

	s->value = value;

	return s;
}

char *eval_str(struct str *s) {
	if (s == NULL) {
		return NULL;
	}

	return s->value;
}

void print_str(struct str *s) {
	if (s == NULL) {
		return;
	}

	printf("\"%s\"", s->value);
}

void free_str(struct str *s) {
	if (s != NULL) {
		if (s->value != NULL) {
			free(s->value);
			s->value = NULL;
		}
		free(s);
		s = NULL;
	}
}