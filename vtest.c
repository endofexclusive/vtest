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

#include <vtest.h>

/* Representation of a failed test */
struct vtest_node {
        struct vtest_node *next;
        const char *file;
        const char *func;
        int line;
        const char *exp;
};

/* Test session state */
struct vtest_context {
        struct vtest_node *head;
        struct vtest_node *tail;
        int nfail;
        int npass;
};

/* Exactly one test session is supported and is allocated here. */
static struct vtest_context ctx;

void vtest_init(void)
{
        ctx.head = NULL;
        ctx.tail = NULL;
        ctx.nfail = 0;
        ctx.npass = 0;
}

void vtest_pass(void)
{
        ctx.npass++;
}

void vtest_fail(const char *file, const char *func, int line, const char *exp)
{
        struct vtest_node *node;

        node = malloc(sizeof *node);
        if (NULL == ctx.head) {
                ctx.head = node;
        } else {
                ctx.tail->next = node;
        }
        ctx.tail = node;

        node->next = NULL;
        node->file = file;
        node->func = func;
        node->line = line;
        node->exp = exp;
        ctx.nfail++;
}

void vtest_end(void)
{
        struct vtest_node *node;

        /* Unlink all nodes in order. */
        node = ctx.head;
        while (node) {
                struct vtest_node *next;

                next = node->next;
                free(node);
                node = next;
        }
        /* Clear state */
        vtest_init();
}

void vtest_report(void)
{
        struct vtest_node *node;

        puts("\n-----------------");
        printf("PASS: %d\nFAIL: %d\n", ctx.npass, ctx.nfail);

        node = ctx.head;
        while (node) {
                printf(" %s:%d '%s'\n", node->func, node->line, node->exp);
                node = node->next;
        }
        puts("-----------------");
}

