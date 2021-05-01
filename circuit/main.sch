EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:AC #PWR?
U 1 1 608D9642
P 6850 1000
F 0 "#PWR?" H 6850 900 50  0001 C CNN
F 1 "AC" H 6850 1275 50  0000 C CNN
F 2 "" H 6850 1000 50  0001 C CNN
F 3 "" H 6850 1000 50  0001 C CNN
	1    6850 1000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J?
U 1 1 608DCB70
P 7700 1250
F 0 "J?" H 7728 1226 50  0000 L CNN
F 1 "appropriate terminal" H 7728 1135 50  0000 L CNN
F 2 "" H 7700 1250 50  0001 C CNN
F 3 "~" H 7700 1250 50  0001 C CNN
	1    7700 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1000 7500 1250
Wire Wire Line
	7500 1350 7500 1800
Connection ~ 6850 1000
Connection ~ 6050 1000
Wire Wire Line
	5350 1200 5350 1000
Wire Wire Line
	6050 1000 6050 1200
Wire Wire Line
	6050 1800 5350 1800
Connection ~ 6050 1800
Wire Wire Line
	6050 1500 6050 1800
$Comp
L Device:Varistor RV?
U 1 1 608D80E6
P 6050 1350
F 0 "RV?" H 6153 1396 50  0000 L CNN
F 1 "Varistor" H 6153 1305 50  0000 L CNN
F 2 "" V 5980 1350 50  0001 C CNN
F 3 "~" H 6050 1350 50  0001 C CNN
	1    6050 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1800 5350 1500
Wire Wire Line
	6100 1800 6050 1800
$Comp
L Device:Fuse F?
U 1 1 608D6774
P 6250 1800
F 0 "F?" V 6053 1800 50  0000 C CNN
F 1 "Fuse" V 6144 1800 50  0000 C CNN
F 2 "" V 6180 1800 50  0001 C CNN
F 3 "~" H 6250 1800 50  0001 C CNN
	1    6250 1800
	0    1    1    0   
$EndComp
$Comp
L Triac_Thyristor:BTA16-600CW Q?
U 1 1 608D42FE
P 5350 1350
F 0 "Q?" H 5478 1396 50  0000 L CNN
F 1 "BTA16-600CW" H 5478 1305 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5550 1275 50  0001 L CIN
F 3 "https://www.st.com/resource/en/datasheet/bta16.pdf" H 5350 1350 50  0001 L CNN
	1    5350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 1000 6050 1000
Wire Wire Line
	6850 1000 7500 1000
$Comp
L Isolator:TLP3022 U?
U 1 1 608E7059
P 4200 1400
F 0 "U?" H 4200 1725 50  0000 C CNN
F 1 "TLP3022" H 4200 1634 50  0000 C CNN
F 2 "Package_DIP:Toshiba_11-7A9" H 4000 1200 50  0001 L CIN
F 3 "https://toshiba.semicon-storage.com/info/docget.jsp?did=1421&prodName=TLP3021(S)" H 4175 1400 50  0001 L CNN
	1    4200 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 608E89AF
P 4850 1000
F 0 "R?" V 5057 1000 50  0000 C CNN
F 1 "100R" V 4966 1000 50  0000 C CNN
F 2 "" V 4780 1000 50  0001 C CNN
F 3 "~" H 4850 1000 50  0001 C CNN
	1    4850 1000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5350 1000 5000 1000
Connection ~ 5350 1000
Wire Wire Line
	4700 1000 4500 1000
Wire Wire Line
	4500 1000 4500 1300
Wire Wire Line
	5200 1450 5200 1800
Wire Wire Line
	5200 1800 4500 1800
Wire Wire Line
	4500 1800 4500 1500
$Comp
L Device:R R?
U 1 1 608EC2F3
P 3550 1000
F 0 "R?" V 3343 1000 50  0000 C CNN
F 1 "330R" V 3434 1000 50  0000 C CNN
F 2 "" V 3480 1000 50  0001 C CNN
F 3 "~" H 3550 1000 50  0001 C CNN
	1    3550 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	3900 1300 3900 1000
Wire Wire Line
	3900 1000 3700 1000
$Comp
L Connector:Conn_01x02_Female J?
U 1 1 608ECEE4
P 2900 1100
F 0 "J?" H 2792 775 50  0000 C CNN
F 1 "Conn_01x02_Female" H 2792 866 50  0000 C CNN
F 2 "" H 2900 1100 50  0001 C CNN
F 3 "~" H 2900 1100 50  0001 C CNN
	1    2900 1100
	-1   0    0    1   
$EndComp
$Comp
L power:GNDS #PWR?
U 1 1 608EE3AC
P 3100 1850
F 0 "#PWR?" H 3100 1600 50  0001 C CNN
F 1 "GNDS" H 3105 1677 50  0000 C CNN
F 2 "" H 3100 1850 50  0001 C CNN
F 3 "" H 3100 1850 50  0001 C CNN
	1    3100 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1800 3900 1800
Wire Wire Line
	3100 1850 3100 1800
