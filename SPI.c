/*
 * SPI.c
 *
 *  Created on: 19 mar. 2020
 *      Author: usuario
 */

#include "SPI.h"


 void SPI_enable(spi_channel_t channel)
 {
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

	 }
 }


 void SPI_set_master(spi_channel_t channel, spi_master_t master_or_slave)
 {
	 switch(channel)
	 {

	 	case SPI_0:
	 		SPI0->MCR |= SPI_MCR_MSTR(master_or_slave);
	 		break;

	 	case SPI_1:
	 		SPI1->MCR |= SPI_MCR_MSTR(master_or_slave);
	 		break;

	 	case SPI_2:
	 	 	SPI2->MCR |= SPI_MCR_MSTR(master_or_slave);
	 	 	break;

	 }
 }


 void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
 {
	 switch(channel)
	 {

	 	case SPI_0:
	 		SPI0->MCR |= SPI_MCR_DIS_RXF(enable_or_disable);
	 		SPI0->MCR |= SPI_MCR_DIS_TXF(enable_or_disable);
	 	 	break;

	 	case SPI_1:
	 		SPI1->MCR |= SPI_MCR_DIS_RXF(enable_or_disable);
	 		SPI1->MCR |= SPI_MCR_DIS_TXF(enable_or_disable);
	 	 	break;

	 	case SPI_2:
	 		SPI2->MCR |= SPI_MCR_DIS_RXF(enable_or_disable);
	 		SPI2->MCR |= SPI_MCR_DIS_TXF(enable_or_disable);
	 	 	break;

	 }
 }

 void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
 {
	 switch(channel)
	 {

	 	case SPI_0:
	 	 	SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL(cpol);
	 	 	break;

	 	case SPI_1:
	 		SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL(cpol);
	 	 	break;

	 	case SPI_2:
	 		SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL(cpol);
	 	 	break;

	 }
 }


 void SPI_frame_size(spi_channel_t channel, uint32_t frame_size)
 {
	 switch(channel)
	 {

	 	case SPI_0:
	 	 	SPI0->CTAR[SPI_CTAR_0] = frame_size;
	 	 	break;

	 	case SPI_1:
	 	 	SPI1->CTAR[SPI_CTAR_0] = frame_size;
	 	 	break;

	 	 case SPI_2:
	 	 	SPI2->CTAR[SPI_CTAR_0] = frame_size;
	 	 	break;

	 }
 }


 void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
 {
	 switch(channel)
	 {

	 	case SPI_0:
	 	 	SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA(cpha);
	 	 	break;

	 	case SPI_1:
	 	 	SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA(cpha);
	 	 	break;

	 	 case SPI_2:
	 	 	SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA(cpha);
	 	 	break;

	 }
 }


 void SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate)
 {
	 switch(channel)
	 {

	 	 case SPI_0:
	 	 	SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_BR(baud_rate);
	 	 	break;

	 	 case SPI_1:
	 	 	SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_BR(baud_rate);
	 	 	break;

	 	 case SPI_2:
	 	 	SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_BR(baud_rate);
	 	 	break;

	 }
 }


 void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb)
 {
	 switch(channel)
	 {

	 	 case SPI_0:
	 	 	SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE(msb);
	 	 	break;

	 	 case SPI_1:
	 	 	SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE(msb);
	 	 	break;

	 	 case SPI_2:
	 	 	SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE(msb);
	 	 	break;

	 }
 }


void SPI_start_tranference(spi_channel_t channel)
{
	switch(channel)
	{
	case SPI_0:
			SPI0->MCR &= (~SPI_MCR_HALT_MASK);
			break;
		case SPI_1:
			SPI1->MCR &= (~SPI_MCR_HALT_MASK);
			break;
		case SPI_2:
			SPI2->MCR &= (~SPI_MCR_HALT_MASK);
			break;
		default:
			break;

	}
}

void SPI_stop_tranference(spi_channel_t channel)
{
	switch(channel)
	{
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


uint8_t SPI_tranference(spi_channel_t channel, uint8_t data)
{
	uint8_t received_data = 0;
	/* SPI0->MCR &= ~SPI_MCR_HALT_MASK */
	SPI0->PUSHR = (data) | SPI_PUSHR_EOQ_MASK;
	while((SPI0->SR & SPI_SR_TCF_MASK) == 0);
	SPI0->SR |= SPI_SR_TCF_MASK;
	received_data = SPI0->POPR & 0xff;
	/* SPI0->MCR |= SPI_MCR_HALT_MASK;*/
	return (received_data);
}


void SPI_init(const spi_config_t* config_struct)
{
	SPI_clk(config_struct->spi_channel);
	GPIO_clock_gating(config_struct->spi_gpio_port.gpio_port_name);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_clk, &(config_struct->pin_config));
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_sout, &(config_struct->pin_config));
	SPI_frame_size(config_struct->spi_channel, config_struct->spi_frame_size);
	SPI_set_master(config_struct->spi_channel, config_struct->spi_master);
	SPI_fifo(config_struct->spi_channel, config_struct->spi_enable_fifo);
	SPI_enable(config_struct->spi_channel);
	SPI_clock_polarity(config_struct->spi_channel, config_struct->spi_polarity);
	SPI_clock_phase(config_struct->spi_channel, config_struct->spi_phase);
	SPI_baud_rate(config_struct->spi_channel, config_struct->spi_baudrate);
	SPI_msb_first(config_struct->spi_channel, config_struct->spi_lsb_or_msb);

}
