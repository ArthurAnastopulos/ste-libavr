// Arquivo: main.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include "defs.h"
#include <stdio.h>
#include "gpio_pin.h"
#include "uart.h"
#include "timer.h"
#include "FQueue.h"
#include "LinkedList.h"

UART uart(UART::UART_9600);
Timer0 timer;
FunctionQueue fqueue;

LinkedList<int, true, true, int> list;

void printMsg(void * arg)
{
    char * msg = (char *) arg;
    uart.puts(msg);
}

const char * MSG = "Oi, tudo bem?";

void setup()
{
    __asm__ ("sei");
    uart.puts("setup\n");
    list.insert(0, 5);
    timer.delay(1000000);
    list.insert(1, 3);
    timer.delay(1000000);
    list.insert(2, 4);
    timer.delay(1000000);
    list.insert(3, 1);
    timer.delay(1000000);
    // Event evt;
    // evt.time = 0;
    // evt.func = printMsg;
    // evt.args = (void*) MSG;
    // fqueue.enqueue(evt);
}

char strbuf[16];

void loop()
{
    while (list.size() > 0)
    {
        sprintf(strbuf, "Dequeued: %d\n", list.remove_head());
        uart.puts(strbuf); // 3 1 2 0
        timer.delay(1000000);
    }
    
    //uart.puts("loop\n");
}

int main()
{
    setup();
    while (true)
    {
       loop();
    }
}