Connection ~ 3100 1800
Wire Wire Line
	3900 1500 3900 1800
Wire Wire Line
	3100 1100 3100 1800
Wire Wire Line
	5350 1000 6050 1000
Text Notes 4100 1650 0    50   ~ 0
zero cross
Text Label 2450 1000 2    50   ~ 0
PWM
Wire Wire Line
	2450 1000 3100 1000
Connection ~ 3100 1000
Wire Wire Line
	3100 1000 3400 1000
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 60905603
P 4400 3850
F 0 "A?" H 4400 5031 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 4400 4940 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 4400 3850 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 4400 3850 50  0001 C CNN
	1    4400 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1800 7500 1800
$Comp
L power:GNDS #PWR?
U 1 1 60922534
P 4500 4950
F 0 "#PWR?" H 4500 4700 50  0001 C CNN
F 1 "GNDS" H 4505 4777 50  0000 C CNN
F 2 "" H 4500 4950 50  0001 C CNN
F 3 "" H 4500 4950 50  0001 C CNN
	1    4500 4950
	1    0    0    -1  
$EndComp
$Sheet
S 6850 2800 950  450 
U 60924309
F0 "Sheet60924308" 50
F1 "thermo.sch" 50
F2 "SCK" I L 6850 2900 50 
F3 "SO" I L 6850 3000 50 
F4 "CS" I L 6850 3150 50 
$EndSheet
$Sheet
S 6850 3550 950  450 
U 60945008
F0 "sheet60945003" 50
F1 "thermo.sch" 50
F2 "SCK" I L 6850 3650 50 
F3 "SO" I L 6850 3750 50 
F4 "CS" I L 6850 3900 50 
$EndSheet
$Sheet
S 6850 4350 950  450 
U 6094541D
F0 "sheet60945418" 50
F1 "thermo.sch" 50
F2 "SCK" I L 6850 4450 50 
F3 "SO" I L 6850 4550 50 
F4 "CS" I L 6850 4700 50 
$EndSheet
Text Label 6300 2900 2    50   ~ 0
SCK
Text Label 6300 3000 2    50   ~ 0
SO
Wire Wire Line
	6850 2900 6300 2900
Wire Wire Line
	6300 3000 6850 3000
Text Label 6300 3650 2    50   ~ 0
SCK
Text Label 6300 3750 2    50   ~ 0
SO
Wire Wire Line
	6850 3650 6300 3650
Wire Wire Line
	6300 3750 6850 3750
Text Label 6300 4450 2    50   ~ 0
SCK
Text Label 6300 4550 2    50   ~ 0
SO
Wire Wire Line
	6850 4450 6300 4450
Wire Wire Line
	6300 4550 6850 4550
Text Label 6300 3150 2    50   ~ 0
CS0
Text Label 6300 3900 2    50   ~ 0
CS1
Text Label 6300 4700 2    50   ~ 0
CS2
Wire Wire Line
	6850 3150 6300 3150
Wire Wire Line
	6850 4700 6300 4700
Wire Wire Line
	6300 3900 6850 3900
Text Label 3600 4350 2    50   ~ 0
PWM
Text Label 3650 3550 2    50   ~ 0
SCK
Text Label 3650 3850 2    50   ~ 0
CS0
Text Label 3650 3750 2    50   ~ 0
CS1
Text Label 3650 3650 2    50   ~ 0
CS2
Text Label 3650 3950 2    50   ~ 0
SO
Wire Wire Line
	3650 3550 3900 3550
Wire Wire Line
	3900 3650 3650 3650
Wire Wire Line
	3650 3750 3900 3750
Wire Wire Line
	3900 3850 3650 3850
Wire Wire Line
	3650 3950 3900 3950
Wire Wire Line
	3600 4350 3900 4350
NoConn ~ 3900 3250
NoConn ~ 3900 3350
NoConn ~ 3900 3450
NoConn ~ 3900 4050
NoConn ~ 3900 4150
NoConn ~ 3900 4250
NoConn ~ 3900 4450
NoConn ~ 3900 4550
NoConn ~ 4300 4950
NoConn ~ 4400 4950
NoConn ~ 4900 4650
NoConn ~ 4900 4550
NoConn ~ 4900 4350
NoConn ~ 4900 4250
NoConn ~ 4900 4150
NoConn ~ 4900 4050
NoConn ~ 4900 3950
NoConn ~ 4900 3850
NoConn ~ 4900 3650
NoConn ~ 4900 3450
NoConn ~ 4900 3250
NoConn ~ 4600 2850
NoConn ~ 4300 2850
$Comp
L power:+3.3V #PWR?
U 1 1 6096C80E
P 4500 2700
F 0 "#PWR?" H 4500 2550 50  0001 C CNN
F 1 "+3.3V" H 4515 2873 50  0000 C CNN
F 2 "" H 4500 2700 50  0001 C CNN
F 3 "" H 4500 2700 50  0001 C CNN
	1    4500 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2700 4500 2850
$EndSCHEMATC
