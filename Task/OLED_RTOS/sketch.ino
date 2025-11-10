#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void OLED(void *pvParameters) {
  display.clearDisplay();

  while (1) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Moch. Faris Afif");
    display.display();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("3223600048");
    display.display();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void setup() {
   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("GAGAL INISIALISASI");
    
  }
  // core 0
   xTaskCreatePinnedToCore(OLED, "OLED", 2048, NULL, 1, NULL, 0);
  // core 1
  // xTaskCreatePinnedToCore(OLED, "OLED", 2048, NULL, 1, NULL, 1);
  
}

void loop() {

}
