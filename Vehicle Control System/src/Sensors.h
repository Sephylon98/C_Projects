/*
 * Sensors.h
 *
 *  Created on: Apr 3, 2022
 *      Author: Midox
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "Vehicle_Logic.h"

typedef struct{


	LogicState engine_state;
	LogicState ac_state;
	LogicState engine_temp_controller_state;
	float32 vehicle_speed;
	uint8 traffic_light_color;
	float32 room_temp;
	float32 engine_temp;

}Sensors;

#endif /* SENSORS_H_ */
