/*
    Timer Interrupt Helper Library
    
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    For a full copy of the GNU General Public License, 
    see <http://www.gnu.org/licenses/>.
*/

#ifndef TIMER_H
#define TIMER_H 1

#define RTTY_MASK   0x01
#define DOMINO_MASK 0x02
#define CW_MASK 0x04

#define LEDPORT     PORTE
#define SWITCHPORT  PORTF

#define RTTY_300    0
#define DOMINOEX8   1
#define QRSS        2 

extern volatile int new_mode;

void init_timer();
uint32_t seconds();
uint32_t millis();

#endif