/*
 * VEHICLE_USER_INTERFACE.h
 *
 *  Created on: Apr 3, 2022
 *      Author: Midox
 */

#ifndef VEHICLE_SYSTEM_H_
#define VEHICLE_SYSTEM_H_

#include <stdio.h>
#include <stdlib.h>

#include "Delay.h"
#include "STD_Types.h"
#include "Sensors.h"
#include "Vehicle_Logic.h"



void Vehicle_UserInterface_Init(void);
void Vehicle_View_State(uint8 *CMD);
void Vehicle_Send_Command(uint8 *CMD , Sensors *Data);
void Vehicle_Sensors_SetMenu_Inteface(void);
void delay(uint32 number_of_seconds);
void Vehicle_Sensors_Send_Command(uint8 *CMD , Sensors *Data);
void Vehicle_Show_Values(Sensors *Data);

#endif /* VEHICLE_SYSTEM_H_ */
