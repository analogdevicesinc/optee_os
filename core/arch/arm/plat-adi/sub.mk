
global-incdirs-y += .
srcs-y += main.c otp_pta.c huk.c spu.c

subdirs-y += $(PLATFORM_FLAVOR)

libdeps += libotp.a
