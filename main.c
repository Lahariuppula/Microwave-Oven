/*
 * Soundharya Lahari Uppula
 * 3-6-2026   8:00PM 
*/
#include "main.h"
#pragma config WDTE = OFF

static void init_config(void)
{
    init_clcd();
    init_matrix_keypad();
    init_timer2();
    
    COOLER_DDR = 0;
    BUZZER_DDR = 0;

    COOLER = 0;
    BUZZER = 0;
    
    PEIE = 1;
    GIE = 1;
}
unsigned char key;
volatile unsigned char run_flag = PAUSED;
volatile unsigned int sec_count=0;

unsigned char digit_count = 0;

unsigned char min = 0;
unsigned char sec = 0;

unsigned char min_tens = 0;
unsigned char min_units = 0;
unsigned char sec_tens = 0;
unsigned char sec_units = 0;

unsigned int temp = 0;
unsigned char preheat_time = 60;

unsigned char flag = POWER_ON_SCREEN;
unsigned char reset_flag = RESET_SCREEN;
    
void main(void)
{
    init_config();    
    while(1)
    {
        key = read_matrix_keypad(STATE);
        switch(flag)
        {
            case POWER_ON_SCREEN:               
                power_on_screen();

                flag = MENU_SCREEN;
                reset_flag = RESET_SCREEN;
            break;
            
            case MENU_SCREEN:
                if(reset_flag == RESET_SCREEN)
                {
                    menu_screen();
                    reset_flag = RESET_NOTHING;
                }
                if(key == 1)
                {
                    flag = POWER_DISPLAY_SCREEN;
                    reset_flag = RESET_SCREEN;
                }
                else if(key == 2)
                {
                    flag = SET_TIME_SCREEN;
                    reset_flag = RESET_SCREEN;
                }
                else if(key == 3)
                {
                    flag = TEMPERATURE_SCREEN;
                    reset_flag = RESET_SCREEN;
                }
                else if(key == 4)
                {
                    min=0;
                    sec=30;
                    
                    flag = RUN_MODE_SCREEN;
                    reset_flag = RESET_SCREEN;
                }
            break;
            
            case POWER_DISPLAY_SCREEN:
                power_display_screen();
                __delay_ms(2000);
                flag = SET_TIME_SCREEN;
                reset_flag = RESET_SCREEN;
            break;
            
            case TEMPERATURE_SCREEN:
                if(reset_flag == RESET_SCREEN)
                {
                    clear_screen();
                    temp=0;
                    reset_flag = RESET_NOTHING;
                }
                temperature_screen();
                if(key == '#')
                {
                    preheat_time = 60;
                    flag = PREHEATING_SCREEN;
                    reset_flag = RESET_SCREEN;
                }
            break;
            
            case SET_TIME_SCREEN:
                if(reset_flag == RESET_SCREEN)
                {
                    clear_screen();

                    min_tens = 0;
                    min_units = 0;
                    sec_tens = 0;
                    sec_units = 0;

                    min = 0;
                    sec = 0;
                    
                    digit_count = 0;
                    
                    reset_flag = RESET_NOTHING;
                }
                set_time_screen();
                if(key == '#')
                {
                    min = (min_tens * 10) + min_units;
                    sec = (sec_tens * 10) + sec_units;
        
                    flag = RUN_MODE_SCREEN;
                    reset_flag = RESET_SCREEN;
                }
            break;
            
            case RUN_MODE_SCREEN:
                if(reset_flag == RESET_SCREEN)
                {                 
                    clear_screen();
                    run_flag = RUNNING;
                    COOLER = 1;
                    reset_flag = RESET_NOTHING;
                }
                run_mode_screen();
                if(key == 4)
                {
                    if(run_flag == PAUSED)
                    {
                        run_flag = RUNNING;
                        COOLER = 1;
                    }
                    else
                    {
                        sec += 30;
                        if(sec >= 60)
                        {
                            min++;
                            sec -= 60;
                        }
                    }
                }
                else if(key == 5)
                {
                    run_flag = PAUSED;
                    COOLER = 0;
                }
                else if(key == 6)
                {
                    run_flag = PAUSED;
                    COOLER = 0;

                    flag = MENU_SCREEN;
                    reset_flag = RESET_SCREEN;
                }

                if(min == 0 && sec == 0 && run_flag == RUNNING)
                {
                    COOLER = 0;
                    clear_screen();
                    clcd_print("TIME UP!!", LINE2(4));
                    clcd_print("ENJOY YOUR MEAL", LINE3(0));

                    BUZZER = 1;
                    __delay_ms(2000);
                    BUZZER = 0;

                    flag = MENU_SCREEN;
                    reset_flag = RESET_SCREEN;
                }
            break;
            case PREHEATING_SCREEN:
                if(reset_flag == RESET_SCREEN)
                {
                    clear_screen();
                    run_flag = RUNNING;
                    sec_count = 0;
                    reset_flag = RESET_NOTHING;
                }
                preheating_screen();
                if(preheat_time == 0)
                {
                    run_flag = PAUSED;
                    flag = SET_TIME_SCREEN;
                    reset_flag = RESET_SCREEN;
                }              
            break;
        }
    }
    return;
}