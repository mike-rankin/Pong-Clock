#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include "State.h"

// Grab RTC instance from .ino
extern RTC_DS1307 RTC;

State::State()
: now(0)
, timeLastUpdated(0)
, timeUpdated(false)
, timeMinuteUpdated(false)
, temperature(0)
, mode24h(false)
, dim(false)
, current_face(0)
, enabled_faces(0xFF)
, tetris_highscore(0)
{
  byte check = EEPROM.read(0);
  // V1
  if (check >= 0x41 && check <= 0x43) {
    byte flags = EEPROM.read(1);
    mode24h = flags & _BV(0);
    dim = flags & _BV(1);
  }
  // V2
  if (check >= 0x42 && check <= 0x43) {
    current_face = EEPROM.read(2);
  }
  // V3
  if (check == 0x43) {
    enabled_faces = EEPROM.read(3);
    tetris_highscore = EEPROM.read(4) | EEPROM.read(5) << 8;
  }
}

void State::save() {
  EEPROM.write(0, 0x43);
  byte flags = 0;
  if (mode24h)
    flags |= _BV(0);
  if (dim)
    flags |= _BV(1);
  EEPROM.write(1, flags);
  EEPROM.write(2, current_face);
  EEPROM.write(3, enabled_faces);
  EEPROM.write(4, tetris_highscore);
  EEPROM.write(5, tetris_highscore >> 8);
}

void State::update() {
  if (millis() - timeLastUpdated > 1000 || timeLastUpdated == 0) {
    uint8_t minute = now.minute();
    now = RTC.now();
    timeLastUpdated = millis();
    timeMinuteUpdated = now.minute() != minute;
    timeUpdated = true;
    readTemperature();
  } else {
    timeMinuteUpdated = false;
    timeUpdated = false;
  }
}

void State::readTemperature() {
  Wire.requestFrom(0x49, 2);

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int sum = ((MSB << 8) | LSB) >> 4;

  temperature = sum * 0.0625f;
}

const __FlashStringHelper* State::getMonthStr(uint8_t m) const {
  switch (m) {
    default:
    case 1: return F("Jan");
    case 2: return F("Feb");
    case 3: return F("Mar");
    case 4: return F("Apr");
    case 5: return F("May");
    case 6: return F("Jun");
    case 7: return F("Jul");
    case 8: return F("Aug");
    case 9: return F("Sep");
    case 10: return F("Oct");
    case 11: return F("Nov");
    case 12: return F("Dec");
  }
}

const __FlashStringHelper* State::getDayStr(uint8_t d) const {
  switch (d) {
    case 1: return F("Mon");
    case 2: return F("Tue");
    case 3: return F("Wed");
    case 4: return F("Thu");
    case 5: return F("Fri");
    case 6: return F("Sat");
    default:
    case 7:
    case 0: return F("Sun");
  }
}

