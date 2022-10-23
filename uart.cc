#include "uart.h"
 
extern "C"
{
   void __vector_18() __attribute__ ((signal));
   void __vector_19() __attribute__ ((signal));
}

void __vector_18()
{
   UART::udre_handler();
}


void __vector_19()
{
   UART::udre_handler();
}
