/*
 * VEHICLE_USER_INTERFACE.c
 *
 *  Created on: Apr 3, 2022
 *      Author: Midox
 */

#include "Vehicle_System.h"

void Vehicle_UserInterface_Init(void){

	/* USER INTERFACE */
	printf("\t\tVEHICLE CONTROL SYSTEM MENU:\n\n");
	printf("Verna S Plus: What would you like to do?\n\n");
	printf(" a.Turn on the vehicle engine\n");
	printf(" b.Turn off the vehicle engine\n");
	printf(" c.Quit the system\n\n");
	/* ------------- */
}

void Vehicle_View_State(uint8 *CMD){

	LogicState Engine; //I was lazy to pass the address of the structure that I made because I created this function earlier, so I didn't want to change it :P

	switch(*CMD){
	case 'a':{
		Engine = ON;
		printf("Current Engine State: %d (ON)\n\n",Engine);
		break;
	}

	case 'b':{
		Engine = OFF;
		printf("Current Engine State: %d (OFF)\n\n",Engine);
		break;
	}

	case 'c':{
		printf("System Shutdown");
		break;
	}
	}
}


void Vehicle_Send_Command(uint8 *CMD,Sensors *Data){

	Vehicle_UserInterface_Init();
	printf("Enter System command: ");
	scanf(" %c",CMD);
	printf("\n");

	switch(*CMD){
	case 'a':{
		Vehicle_View_State(CMD);
		Vehicle_Sensors_Send_Command(CMD ,Data);
		break;
	}

	case 'b':{
		Vehicle_View_State(CMD);
		Vehicle_Send_Command(CMD,Data);
		break;
	}

	case 'c':{
		Vehicle_View_State(CMD);
		printf(".");
		delay(1);
		printf(".");
		delay(1);
		printf(".");
		delay(1);
		printf(" DONE");
		exit(0);
	}

	default:{
		printf("Wrong Entry!, Shutting down Engine\n");
		printf("Current Engine State: 0 (OFF)\n\n");
		Vehicle_Send_Command(CMD,Data);
	}
	}
}



void Vehicle_Sensors_SetMenu_Inteface(void){

	printf("\t\tSENSORS SET MENU:\n\n");
	printf(" a.Turn off the vehicle engine\n");
	printf(" b.Set the traffic light color\n");
	printf(" c.Set the room temperature\n");
	printf(" d.Set the engine temperature\n\n");

}


void Vehicle_Sensors_Send_Command(uint8 *CMD , Sensors *Data){

	//Check Velocity here but don't show values
	if(Data->vehicle_speed == 30){
		Data->ac_state = ON;
		Data->room_temp += (5/4) + 1;
	}

	Vehicle_Sensors_SetMenu_Inteface();
	printf("Enter System command: ");
	scanf(" %c",CMD);
	printf("\n");

	switch(*CMD){
	case 'a':{
		printf("Current Engine State: 0 (OFF)\n\n");
		Vehicle_Send_Command(CMD,Data);
		break;
	}

	case 'b':{
		printf("Enter traffic light color: ");
		scanf(" %c",CMD);
		printf("\n");
		switch(*CMD){
		case 'G':{
			Data->vehicle_speed=100;
			break;
		}

		case 'O':{
			Data->vehicle_speed=30;
			if(Data->vehicle_speed == 30){
				Data->ac_state = ON;
				Data->room_temp += ((5/4) + 1);
				Vehicle_Show_Values(Data);
				Vehicle_Sensors_Send_Command(CMD,Data);
			}
			break;
		}

		case 'R':{
			Data->vehicle_speed=0;
			break;
		}
		default:{
			printf("Wrong Entry! going back to SENSORS SET MENU\n");
			Vehicle_Sensors_Send_Command(CMD,Data);
			break;
		}
		}
		Vehicle_Show_Values(Data);
		Vehicle_Sensors_Send_Command(CMD,Data);
		break;
	}

	case 'c':{
		if(Data->room_temp<10){
			Data->ac_state = ON;
			Data->room_temp = 20;
		}
		else if(Data->room_temp>30){
			Data->ac_state = ON;
			Data->room_temp = 20;
		}
		else{
			Data->ac_state = OFF;
		}
		Vehicle_Show_Values(Data);
		Vehicle_Sensors_Send_Command(CMD,Data);
		break;
	}

	case 'd':{
		if(Data->engine_temp<100){
			Data->engine_temp_controller_state= ON;
			Data->engine_temp = 125;
		}
		else if(Data->engine_temp>150){
			Data->engine_temp_controller_state = ON;
			Data->engine_temp = 125;
		}
		else{
			Data->engine_temp_controller_state = OFF;
		}
		Vehicle_Show_Values(Data);
		Vehicle_Sensors_Send_Command(CMD,Data);
		break;
	}
	default:{
		printf("Wrong Entry!, Turning off Engine\n");
		printf("Current Engine State: 0 (OFF)\n\n");
		Vehicle_Send_Command(CMD,Data);
		break;
	}

	}
}

void Vehicle_Show_Values(Sensors *Data){

	/* ENGINE */
	if(Data->engine_state == 1){
		printf("Engine state: ON\n");
	}
	else{
		printf("Engine state: OFF\n");
	}
	/* ****** */

	/* AC */
	if(Data->ac_state == 1){
		printf("AC state: ON\n");
	}
	else{
		printf("AC state: OFF\n");
	}
	/* ** */

	printf("Vehicle Speed: %f\n",Data->vehicle_speed);

	printf("Room Temperature: %f\n",Data->room_temp);

	/* Engine Temperature Controller */
	if(Data->engine_temp_controller_state == 1){
		printf("Engine Temperature Controller State: ON\n");
	}
	else{
		printf("Engine Temperature Controller State: OFF\n");
	}

	printf("Engine Temperature: %f\n\n",Data->engine_temp);

}
