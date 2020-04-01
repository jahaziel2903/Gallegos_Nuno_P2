
/*
 * PWMrgb.c
 *
 *  Created on: 19 mar. 2020
 *      Author: usuario
 */

#include "SPI.h"
#include "LCD_nokia.h"

/*It configures the SPI for transmission*/
void SPI_init(const spi_config_t* config_struct)
{
	GPIO_clock_gating(config_struct->spi_gpio_port.gpio_port_name); /*Starts the clock of GPIO*/

	/*Configure the pin control registers"*/
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name,
				config_struct->spi_gpio_port.spi_clk, &config_struct->pin_config);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name,
				config_struct->spi_gpio_port.spi_cs, &config_struct->pin_config);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name,
				config_struct->spi_gpio_port.spi_sin, &config_struct->pin_config);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name,
				config_struct->spi_gpio_port.spi_sout, &config_struct->pin_config);
	/*Starts clk**/
	SPI_clk(config_struct->spi_channel);
	/*Enable configuration chanel*/
	SPI_enable(config_struct->spi_channel);
	/*SPI MASTER**/
	SPI_set_master(config_struct->spi_channel, config_struct->spi_master);
	/*Enable the trasmi of data*/
	SPI_fifo(config_struct->spi_channel, config_struct->spi_enable_fifo);
	/*clk POLARITY**/
	SPI_clock_polarity(config_struct->spi_channel, config_struct->spi_polarity);
	/*CLK Phase**/
	SPI_clock_phase(config_struct->spi_channel, config_struct->spi_phase);
	/*Baud Rte**/
	SPI_baud_rate(config_struct->spi_channel, config_struct->spi_baudrate);
	/*Frame size selected**/
	SPI_frame_size(config_struct->spi_channel, config_struct->spi_frame_size);
	/*SPi select MSB**/
	SPI_msb_first(config_struct->spi_channel, config_struct->spi_lsb_or_msb);
}

/*it enable the clock module of the SPI by modifying the MDIS bits*/
void SPI_enable(spi_channel_t channel)
{
	/* Enable with zero*/
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= (~SPI_MCR_MDIS_MASK);
			break;
		case SPI_1:
			SPI1->MCR &= (~SPI_MCR_MDIS_MASK);
			break;
		case SPI_2:
			SPI2->MCR &= (~SPI_MCR_MDIS_MASK);
			break;
		default:
			break;
	}
}

/*It activate the clock for SPI*/
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

/*Configure the SPI as a master or slave*/
void SPI_set_master(spi_channel_t channel, spi_master_t master_or_slave)
{
	/*Depending on master_or_slave
	 * Spi is configure as master or slave**/
	switch(channel)
	{

		case SPI_0:
			if(master_or_slave)
			{
				SPI0->MCR |= SPI_MCR_MSTR_MASK;
			}
			else
			{
				SPI0->MCR &= ~(SPI_MCR_MSTR_MASK);
			}
			break;
		case SPI_1:
			if(master_or_slave)
			{
				SPI1->MCR |= SPI_MCR_MSTR_MASK;
			}
			else
			{
				SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);
			}
			break;
		case SPI_2:
			if(master_or_slave)
			{
				SPI2->MCR |= SPI_MCR_MSTR_MASK;
			}
			else
			{
				SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);
			}
			break;
		default:
			break;
	 }
}

/*It activate the TX and RX FIFOs of the SPI*/
void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
{
	/*First activate TX and the RX*/
	/*Then diactivate the TX and the RX*/
	switch(channel)
	{
		case SPI_0:
			if(enable_or_disable)
			{
				SPI0->MCR &= (~SPI_MCR_DIS_RXF_MASK & ~SPI_MCR_DIS_TXF_MASK);
			}
			else
			{

				SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;
				SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;
			}
			break;
		case SPI_1:
			if(enable_or_disable)
			{
				SPI1->MCR &= (~SPI_MCR_DIS_RXF_MASK & ~SPI_MCR_DIS_TXF_MASK);
			}
			else
			{
				SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;
				SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;
			}
			break;
		case SPI_2:
			if(enable_or_disable)
			{
				SPI2->MCR &= (~SPI_MCR_DIS_RXF_MASK & ~SPI_MCR_DIS_TXF_MASK);
			}
			else
			{
				SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;
				SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;
			}
			break;
		default:
			break;
	}
}

/*Selects the clock polarity*/
 void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
{
	switch(channel)
	{
	/*First if:high polarity**/
	/*Else: low polarity**/
		case SPI_0:
			if(cpol)
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
			}
			else
			{
				SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		case SPI_1:
			if(cpol)
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
			}
			else
			{
				SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		case SPI_2:
			if(cpol)
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
			}
			else
			{
				SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		default:
			break;
	}
}

/*It selects the frame size*/
void SPI_frame_size(spi_channel_t channel, uint32_t frame_size)
{
	switch(channel)
	{
		case SPI_0:
			/*Clear frame size*/
			/*Define new frame size with parameter received*/
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_FMSZ_MASK);

			SPI0->CTAR[SPI_CTAR_0] |= frame_size;
			break;
		case SPI_1:
			SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_FMSZ_MASK);
			SPI1->CTAR[SPI_CTAR_0] = frame_size;
			break;
		case SPI_2:
			SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_FMSZ_MASK);
			SPI2->CTAR[SPI_CTAR_0] = frame_size;
			break;
		default:
			break;
	}
}

/*Selection of clock phase*/
void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
{
	switch(channel)
	{
	 /*HIGH phase to the SPI*/
	/*LOW phase to the SPI*/
		case SPI_0:
			if(cpha)
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK;
			}
			else
			{
				SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK);
			}
			break;
		case SPI_1:
			if(cpha)
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK;
			}
			else
			{
				SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK);
			}
			break;
		case SPI_2:
			if(cpha)
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK;
			}
			else
			{
				SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK);
			}
			break;
		default:
			break;
	}
}

/*Selects the baud rate depending on channel*/
void SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_BR_MASK);
			SPI0->CTAR[SPI_CTAR_0] |= baud_rate;
			break;
		case SPI_1:
			SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_BR_MASK);
			SPI1->CTAR[SPI_CTAR_0] |= baud_rate;
			break;
		case SPI_2:
			SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_BR_MASK);
			SPI2->CTAR[SPI_CTAR_0] |= baud_rate;
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
	/* LSB bits*/
	/* MSB bits*/
		case SPI_0:
			if(msb)
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK;
			}
			else
			{
				SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK);
			}
			break;
		case SPI_1:
			if(msb)
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK;
			}
			else
			{
				SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK);
			}
			break;
		case SPI_2:
			if(msb)
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK;
			}
			else
			{
				SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK);
			}
			break;
		default:
			break;
	}
}

/*It stars the SPI transmission*/
void SPI_start_tranference(spi_channel_t channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= (~SPI_MCR_HALT_MASK); /*Start SPI transference */
			break;
		case SPI_1:
			SPI1->MCR &= (~SPI_MCR_HALT_MASK); /*Start SPI transference */
			break;
		case SPI_2:
			SPI2->MCR &= (~SPI_MCR_HALT_MASK); /*Start SPI transference */
			break;
		default:
			break;
	}
}

/*It stops the SPI transmission*/
void SPI_stop_tranference(spi_channel_t channel)
{
	switch(channel)
	{
	/*SPI Stop*/
		case SPI_0:
			SPI0->MCR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->MCR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_2:
			SPI2->MCR |= SPI_MCR_HALT_MASK;
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
	/*Clear the flag for transmtion */
	SPI0->SR |= SPI_SR_TCF_MASK;
	return TRUE;
}

