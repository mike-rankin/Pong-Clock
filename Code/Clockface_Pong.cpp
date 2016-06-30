/*
 * Pong Clockface
 * Plays a game of Pong and makes the score equal the time!
 *
 * The code and algorythms originated from https://github.com/rparrett/pongclock
 * It was modified by mic159 to use classes, and to fit into the Pong Clock code structure.
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Paddle.h"
#include "Ball.h"
#include "Clockface_Pong.h"

#define WHITE 1
#define WIDTH 128
#define HEIGHT 64

#define BALL_SPEED 2

ClockfacePong::ClockfacePong()
: lpaddle(0, 0), rpaddle(WIDTH - 2, HEIGHT - 14)
, ball(2, 2, BALL_SPEED, BALL_SPEED)
, lscore(0), rscore(0)
, pause(0)
{
  lpaddle.y = random(0, HEIGHT - lpaddle.h);
  ball.x = lpaddle.w;
  ball.y = lpaddle.y + (lpaddle.h / 2);
  ball.calcTarget();
}

void ClockfacePong::begin(uint8_t hour, uint8_t minute) {
  lscore = hour;
  rscore = minute;
}

void ClockfacePong::update(uint8_t hour, uint8_t minute) {
  // If paused, dont do any movements
  if (pause > 0) {
    --pause;
    return;
  }

  lpaddle.update(ball.target_y, ball.dx, rscore != minute && lscore == hour);
  rpaddle.update(ball.target_y, ball.dx, lscore != hour);

  bool hit = ball.update(lpaddle, rpaddle);

  if (hit) {
    // Wohoo, a score!
    lscore = hour;
    rscore = minute;
    // New game (ball on lpaddle)
    lpaddle.y = random(0, HEIGHT - lpaddle.h);
    ball.x = lpaddle.w;
    ball.y = lpaddle.y + (lpaddle.h / 2);
    if (ball.dx < 0)
      ball.dx *= -1;
    ball.calcTarget();
    pause = 50;
  }
}

void ClockfacePong::draw(Adafruit_GFX* display) const {
  lpaddle.draw(display);
  rpaddle.draw(display);
  // Middle line
  for(uint8_t i = rscore % 2; i < HEIGHT / 4; i = i + 2) {
    display->fillRect(WIDTH / 2 - 1, i * 4, 2, 4, WHITE);
  }
  drawScore(display);
  ball.draw(display);
}

void ClockfacePong::drawScore(Adafruit_GFX* display) const {
  int lscore_x, rscore_x;
  static const int font_w = 10;
  static const int font_sp = 4;

  if (lscore > 9) lscore_x = WIDTH / 2 - font_w - font_w - font_sp - 10;
  else lscore_x = WIDTH / 2 - font_w - 10;

  rscore_x = WIDTH / 2 + 10;

  display->setTextSize(2);
  display->setTextColor(WHITE);

  display->setCursor(lscore_x, 4/2);
  display->println(lscore);

  display->setCursor(rscore_x, 4/2);
  display->println(rscore);
}

