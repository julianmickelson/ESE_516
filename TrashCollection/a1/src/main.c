//HEADERS//
#include <samd21g18a.h>
#include <asf.h>

//DEFINES//
#define MAX_RX_BUFFER_LENGTH	100
#define BAUDRATE				115200

//Global Variable//
struct usart_module usart_instance;
volatile uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];
uint8_t test[] = "Test!\r\n";

void usart_read_callback(struct usart_module *const usart_module)
{
	//usart_write_buffer_job(&usart_instance,
	//(uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
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
    config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
    config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
    config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
    config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
	
	//while (usart_init(&usart_instance,
	//EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	//}
	//usart_enable(&usart_instance);
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
	board_init();

	configure_usart();
	configure_usart_callbacks();
	
    system_interrupt_enable_global();
    uint8_t string[] = "Hello World!\r\n";
    usart_write_buffer_wait(&usart_instance, string, sizeof(string));
	
	printf("Test");
	
    while (true) {
	    usart_read_buffer_job(&usart_instance,
	    (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
    }
}