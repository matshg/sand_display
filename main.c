#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_delay.h"

#include "twi_control.h"
#include "LIS3DH.h"
#include "IS31FL3731.h"

 /* Number of possible TWI addresses. */
 #define TWI_ADDRESSES      127

/* DATA BUFFER */
static uint8_t data_input_register;
static uint8_t x_data[2];
static uint8_t xyz_data[6];


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    ret_code_t err_code;
    uint8_t address;
    uint8_t sample_data;
    bool detected_device = false;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
	
		nrf_drv_twi_t twi_instance;
    twi_instance = twi_init();
		lis3dh_config(&twi_instance); // Configure accelerometer
		charlieplex_config(&twi_instance); //Configure LED Display
		
    while (true)
    {	
			
    }
}

/** @} */
