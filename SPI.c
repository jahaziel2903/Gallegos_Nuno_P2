/*
 * SPI.c
 *
 *  Created on: Mar 13, 2020
 *      Author: edwin
 */

#include "SPI.h"
#include "LCD_nokia.h"

/*it enable the clock module of the SPI by modifying the MDIS bits*/
void SPI_enable(spi_channel_t channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= (~SPI_MCR_MDIS_MASK); /* its enable with zero*/
			break;
		case SPI_1:
			SPI1->MCR &= (~SPI_MCR_MDIS_MASK); /* its enable with zero*/
			break;
		case SPI_2:
			SPI2->MCR &= (~SPI_MCR_MDIS_MASK); /* its enable with zero*/
			break;
		default:
			break;
	}
}
/*It activate the clock gating*/
void SPI_clk(spi_channel_t channel)
{
	switch(channel)
	{
	 	case SPI_0:
			SIM->SCGC6 |= SPI0_CLOCK_GATING;
			break;
		case SPI_1:
			SIM->SCGC6 |= SPI1_CLOCK_GATING;
			break;
		case SPI_2:
			SIM->SCGC3 |= SPI2_CLOCK_GATING;
			break;
		default:
			break;
	}
}
/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
void SPI_set_master(spi_channel_t channel, spi_master_t master_or_slave)
{
	switch(channel)
	{
		case SPI_0:
			if(master_or_slave)
			{
				SPI0->MCR |= SPI_MCR_MSTR_MASK; /*configure the SPI as master*/
			}
			else
			{
				SPI0->MCR &= ~(SPI_MCR_MSTR_MASK); /*configure the SPI as slave*/
			}
			break;
		case SPI_1:
			if(master_or_slave)
			{
				SPI1->MCR |= SPI_MCR_MSTR_MASK; /*configure the SPI as master*/
			}
			else
			{
				SPI1->MCR &= ~(SPI_MCR_MSTR_MASK); /*configure the SPI as slave*/
			}
			break;
		case SPI_2:
			if(master_or_slave)
			{
				SPI2->MCR |= SPI_MCR_MSTR_MASK; /*configure the SPI as master*/
			}
			else
			{
				SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);  /*configure the SPI as slave*/
			}
			break;
		default:
			break;
	 }
}
/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
{
	switch(channel)
	{
		case SPI_0:
			if(enable_or_disable)
			{
				SPI0->MCR &= (~SPI_MCR_DIS_RXF_MASK & ~SPI_MCR_DIS_TXF_MASK); /*Activate the TX and the RX*/
			}
			else
			{
				/*Disactivate the TX and the RX*/
				SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;
				SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;
			}
			break;
		case SPI_1:
			if(enable_or_disable)
			{
				SPI1->MCR &= (~SPI_MCR_DIS_RXF_MASK & ~SPI_MCR_DIS_TXF_MASK); /*Activate the TX and the RX*/
			}
			else
			{
				/*Disactivate the TX and the RX*/
				SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;
				SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;
			}
			break;
		case SPI_2:
			if(enable_or_disable)
			{
				SPI2->MCR &= (~SPI_MCR_DIS_RXF_MASK & ~SPI_MCR_DIS_TXF_MASK); /*Activate the TX and the RX*/
			}
			else
			{
				/*Disactivate the TX and the RX*/
				SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;
				SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;
			}
			break;
		default:
			break;
	}
}
/*It selects the clock polarity depending on the value of cpol*/
 void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
{
	switch(channel)
	{
		case SPI_0:
			if(cpol)
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK; /*HIGH polarity of SPI*/
			}
			else
			{
				SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK); /*LOW polarity of SPI*/
			}
			break;
		case SPI_1:
			if(cpol)
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK; /*HIGH polarity of SPI*/
			}
			else
			{
				SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK); /*LOW polarity of SPI*/
			}
			break;
		case SPI_2:
			if(cpol)
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK; /*HIGH polarity of SPI*/
			}
			else
			{
				SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK); /*LOG polarity of SPI*/
			}
			break;
		default:
			break;
	}
}
/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
void SPI_frame_size(spi_channel_t channel, uint32_t frame_size)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_FMSZ_MASK); /*Clear the frame size*/
			SPI0->CTAR[SPI_CTAR_0] |= frame_size; /*Define the new frame size*/
			break;
		case SPI_1:
			SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_FMSZ_MASK); /*Clear the frame size*/
			SPI1->CTAR[SPI_CTAR_0] = frame_size; /*Define the new frame size*/
			break;
		case SPI_2:
			SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_FMSZ_MASK); /*Clear the frame size*/
			SPI2->CTAR[SPI_CTAR_0] = frame_size; /*Define the new frame size*/
			break;
		default:
			break;
	}
}
/*It selects the clock phase depending on the value of cpha*/
void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
{
	switch(channel)
	{
		case SPI_0:
			if(cpha)
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK; /*HIGH phase to de SPI*/
			}
			else
			{
				SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK); /*LOW phase to de SPI*/
			}
			break;
		case SPI_1:
			if(cpha)
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK; /*HIGH phase to de SPI*/
			}
			else
			{
				SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK); /*LOW phase to de SPI*/
			}
			break;
		case SPI_2:
			if(cpha)
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK; /*HIGH phase to de SPI*/
			}
			else
			{
				SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK); /*LOW phase to de SPI*/
			}
			break;
		default:
			break;
	}
}
/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
void SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_BR_MASK); /*Clear the Baud Rate*/
			SPI0->CTAR[SPI_CTAR_0] |= baud_rate; /*Define the new Baud rate*/
			break;
		case SPI_1:
			SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_BR_MASK); /*Clear the Baud Rate*/
			SPI1->CTAR[SPI_CTAR_0] |= baud_rate; /*Define the new Baud rate*/
			break;
		case SPI_2:
			SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_BR_MASK); /*Clear the Baud Rate*/
			SPI2->CTAR[SPI_CTAR_0] |= baud_rate; /*Define the new Baud rate*/
			break;
		default:
			break;
	}
}
/*It selects if MSB or LSM bits is first transmitted*/
void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb)
{
	switch(channel)
	{
		case SPI_0:
			if(msb)
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK; /*Selects the LSB bits*/
			}
			else
			{
				SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK); /*Selects the MSB bits*/
			}
			break;
		case SPI_1:
			if(msb)
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK; /*Selects the LSB bits*/
			}
			else
			{
				SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK); /*Selects the MSB bits*/
			}
			break;
		case SPI_2:
			if(msb)
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK; /*Selects the LSB bits*/
			}
			else
			{
				SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK); /*Selects the MSB bits*/
			}
			break;
		default:
			break;
	}
}
/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_start_tranference(spi_channel_t channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= (~SPI_MCR_HALT_MASK); /*Starts the transference */
			break;
		case SPI_1:
			SPI1->MCR &= (~SPI_MCR_HALT_MASK); /*Starts the transference */
			break;
		case SPI_2:
			SPI2->MCR &= (~SPI_MCR_HALT_MASK); /*Starts the transference */
			break;
		default:
			break;
	}
}
/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stop_tranference(spi_channel_t channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR |= SPI_MCR_HALT_MASK; /*Stops the transference */
			break;
		case SPI_1:
			SPI1->MCR |= SPI_MCR_HALT_MASK; /*Stops the transference */
			break;
		case SPI_2:
			SPI2->MCR |= SPI_MCR_HALT_MASK; /*Stops the transference */
			break;
		default:
			break;
	}
}
/*It transmits the information contained in data*/
uint8_t SPI_tranference(spi_channel_t channel, uint8_t data)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->PUSHR = data; /*Transmits the value to the SPI*/
			break;
		case SPI_1:
			SPI1->PUSHR = data; /*Transmits the value to the SPI*/
			break;
		case SPI_2:
			SPI2->PUSHR = data; /*Transmits the value to the SPI*/
			break;
		default:
			return FALSE;
			break;
	}
	delay(0);
	SPI0->SR |= SPI_SR_TCF_MASK; /*Clear the flag for transmtion */
	return TRUE;
}

