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

#include "runtime.h"

#include "command.h"
#include "line.h"

struct command *new_command(int type) {

	struct command *cmd = NULL;

	cmd = (struct command *) malloc(sizeof(struct command));
	if (cmd == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memset(cmd, '\0', sizeof(struct command));

	cmd->type = type;

	return cmd;
}

void exec_command(struct command *cmd) {

	int r;
	struct line *cur;

	if (cmd == NULL) {
		return;
	}

	switch (cmd->type) {
		case CLEAR:
			runtime_reset();
			break;
		case LIST:
			print_line(runtime_get_first_line());
			break;
		case RUN:
			cur = runtime_get_first_line();
			while (cur != NULL) {
				r = eval_line(cur);
				if (r == -1) {
					cur = cur->next;
				} else if (r == -2) {
					break;
				} else {
					cur = runtime_get_line(r);
				}
			}
			break;
	}
}

void print_command(struct command *cmd) {

	if (cmd == NULL) {
		return;
	}

	switch (cmd->type) {
		case CLEAR:
			printf("CLEAR");
			break;
		case LIST:
			printf("LIST");
			break;
		case RUN:
			printf("RUN");
			break;
		default:
			printf("?");
			break;
	}
}

void free_command(struct command *cmd) {
	if (cmd != NULL) {
		free(cmd);
		cmd = NULL;
	}
}