int direction = 1;
int counter = 0;
int prev_CLK_state;

void ENCODER(void *pvParameters) {
  while (1) {
    int CLK_state = digitalRead(19);

    if (CLK_state != prev_CLK_state && CLK_state == HIGH) {
      if (digitalRead(20) == HIGH) {
        counter--;
        direction = 0;
      } else {
        counter++;
        direction = 1;
      }
      Serial.print("COUNTER: ");
      Serial.println(counter);
    }

    if (digitalRead(21) == LOW) {
      Serial.println("BUTTON DI TEKAN");
    }

    prev_CLK_state = CLK_state;  
    vTaskDelay(1 / portTICK_PERIOD_MS); 
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT_PULLUP);
  prev_CLK_state = digitalRead(19);
  xTaskCreatePinnedToCore(ENCODER, "ENCODER", 2048, NULL, 1, NULL, 0);
}

void loop() {
  // tidak perlu apa-apa, task menangani semuanya
}
