#include "main.h"
extern unsigned int temp;
extern unsigned char min;
extern unsigned char sec;
extern unsigned char preheat_time;
extern unsigned char digit_count;
extern unsigned char min_tens;
extern unsigned char min_units;
extern unsigned char sec_tens;
extern unsigned char sec_units;

extern unsigned char key;
void power_on_screen(void)
{
    clear_screen();
    unsigned char i;
    for(i = 0; i < 16; i++)
    {
        clcd_putch(0xFF, LINE1(i));
        __delay_ms(100);
    }
    clcd_print("POWERING ON", LINE2(2));
    clcd_print("MICROWAVE OVEN", LINE3(1));
    for(i = 0; i < 16; i++)
    {
        clcd_putch(0xFF, LINE4(i));
        __delay_ms(100);
    }
}

void menu_screen(void)
{
    clear_screen();
    clcd_print("1.MICRO", LINE1(0));
    clcd_print("2.GRILL", LINE2(0));
    clcd_print("3.CONVECTION", LINE3(0));
    clcd_print("4.START", LINE4(0));
}

void power_display_screen(void)
{
    clear_screen();
    clcd_print("Power = 900W", LINE2(2));
}

void temperature_screen(void)
{
    if(key <= 9)
    {
        temp = (temp * 10) + key;

        if(temp > 180)
        {
            temp = 180;
        }
    }
    else if(key == '*')
    {
        temp = 0;
    }
    clcd_print("SET TEMP  < C>",LINE1(0));
    clcd_putch(0xDF,LINE1(11));
    clcd_print("TEMP = ",LINE2(0));
    clcd_putch(((temp / 100) % 10) + '0', LINE2(7));
    clcd_putch(((temp / 10) % 10) + '0', LINE2(8));
    clcd_putch((temp % 10) + '0', LINE2(9));
    clcd_print("*CLEAR   #ENTER",LINE4(0));
}

void set_time_screen(void)
{
    static unsigned int  blink_count = 0;
    static unsigned char blink_flag = 0;
      
    if(key <= 9)
    {
        switch(digit_count)
        {
            case 0:
                sec_units = key;
            break;

            case 1:
                sec_tens = sec_units;
                sec_units = key;
            break;

            case 2:
                min_units = key;
            break;

            case 3:
                min_tens = min_units;
                min_units = key;
            break;
        }
        if(digit_count < 4)
        {
            digit_count++;
        }
    }
    else if(key == '*')
    {
        min_tens = 0;
        min_units = 0;
        sec_tens = 0;
        sec_units = 0;
        
        digit_count = 0;
    }
    if(++blink_count >= 5)
    {
        blink_count = 0;
        blink_flag = !blink_flag;
    }
    
    clcd_print("SET TIME <MM:SS>", LINE1(0));
    clcd_print("TIME    ", LINE2(0));  
    clcd_print("*CLEAR   #ENTER", LINE4(0));
    clcd_putch(':', LINE2(11));
    
    if(digit_count < 3)
    {
        clcd_putch(min_tens + '0', LINE2(9));
        clcd_putch(min_units + '0', LINE2(10));

        if(blink_flag)
        {
            clcd_putch(' ', LINE2(12));
            clcd_putch(' ', LINE2(13));
        }
        else
        {
            clcd_putch(sec_tens + '0', LINE2(12));
            clcd_putch(sec_units + '0', LINE2(13));
        }
    }
    else
    {
        clcd_putch(sec_tens + '0', LINE2(12));
        clcd_putch(sec_units + '0', LINE2(13));

        if(blink_flag)
        {
            clcd_putch(' ', LINE2(9));
            clcd_putch(' ', LINE2(10));
        }
        else
        {
            clcd_putch(min_tens + '0', LINE2(9));
            clcd_putch(min_units + '0', LINE2(10));
        }
    }  
}

void run_mode_screen(void)
{
    char time[6];
    time[0] = (min / 10) + '0';
    time[1] = (min % 10) + '0';
    time[2] = ':';
    time[3] = (sec / 10) + '0';
    time[4] = (sec % 10) + '0';
    time[5] = '\0';
    
    clcd_print("TIME = ",LINE1(0));
    clcd_print(time, LINE1(8));
    clcd_print("4.START/RESUME",LINE2(0));
    clcd_print("5.PAUSE",LINE3(0));
    clcd_print("6.STOP",LINE4(0));
}

void preheating_screen(void)
{
    clcd_print("PRE-HEATING", LINE1(2));
    clcd_print("TIME LEFT:", LINE2(0));
    clcd_putch((preheat_time / 100) + '0', LINE2(11));
    clcd_putch(((preheat_time / 10) % 10) + '0', LINE2(12));
    clcd_putch((preheat_time % 10) + '0', LINE2(13));
    clcd_putch('s', LINE2(14));
}

void clear_screen(void)
{
    clcd_write(CLEAR_DISP_SCREEN,INST_MODE);
    __delay_ms(2);
}