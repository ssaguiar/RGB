#ifndef __RGB_H
#define __RGB_H

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

struct Color
{
  const uint8_t r, g, b;
  
  Color(uint8_t red, uint8_t green, uint8_t blue): r(red), g(green), b(blue) {}
};

const Color RED(255, 0, 0);
const Color ORANGE(83, 4, 0);
const Color YELLOW(255, 255, 0);
const Color GREEN(0, 255, 0);
const Color BLUE(0, 0, 255);
const Color INDIGO(4, 0, 19);
const Color VIOLET(23, 0, 22);
const Color CYAN(0, 255, 255);
const Color MAGENTA(255, 0, 255);
const Color WHITE(255, 255, 255);
const Color BLACK(0, 0, 0);
const Color PINK(158, 4, 79);

class RGB 
{  
private:  

  int redPin, greenPin, bluePin;
  
public:
  
  void init(int redPin, int greenPin, int bluePin) {
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
  }
  
  void setColor(uint8_t r, uint8_t g, uint8_t b) {
    analogWrite(redPin, 255 - r);
    analogWrite(greenPin, 255 - g);
    analogWrite(bluePin, 255 - b);
  }
  
  void setColor(const Color &color) {
    setColor(color.r, color.g, color.b);
  }
  
  void fadeToColor(const Color &start, const Color &end, int fadeDelay) {
    int dr = end.r - start.r, dg = end.g - start.g, db = end.b - start.b;
    int steps = max(abs(dr),max(abs(dg), abs(db)));
    for (int i = 0; i < steps; i++) {
      uint8_t newRed = start.r + (i * dr / steps);
      uint8_t newGreen = start.g + (i * dg / steps);
      uint8_t newBlue = start.b + (i * db / steps);
      setColor(newRed, newGreen, newBlue);
      delay(fadeDelay);
    }
    setColor(end);
  }

};

#endif
