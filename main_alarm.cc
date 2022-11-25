#include "defs.h"
#include "uart.h"
#include "timer.h"
#include "alarm.h"
#include <stdio.h>

UART uart(UART::UART_9600);
char strbuf[32];

FunctionQueue fqueue;
Timer0 timer;
Alarm alarm(&fqueue);

Event evt;

void printMsg(void * arg)
{
    char * msg = (char *) arg;
    uart.puts(msg);
}

const char * MSG = "Oi, tudo bem?\n";

void setup()
{
    uart.puts("setup\n");
    timer.registerObserver(&alarm);
    evt.time = 1000000;
    evt.func = printMsg;
    evt.args = (void*) MSG;
    alarm.schedule(evt);
}

void loop()
{
    fqueue.run();
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}