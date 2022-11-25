#ifndef __FUNCTIONQUEUE_H__
#define __FUNCTIONQUEUE_H__

#include "fifo.h"
#include "timer.h"

struct Event
{
    Timer0::Microseconds time;
    void (*func)(void*);
    void * args;
};

class FunctionQueue : public FIFO<Event, 16>
{
    private:

    public:

        void run()
        {
            Event next;
            //cli
            __asm__ ("cli");
            while ( this->size() > 0)
            {
                this->dequeue(&next);
                //sei
                __asm__ ("sei");
                next.func(next.args);
                //cli
                __asm__ ("cli");
            }
            //sei
            __asm__ ("sei");
        }
};

#endif