#include "TimeController.h"
#include <Arduino.h>

void fpsController_t_setFpsTrigger(fpsController_t *controller, functionCall_t function, uint32_t fpsTrigger){
	controller->fpsErrorTrigger = fpsTrigger;
	controller->triggerCall = function;
}

void TimeController::initializeFPSController(fpsController_t *controller){

	controller->lastMicros = micros();

	controller->lastRecordedFPS = 0.0;
	controller->averageFPS = 0.0;
	controller->fpsReadings = 0;
	controller->lastExecutionTime = 0;

	controller->fpsErrorTrigger = 0;
	controller->triggerCall = NULL;
}

void TimeController::controlFPS(fpsController_t *controller){

	// Calculating the fps of this execution
	uint64_t newMicros = micros();
	uint64_t microsDifference = newMicros - controller->lastMicros;
	controller->lastMicros = newMicros;
	controller->lastRecordedFPS = (1000000.0/microsDifference);

	// Calculating the average fps of all the readings
	controller->averageFPS = (controller->averageFPS*controller->fpsReadings) + controller->lastRecordedFPS;
	controller->fpsReadings++;
	controller->averageFPS = controller->averageFPS/controller->fpsReadings;

	// Determining if each timed function needs to be executed on this loop
	for(unsigned int i = 0; i < timedFunctions.size(); i++){
		if(micros() - timedFunctions.at(i).lastCall >= 1000000.0/timedFunctions.at(i).frequency){
			uint64_t initExecutionTime = micros();
			timedFunctions.at(i).function();
			timedFunctions.at(i).lastExecutionTime = micros() - initExecutionTime;
			timedFunctions.at(i).lastCall = initExecutionTime;
		}
	}

	// Checking if the fpsTrigger is activated
	if(controller->lastRecordedFPS < controller->fpsErrorTrigger){
		controller->triggerCall();
	}
	controller->lastExecutionTime = micros() - newMicros;
}

void TimeController::addTimedFunction(functionCall_t function, double callFreq, bool freqFirstCall){
	timedFunction_t newTimerFunction;
	newTimerFunction.function = *function;
	newTimerFunction.frequency = callFreq;

	// Determining if the first call is going to be after the period stablished by the frequency or in the first call to controlFPS
	if(freqFirstCall){
		newTimerFunction.lastCall = micros(); // After the period stablished
	}else{
		newTimerFunction.lastCall = 0; // Immediately
	}
	newTimerFunction.lastExecutionTime = 0;
	timedFunctionsBegin = timedFunctions.insert(timedFunctionsBegin, newTimerFunction);
}

void TimeController::addTimedFunction(functionCall_t function, double callFreq){
	addTimedFunction(function, callFreq, false);
}