// Arquivo: main.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include <stdio.h>
#include "gpio_pin.h"
#include "uart.h"
#include "adc.h"

// void int0_isr();
// void int1_isr();

// GPIO_Pin btn0(GPIO_Pin::GPIO_PORTD,
//              GPIO_Pin::GPIO_PIN_2,
//              GPIO_Pin::GPIO_INT_RISING,
//              int0_isr);
// GPIO_Pin btn1(GPIO_Pin::GPIO_PORTD,
//              GPIO_Pin::GPIO_PIN_3,
//              GPIO_Pin::GPIO_INT_RISING,
//              int1_isr);

ADC adc(ADC::ADC_CH0);

UART uart(UART::UART_9600);

// void int0_isr()
// {
//     uart.puts("INT0\n");
// }
// void int1_isr()
// {
//     uart.puts("INT1\n");
// }

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

char * strbuf;

void loop()
{
    //uart.puts("loop\n");
    int avg = 0;
    for (int i = 0; i < 16; i++)
    {
        // sprintf(strbuf, "Valor: %d \n", adc.get(i));
        // uart.puts(strbuf);
        avg = avg + adc.get(i);
        busy_wait_delay(1);
    }

    avg = avg / 16;
    sprintf(strbuf, "Average Value from ADC: %d \n", avg);
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
