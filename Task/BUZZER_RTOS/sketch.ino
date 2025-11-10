#include <Adafruit_GFX.h>


void BUZZER(void *pvParameters) {
  while (1) {
    tone(4, 300);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    noTone(4);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {

  Serial.begin(115200);
  pinMode(4, OUTPUT);
  // core 0
  xTaskCreatePinnedToCore(BUZZER, "BUZZER", 2048, NULL, 1, NULL, 0);
  // core 1
  // xTaskCreatePinnedToCore(BUZZER, "BUZZER", 2048, NULL, 1, NULL, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulatiAWDAon
}
