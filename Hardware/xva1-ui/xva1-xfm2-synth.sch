EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title "XVA1 / XFM2 User Interface"
Date "2021-03-07"
Rev ""
Comp "MacMannes"
Comment1 "UNVERIFIED!!!"
Comment2 ""
Comment3 "See https://www.futur3soundz.com/xfm2 for more info"
Comment4 "Original schematic: FUTUR3SOUNDZ"
$EndDescr
Text GLabel 8100 2700 0    50   Input ~ 0
XIAO-RX
Text GLabel 8100 2800 0    50   Input ~ 0
XIAO-TX
$Comp
L Diode:1N4148 D1
U 1 1 6043C362
P 3800 3600
F 0 "D1" H 3800 3817 50  0000 C CNN
F 1 "1N4148" H 3800 3726 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3800 3425 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3800 3600 50  0001 C CNN
	1    3800 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 60444D78
P 5550 4250
F 0 "R2" H 5620 4296 50  0000 L CNN
F 1 "470" H 5620 4205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5480 4250 50  0001 C CNN
F 3 "~" H 5550 4250 50  0001 C CNN
	1    5550 4250
	-1   0    0    1   
$EndComp
$Comp
L Isolator:4N36 U9
U 1 1 60445EE7
P 4800 3800
F 0 "U9" H 4800 4125 50  0000 C CNN
F 1 "4N36" H 4800 4034 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 4600 3600 50  0001 L CIN
F 3 "https://www.vishay.com/docs/81181/4n35.pdf" H 4800 3800 50  0001 L CNN
	1    4800 3800
	1    0    0    -1  
$EndComp
$Comp
L Memory_EEPROM:24LC01 U8
U 1 1 60447AEB
P 6050 5450
F 0 "U8" H 5850 5800 50  0000 C CNN
F 1 "24LC1025-I/P" H 6400 5800 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6050 5450 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21711J.pdf" H 6050 5450 50  0001 C CNN
	1    6050 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 5350 7500 5350
Wire Wire Line
	7500 5350 7500 4900
Wire Wire Line
	7500 4900 8100 4900
Wire Wire Line
	8100 4800 7400 4800
Wire Wire Line
	7400 4800 7400 5450
Wire Wire Line
	7400 5450 6450 5450
Wire Wire Line
	8100 4700 7250 4700
Wire Wire Line
	7250 4700 7250 5900
Wire Wire Line
	7250 5900 6550 5900
Wire Wire Line
	6050 5900 6050 5750
Wire Wire Line
	6050 5900 5400 5900
Wire Wire Line
	5400 5900 5400 5450
Wire Wire Line
	5400 5450 5650 5450
Connection ~ 6050 5900
Wire Wire Line
	5400 5450 5400 5350
Wire Wire Line
	5400 5350 5650 5350
Connection ~ 5400 5450
Wire Wire Line
	5650 5550 5550 5550
Wire Wire Line
	5550 4400 5550 4600
Wire Wire Line
	8100 4600 6050 4600
Connection ~ 5550 4600
Wire Wire Line
	5550 4600 5550 5550
Wire Wire Line
	6050 4600 6050 5150
Connection ~ 6050 4600
Wire Wire Line
	6050 4600 5550 4600
Wire Wire Line
	6450 5550 6550 5550
Wire Wire Line
	6550 5550 6550 5900
Connection ~ 6550 5900
Wire Wire Line
	6550 5900 6050 5900
Wire Wire Line
	5550 4100 5550 3800
Wire Wire Line
	5550 3800 5100 3800
NoConn ~ 5100 3700
Wire Wire Line
	8100 3700 6800 3700
Wire Wire Line
	6800 3700 6800 3150
Wire Wire Line
	6800 2900 6600 2900
Wire Wire Line
	8100 4400 6050 4400
Wire Wire Line
	6050 4400 6050 3900
Wire Wire Line
	6050 3900 5100 3900
Wire Wire Line
	5550 3800 6150 3800
Wire Wire Line
	6150 3800 6150 4300
Wire Wire Line
	6150 4300 8100 4300
Connection ~ 5550 3800
Wire Wire Line
	6800 3150 5500 3150
