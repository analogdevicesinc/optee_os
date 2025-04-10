
global-incdirs-y += . $(PLATFORM_FLAVOR)
ifeq ($(PLATFORM_FLAVOR),adsp_sc598)
	srcs-y += smpu.c
endif

srcs-y += entry_fast.c main.c spu.c

srcs-$(CFG_ADSP_SC5XX_OTP) += huk.c otp_pta.c
srcs-$(CFG_PSCI_ARM32) += psci.c
srcs-$(CFG_ADSP_SC5XX_TRNG) += trng.c

subdirs-y += $(PLATFORM_FLAVOR)
subdirs-y += drivers

ifeq ($(CFG_ADSP_SC5XX_OTP),y)
libdeps += libotp.a
endif
