#include "main.hpp"

// Pinout
#define LED_PIN PIN_A1
#define LEVER_PIN PIN_A0
#define LSIDE_LED_PIN 16
#define RSIDE_LED_PIN 10

// Some color preset
const CRGB GOLDEN_YELLOW = 0xFFEE40;
const CRGB SAKURA_PINK = 0xFF8080;

// Yes you can change as you wish
const int KEY_MAP[10] = {
    // L: A    B    C   SIDE MENU
    'a', 's', 'd', KEY_RIGHT_ARROW, 'u',
    // R: A    B    C   SIDE MENU
    'j', 'k', 'l', KEY_LEFT_ARROW, 'o'};
const CRGB KEY_COLOR = SAKURA_PINK;

// Do not modify
const uint8_t PIN_MAP[10] = {
    // L: A B C SIDE MENU
    1, 0, 4, 14, 8,
    // R: A B C SIDE MENU
    5, 6, 7, 15, 9};
bool is_pressed[10];
bool updated[10];
int last_lever_value = -1;
CRGB lightColors[6];
const uint8_t COLOR_MAP[6] = {7, 6, 5, 2, 1, 0}; // 哈哈 我写出来自己都看不懂
CRGB leftSideColors[1];
CRGB rightSideColors[1];

int multiMap(int val, int *_in, int *_out, uint8_t size) {
  // 边界处理
  if (val <= _in[0])
    return _out[0];
  if (val >= _in[size - 1])
    return _out[size - 1];

  // 寻找输入值所在的区间
  uint8_t pos = 1;
  while (val > _in[pos])
    pos++;

  // 类似于 map() 函数，但只针对当前的一小段区间
  if (val == _in[pos])
    return _out[pos];

  // 数学公式: y = y0 + (x - x0) * (y1 - y0) / (x1 - x0)
  return (val - _in[pos - 1]) * (long)(_out[pos] - _out[pos - 1]) /
             (_in[pos] - _in[pos - 1]) +
         _out[pos - 1];
}

uint16_t p_15A_to_joystick(int rawInput) {
  if (rawInput < 0)
    rawInput = 0;
  if (rawInput > 1023)
    rawInput = 1023;

  static const int in[] = {0, 4, 14, 29, 75, 142, 226, 460, 787, 994, 1023};
  static const int out[] = {0,   0,   128, 256,  384, 512,
                            640, 768, 896, 1023, 1023};

  return multiMap(rawInput, (int *)in, (int *)out, sizeof(in) / sizeof(in[0]));
}

void setup() {
  for (unsigned char i : PIN_MAP) {
    pinMode(i, INPUT_PULLUP);
  }
  memset(is_pressed, 0, 10);
  FastLED.addLeds<WS2812B, LSIDE_LED_PIN, GRB>(leftSideColors, 1);
  FastLED.addLeds<WS2812B, RSIDE_LED_PIN, GRB>(rightSideColors, 1);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(lightColors, 6);
  Keyboard.begin();
  // Mouse.begin();
  AbsMouse.init(1920, 1080);
}

void loop() {
  // KEYBOARD
  for (auto i = 0; i < 10; i++) {
    bool read = digitalRead(PIN_MAP[i]) == LOW;
    if (read == true && is_pressed[i] == false) {
      is_pressed[i] = true;
      updated[i] = true;
      Keyboard.press(KEY_MAP[i]);
    } else if (read == false && is_pressed[i] == true) {
      is_pressed[i] = false;
      updated[i] = true;
      Keyboard.release(KEY_MAP[i]);
    } else {
      updated[i] = false;
    }
  }
  // MOUSE
  int read = 0;

  for (auto i = 0; i < 8; i++) {
    read += p_15A_to_joystick(analogRead(LEVER_PIN)) >> 3; // debounce
  }
  
  AbsMouse.move(map(read, 0, 1024, 960-128, 960+128), 540);
  // LED
  // single_color_when_pressed();
  random_color_when_pressed();
}

void random_color_when_pressed() {
  for (auto i = 0; i < 6; i++) {
    if (updated[COLOR_MAP[i]])
      lightColors[i] =
          is_pressed[COLOR_MAP[i]] ? get_rand_color() : CRGB::Black;
  }
  if (updated[3])
    leftSideColors[0] = is_pressed[3] ? get_rand_color() : CRGB::Black;
  if (updated[8])
    rightSideColors[0] = is_pressed[8] ? get_rand_color() : CRGB::Black;
  FastLED.show();
}

void single_color_when_pressed() {
  for (auto i = 0; i < 6; i++) {
    if (updated[COLOR_MAP[i]])
      lightColors[i] = is_pressed[COLOR_MAP[i]] ? KEY_COLOR : CRGB::Black;
  }
  if (updated[3])
    leftSideColors[0] = is_pressed[3] ? KEY_COLOR : CRGB::Black;
  if (updated[8])
    rightSideColors[0] = is_pressed[8] ? KEY_COLOR : CRGB::Black;
  FastLED.show();
}

void always_on() { FastLED.showColor(KEY_COLOR); }