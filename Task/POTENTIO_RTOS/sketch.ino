

void POTENTIO(void *pvParameters) {
  while (1) {
    int value = analogRead(5);
    Serial.print("Value: ");
    Serial.println(value);
    vTaskDelay(200 / portTICK_PERIOD_MS);  
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // core 0
  xTaskCreatePinnedToCore(POTENTIO, "POTENTIO", 2048, NULL, 1, NULL, 0);
  // core 1
  // xTaskCreatePinnedToCore(POTENTIO, "POTENTIO", 2048, NULL, 1, NULL, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
