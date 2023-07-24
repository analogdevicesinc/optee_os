// SPDX-License-Identifier: BSD-2-Clause
/**
 * RCU driver for ADI SC5xx SoCs
 *
 * Copyright (c) 2023, Analog Devices, Inc.
 */

#include <inttypes.h>
#include <initcall.h>
#include <io.h>
#include <kernel/panic.h>
#include <mm/core_mmu.h>
#include <mm/core_memprot.h>
#include <platform_config.h>
#include <trace.h>

#include <adi_rcu.h>

/* Base register offsets */
#define ADI_RCU_REG_CTL				0x00
#define ADI_RCU_REG_STAT			0x04
#define ADI_RCU_REG_CRCTL			0x08
#define ADI_RCU_REG_CRSTAT			0x0c

// @todo move platform-specific options into a platform_flavor-based header
#ifdef CONFIG_ARCH_SC58X
#define ADI_RCU_REG_SIDIS			0x10
#define ADI_RCU_REG_SISTAT			0x14
#define ADI_RCU_REG_SVECT_LCK		0x18
#define ADI_RCU_REG_BCODE			0x1c
#define ADI_RCU_REG_SVECT0			0x20
#define ADI_RCU_REG_SVECT1			0x24
#define ADI_RCU_REG_SVECT2			0x28
#define ADI_RCU_REG_MSG				0x60
#define ADI_RCU_REG_MSG_SET			0x64
#define ADI_RCU_REG_MSG_CLR			0x68
#else
#define ADI_RCU_REG_SRRQSTAT		0x18
#define ADI_RCU_REG_SIDIS			0x1c
#define ADI_RCU_REG_SISTAT			0x20
#define ADI_RCU_REG_BCODE			0x28
#define ADI_RCU_REG_SVECT0			0x2c
#define ADI_RCU_REG_SVECT1			0x30
#define ADI_RCU_REG_SVECT2			0x34
#define ADI_RCU_REG_MSG				0x6c
#define ADI_RCU_REG_MSG_SET			0x70
#define ADI_RCU_REG_MSG_CLR			0x74
#endif

/* Register bit definitions */
#define ADI_RCU_CTL_SYSRST		BIT(0)

/* Bit values for the RCU0_MSG register */
#define RCU0_MSG_C0IDLE			0x00000100		/* Core 0 Idle */
#define RCU0_MSG_C1IDLE			0x00000200		/* Core 1 Idle */
#define RCU0_MSG_C2IDLE			0x00000400		/* Core 2 Idle */
#define RCU0_MSG_CRR0			0x00001000		/* Core 0 reset request */
#define RCU0_MSG_CRR1			0x00002000		/* Core 1 reset request */
#define RCU0_MSG_CRR2			0x00004000		/* Core 2 reset request */
#define RCU0_MSG_C1ACTIVATE		0x00080000		/* Core 1 Activated */
#define RCU0_MSG_C2ACTIVATE		0x00100000		/* Core 2 Activated */

register_phys_mem(MEM_AREA_IO_SEC, ADSP_SC5XX_RCU_BASE, ADSP_SC5XX_RCU_SIZE);

static vaddr_t rcu_base __nex_bss;

void adi_rcu_reset(void) {
	uint32_t val = io_read32(rcu_base + ADI_RCU_REG_CTL);
	io_write32(rcu_base + ADI_RCU_REG_CTL, val | ADI_RCU_CTL_SYSRST);
}

static TEE_Result adi_init_rcu(void) {
	rcu_base = core_mmu_get_va(ADSP_SC5XX_RCU_BASE, MEM_AREA_IO_SEC,
		ADSP_SC5XX_RCU_SIZE);

	if (!rcu_base)
		panic();

	return TEE_SUCCESS;
}

driver_init(adi_init_rcu);
