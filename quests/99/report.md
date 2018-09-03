# Quest Reporting Guidelines Example

Authors: Emily Lam, Tom Little, 2018-09-01

## Summary

In this skill quest, we wired a 8x8 LED Dot-Array to the ESP32
using shift registers. This allows us to use 3 GPIO pins on the
micro-controller to control 64 LEDs. In this example, we used the
dot-array display one line of the dot-array at a time to test out the
functionality.

## Evaluation Criteria

We decided on the following specifications for a successful solution to this quest:
- Able to send an ASCII character from console to dot matrix for display
- Holds character until next display
- When two characters are sent to display, each one displayed for 1 s, then toggles


## Solution Design

We used the SN74HC595 shift register to convert serial data to
parallel data and the Arduino Shift Register Tutorial for the approach
to our solution.  The pins used for communications are:

- ST_CP of 74HC595 --> pin 33 of ESP32
- DS of 74HC595 --> 27
- SH_CP of 74HC595 --> pin 12 of ESP32

Since the ESP32 has 3.3 V logic level, current limiting resistors (220
ohms) were used to limit the current to the LED matrix.  Important to
note is that the shift registers operate on a rising edge, so it was
important to send bits in on the rising edge of the clock pin. The
latch pin was used to disable the display when transmitting data.


## Sketches and Photos

<center><img src="./images/dot-array.JPG" width="100%" /></center>
<center> Dot Array Implementation</center>


## Modules, Tools, Source Used in Solution
- [Arduino Serial to Parallel with Shift Register](https://www.arduino.cc/en/Tutorial/ShiftOut)


## Supporting Artifacts

- [Github repo for our
  solution](https://github.com/BU-EC444/model-student/tree/master/skills/2-1-dot-array)
- [Youtube video demo[()


-----

## Reminders

- Please remember to post a link to this report.md file on [Piazza](https://piazza.com/class/jja9ukam6dp48f) including references to each team member.
- Video recording not to exceed 90s
- Each team member appears in video
- Repo is private
