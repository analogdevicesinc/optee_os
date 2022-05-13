#ifndef PLAT_ADI_OTP_H
#define PLAT_ADI_OTP_H

#include <adi_otp_pta.h>

#include <util.h>
#include <tee_api_types.h>

struct adi_otp {
	vaddr_t otp_rom_base;
	vaddr_t control_base;
};

TEE_Result adi_otp_read(struct adi_otp *otp, uint32_t id, void *buf, uint32_t *len);
TEE_Result adi_otp_write(struct adi_otp *otp, uint32_t id, void *buf, uint32_t len);
TEE_Result adi_otp_invalidate(struct adi_otp *otp, uint32_t id);

struct adi_otp *adi_get_otp(void);

#endif
