/*
 * TimedFunctions: Introduces the timed functions, which can be 
 * executed with a certain frequency determined by the user, it
 * can also be obtained different parameters like the time of execution,
 * or the last execution time.
 * 
 * Version 0.1 July, 2020
 * Copyright 2020 Pablo Rivero
 */

#include <TimeController.h>

// Creating the instances of the time controller object and the fps controller variable type
TimeController timeController = TimeController();

fpsController_t controller;

// First timed function
void func1(){
  Serial.println("This function is executed in a 2Hz frequency");
}

// Second timed function
void func2(){
  Serial.println("This function is executed in a 4Hz frequency");
}

void setup() {
  Serial.begin(115200);
  timeController.initializeFPSController(&controller);

  // The order of addition matters because when both have to be executed in the same tick of the program,
  // the first added is prioritized. The last boolean parameter, which is optional, determines if when the
  // function is created in the first tick the function should be executed (false, DEFAULT) or if the 
  // function has to wait its correspondant time depending of their frquency to be executed (true).
  timeController.addTimedFunction(&func1, 2.0);
  timeController.addTimedFunction(&func2, 4.0, true);

}

void loop() {

  // Controlling the fps with the defined fps controller each loop, and also controlling the timed functions
  timeController.controlFPS(&controller);
}