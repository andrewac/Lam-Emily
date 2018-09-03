/*

Dot-Array Example
Emily Lam
July 5th, 2018
EC444

Adapted from shift register arduino example.

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Define  pins
#define LATCH 33
#define DATA 27
#define CLK 12

const int latchPin = LATCH;
const int clockPin = CLK;
const int dataPin = DATA;

void shiftOut(int myDataPin, int myClockPin, char myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

//internal function setup
  int i=0;
  int pinState;

 //clear everything out just in case to
 //prepare shift register for bit shifting
  gpio_set_level(myDataPin, 0);
  gpio_set_level(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    gpio_set_level(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    gpio_set_level(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    gpio_set_level(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    gpio_set_level(myDataPin, 0);
  }

  //stop shifting
  gpio_set_level(myClockPin, 0);
}

void setup() {
  // Pins are multiplexed --> choose GPIO
  gpio_pad_select_gpio(latchPin);
  gpio_pad_select_gpio(clockPin);
  gpio_pad_select_gpio(dataPin);
  // Set pins as outputs
  gpio_set_direction(latchPin, GPIO_MODE_OUTPUT);
  gpio_set_direction(clockPin, GPIO_MODE_OUTPUT);
  gpio_set_direction(dataPin, GPIO_MODE_OUTPUT);
}

void loop() {
  //count up routine
  for (int j = 0; j < 256; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    gpio_set_level(latchPin, 0);
    // Cathodes
    shiftOut(dataPin, clockPin, 0);
    // Anodes
    shiftOut(dataPin, clockPin, j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    gpio_set_level(latchPin, 1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void app_main()
{
  setup();
  while (1) {
    loop();
  }

}
