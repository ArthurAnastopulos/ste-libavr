// Arquivo: main.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include <stdio.h>
#include "gpio_pin.h"
#include "uart.h"
#include "adc.h"

ADC adc(ADC::ADC_CH0);

UART uart(UART::UART_9600);

void setup()
{
    __asm__ ("sei");
    uart.puts("setup\n");
}

void busy_wait_delay(int times)
{
    while (times--)
    {
        unsigned long x = 0x7ffff;
        while(x--) __asm__ ("nop");
    }
}

char strbuf[64];

void loop()
{
    sprintf(strbuf, "Average Value from ADC: %d \n", adc.get());
    uart.puts(strbuf);
    busy_wait_delay(2);
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
