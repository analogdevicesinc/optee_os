
global-incdirs-y += .
srcs-y += main.c otp_pta.c huk.c smpu.c spu.c

srcs-$(CFG_PSCI_ARM32) += psci.c 

srcs-$(CFG_ADSP_SC5XX_TRNG) += trng.c

subdirs-y += $(PLATFORM_FLAVOR)
subdirs-y += drivers

libdeps += libotp.a
