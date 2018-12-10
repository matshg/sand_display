#include "IS31FL3731.h"

void charlieplex_config(nrf_drv_twi_t * m_twi)
{
		static uint8_t rx_data;
		nrf_drv_twi_rx(m_twi, IS31_ADDRESS, &rx_data, sizeof(rx_data));
		NRF_LOG_INFO("IS31: 0x%x", rx_data);
		NRF_LOG_FLUSH();
	
		static uint8_t tx_data[2];
	
		// 1. Configure Command Register - Point to page nine (Function register available)
		tx_data[0] = IS31_COMMAND_REG;
		tx_data[1] = IS31_COMMAND_REG_DATA_POINT_TO_PAGE_NINE;
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
	
		// Configure Shutdown register - Set to shutdown mode
		tx_data[0] = 0x0AU; // Shutdown register
		tx_data[1] = 0x00U; // 0000 0000 Shutdown mode 
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
	
		// 2. Configure Command Register - Point to page nine (Function register available)
		tx_data[0] = IS31_COMMAND_REG;
		tx_data[1] = IS31_COMMAND_REG_DATA_POINT_TO_PAGE_NINE;
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
	
		// Configure Shutdown register - Set to operation mode
		tx_data[0] = 0x0AU; // Shutdown register
		tx_data[1] = 0x01U; // 0000 0001 Operation mode 
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
		
		// 3. Configure Command Register - Point to page nine (Function register available)
		tx_data[0] = IS31_COMMAND_REG;
		tx_data[1] = IS31_COMMAND_REG_DATA_POINT_TO_PAGE_NINE;
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
		
		// Configure configuration register belonging to function register
		tx_data[0] = 0x00U; // Configuration register - Sets operating mode of the IS31
		tx_data[1] = 0x00U; // 000 00 000 Picture mode - Start from frame 1 
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);	

		// 4. displayframe
		// Configure Command Register - Point to page nine (Function register available)
		tx_data[0] = IS31_COMMAND_REG;
		tx_data[1] = IS31_COMMAND_REG_DATA_POINT_TO_PAGE_NINE;
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
		
		tx_data[0] = 0x01U; // Pictureframe register
		tx_data[1] = 0x00U; // Choose frame 1
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
	
		// 5. clear
		// 5.1 selectBank
		// Configure Command Register - Point to page nine (Function register available)
		tx_data[0] = IS31_COMMAND_REG;
		tx_data[1] = IS31_COMMAND_REG_DATA_POINT_TO_PAGE_ONE;
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
		
		// For loop - Set all LEDs on & 0 PWM
		for (uint8_t i = 0; i < 6; i++)
		{
			tx_data[0] = 0x024+i*24;
			nrf_drv_twi_tx(m_twi, IS31_ADDRESS, &tx_data[0], sizeof(tx_data[0]), false);
			
			for (uint8_t j=0; j<24; j++){
				tx_data[0] = 0;
				nrf_drv_twi_tx(m_twi, IS31_ADDRESS, &tx_data[0], sizeof(tx_data[0]*24), false);
		}
		
		// For loop - Set each 8 LEDs on
		for (uint8_t f=0; f<8; f++)
		{
				for (uint8_t i=0; i <= 0x11; i++){
					tx_data[0] = f;
					tx_data[1] = i;
					nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
				}
		}
		
		// Configure Audio Sync
		tx_data[0] = IS31_COMMAND_REG;
		tx_data[1] = IS31_COMMAND_REG_DATA_POINT_TO_PAGE_NINE;
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
		
		tx_data[0] = 0x06;
		tx_data[1] = 0x00;
		nrf_drv_twi_tx(m_twi, IS31_ADDRESS, tx_data, sizeof(tx_data), false);
		
		
		
	}	
};

