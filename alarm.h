#ifndef __ALARM_H__
#define __ALARM_H__

#include "observer.h"
#include "FQueue.h"
#include "time.h"
#include "LinkedList.h"

class  Alarm : public Observer
{
public:
    Alarm(FunctionQueue * _fqueue)
        : fqueue(_fqueue)
    {

    }
    ~ Alarm() {};

    void update(int val)
    {
        if(events.size() == 0) return;

        Timer0::Microseconds rank = events.update_head_rank(val);

        if(rank == 0)
        {
            while (events.update_head_rank(0) == 0)
            {
                Event ev = events.remove_head();
                fqueue->enqueue(ev);
            }
        }
    }

    void schedule(Event event_)
    {
        //cli
        __asm__ ("cli");
        events.insert(event_, event_.time);
        __asm__ ("sei");
        //sei
    }
private:
    LinkedList<Event, true, true, Timer0::Microseconds> events;
    FunctionQueue * fqueue;
};

#endif
