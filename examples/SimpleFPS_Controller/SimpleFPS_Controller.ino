/*
 * SimpleFPS_Controller: Prints the fps of the main loop of
 * arduino on screen each second making use of the time
 * controller library
 *
 * Version 0.1 July, 2020
 * Copyright 2020 Pablo Rivero
 */

#include <TimeController.h>

// Creating the instances of the time controller object and the fps controller variable type
TimeController timeController = TimeController();

fpsController_t controller;


// Variable to avoid the repetition of the fps printing each second
bool ended;

void setup() {
  Serial.begin(115200);

  // Initializing the time controller by passing the fps controller as argument to make possible the controll of fps in a loop
  timeController.initializeFPSController(&controller);
  ended = false;

}

void loop() {

  // Controlling the fps with the defined fps controller each loop
  timeController.controlFPS(&controller);

  // Printing the last fps each second
  if(millis()%1000 == 0){
    if(!ended){
      Serial.print("FPS: ");
      Serial.println(controller.lastRecordedFPS);
    }
    ended = true;
  }else{
    ended = false;
  }
}