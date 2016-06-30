#ifndef STATE_H
#define STATE_H

#include <RTClib.h>

/*
 * A global object holding state and settings.
 */
struct State {
  State();

  // This is called every frame.
  // When 1 second has elapsed, it will update "now" from the RTC.
  void update();

  // Call this everytime you change something in the Settings section.
  void save();

  // The time
  DateTime now;
  bool timeUpdated;       // If the time was updated this frame
  bool timeMinuteUpdated; // Did the minute change this frame
  const __FlashStringHelper* getMonthStr(uint8_t m) const;
  const __FlashStringHelper* getDayStr(uint8_t d) const;

  float temperature;

  // Settings
  bool mode24h;
  bool dim;
  uint8_t current_face;
  uint8_t enabled_faces;
  uint16_t tetris_highscore;

private:
  void readTemperature();
  unsigned long timeLastUpdated;
};

// Import the global object into wherever this is included.
// Its real location is in the .ino file.
extern State state;

#endif
