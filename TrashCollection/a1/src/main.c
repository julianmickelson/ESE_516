#include <samd21g18a.h>
 
#define MAX_RX_BUFFER_LENGTH   5
#define BAUDRATE        115200

volatile uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];
struct usart_module usart_instance;

void usart_read_callback(struct usart_module *const usart_module)
{
	usart_write_buffer_job(&usart_instance,
	(uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
}
void usart_write_callback(struct usart_module *const usart_module)
{
	port_pin_toggle_output_level(LED_0_PIN);
}
	
void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = BAUDRATE;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = PINMUX_UNUSED;
	config_usart.pinmux_pad1 = PINMUX_UNUSED;
	config_usart.pinmux_pad2 = PIN_PA20D_SERCOM3_PAD2 ;
	config_usart.pinmux_pad3 = PIN_PA21D_SERCOM3_PAD3 ;
	while (usart_init(&usart_instance,
	EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}
	usart_enable(&usart_instance);
}
void configure_usart_callbacks(void)
{
	usart_register_callback(&usart_instance,
	usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_instance,
	usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_RECEIVED);
}


int main (void)
{
	//Initializing
	system_init();
	nm_bsp_init();
	delay_init(); //http://asf.atmel.com/docs/3.32.0/samd21/html/group__group__common__services__delay.html
	stdio_serial_init();
	configure_usart();
	configure_usart_callbacks();
	system_interrupt_enable_global();
	
	uint8_t string[] = "Hello World!\r\n";
	usart_write_buffer_wait(&usart_instance, string, sizeof(string));
	/* This skeleton code simply sets the LED to the state of the button. */
	while (true) {
		usart_read_buffer_job(&usart_instance,
		(uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
	}
}
