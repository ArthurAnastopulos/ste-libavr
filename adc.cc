// Arquivo: adc.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include "adc.h"

ADC::ADC_Registers_t * ADC::regs = (ADC::ADC_Registers_t *) 0x78;

extern "C"
{
   void __vector_21() __attribute__ ((signal));
}


void __vector_18()
{
   ADC::int_handler();
}