/*
 * Pongclock Code for 0miker0's Pong Clock.
 * Code by mic159.
 *
 * FOR HARDWARE REVISION 2.3!
 * Earlier revisions should use 2.2 branch.
 *
 * Requirements:
 * Adafruit GFX https://github.com/adafruit/Adafruit-GFX-Library
 * Adafriut SSD1306 https://github.com/adafruit/Adafruit_SSD1306
 * RTClib https://github.com/mic159/RTClib
 */

#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Buttons.h"
#include "Menu.h"
#include "Menu_Settings.h"
#include "Menu_Settings_24.h"
#include "Menu_Settings_Time.h"
#include "Menu_Settings_Date.h"
#include "Menu_Settings_Brightness.h"
#include "Menu_Clockface.h"
#include "State.h"

#define NEXT_PIN   2
#define SELECT_PIN 3

#define OLED_RESET 4
#define WIDTH      128
#define HEIGHT     64

// Set this to enable printing debug stats to the screen
//#define DEBUG_STATS

Button btnNext(NEXT_PIN);
Button btnSelect(SELECT_PIN);
Adafruit_SSD1306 display(OLED_RESET);
RTC_DS1307 RTC;

void buttonNextPressed() {
  btnNext.interrupt();
}
void buttonSelectPressed() {
  btnSelect.interrupt();
}

State state;
Menu* menu = NULL;

void setup(void) {
  Serial.begin(9600);
  randomSeed(analogRead(A3));
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setRotation(2);

  // First time init, set to code compile date.
  if (!RTC.isrunning()) {
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Setup buttons
  pinMode(NEXT_PIN, INPUT);
  pinMode(SELECT_PIN, INPUT);
  attachInterrupt(0, buttonSelectPressed, RISING);
  attachInterrupt(1, buttonNextPressed, RISING);

  // Splash
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 20);
  display.print(F("Pong Clock"));
  display.setTextSize(1);
  display.setCursor(66, 48);
  display.print(F("by 0miker0"));
  display.setCursor(78, 56);
  display.print(F("& mic159"));
  display.display();
  delay(2000);

  // Load things from state
  display.dim(state.dim);

  state.update();
  switchMenu(MENU_CLOCK);
}

void loop() {
  // As an optimisation, we only draw the display
  // when we really need to. Drawing the display
  // every time is wasteful if nothing has changed.
  bool draw = false;
#ifdef DEBUG_STATS
  unsigned long timer = millis();
#endif

  // Buttons
  if (btnNext.update() && btnNext.read()) {
    menu->button1();
    draw = true;
  }
  if (btnSelect.update() && btnSelect.read()) {
    menu->button2();
    draw = true;
  }

  // Switch menu if indicated.
  updateMenuSelection();

  // Update
  state.update();
  if(menu->update()) {
    draw = true;
  }

  // Display
  if (draw) {
    display.clearDisplay();
    menu->draw(&display);

#ifdef DEBUG_STATS
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(80, HEIGHT - 10);
    display.print(freeRam());
    display.setCursor(109, HEIGHT - 10);
    display.print(millis() - timer);
#endif

    display.display();
  }

}

#ifdef DEBUG_STATS
int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
#endif

