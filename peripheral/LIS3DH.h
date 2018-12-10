#include <stdint.h>

#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

void lis3dh_config (nrf_drv_twi_t *);

/* LIS3DH ACCELEROMETER ADDRESSES */
#define LIS3DH_ADDRESS 0x18U
#define LIS3DH_REG_DUMMY 0x0FU

/* CTRL REGISTERS */
#define CTRL_REG1 0x20U
#define CTRL_REG4 0x23U

/* XYZ REGISTERS */
#define OUT_X_L 0x28U
#define OUT_X_H 0x29U