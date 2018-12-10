#include "twi_control.h"

nrf_drv_twi_t twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
		
		const nrf_drv_twi_t * twi_instance;
		
		twi_instance = &m_twi;
		
		NRF_LOG_INFO("twi_control:");
		NRF_LOG_INFO("&m_twi 0x%x, twi_instance: 0x%x", &m_twi, twi_instance);
		NRF_LOG_FLUSH();
		
		return *twi_instance;
}