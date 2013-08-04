/*
 * Copyright (C) 2013, Krzysztof Kliś <krzysztof.klis@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version with the following modification:
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this library with independent modules to produce an
 * executable, regardless of the license terms of these independent modules,
 * and to copy and distribute the resulting executable under terms of your choice,
 * provided that you also meet, for each linked independent module, the terms
 * and conditions of the license of that module. An independent module is a
 * module which is not derived from or based on this library. If you modify this
 * library, you may extend this exception to your version of the library, but
 * you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum {TRUE = 1, FALSE = 0} bool;

int level = 0;
bool escape = FALSE, intern = FALSE, newline = FALSE;

void parse(int c);
void format(int c);
void print(int c);
void indent(void);

int main() {
    int c;

    while ((c = fgetc(stdin)) != EOF) {
        if (c != '\r' && c != '\n') {
            parse(c);
        }
    }
    return 0;
}

void parse(int c) {
    /* parse escaped and unescaped quote */
    if (c == '"' && escape == FALSE) {
        format(c);
        intern = (intern == TRUE) ? FALSE : TRUE;
    } else if (intern == FALSE) {
        if (c != ' ' && c != '\t') {
            format(c);
        }
    } else {
        printf("%c", c);
    }
    /* handle backslash escape */
    if (c == '\\') {
        escape = (escape == TRUE) ? FALSE : TRUE;
    } else {
        escape = FALSE;
    }
}

void format(int c) {
    if (c == '[' || c == '{') {
        print(c);
        level++;
        newline = TRUE;
    } else if (c == ']' || c == '}') {
        if (level > 0) {
            level--;
        }
        indent();
        printf("%c", c);
        newline = TRUE;
    } else if (c == ',') {
        printf("%c", c);
        newline = TRUE;
    } else if (c == ':') {
        printf(" %c ", c);
    } else {
        print(c);
    }
}

void print(int c) {
    if (newline) {
        indent();
        newline = FALSE;
    }
    printf("%c", c);
}

void indent(void) {
    int i;

    printf("\n");
    for (i = 0; i < level; i++) {
        printf("  ");
    }
}
