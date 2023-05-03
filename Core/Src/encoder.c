
#include "encoder.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include  "pid.h"
#include  "motorDriver.h"
//#define ENCODER_SAMPLE_FREQ 30.51
//#define ENCODER_SAMPLE_PERIOD 1.0/ENCODER_SAMPLE_FREQ
#define MEGA 1000000.0
#define PERIOD SAMPLE_PERIOD/MEGA
#define FREQ MEGA/SAMPLE_PERIOD
#define GEAR_BOX 1/45.0
#define COUNT_PER_REV 64.0 * GEAR_BOX
void initEncoder(Encoder * enc, TIM_HandleTypeDef * intTIM, TIM_HandleTypeDef * InputTIM,PID_Params pidParams){
	enc->INT_Timer = intTIM;
	enc->encoderInputTimer = InputTIM;
	enc->distance = 0;
	enc->lastCounterValue =0;
	enc->lastMeasurement =0;
	enc->sampleCount =0;
	enc->sampleRate= 10;
	enc->sampleSum =0;
	enc->speedController = pidParams.uPID;
	enc->desiredSpeed = pidParams.Setpoint;
	enc->realSpeed = pidParams.Input;
	enc->motorSpeed = pidParams.Output;
	PID(enc->speedController,enc->realSpeed , enc->motorSpeed, enc->desiredSpeed, pidParams.Kp,pidParams.Ki, pidParams.Kd, pidParams.POn, pidParams.ControllerDirection);
	PID_SetMode(enc->speedController, _PID_MODE_AUTOMATIC);
	PID_SetSampleTime(enc->speedController,500);
	PID_SetOutputLimits(enc->speedController, 0, 90);


}
int getCounter(Encoder * enc){
	return  -1*__HAL_TIM_GET_COUNTER(enc->encoderInputTimer);

}

float getVelocity(Encoder * enc){
	uint32_t current;
// //compare current and last counter
	current = getCounter(enc);
////	// calc difference
	int counterDiff = current - enc->lastCounterValue;
	// transfer to angle
	float angularVelocity  =  (counterDiff * COUNTER_TO_ANGLE) * 1000; // 1kHz

	enc->lastCounterValue = current;
	return angularVelocity;
//	float v;
//	if(current == enc->lastCounterValue){
//		v = 0;
//		enc->lastCounterValue = current;
//		return v;
//	}
//	if(current > enc->lastCounterValue){
//		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(enc->encoderInputTimer)){
//			v =  -enc->lastCounterValue - (__HAL_TIM_GET_AUTORELOAD(enc->encoderInputTimer) - current);
//
//		}else{
//			v = current - enc->lastCounterValue;
//		}
//	}else{
//		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(enc->encoderInputTimer)){
//			v =  current-enc->lastCounterValue;
//
//		}else{
//			v =   current +  (__HAL_TIM_GET_AUTORELOAD(enc->encoderInputTimer) - enc->lastCounterValue);
//
//		}
//	}
//	enc->lastCounterValue = current;

//	float v;
//
//	return v; //

}
float getDistance(Encoder * enc){
	int ticks_per_rev = 32;
	int wheel_radius = 8;
	int current;
 //compare current and last counter
	current = getCounter(enc);
	if(current == enc->lastCounterValue){
		return 0;
	}
	// calc difference
	int counterDiff = current - enc->lastCounterValue;
	// get velocity
//	float angularVelocity = getVelocity(enc);
	// multiply by time const
//	float angle = angularVelocity * 0.001;
	// convert to radians
//	float angleRad = angle * DEG_TO_RAD;
	// multipy by radius of wheel
//	int distance = angleRad * WHEEL_RADIUS; //cm
	float distance = (counterDiff * PI * wheel_radius) / ticks_per_rev;
	enc->lastCounterValue = current;
	return distance;
}
void Encoder_IT_Handler(Encoder * enc){
	__disable_irq();
	int current = getCounter(enc);
	enc->counterValue = current;
	int diff = (current - enc->lastCounterValue);
//	float rps = (diff) / (COUNT_PER_REV);
//	float revCount = rps * PERIOD;
	float revCount = diff / COUNT_PER_REV;
	enc->distance = revCount *2 * PI * WHEEL_RADIUS_CM; //cm
	*enc->realSpeed = enc->distance * FREQ;
	enc->lastCounterValue = current;
//	PID_Compute(enc->speedController);
	__enable_irq();

//	if(enc->sampleCount < enc->sampleRate){
//		enc->sampleSum += getVelocity(enc) *100;
////		enc->sampleSum += getDistance(enc);
//		enc->sampleCount++;
//		return;
//	}
//	 enc->currentSpeed= enc->sampleSum / enc->sampleRate;
//	 enc->sampleSum =0;
//	 enc->sampleCount =0;
}
