EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "LED Light Controller"
Date "2020-12-29"
Rev "1"
Comp "Jonathan Ludwig"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L led_controller_board:DRV8833_Breakout D1
U 1 1 5FEBC79A
P 5300 3850
F 0 "D1" H 5300 4365 50  0000 C CNN
F 1 "DRV8833_Breakout" H 5300 4274 50  0000 C CNN
F 2 "led_light_contoller_board:DRV8833_Breakout" H 5300 3950 50  0001 C CNN
F 3 "" H 5300 3950 50  0001 C CNN
	1    5300 3850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5FEBDB0F
P 2850 3500
F 0 "J1" H 2768 3717 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 2768 3626 50  0000 C CNN
F 2 "led_light_contoller_board:Screw_Terminal_2.54mm" H 2850 3500 50  0001 C CNN
F 3 "~" H 2850 3500 50  0001 C CNN
	1    2850 3500
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5FEBEDE7
P 2850 4100
F 0 "J2" H 2768 4317 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 2768 4226 50  0000 C CNN
F 2 "led_light_contoller_board:Screw_Terminal_2.54mm" H 2850 4100 50  0001 C CNN
F 3 "~" H 2850 4100 50  0001 C CNN
	1    2850 4100
	-1   0    0    -1  
$EndComp
$Comp
L led_controller_board:Electrodragon_ESP8266_USB E1
U 1 1 5FEBA659
P 7150 3900
F 0 "E1" H 7778 3946 50  0000 L CNN
F 1 "Electrodragon_ESP8266_USB" H 7778 3855 50  0000 L CNN
F 2 "led_light_contoller_board:Electrodragon ESP8266 USB" H 7150 3900 50  0001 C CNN
F 3 "" H 7150 3900 50  0001 C CNN
	1    7150 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5FEC6327
P 3550 3500
F 0 "R1" V 3343 3500 50  0000 C CNN
F 1 "330" V 3434 3500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3480 3500 50  0001 C CNN
F 3 "~" H 3550 3500 50  0001 C CNN
	1    3550 3500
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5FEC6F08
P 3550 4200
F 0 "R2" V 3343 4200 50  0000 C CNN
F 1 "330" V 3434 4200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3480 4200 50  0001 C CNN
F 3 "~" H 3550 4200 50  0001 C CNN
	1    3550 4200
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5FEC7536
P 5300 3050
F 0 "R3" V 5093 3050 50  0000 C CNN
F 1 "1K" V 5184 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5230 3050 50  0001 C CNN
F 3 "~" H 5300 3050 50  0001 C CNN
	1    5300 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 3800 6450 3800
Wire Wire Line
	6450 3800 6450 3350
Wire Wire Line
	6450 3350 7250 3350
Wire Wire Line
	7250 3350 7250 3500
Wire Wire Line
	6000 3900 6400 3900
Wire Wire Line
	6400 3900 6400 3300
Wire Wire Line
	6400 3300 7350 3300
Wire Wire Line
	7350 3050 5450 3050
Wire Wire Line
	7350 3050 7350 3300
Connection ~ 7350 3300
Wire Wire Line
	7350 3300 7350 3500
Wire Wire Line
	5150 3050 4500 3050
Wire Wire Line
	4500 3050 4500 3600
Wire Wire Line
	4500 3600 4600 3600
Wire Wire Line
	7150 4300 7150 4650
Wire Wire Line
	7150 4650 6300 4650
Wire Wire Line
	6300 4650 6300 3700
Wire Wire Line
	6300 3700 6000 3700
Wire Wire Line
	6850 3500 6850 3200
Wire Wire Line
	6850 3200 6300 3200
Wire Wire Line
	6300 3200 6300 3600
Wire Wire Line
	6300 3600 6000 3600
NoConn ~ 4600 4100
NoConn ~ 6650 3500
NoConn ~ 6750 3500
NoConn ~ 6950 3500
NoConn ~ 7050 3500
NoConn ~ 7150 3500
NoConn ~ 7450 3500
NoConn ~ 7550 3500
NoConn ~ 7650 3500
NoConn ~ 6650 4300
NoConn ~ 6750 4300
NoConn ~ 6850 4300
NoConn ~ 7250 4300
NoConn ~ 7350 4300
NoConn ~ 7450 4300
NoConn ~ 7550 4300
NoConn ~ 7650 4300
Wire Wire Line
	6950 4300 6950 4400
Wire Wire Line
	6950 4400 6450 4400
Wire Wire Line
	6450 4400 6450 4100
Wire Wire Line
	6450 4100 6000 4100
Wire Wire Line
	7050 4300 7050 4500
Wire Wire Line
	7050 4500 6400 4500
Wire Wire Line
	6400 4500 6400 4000
Wire Wire Line
	6400 4000 6000 4000
Wire Wire Line
	3050 3500 3400 3500
Wire Wire Line
	3050 4200 3400 4200
Wire Wire Line
	3700 3500 4400 3500
Wire Wire Line
	4400 3500 4400 3700
Wire Wire Line
	4400 3700 4600 3700
Wire Wire Line
	3700 4200 4400 4200
Wire Wire Line
	4400 4200 4400 4000
Wire Wire Line
	4400 4000 4600 4000
Wire Wire Line
	3050 3600 4300 3600
Wire Wire Line
	4300 3600 4300 3800
Wire Wire Line
	4300 3800 4600 3800
Wire Wire Line
	3050 4100 4300 4100
Wire Wire Line
	4300 4100 4300 3900
Wire Wire Line
	4300 3900 4600 3900
$EndSCHEMATC
