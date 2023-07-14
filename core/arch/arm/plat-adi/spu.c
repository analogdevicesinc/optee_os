/**
 * SPU driver for ADI SC5xx SoCs
 */

#include <inttypes.h>
#include <initcall.h>
#include <io.h>
#include <kernel/panic.h>
#include <mm/core_mmu.h>
#include <mm/core_memprot.h>
#include <platform_config.h>
#include <trace.h>

#include "spu.h"

#define SPU_SECUREP(n) (0xa00 + 4*(n))
#define SPU_SECUREP_MSEC (1 << 1)
#define SPU_SECUREP_SSEC (1 << 0)

#define SPU_WP(n) (0x400 + 4*(n))

// SC598 specific, other SoCs have fewer peripheral regions supported
#define SPU_SECUREP_COUNT 213
#define SPU_WP_COUNT 213

register_phys_mem(MEM_AREA_IO_SEC, ADSP_SC5XX_SPU0_BASE, ADSP_SC5XX_SPU0_SIZE);

static vaddr_t spu0_base __nex_bss;

void spu_peripheral_writeprotect(uint32_t n, uint32_t mask) {
	if (n < SPU_WP_COUNT)
		io_write32(spu0_base + SPU_WP(n), mask);
	DMSG("Setting peripheral %u WP to 0x%x\n", n, mask);
}

void spu_peripheral_secure(uint32_t n) {
	if (n < SPU_SECUREP_COUNT)
		io_write32(spu0_base + SPU_SECUREP(n), SPU_SECUREP_MSEC | SPU_SECUREP_SSEC);
	DMSG("Setting peripheral %u to secure\n", n);
}

/**
 * @todo consider RCU as well, this requires the reset control unit to be migrated
 * and properly supported through ARM PSCI (power state coordination interface)
 * @todo Consider:
 * - SMPU L2-related registers; these should only be configurable on sharc possibly?
 * - More of the debug registers need to be covered to prevent enabling them
 */
static TEE_Result init_spu(void) {
	size_t i;

	/**
	 * Note that the CGU, CDU, and PLL are WP only so that
	 * they can be read by the nonsecure components
	 */
	uint32_t securep_ids[] = {
		109, // DMC0
		121, // SPU0
		126, // DPM0
		129, 130, 131, 132, 133, 134, // System Watchpoint Units
		139, 140, // SWU and SMPU for DMC0
		181, // DAP ROM
		182, 183, 184, // SHARC0 DBG, CTI, PTM
		186, 187, 188, // SHARC1 DBG, CTI, PTM
		201, // TAPC
		202, // Debug Control
		203, 204, 205, 206, // System Watchpoint Units
	};

	/**
	 * If these are not also secured, they can still be read by the open world
	 * @todo linux needs some read-only support to be able to lock cgu/cdu configs
	 */
	uint32_t wp_ids[] = {
		109, // DMC0
		127, // PLL0
		128, // PLL1
	};

	spu0_base = core_mmu_get_va(ADSP_SC5XX_SPU0_BASE, MEM_AREA_IO_SEC,
		ADSP_SC5XX_SPU0_SIZE);

	if (!spu0_base)
		panic();

	// Initially, all peripherals are marked to support non-secure transactions
	// Here, mark the core protected peripherals as secure; other drivers can
	// also protect their peripherals with the SPU api separately

	for (i = 0; i < ARRAY_SIZE(securep_ids); ++i) {
		spu_peripheral_secure(securep_ids[i]);
	}

	for (i = 0; i < ARRAY_SIZE(wp_ids); ++i) {
		spu_peripheral_writeprotect(wp_ids[i], SPU_WP_ALL);
	}

	return TEE_SUCCESS;
}

early_init(init_spu);