/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const spi_config_t* config_struct)
{
	GPIO_clock_gating(config_struct->spi_gpio_port.gpio_port_name); /*Starts the clock of GPIO*/

	/*Configure the registers contain in the structure "config_struct"*/
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_clk, &config_struct->pin_config);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_cs, &config_struct->pin_config);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_sin, &config_struct->pin_config);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_sout, &config_struct->pin_config);

	SPI_clk(config_struct->spi_channel); /*Starts clock for the SPI*/
	SPI_enable(config_struct->spi_channel); /*Enable configurations on the SPI*/
	SPI_set_master(config_struct->spi_channel, config_struct->spi_master); /*Configure the SPI as master*/
	SPI_fifo(config_struct->spi_channel, config_struct->spi_enable_fifo); /*Enable the trasmition of datas FIFO*/
	SPI_clock_polarity(config_struct->spi_channel, config_struct->spi_polarity); /*Selects the clock polarity of SPI*/
	SPI_clock_phase(config_struct->spi_channel, config_struct->spi_phase); /*Selects the clock phase of SPI*/
	SPI_baud_rate(config_struct->spi_channel, config_struct->spi_baudrate); /*Selects the Baud rate value */
	SPI_frame_size(config_struct->spi_channel, config_struct->spi_frame_size); /*Selects the Frame Size value */
	SPI_msb_first(config_struct->spi_channel, config_struct->spi_lsb_or_msb); /*Selects MSB bits when is first trasmition*/
}
