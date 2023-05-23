#ifndef DHT11_ESP32_H
#define DHT11_ESP32_H

#include <Arduino.h>

class DHT11_ESP32 {
  public:
    DHT11_ESP32(uint8_t pin) : _pin(pin) {}

    float getTEMP() {
      int data[5];
      for (int i = 0; i < 5; i++) {
        data[i] = 0;
      }

      pinMode(_pin, OUTPUT);
      digitalWrite(_pin, LOW);
      delay(18);
      digitalWrite(_pin, HIGH);
      delayMicroseconds(30);
      pinMode(_pin, INPUT_PULLUP);

      int timeout = 10000;
      while (digitalRead(_pin) == LOW) {
        if (--timeout == 0) return NAN;
      }

      timeout = 10000;
      while (digitalRead(_pin) == HIGH) {
        if (--timeout == 0) return NAN;
      }

      for (int i = 0; i < 40; i++) {
        timeout = 10000;
        while (digitalRead(_pin) == LOW) {
          if (--timeout == 0) return NAN;
        }

        unsigned long start_time = micros();

        timeout = 10000;
        while (digitalRead(_pin) == HIGH) {
          if (--timeout == 0) return NAN;
        }

        unsigned long end_time = micros();

        data[i / 8] <<= 1;
        if (end_time - start_time > 40) {
          data[i / 8] |= 1;
        }
      }

      if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        float temperature_c = (float)data[2];
        return temperature_c;
      } else {
        return NAN;
      }
    }

    float getHUM() {
      int data[5];
      for (int i = 0; i < 5; i++) {
        data[i] = 0;
      }

      pinMode(_pin, OUTPUT);
      digitalWrite(_pin, LOW);
      delay(18);
      digitalWrite(_pin, HIGH);
      delayMicroseconds(30);
      pinMode(_pin, INPUT_PULLUP);

      int timeout = 10000;
      while (digitalRead(_pin) == LOW) {
        if (--timeout == 0) return NAN;
      }

      timeout = 10000;
      while (digitalRead(_pin) == HIGH) {
        if (--timeout == 0) return NAN;
      }

      for (int i = 0; i < 40; i++) {
        timeout = 10000;
        while (digitalRead(_pin) == LOW) {
          if (--timeout == 0) return NAN;
        }

        unsigned long start_time = micros();

        timeout = 10000;
        while (digitalRead(_pin) == HIGH) {
          if (--timeout == 0) return NAN;
        }

        unsigned long end_time = micros();

        data[i / 8] <<= 1;
        if (end_time - start_time > 40) {
          data[i / 8] |= 1;
        }
      }

        if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
    float humidity = (float)data[0];
    return humidity;
  } else {
    return NAN;
  }
}
private:
uint8_t _pin;
};

#endif
