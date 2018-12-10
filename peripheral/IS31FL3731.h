#ifndef IS31FL3731_INCLUSION_GUARD_H
#define IS31FL3731_INCLUSION_GUARD_H

#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

/* IS31FL3731 SLAVE ADDRESS */
#define IS31_ADDRESS 0x74U

/* COMMAND REGISTER */
#define IS31_COMMAND_REG 0xFD

/* COMMAND REGISTER DATA */
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_ONE 	0x00U // Frame 1 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_TWO 	0x01U // Frame 2 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_THREE 0x02U // Frame 3 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_FOUR 	0x03U // Frame 4 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_FIVE 	0x04U // Frame 5 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_SIX 	0x05U // Frame 6 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_SEVEN 0x06U // Frame 7 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_EIGHT 0x07U // Frame 8 Register is available
#define IS31_COMMAND_REG_DATA_POINT_TO_PAGE_NINE 	0x08U // Function Register is available

/* OUTPUT REGISTERS */
#define MATRIX_CA1 0x00U

#define LED_SIZE 255
#define MATRIX_SIZE 0x23

void charlieplex_config(nrf_drv_twi_t *);

#endif