#ifndef TIMER_H
#define TIMER_H

struct Timer_t
{
    double getTime() const;
private:
    Timer_t()
    {
    }
    Timer_t(const Timer_t & rt); // not implemented
    const Timer_t operator =(const Timer_t & rt); // not implemented
    friend Timer_t & makeTimer();
};

extern Timer_t & Timer;

#endif // TIMER_H
