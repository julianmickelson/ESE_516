#define USART_SERIAL                 USART0
#define USART_SERIAL_ID              ID_USART0  //USART0 for sam4l
#define USART_SERIAL_BAUDRATE        9600
#define USART_SERIAL_CHAR_LENGTH     US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY          US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT        US_MR_NBSTOP_1_BIT

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <stdlib.h>
#include <conf_board.h>
#include <usart.h>


int main (void)
{
	//initializing
	system_init();
	system_interrupt_enable_global();
	delay_init(); //http://asf.atmel.com/docs/3.32.0/samd21/html/group__group__common__services__delay.html
	
	sysclk_init();
	board_init();
	const sam_usart_opt_t usart_console_settings = {
		USART_SERIAL_BAUDRATE,
		USART_SERIAL_CHAR_LENGTH,
		USART_SERIAL_PARITY,
		USART_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL
	};
	#if SAM4L
	sysclk_enable_peripheral_clock(USART_SERIAL);
	#else
	sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	#endif
	usart_init_rs232(USART_SERIAL, &usart_console_settings,
	sysclk_get_main_hz());
	usart_enable_tx(USART_SERIAL);
	usart_enable_rx(USART_SERIAL);
	
	
	/* This skeleton code simply sets the LED to the state of the button. */
	while (1) {
	}
}
