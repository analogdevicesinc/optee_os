/**
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2022, Analog Devices, Inc.
 */
#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

#include <mm/generic_ram_layout.h>

#define STACK_ALIGNMENT 64

#define ADSP_SC598_GICD_BASE 0x31200000
#define ADSP_SC598_GICR_BASE 0x31240000
#define ADSP_SC598_GIC_SIZE 0x80000

#define ADSP_SC598_UART0_BASE 0x31003000
#define ADSP_SC598_UART_SIZE 0x1000

#define ADSP_SC5XX_SPU0_BASE 0x3108B000
#define ADSP_SC5XX_SPU0_SIZE 0x1000

#endif
