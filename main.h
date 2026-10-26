/* 
 * File:   main.h
 * Author: Soundharya Lahari
 *
 * Created on 3 June, 2026, 7:41 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "microwave.h"
#include "timers.h"

#define POWER_ON_SCREEN         0x01
#define MENU_SCREEN             0x02
#define POWER_DISPLAY_SCREEN    0x03
#define SET_TIME_SCREEN         0x04
#define TEMPERATURE_SCREEN      0x05
#define RUN_MODE_SCREEN         0x06
#define PREHEATING_SCREEN       0x07

#define MICRO_MODE              0x11
#define GRILL_MODE              0x12
#define CONVECTION_MODE         0x13
#define START_MODE              0x14

#define RESET_NOTHING           0x00
#define RESET_SCREEN            0xFF
#define DISPLAY_TIME            0xDD

#define START                   0xAA
#define STOP                    0xBB
#define PAUSE                   0xCC
#define PRE_HEAT                0xDD

#define COOLER_DDR              TRISC2
#define COOLER                  RC2

#define BUZZER_DDR              TRISC1
#define BUZZER                  RC1

#define RUNNING                 1
#define PAUSED                  0

#endif	/* MAIN_H */

