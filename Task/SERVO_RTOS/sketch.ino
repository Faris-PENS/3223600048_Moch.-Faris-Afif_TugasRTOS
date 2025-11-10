#include <ESP32Servo.h>

Servo servo;

void SERVO(void *pvParameters) {
  
  while (1) {
    servo.write(0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    servo.write(180);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  servo.setPeriodHertz(50);
  servo.attach(14, 500, 2400);
  Serial.begin(115200);
  xTaskCreatePinnedToCore(SERVO, "SERVO", 2048, NULL, 1, NULL, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
