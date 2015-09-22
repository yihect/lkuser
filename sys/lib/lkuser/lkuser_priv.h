/*
 * Copyright (c) 2015 Travis Geiselbrecht
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <list.h>
#include <kernel/thread.h>
#include <kernel/event.h>
#include <assert.h>
#include <lib/lkuser.h>
#include <sys/lkuser_syscalls.h>

typedef struct lkuser_state {
    struct list_node node;

    int retcode;
    enum {
        STATE_INITIAL,
        STATE_RUNNING,
        STATE_DEAD,
    } state;
    event_t event;

    int (*entry)(const struct lkuser_syscall_table *table);

    thread_t main_thread;
    void *main_thread_stack;
} lkuser_state_t;

/* defined in syscalls.c */
const struct lkuser_syscall_table lkuser_syscalls;

static inline lkuser_state_t *get_lkuser_state(void)
{
    lkuser_state_t *s = (lkuser_state_t *)tls_get(TLS_ENTRY_LKUSER);
    DEBUG_ASSERT(s);
    return s;
}