Wire Wire Line
	5500 3150 5500 2650
Connection ~ 6800 3150
Wire Wire Line
	6800 3150 6800 2900
Wire Wire Line
	5350 3300 6650 3300
Wire Wire Line
	6650 3300 6650 3600
Wire Wire Line
	6650 3600 8100 3600
Wire Wire Line
	6600 2700 6900 2700
Wire Wire Line
	6900 2700 6900 3500
Wire Wire Line
	6900 3500 8100 3500
Wire Wire Line
	8100 3400 7000 3400
Wire Wire Line
	7000 3400 7000 2600
Wire Wire Line
	7000 2600 6600 2600
Wire Wire Line
	6600 2500 7100 2500
Wire Wire Line
	7100 2500 7100 3300
Wire Wire Line
	7100 3300 8100 3300
Wire Wire Line
	7200 3200 7200 2400
Wire Wire Line
	7200 2400 6600 2400
NoConn ~ 6600 2100
NoConn ~ 6600 2200
NoConn ~ 6600 2300
NoConn ~ 5700 2250
NoConn ~ 5700 2350
NoConn ~ 5700 2750
NoConn ~ 6600 2800
$Comp
L Device:R R3
U 1 1 6049800A
P 3450 1100
F 0 "R3" V 3657 1100 50  0000 C CNN
F 1 "33" V 3566 1100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3380 1100 50  0001 C CNN
F 3 "~" H 3450 1100 50  0001 C CNN
	1    3450 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8100 3000 7450 3000
Wire Wire Line
	7550 2900 8100 2900
Wire Wire Line
	5050 3450 6450 3450
Wire Wire Line
	6450 3450 6450 4200
Wire Wire Line
	6450 4200 8100 4200
$Comp
L Device:R R5
U 1 1 604BE64C
P 3450 2150
F 0 "R5" V 3657 2150 50  0000 C CNN
F 1 "10" V 3566 2150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3380 2150 50  0001 C CNN
F 3 "~" H 3450 2150 50  0001 C CNN
	1    3450 2150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:DIN-5_180degree J1
U 1 1 604FA5A6
P 2700 3600
F 0 "J1" V 2654 3371 50  0000 R CNN
F 1 "DIN-5_180degree" V 2745 3371 50  0000 R CNN
F 2 "xva1-ui:MIDI_CONNECTOR_PCB" H 2700 3600 50  0001 C CNN
F 3 "" H 2700 3600 50  0001 C CNN
	1    2700 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 604CA798
P 3450 3300
F 0 "R1" V 3243 3300 50  0000 C CNN
F 1 "220" V 3334 3300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3380 3300 50  0001 C CNN
F 3 "~" H 3450 3300 50  0001 C CNN
	1    3450 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 3900 3800 3900
Wire Wire Line
	2800 3300 3300 3300
Wire Wire Line
	3600 3300 3800 3300
Wire Wire Line
	3800 3300 3800 3450
Wire Wire Line
	3800 3750 3800 3900
Connection ~ 3800 3900
Wire Wire Line
	3800 3900 2800 3900
Wire Wire Line
	4500 3700 4350 3700
Wire Wire Line
	4350 3700 4350 3300
Wire Wire Line
	4350 3300 3800 3300
Connection ~ 3800 3300
$Comp
L Connector:DIN-5_180degree J2
U 1 1 605336FE
P 2700 2450
F 0 "J2" V 2654 2221 50  0000 R CNN
F 1 "DIN-5_180degree" V 2745 2221 50  0000 R CNN
F 2 "xva1-ui:MIDI_CONNECTOR_PCB" H 2700 2450 50  0001 C CNN
F 3 "" H 2700 2450 50  0001 C CNN
	1    2700 2450
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 604C5A5E
P 3450 2750
F 0 "R4" V 3657 2750 50  0000 C CNN
F 1 "33" V 3566 2750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3380 2750 50  0001 C CNN
F 3 "~" H 3450 2750 50  0001 C CNN
	1    3450 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2800 2750 3300 2750
Wire Wire Line
	3600 2750 5050 2750
Wire Wire Line
	5050 2750 5050 3450
Wire Wire Line
	2800 2150 3300 2150
