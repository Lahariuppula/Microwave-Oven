#include <xc.h>
#include "main.h"
extern unsigned char min;
extern unsigned char sec;
extern unsigned char flag;
extern unsigned char preheat_time;
extern volatile unsigned char run_flag;
extern volatile unsigned int sec_count;

void __interrupt() isr(void)
{
    //Timer2
    if(TMR2IF)
    {
        if(run_flag)
        {
            if(++sec_count >= 20000)
            {
                sec_count = 0;
                if(flag == PREHEATING_SCREEN)
                {
                    if(preheat_time > 0)
                    {
                        preheat_time--;
                    }
                }
                else
                {
                    if(sec > 0)
                    {
                        sec--;
                    }
                    else if(min > 0)
                    {
                        min--;
                        sec = 59;
                    }
                }
            }
        }
        TMR2IF = 0;
    }
}
