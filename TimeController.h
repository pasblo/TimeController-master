#ifndef TIME_CONTROLLER
#define TIME_CONTROLLER

#include "Arduino.h"
#include <vector>

// Namespace used to cast the function that is going to be passed as parameter to the addTimedFunction method
namespace timeController_n {

	// Type used to pass functions as parameters, with the constrint of not having either parameters or returned values
	using functionCall_t = void (*)();
}

using namespace timeController_n;

// Struct for each fps controller
typedef struct {

	// Calculating the FPS
	uint64_t lastMicros; // The time in microseconds of the last time the fps were calculated

	// FPS readings
	double lastRecordedFPS; // The fps calculated in the last call of the function controlFPS
	double averageFPS; // The average fps calculated by the fps controller since the initalization of the fps controller
	uint32_t fpsReadings; // The number of readings of fps since the initialization of the fps controller
	uint32_t lastExecutionTime; // The time that took to execute the controlFPS function

	// Trigger that calls a function when the fps are below a stablished limit
	uint32_t fpsErrorTrigger; // If the lastRecordedFPS are LOWER than the fpsErrorTrigger, the program will call the trigger call, but it will continue working
	functionCall_t triggerCall; // The function that the program is going to call if the tigger is triggered

} fpsController_t;

// Function to modify the variables related to the fps trigger in a fps controller
void fpsController_t_setFpsTrigger(fpsController_t *controller, functionCall_t function, uint32_t fpsTrigger);

// Struct for each timed function
typedef struct {

	functionCall_t function; // Function to be called every period
	double frequency; // Times to call the function per second
	uint64_t lastCall; // The time in microseconds when the last call to the function was performed
	uint32_t lastExecutionTime; // The time that took to execute the function the last time executed

} timedFunction_t;

// Class to controll the fps of different loops, you can also add functions with different calling frequencies
class TimeController{
	public:

		// FPS controller
		void initializeFPSController(fpsController_t *controller); // Sets the variables of the controller to default
		void controlFPS(fpsController_t *controller); // Method to call every loop in the loop to measure

		// Timed functions
		void addTimedFunction(functionCall_t function, double callFreq, bool freqFirstCall);
		void addTimedFunction(functionCall_t function, double callFreq);

	protected:
	private:

		// Timed functions
		std::vector<timedFunction_t> timedFunctions;
		std::vector<timedFunction_t>::iterator timedFunctionsBegin;
};
#endif