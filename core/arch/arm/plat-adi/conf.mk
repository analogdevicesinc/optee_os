PLATFORM_FLAVOR ?= adsp_sc598

$(call force,CFG_ARM64_core,y)
include core/arch/arm/cpu/cortex-armv8-0.mk
supported-ta-targets = ta_arm64
$(call force,CFG_GIC,y)
$(call force,CFG_ARM_GICV3,y)
$(call force,CFG_WITH_LPAE,y)
$(call force,CFG_WITH_ARM_TRUSTED_FW,y)
$(call force,CFG_SECURE_TIME_SOURCE_CNTPCT,y)

$(call force,CFG_CORE_ASLR,n)

CFG_TEE_CORE_NB_CORE ?= 1

CFG_TZDRAM_START ?= 0x9ef00000
CFG_TZDRAM_SIZE ?= 0x01000000
CFG_SHMEM_SIZE ?= 0x00f00000
CFG_SHMEM_START ?= ($(CFG_TZDRAM_START) - $(CFG_SHMEM_SIZE))
CFG_TEE_RAM_VA_SIZE ?= 0x00100000

CFG_MMAP_REGIONS ?= 24
