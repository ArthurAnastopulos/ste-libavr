// Arquivo: uart.h
// Autor: Arliones Hoeller, IFSC-SJE

#ifndef __UART_H__
#define __UART_H__

#include "fifo.h"

typedef FIFO< unsigned char, 16> FIFO_Queue;

class UART
{
private:
    struct UART_Registers_t
    {
        unsigned char ucsra;
        unsigned char ucsrb;
        unsigned char ucsrc;
        unsigned char reserved;
        unsigned char ubrrl;
        unsigned char ubrrh;
        unsigned char udr;
    };
    UART_Registers_t * regs;
    
    FIFO_Queue RxFIFO;
    FIFO_Queue TxFIFO;

public:
    enum UART_Baudrate_t
    {
        UART_9600 = 103,
        UART_14400 = 68,
        UART_19200 = 51
    };

    UART(UART_Baudrate_t baud = UART_9600, int db = 8, int pr = 0, int sb = 1)
    {
        regs = (UART_Registers_t*) 0xc0;
        regs->ubrrh = (unsigned char) ((baud >> 8) & 0x0f);
        regs->ubrrl = (unsigned char)  (baud & 0x00ff);
        regs->ucsra = 0;
        regs->ucsrb = (1 << 4) | (1 << 3);
        regs->ucsrc = (3 << 1);
    }

    void put(char c)
    {
        while (! (regs->ucsra & (1 << 5)) ) ;
        //regs->udr = c; 
        TxFIFO.enqueue(c);

        // ligar interrupção UDRE
        regs->ucsrb |= (1 << 5); //(1 << UDRIE0)
    }

    void puts(char *s)
    {
        puts((const char *)s);
    }
    void puts(const char * s)
    {
        while(*s != '\0')
            put(*s++);
    }

    char get()
    {
        //while (! (regs->ucsra & (1 << 7)) ) ;
        // return regs->udr;

        if(RxFIFO.size() > 0){
            unsigned char data;
            RxFIFO.dequeue(data);
            return data;
        }
    }

    void udre_handler()
    {
        if (TxFIFO.size() > 0)
        {
            TxFIFO.dequeue(regs->udr);
        }
        else
        {
            // Desligar interrupção UDRE
            regs->ucsrb &= ~(1 << 5);
        }
    }

    void rxc_handler() 
    {
        while (! (regs->ucsra & (1 << 7)) ) ;
        RxFIFO.enqueue(regs->udr);  
    }
};

#endif