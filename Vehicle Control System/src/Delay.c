/*
 * delay.c
 *
 *  Created on: Apr 3, 2022
 *      Author: Midox
 */


#include "Delay.h"

void delay(uint32 number_of_seconds)
{
    // Converting time into milli_seconds
    uint32 milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
