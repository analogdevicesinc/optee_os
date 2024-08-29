/**
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Memory mapping for the sc598
 *
 * Copyright (c) 2023, Analog Devices, Inc.
 */
#ifndef PLATFORM_FLAVOR_CONFIG_H
#define PLATFORM_FLAVOR_CONFIG_H

#define ADSP_SC5XX_GICD_BASE 0x31200000
#define ADSP_SC5XX_GIC_SIZE 0x80000

#define ADSP_SC5XX_RCU_BASE 0x3108c000
#define ADSP_SC5XX_RCU_SIZE 0x1000

#define ADSP_SC5XX_SEC_BASE 0x31089000
#define ADSP_SC5XX_SEC_SIZE 0x1000

#define ADSP_SC5XX_SPU0_BASE 0x3108B000
#define ADSP_SC5XX_SPU0_SIZE 0x1000

#define SPU_SECUREP_COUNT 213
#define SPU_WP_COUNT 213

#define ADSP_SC5XX_SMPU9_BASE 0x310a0000
#define ADSP_SC5XX_SMPU9_SIZE 0x1000

#define ADSP_SC5XX_TRNG0_BASE 0x310d0000
#define ADSP_SC5XX_TRNG0_SIZE 0x1000

#define ADSP_SC5XX_TRU_BASE 0x3108a000
#define ADSP_SC5XX_TRU_SIZE 0x1000

#define ADSP_SC5XX_UART0_BASE 0x31003000
#define ADSP_SC5XX_UART_SIZE 0x1000

#define ADSP_SC5XX_SHARC0_L1_BASE	0x28240000
#define ADSP_SC5XX_SHARC0_L1_SIZE	0x00160000
#define ADSP_SC5XX_SHARC1_L1_BASE	0x28a40000
#define ADSP_SC5XX_SHARC1_L1_SIZE	0x00160000
#define ADSP_SC5XX_L2_BASE			0x20000000
#define ADSP_SC5XX_L2_SIZE			0x00200000

#define ADSP_SC5XX_NUM_SHARC_CORES	2
#define ADSP_SHARC_IDLE_ADDR		0x00090004

#define ADSP_SC5XX_SHARC0_IRQ		106 // SOFT1
#define ADSP_SC5XX_SHARC1_IRQ		107 // SOFT2

#define ADSP_SC5XX_SPUID_RCU 		122
#define ADSP_SC5XX_SPUID_SEC		119

#endif