#include <xc.h>
#include "timers.h"

//Timer2
void init_timer2(void)
{
    PR2 = 250;
    TMR2IE = 1;
    TMR2ON = 1;
    T2CKPS0 = 0;
    T2CKPS1 = 0;
}