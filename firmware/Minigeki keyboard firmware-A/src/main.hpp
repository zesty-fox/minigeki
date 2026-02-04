#include <Arduino.h>
#include <Keyboard.h>
// #include <Mouse.h>
#include <AbsMouse.h>
#include <FastLED.h>

#define PROFILE_WINDOWS

void setup();
void loop();
CRGB get_rand_color()
{
  return (random(0, 255) << 16) + (random(0, 255) << 8) + random(0, 255);
}
void random_color_when_pressed();
void single_color_when_pressed();
void always_on();