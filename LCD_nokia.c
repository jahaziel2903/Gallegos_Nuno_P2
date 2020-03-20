
#include "LCD_nokia.h"


void LCD_nokia_init(void)
{

	gpio_pin_control_register_t lcd_pin_conf = GPIO_MUX1|GPIO_DSE;

	GPIO_clock_gating(GPIO_C);


	GPIO_pin_control_register(GPIO_C, DATA_OR_CMD_PIN, &lcd_pin_conf);
	GPIO_pin_control_register(GPIO_C, RESET_PIN, &lcd_pin_conf);
	GPIO_pin_control_register(GPIO_C, CE, &lcd_pin_conf);


	GPIO_set_pin(GPIO_C, DATA_OR_CMD_PIN);
	GPIO_set_pin(GPIO_C, RESET_PIN);
	GPIO_set_pin(GPIO_C, CE);

	GPIO_data_direction_pin(GPIO_C, GPIO_OUTPUT, DATA_OR_CMD_PIN);
	GPIO_data_direction_pin(GPIO_C, GPIO_OUTPUT, RESET_PIN);
	GPIO_data_direction_pin(GPIO_C, GPIO_OUTPUT, CE);

	GPIO_clear_pin(GPIO_C, RESET_PIN);
	LCD_nokia_delay();
	GPIO_set_pin(GPIO_C, RESET_PIN);

	LCD_nokia_write_byte(LCD_CMD, 0x21);
	LCD_nokia_write_byte(LCD_CMD, 0xBF);
	LCD_nokia_write_byte(LCD_CMD, 0x04);
	LCD_nokia_write_byte(LCD_CMD, 0x14);

	LCD_nokia_write_byte(LCD_CMD, 0x20);
	LCD_nokia_write_byte(LCD_CMD, 0x0C);
}


void LCD_nokia_bitmap(const uint8_t bitmap[]){
	uint16_t index=0;
  for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
	  LCD_nokia_write_byte( LCD_DATA, *(bitmap + index));
}


void LCD_nokia_write_byte(uint8_t data_or_command, uint8_t data)
{

	GPIO_clear_pin(GPIO_C, CE);

	if(data_or_command)
		GPIO_set_pin(GPIO_C, DATA_OR_CMD_PIN);
	else
		GPIO_clear_pin(GPIO_C, DATA_OR_CMD_PIN);


	SPI_start_tranference(SPI_0);
	SPI_tranference(SPI_0, data);
	SPI_stop_tranference(SPI_0);

	GPIO_set_pin(GPIO_C, CE);
}


void LCD_nokia_send_char(uint8_t character) {
  uint16_t index = 0;

  LCD_nokia_write_byte(LCD_DATA, 0x00);

  for (index = 0 ; index < 5 ; index++)
	  LCD_nokia_write_byte(LCD_DATA, ASCII[character - 0x20][index]);


  LCD_nokia_write_byte(LCD_DATA, 0x00);
}


void LCD_nokia_send_string(uint8_t characters []) {
  while (*characters)
	  LCD_nokia_send_char(*characters++);
}


void LCD_nokia_clear(void) {
	uint16_t index = 0;
  for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
	  LCD_nokia_write_byte(LCD_DATA, 0x00);
  LCD_nokia_goto_xy(0, 0);
}


void LCD_nokia_goto_xy(uint8_t x, uint8_t y) {
	LCD_nokia_write_byte(LCD_CMD, 0x80 | x);
	LCD_nokia_write_byte(LCD_CMD, 0x40 | y);
}


void LCD_nokia_delay(void)
{
	int counter;

	for(counter=0; counter<1500; counter++)
	{

	}
}