$Comp
L Connector:DIN-5_180degree J3
U 1 1 60569A51
P 2700 1400
F 0 "J3" V 2654 1171 50  0000 R CNN
F 1 "DIN-5_180degree" V 2745 1171 50  0000 R CNN
F 2 "xva1-ui:MIDI_CONNECTOR_PCB" H 2700 1400 50  0001 C CNN
F 3 "" H 2700 1400 50  0001 C CNN
	1    2700 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	2800 1100 3300 1100
Wire Wire Line
	3600 1100 7450 1100
Wire Wire Line
	7450 1100 7450 3000
Wire Wire Line
	5500 2650 5700 2650
Wire Wire Line
	5700 2550 5350 2550
Wire Wire Line
	5500 2450 5700 2450
$Comp
L xva1-ui:UDA1334 U7
U 1 1 60473FAD
P 6150 2500
F 0 "U7" H 6150 3234 50  0000 C CNN
F 1 "UDA1334" H 6150 3143 50  0000 C CNN
F 2 "xva1-ui:UDA1334" H 5850 3200 50  0001 C CNN
F 3 "" H 5850 3200 50  0001 C CNN
	1    6150 2500
	1    0    0    -1  
$EndComp
NoConn ~ 2700 1100
NoConn ~ 3000 1400
NoConn ~ 2700 1700
NoConn ~ 2700 2150
NoConn ~ 3000 2450
NoConn ~ 2700 2750
NoConn ~ 2700 3300
NoConn ~ 3000 3600
NoConn ~ 2700 3900
Wire Wire Line
	2800 1700 3300 1700
Wire Wire Line
	3300 1700 3300 1300
Wire Wire Line
	3300 1300 7550 1300
Wire Wire Line
	7550 1300 7550 2900
Wire Wire Line
	3600 2150 3900 2150
Wire Wire Line
	3900 2450 5500 2450
NoConn ~ 8100 3100
NoConn ~ 8100 3800
NoConn ~ 8100 3900
NoConn ~ 8100 4000
NoConn ~ 8100 4100
Wire Wire Line
	8100 3200 7200 3200
Text GLabel 9000 3400 2    50   Input ~ 0
CV-INPUT-2
Text GLabel 9000 3500 2    50   Input ~ 0
CV-INPUT-1
NoConn ~ 9000 2700
NoConn ~ 9000 2800
NoConn ~ 9000 2900
NoConn ~ 9000 3000
NoConn ~ 9000 3100
NoConn ~ 9000 3200
NoConn ~ 9000 3300
NoConn ~ 9000 3600
NoConn ~ 9000 3700
NoConn ~ 9000 3800
NoConn ~ 9000 3900
NoConn ~ 9000 4000
NoConn ~ 9000 4100
NoConn ~ 9000 4200
NoConn ~ 9000 4300
NoConn ~ 9000 4400
NoConn ~ 9000 4500
NoConn ~ 9000 4600
NoConn ~ 9000 4700
NoConn ~ 9000 4800
NoConn ~ 9000 4900
NoConn ~ 1000 -1200
Text GLabel 8100 4500 0    50   Input ~ 0
SPDIF-OUT
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 607B59A6
P 1050 6650
F 0 "J4" H 1150 6950 50  0000 C CNN
F 1 "Conn_01x02" H 1150 6850 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 1050 6650 50  0001 C CNN
F 3 "~" H 1050 6650 50  0001 C CNN
	1    1050 6650
	1    0    0    -1  
$EndComp
Text GLabel 1250 6750 2    50   Input ~ 0
SPDIF-OUT
$Comp
L power:GND #PWR0157
U 1 1 607B76A6
P 2000 6650
F 0 "#PWR0157" H 2000 6400 50  0001 C CNN
F 1 "GND" H 2005 6477 50  0000 C CNN
F 2 "" H 2000 6650 50  0001 C CNN
F 3 "" H 2000 6650 50  0001 C CNN
	1    2000 6650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 607BBD49
P 2300 6650
F 0 "J5" H 2400 6950 50  0000 C CNN
F 1 "Conn_01x02" H 2400 6850 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 2300 6650 50  0001 C CNN
F 3 "~" H 2300 6650 50  0001 C CNN
	1    2300 6650
	1    0    0    -1  
