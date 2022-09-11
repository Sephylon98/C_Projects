/*
 ============================================================================
 Name        : Mohamed_Ashraf_Mini_Project1.c
 Author      : Mohamed Shebl
 Version     :
 Copyright   :
 Description : C Mini Project 1
 ============================================================================
 */

#include "Vehicle_System.h"

#define DisableBuffer setvbuf(stdout, NULL, _IONBF, 0)

uint8 UsrCmd;
Sensors UserData = {1,1,1,30,'R',10,125}; //Enter Custom Data here

int main(void) {
	DisableBuffer;
	/* Initialization*/
	//Vehicle_UserInterface_Init();
	Vehicle_Send_Command(&UsrCmd,&UserData);
	return EXIT_SUCCESS;
}
