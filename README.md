# Langkah Percobaan
- RTOS pada ESP32 - S3 sudah bawaan tidak usah download library
- Menggunakan Fungsi xTaskCreatePinnedToCore() Dimana :
  <pre>  ```xTaskCreatePinnedToCore(
    STEPPER,          // fungsi task
    "STEPPER",        // nama task
    4096,             // ukuran stack
    NULL,             // parameter task
    1,                // prioritas
    NULL,             // handle task
    0                 // core 0
    );```  </pre>
- Kemudian membuat nama fungsi sesuai yang diisi pada langkah sebelumnya contoh:
  <pre>void STEPPER(void *pvParameters) {

  while (1) {
   stepper.setSpeed(speed);
   vTaskDelay(1000 / portTICK_PERIOD_MS);
   stepper.setSpeed(-speed);
   vTaskDelay(1000 / portTICK_PERIOD_MS); 
   }
  } </pre>
- Terdapat Syntax :
  <pre>
   vTaskDelay(1000 / portTICK_PERIOD_MS); </pre>
   Yang berfungsi mengatur delay didalam task tersebut




  ### UNTUK GAMBAR, CODE DAN VIDEO TERDAPAT PADA MASING-MASING FOLDER