$EndComp
Text GLabel 2500 6750 2    50   Input ~ 0
CV-INPUT-1
$Comp
L power:GND #PWR0158
U 1 1 607BBD50
P 3250 6650
F 0 "#PWR0158" H 3250 6400 50  0001 C CNN
F 1 "GND" H 3255 6477 50  0000 C CNN
F 2 "" H 3250 6650 50  0001 C CNN
F 3 "" H 3250 6650 50  0001 C CNN
	1    3250 6650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 607BF456
P 3450 6650
F 0 "J6" H 3550 6950 50  0000 C CNN
F 1 "Conn_01x02" H 3550 6850 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 3450 6650 50  0001 C CNN
F 3 "~" H 3450 6650 50  0001 C CNN
	1    3450 6650
	1    0    0    -1  
$EndComp
Text GLabel 3650 6750 2    50   Input ~ 0
CV-INPUT-2
$Comp
L power:GND #PWR0159
U 1 1 607BF45D
P 4350 6650
F 0 "#PWR0159" H 4350 6400 50  0001 C CNN
F 1 "GND" H 4355 6477 50  0000 C CNN
F 2 "" H 4350 6650 50  0001 C CNN
F 3 "" H 4350 6650 50  0001 C CNN
	1    4350 6650
	1    0    0    -1  
$EndComp
Text Notes 3050 6050 2    50   ~ 0
Optional Connectors
Text Notes 3600 7200 2    63   Italic 13
WARNING!!!!
Text Notes 3800 7350 2    50   Italic 10
LIMIT CV INPUTS TO 3.3V
Wire Notes Line
	900  7450 900  5900
Wire Notes Line
	4500 5900 4500 7450
Wire Notes Line
	2150 6150 2150 7450
$Comp
L xva1-ui:CMOD-A7 U?
U 1 1 60432E04
P 8700 3800
AR Path="/60432E04" Ref="U?"  Part="1" 
AR Path="/60431802/60432E04" Ref="U6"  Part="1" 
F 0 "U6" H 8850 2385 50  0000 C CNN
F 1 "CMOD-A7" H 8850 2476 50  0000 C CNN
F 2 "xva1-ui:CMOD-A7-DIP-48_W15.24mm" H 8800 5100 50  0001 C CNN
F 3 "" H 8800 5100 50  0001 C CNN
	1    8700 3800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0160
U 1 1 60435EBF
P 8000 2450
F 0 "#PWR0160" H 8000 2200 50  0001 C CNN
F 1 "GND" V 8005 2322 50  0000 R CNN
F 2 "" H 8000 2450 50  0001 C CNN
F 3 "" H 8000 2450 50  0001 C CNN
	1    8000 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 2600 8000 2450
Wire Wire Line
	8100 2600 8000 2600
Wire Wire Line
	9100 2600 9000 2600
$Comp
L power:+5V #PWR0161
U 1 1 60436464
P 9100 2450
F 0 "#PWR0161" H 9100 2300 50  0001 C CNN
F 1 "+5V" V 9115 2578 50  0000 L CNN
F 2 "" H 9100 2450 50  0001 C CNN
F 3 "" H 9100 2450 50  0001 C CNN
	1    9100 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	9100 2450 9100 2600
Text Notes 2450 3850 2    50   ~ 0
MIDI-IN
Text Notes 2450 2700 2    50   ~ 0
MIDI-THRU
Text Notes 2450 1650 2    50   ~ 0
MIDI-OUT
Connection ~ 5500 2650
Wire Wire Line
	5350 2550 5350 3300
Connection ~ 5500 2450
Wire Wire Line
	5500 2450 5500 2650
Wire Wire Line
	3900 2150 3900 2450
Text Notes 6450 5250 0    50   ~ 0
(EPROM 1MBIT)
Wire Notes Line
	900  5900 4500 5900
Wire Notes Line
	900  6150 4500 6150
Wire Notes Line
	900  7450 4500 7450
Wire Wire Line
	4350 6650 3650 6650
Wire Wire Line
	3250 6650 2500 6650
Wire Wire Line
	2000 6650 1250 6650
$EndSCHEMATC