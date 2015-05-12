/*
    tcbasic - a small BASIC Interpreter written in C.
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

#ifndef __EXP_H
#define __EXP_H

struct number;
struct tokenizer;

struct exp {
	struct expression *e;
};

struct exp *new_exp(struct expression *e);
struct exp *parse_exp(struct tokenizer *t);
struct number *eval_exp(struct exp *l);
void print_exp(struct exp *l);
void free_exp(struct exp *l);

#endif