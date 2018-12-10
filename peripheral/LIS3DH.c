#include "LIS3DH.h"


static uint8_t tx_data[2];
static uint8_t data_input_register;
	
void lis3dh_config (nrf_drv_twi_t * m_twi) {	
	  /* READ DUMMY DATA REGISTER VALUE (EXPECTED: 0x33) */
		tx_data[0] = LIS3DH_REG_DUMMY;
		nrf_drv_twi_tx (m_twi, LIS3DH_ADDRESS, &tx_data[0], sizeof(tx_data[0]), false);
		nrf_drv_twi_rx (m_twi, LIS3DH_ADDRESS, &data_input_register, sizeof(data_input_register));
	
		nrf_drv_twi_t twi_instance = *m_twi;
	
		NRF_LOG_INFO("LIS3DH:");
		NRF_LOG_INFO("m_twi 0x%x, &m_twi: 0x%x", m_twi, &m_twi);
		NRF_LOG_FLUSH();
	
		NRF_LOG_INFO("Dummy register: 0x%x", data_input_register);
		NRF_LOG_FLUSH();
	
		/* CONFIGURE CTRL REG1 */
		tx_data[0] = CTRL_REG1;
		tx_data[1] = 0x47U; // 0100 0111 - Set ODR2 High (50 Hz) and enable XYZ
		nrf_drv_twi_tx(m_twi, LIS3DH_ADDRESS, tx_data, sizeof(tx_data), false);
		
		/* CONFIGURE CTRL REG4 */
		tx_data[0] = CTRL_REG4;
		tx_data[1] = 0x08U; // 0000 1000 - Set HR (High Resolution) High (12 Bit output mode).
		nrf_drv_twi_tx(m_twi, LIS3DH_ADDRESS, tx_data, sizeof(tx_data), false);
}

/*
void lis3dh_read_data (void) {

			// READ X_DATA_L
			tx_data[0] = OUT_X_L;
			nrf_drv_twi_tx(&m_twi, LIS3DH_ADDRESS, &tx_data[0], sizeof(tx_data[0]), false);
			nrf_drv_twi_rx(&m_twi, LIS3DH_ADDRESS, &x_data[0], sizeof(data_input_register));
			
			// READ X_DATA_H
			tx_data[0] = OUT_X_H;
			nrf_drv_twi_tx(&m_twi, LIS3DH_ADDRESS, &tx_data[0], sizeof(tx_data[0]), false);
			nrf_drv_twi_rx(&m_twi, LIS3DH_ADDRESS, &x_data[1], sizeof(data_input_register));
			
			for (int i = 0; i < sizeof(x_data); i++)
			{
			NRF_LOG_INFO("X Register: %d", x_data[i]);
			}
			NRF_LOG_FLUSH();
			nrf_delay_ms(200);
}
*/