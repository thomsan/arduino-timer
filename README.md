# Arduino day counter
Simple arduino application to count the days since the last reset and display it on a TFT.
Something like the [Simpsons "Days without an accident" counter](https://www.youtube.com/watch?v=hfzbB_B3HS0) but digital :)

[![Simpsons "Days without an accident" counter](https://img.youtube.com/vi/hfzbB_B3HS0/0.jpg)](https://www.youtube.com/watch?v=hfzbB_B3HS0)

There are hidden buttons in the bottom left and right corners to de- and increase the counter by 1.

## Prerequisites
This projects uses the following libraries which can be installed via the Arduino IDE Library Manager:
+ `Adafruit_GFX`
+ `MCUFRIEND_kbv`

## Hardware
+ Aruino Uno
+ 2.4" TFT LCD Display Shield Touch Panel ILI9341
