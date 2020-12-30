# LED Light Controller #
This is a simple controller for for cheap 2-wire LED strings. These strings are setup with LED's alternating polarity along the two wires. Current inone direction lights every other LED and current in the other direction lights the other LED's in the string. These LED strings are really cheap and often sold with remote controls to control the lighting. The battery life is terrible and the light patterns selections weren't that great. I wrote this Arduino sketch for and ESP8266 to control the LED strings. I am using ESP8266 breakouts from Electrodragon that include a USB port for programming and power. I am also using a DRV8833 H-bridge to controll the LED's powered by the 5V pin from the USB connector to the Electordragon board.

- Electrodragon board link: https://www.electrodragon.com/product/esp8266-smd-adapter-breakout-board-r3/
- DRV8833 Link: https://www.amazon.com/gp/product/B08FJ3TX3Z/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1
- LED Light Strings: https://www.amazon.com/gp/product/B07QC65SZP/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1

## Schematic ##
![alt text](https://github.com/jludwig75/led_light_contoller/blob/master/board_kicad/led_controller_schematic.png)

## PCB Board ##
![alt text](https://github.com/jludwig75/led_light_contoller/blob/master/board_kicad/led_light_contoller_board.png)