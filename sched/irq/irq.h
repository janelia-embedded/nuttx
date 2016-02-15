/****************************************************************************
 * sched/irq/irq.h
 *
 *   Copyright (C) 2007, 2008, 2013-2014 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __SCHED_IRQ_IRQ_H
#define __SCHED_IRQ_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/spinlock.h>

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* This is the list of interrupt handlers, one for each IRQ.  This is used
 * by irq_dispatch to transfer control to interrupt handlers after the
 * occurrence of an interrupt.
 */

extern FAR xcpt_t g_irqvector[NR_IRQS+1];

#ifdef CONFIG_SMP
/* This is the spinlock that enforces critical sections when interrupts are
 * disabled.
 */

extern spinlock_t g_cpu_irqlock;

/* Used to keep track of which CPU(s) hold the IRQ lock.  There really should
 * only be one.
 */

#if (CONFIG_SMP_NCPUS <= 8)
volatile uint8_t  g_cpu_irqset;
#elif (CONFIG_SMP_NCPUS <= 16)
volatile uint16_t g_cpu_irqset;
#elif (CONFIG_SMP_NCPUS <= 32)
volatile uint32_t g_cpu_irqset;
#else
#  error SMP: Extensions needed to support this number of CPUs
#endif
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

void weak_function irq_initialize(void);
int irq_unexpected_isr(int irq, FAR void *context);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __SCHED_IRQ_IRQ_H */

