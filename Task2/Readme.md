# LANGKAH PERCOBAAN

- RTOS pada ESP32 - S3 sudah bawaan tidak usah download library
- Menggunakan Fungsi xTaskCreatePinnedToCore() Dimana :
  <pre>  xTaskCreatePinnedToCore(
    STEPPER,          // fungsi task
    "STEPPER",        // nama task
    4096,             // ukuran stack
    NULL,             // parameter task
    1,                // prioritas
    NULL,             // handle task
    0                 // core 0
    );  </pre>
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
   Yang berfungsi mengatur delay didalam task tersebut dalam satuan milisecond
 - Mengatur penggunaan Core dan Task yang bergantung pada beban program yang dijalankan
   <pre>
    // Core 0 → beban ringan (OLED, LED, BUZZER)
    xTaskCreatePinnedToCore(OLED, "OLED", 2048, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(LED, "LED", 1024, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(BUZZER, "BUZZER", 1024, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(BUTTON, "BUTTON", 1024, NULL, 2, NULL, 0);

    // Core 1 → kontrol utama
    xTaskCreatePinnedToCore(SERVO, "SERVO", 2048, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(STEPPER, "STEPPER", 2048, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(ENCODER, "ENCODER", 2048, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(POTENTIO, "POTENTIO", 2048, NULL, 1, NULL, 1); </pre>
  Untuk core 0 dan Task priority 2 digunakan untuk program ringan dan tidak membutuhkan realtime (proses tinggi),
  Sedangkan core 1 dan Task priority 1 digunakan untuk program yang berat supaya data yang didapat dan dikeluarkan 
  menghasilkan data realtime (Membutuhkan proses cepat dan CPU tinggi)
  

# VIDEO

https://github.com/user-attachments/assets/89e14517-f711-4505-a90d-d845f6bb1415

# FOTO

<img width="610" height="597" alt="image" src="https://github.com/user-attachments/assets/0a5d63a3-fb1c-47b0-b0e0-03cdc385eb25" />

# LINK PROJECT

https://wokwi.com/projects/447289418009033729
