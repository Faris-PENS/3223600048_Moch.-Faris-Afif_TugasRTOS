#include <Arduino.h>

void Button1(void *pvParameters) {
  while (1) {
    if(digitalRead(41) == LOW)
    {
       Serial.println("Button 1 Ditekan");
    }
      
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Button2(void *pvParameters) {
  while (1) {
    if(digitalRead(40) == LOW)
    {
       Serial.println("Button 2 Ditekan");
    }
   
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


void setup() {
  Serial.begin(115200);
 pinMode(41, INPUT_PULLUP);
 pinMode(40, INPUT_PULLUP);

  xTaskCreatePinnedToCore(
    Button1,             // fungsi task
    "Button1",           // nama task
    1024,              // ukuran stack (byte)
    NULL,              // parameter ke task
    1,                 // prioritas task
    NULL,              // handle task (tidak digunakan)
    1                  // core 1 atau 0
  );

    xTaskCreatePinnedToCore(
    Button2,             // fungsi task
    "Button2",           // nama task
    1024,              // ukuran stack (byte)
    NULL,              // parameter ke task
    1,                 // prioritas task
    NULL,              // handle task (tidak digunakan)
    1                  // core 1 atau 0
  );


  

}

void loop() {
  // kosong, semua dijalankan di task RTOS
}
