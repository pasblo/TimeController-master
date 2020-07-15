/*
 * AdvancedFPS_Controller: Makes use of all the functionalities
 * that the type fpsController_t can handle.
 *
 * Version 0.1 July, 2020
 * Copyright 2020 Pablo Rivero
 */

#include <TimeController.h>

// Creating the instances of the time controller object and the fps controller variable type
TimeController timeController = TimeController();

fpsController_t controller;

bool ended;

// Function that is executed when the fps are lower than the limit stablished
void errorWithTheFPS(){
  Serial.println("There was a error in the fps");
}

void setup() {
  Serial.begin(115200);

  // Initializing the time controller by passing the fps controller as argument to make possible the controll of fps in a loop
  timeController.initializeFPSController(&controller);

  // Setting the trigger introducing at what controller you want to introduce it, the trigger function and the fps trigger
  fpsController_t_setFpsTrigger(&controller, &errorWithTheFPS, 100);
  ended = false;

}

void loop() {

  // Controlling the fps with the defined fps controller each loop
  timeController.controlFPS(&controller);

  // Writting anything on the serial port creates a dely of 1 second making the fps of the loop drop to 1fps.
  if(Serial.available()){
    Serial.read();
    delay(1000);
  }

  // Printing all the information contained inside the fps controller
  if(millis()%1000 == 0){
    if(!ended){
      Serial.print("FPS: ");
      Serial.print(controller.lastRecordedFPS);
      Serial.print(", Average FPS: ");
      Serial.print(controller.averageFPS);
      Serial.print(", Number of FPS readings: ");
      Serial.print(controller.fpsReadings);
      Serial.print(", Last execution time: ");
      Serial.print(controller.lastExecutionTime);
      Serial.println("us");
    }
    ended = true;
  }else{
    ended = false;
  }

}
