/*
 * Copyright 2016 Martin Aberg
 *
 * This file is part of vtest.
 *
 * vtest is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * vtest is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VTEST_H_
#define VTEST_H_

/*
 * vtest - a minimal unit test framework
 *
 * USAGE: See vtest_example.c.
 */

#include <stdlib.h>
#include <stdio.h>

/* Initialize a test session */
void vtest_init(void);
/* End a test session */
void vtest_end(void);
/* Report failed tests */
void vtest_report(void);

/* Test the expression exp and log information if false. */
#define vtest(exp) \
        do { \
                if (exp) { \
                        vtest_pass(); \
                } else { \
                        vtest_fail(__FILE__, __func__, __LINE__, #exp); \
                }\
} while (0);

/* Action for a test expression evaluated as false (internal). */
void vtest_pass(void);
/* Action for a test expression evaluated as true (internal). */
void vtest_fail(const char *file, const char *func, int line, const char *exp);

#endif

