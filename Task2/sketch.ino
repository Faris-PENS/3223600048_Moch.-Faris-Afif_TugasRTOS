#include <Adafruit_GFX.h>
#include "AccelStepper.h"
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define dirPin 47
#define stepPin 48
#define motorInterfaceType 1

unsigned long previousMillis = 0;
int direction = 1;
int counter = 0;
int prev_CLK_state;
int speed = 500;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
AccelStepper stepper(motorInterfaceType, stepPin, dirPin);
Servo servo;

// ---------------- SERVO ----------------
void SERVO(void *pvParameters) {
  while (1) {
    servo.write(0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    servo.write(180);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void OLED(void *pvParameters) {
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

void STEPPER(void *pvParameters) {
  while (1) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis > 2000) {
      previousMillis = currentMillis;
    }

    if (currentMillis - previousMillis <= 1000) {
      stepper.setSpeed(speed);
    } else if (currentMillis - previousMillis <= 2000) {
      stepper.setSpeed(-speed);
    }

    stepper.runSpeed();
    vTaskDelay(1);  // biar tidak makan CPU penuh
  }
}

void BUTTON(void *pvParameters) {
  while (1) {
    if (digitalRead(41) == LOW) {
      Serial.println("Button 1 Ditekan");
    }

    if (digitalRead(40) == LOW) {
      Serial.println("Button 2 Ditekan");
    }

    vTaskDelay(400 / portTICK_PERIOD_MS);
  }
}

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
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void LED(void *pvParameters) {
  while (1) {
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(42, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(42, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void POTENTIO(void *pvParameters) {
  while (1) {
    int value = analogRead(5);
    Serial.print("Value: ");
    Serial.println(value);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void BUZZER(void *pvParameters) {

  while (1) {
    unsigned long start = millis();
    while (millis() - start < 1000) {  
      digitalWrite(4, HIGH);
      delayMicroseconds(2000);
      digitalWrite(4, LOW);
      delayMicroseconds(2000);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}


void setup() {
  Serial.begin(115200);

  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  prev_CLK_state = digitalRead(19);
  stepper.setMaxSpeed(speed);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("GAGAL INISIALISASI OLED");
  }

  servo.setPeriodHertz(50);
  servo.attach(13, 500, 2400);

  // Core 0 → beban ringan (OLED, LED, BUZZER)
  xTaskCreatePinnedToCore(OLED, "OLED", 2048, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(LED, "LED", 1024, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(BUZZER, "BUZZER", 1024, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(BUTTON, "BUTTON", 1024, NULL, 2, NULL, 0);

  // Core 1 → kontrol utama
  xTaskCreatePinnedToCore(SERVO, "SERVO", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(STEPPER, "STEPPER", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(ENCODER, "ENCODER", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(POTENTIO, "POTENTIO", 2048, NULL, 1, NULL, 1);
}

void loop() {
  vTaskDelay(10);
}
