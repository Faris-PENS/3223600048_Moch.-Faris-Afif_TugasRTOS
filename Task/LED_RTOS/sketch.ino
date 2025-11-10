#include <Arduino.h>

void Task1(void *pvParameters) {
  while (1) {
    digitalWrite(1, HIGH);
    vTaskDelay(1250 / portTICK_PERIOD_MS); 
    digitalWrite(1, LOW);
    vTaskDelay(1250 / portTICK_PERIOD_MS);
  }
}

void Task2(void *pvParameters) {
  while (1) {
    digitalWrite(2, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); 
    digitalWrite(2, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void Task3(void *pvParameters) {
  while (1) {
    digitalWrite(42, HIGH);
    vTaskDelay(1250 / portTICK_PERIOD_MS); 
    digitalWrite(42, LOW);
    vTaskDelay(1250 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
 pinMode(1, OUTPUT);
 pinMode(2, OUTPUT);
 pinMode(42, OUTPUT);

  xTaskCreatePinnedToCore(
    Task1,             // fungsi task
    "Task1",           // nama task
    1024,              // ukuran stack (byte)
    NULL,              // parameter ke task
    1,                 // prioritas task
    NULL,              // handle task (tidak digunakan)
    1                  // core 1 atau 0
  );

  xTaskCreatePinnedToCore(
    Task2,             // fungsi task
    "Task2",           // nama task
    1024,              // ukuran stack (byte)
    NULL,              // parameter ke task
    2,                 // prioritas task
    NULL,              // handle task (tidak digunakan)
    0                  // core 1 atau 0
  );

  xTaskCreatePinnedToCore(
    Task3,             // fungsi task
    "Task3",           // nama task
    1024,              // ukuran stack (byte)
    NULL,              // parameter ke task
    3,                 // prioritas task
    NULL,              // handle task (tidak digunakan)
    1                  // core 1 atau 0
  );
}

void loop() {
  // kosong, semua dijalankan di task RTOS
}
