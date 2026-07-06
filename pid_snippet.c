/**
 * @file pid_snippet.c
 * @brief Differential steering control loop utilizing dual-loop PID error tracking.
 * 
 * NOTE: This is a conceptual snippet demonstrating architecture, math structure, 
 * and sensor integration. Full system tuning constants and routing matrices 
 * are redacted to preserve academic integrity.
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
/* USER CODE END Includes */
// INPUT FROM MAPPING
unsigned int Move_Command = 0;

//PID Constants
float Kp_Vel = 2.0f;
float Ki_Vel = 0.01;
float Kd_Vel = 0.0;

//PID Output
float Motor1_error_integral = 0.0f;
float Motor1_prev_error = 0.0f;
float Motor2_error_integral = 0.0f;
float Motor2_prev_error = 0.0f;
float Motor1_Raw_Drive;
float Motor2_Raw_Drive;

// Distance and Velocity Set Points
signed int Motor1_Distance_Setpoint = 0;
signed int Motor2_Distance_Setpoint = 0; // target distance
float Motor1_Velocity_Setpoint = 0; // target speed (distance PID output)
float Motor2_Velocity_Setpoint = 0;

// MOTOR 1 Distance Proportional Control
float Calculate_Distance_PID_Motor1(int setpoint, int actual) {
	float error = setpoint - actual;
	// Check if target distance is reached
	if (fabs(error) < 20) {
		Motor1_Moving_State = 0; // it arrived
		return 0.0f; // target velocity is 0 so it stop
	} else {
		Motor1_Moving_State = 1; // keep moving
	}
	// Proportional logic for Distance

	float target_velocity = error * Kp_Dist;

	// the maximum speed
	if (target_velocity > (float)SPEED_LIMIT){
		target_velocity = (float)SPEED_LIMIT;
	}

	if (target_velocity < -(float)SPEED_LIMIT){
		target_velocity = -(float)SPEED_LIMIT;
	}
	return target_velocity;
}

// MOTOR 1 Velocity Proportional Integral Control
float Calculate_Velocity_PID_Motor1(float setpoint, float actual) {
	float drive;

	float current_error = setpoint - actual;
	float p_out = current_error * Kp_Vel;
	Motor1_error_integral += current_error;
	if(Motor1_error_integral > 32000) {
		Motor1_error_integral = 32000;
	}
	if(Motor1_error_integral < -32000) {
		Motor1_error_integral = -32000;
	}
	float i_out = Motor1_error_integral * Ki_Vel;
	float d_out = (current_error - Motor1_prev_error) * Kd_Vel;
	Motor1_prev_error = current_error;
	drive = p_out + i_out + d_out;
	return drive;
}
float Kp_Dist = 2.0f;
float Kp_Steer = 0.5f;
