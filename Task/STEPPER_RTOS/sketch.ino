#include "AccelStepper.h"
#define dirPin 47
#define stepPin 48
#define motorInterfaceType 1
AccelStepper stepper(motorInterfaceType, stepPin, dirPin);
int speed = 500;

void STEPPER(void *pvParameters) {

  while (1) {
   
   stepper.setSpeed(speed);
   vTaskDelay(1000 / portTICK_PERIOD_MS);
   stepper.setSpeed(-speed);
   vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}

void setup() {
  Serial.begin(115200);
  stepper.setMaxSpeed(speed);
  xTaskCreatePinnedToCore(STEPPER, "STEPPER", 2048, NULL, 1, NULL, 0);
}

void loop() {
  stepper.runSpeed();
}
