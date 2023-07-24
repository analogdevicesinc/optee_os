// SPDX-License-Identifier: BSD-2-Clause
#ifndef ADI_RCU_H
#define ADI_RCU_H
/**
 * The reset control unit is used to reset the platform as well as reset individual
 * cores, as required when code is loaded to a SHARC from another core
 *
 * Copyright (c) 2023, Analog Devices, Inc.
 */

void adi_rcu_reset(void);

#endif
