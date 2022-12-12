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
        Timer0::Microseconds rank = events.update_head_rank(val);

        if(rank == 0)
        {
            while (events.update_head_rank(0) == 0)
            {
                Event * ev = events.remove_head();
                //fqueue->enqueue(ev);
                //atualizar release time
                ev->release_time = Timer0::micros();
                fqueue->insert(ev, ev->priority);
                rank = events.update_head_rank(0);
            }
        }
    }

    void schedule(Event * event_)
    {

        Timer0::Microseconds t = event_->time - (Timer0::micros() - event_->release_time );
        //cli
        __asm__ ("cli");
        events.insert(event_, t);
        __asm__ ("sei");
        //sei
    }
private:
    LinkedList<Event *, true, true, Timer0::Microseconds> events;
    FunctionQueue * fqueue;
};

#endif
