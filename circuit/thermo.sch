EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L Device:Thermocouple TC?
U 1 1 60935DE0
P 6050 2700
AR Path="/60935DE0" Ref="TC?"  Part="1" 
AR Path="/60924309/60935DE0" Ref="TC?"  Part="1" 
AR Path="/609437CE/60935DE0" Ref="TC?"  Part="1" 
AR Path="/60943BDD/60935DE0" Ref="TC?"  Part="1" 
AR Path="/60945008/60935DE0" Ref="TC?"  Part="1" 
AR Path="/6094541D/60935DE0" Ref="TC?"  Part="1" 
F 0 "TC?" H 5852 2768 50  0000 R CNN
F 1 "Thermocouple" H 5852 2677 50  0000 R CNN
F 2 "" H 5475 2750 50  0001 C CNN
F 3 "~" H 5475 2750 50  0001 C CNN
	1    6050 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5700 2800 5950 2800
Wire Wire Line
	5950 2600 5700 2600
Wire Wire Line
	4900 2800 4650 2800
Wire Wire Line
	4900 2500 4650 2500
Wire Wire Line
	4650 2600 4900 2600
Wire Wire Line
	5300 2000 5300 2300
$Comp
L power:+3.3V #PWR?
U 1 1 60935DEF
P 5300 2000
AR Path="/60935DEF" Ref="#PWR?"  Part="1" 
AR Path="/60924309/60935DEF" Ref="#PWR?"  Part="1" 
AR Path="/609437CE/60935DEF" Ref="#PWR?"  Part="1" 
AR Path="/60943BDD/60935DEF" Ref="#PWR?"  Part="1" 
AR Path="/60945008/60935DEF" Ref="#PWR?"  Part="1" 
AR Path="/6094541D/60935DEF" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5300 1850 50  0001 C CNN
F 1 "+3.3V" H 5315 2173 50  0000 C CNN
F 2 "" H 5300 2000 50  0001 C CNN
F 3 "" H 5300 2000 50  0001 C CNN
	1    5300 2000
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:MAX31855KASA U?
U 1 1 60935DF5
P 5300 2700
AR Path="/60935DF5" Ref="U?"  Part="1" 
AR Path="/60924309/60935DF5" Ref="U?"  Part="1" 
AR Path="/609437CE/60935DF5" Ref="U?"  Part="1" 
AR Path="/60943BDD/60935DF5" Ref="U?"  Part="1" 
AR Path="/60945008/60935DF5" Ref="U?"  Part="1" 
AR Path="/6094541D/60935DF5" Ref="U?"  Part="1" 
F 0 "U?" H 5300 3281 50  0000 C CNN
F 1 "MAX31855KASA" H 5300 3190 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6300 2350 50  0001 C CIN
F 3 "http://datasheets.maximintegrated.com/en/ds/MAX31855.pdf" H 5300 2700 50  0001 C CNN
	1    5300 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5300 3100 5300 3200
$Comp
L power:GNDS #PWR?
U 1 1 60935DFC
P 5300 3200
AR Path="/60935DFC" Ref="#PWR?"  Part="1" 
AR Path="/60924309/60935DFC" Ref="#PWR?"  Part="1" 
AR Path="/609437CE/60935DFC" Ref="#PWR?"  Part="1" 
AR Path="/60943BDD/60935DFC" Ref="#PWR?"  Part="1" 
AR Path="/60945008/60935DFC" Ref="#PWR?"  Part="1" 
AR Path="/6094541D/60935DFC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5300 2950 50  0001 C CNN
F 1 "GNDS" H 5305 3027 50  0000 C CNN
F 2 "" H 5300 3200 50  0001 C CNN
F 3 "" H 5300 3200 50  0001 C CNN
	1    5300 3200
	1    0    0    -1  
$EndComp
Text HLabel 4650 2500 0    50   Input ~ 0
SCK
Text HLabel 4650 2600 0    50   Input ~ 0
SO
Text HLabel 4650 2800 0    50   Input ~ 0
CS
$EndSCHEMATC
