// SPDX-License-Identifier: BSD-2-Clause
/**
 * HUK retrieval via OTP
 *
 * Copyright (c) 2022, Analog Devices, Inc.
 */

#include <assert.h>
#include <inttypes.h>
#include <kernel/tee_common_otp.h>

#include "otp.h"

#define ADI_OTP_HUK_BYTE_LEN 32

TEE_Result tee_otp_get_hw_unique_key(struct tee_hw_unique_key *hwkey)
{
	TEE_Result result;
	struct adi_otp *otp = adi_get_otp();
	uint8_t buffer[ADI_OTP_HUK_BYTE_LEN];
	uint32_t len = sizeof(buffer);
	bool zeroes = true;
	int i;

	result = adi_otp_read(otp, ADI_OTP_ID_huk, buffer, &len, ADI_OTP_ACCESS_SECURE);
	if (TEE_SUCCESS != result)
		return result;

	assert(sizeof(hwkey->data) <= sizeof(buffer));

	for (i = 0; i < ADI_OTP_HUK_BYTE_LEN; ++i) {
		if (0 != buffer[i]) {
			zeroes = false;
			break;
		}
	}

	if (zeroes)
		EMSG("HUK OTP is programmed with zeroes--please program a real HUK or enable autogeneration\n");

	memcpy(&hwkey->data[0], buffer, sizeof(hwkey->data));
	return TEE_SUCCESS;
}

