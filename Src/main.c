#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define RCC 0x40023800
#define GPIOA 0x40020000

void delay();

int main(void)
{
	volatile uint32_t* rcc_clock_enable_register = (uint32_t*)(RCC + 0x30);
	*rcc_clock_enable_register |= 0x1;

	volatile uint32_t* gpioa_port_mode_register = (uint32_t*)(GPIOA);
	*gpioa_port_mode_register &= ~(3 << 10);
	*gpioa_port_mode_register |= (1 << 10);

	volatile uint32_t* gpioa_port_output_data_register = (uint32_t*)(GPIOA + 0x14);

	for(;;)
	{
		*gpioa_port_output_data_register |= (1 << 5);
		delay();
		*gpioa_port_output_data_register &= ~(1 << 5);
		delay();
	}
}

void delay()
{
	for(volatile uint32_t timer = 0; timer < 100000; ++timer);
}
