# 📘 Live Time Display on 16x2 LCD using ESP32
## 🎯 Objective
This project demonstrates how to interface a 16x2 HD44780-based LCD with an ESP32 microcontroller to display the current time in real-time. The time is fetched using the internal timer of the ESP32, and it is displayed on the LCD in HH:MM:SS format. The LCD operates in 4-bit mode, and no prebuilt libraries are used for controlling the LCD.

## 🧠 Features
✅ Display real-time clock (HH:MM:SS) on the LCD

✅ Use of internal ESP32 timer to keep track of time

✅ Modular code for easy updates and maintenance (lcd.h / lcd.c)

✅ Option to add further features like time editing (to be added later)

## 🛠️ Hardware Required
 -ESP32 Dev Board

 -16x2 LCD Display (HD44780)

 -Breadboard

 -Jumper Wires

 -USB Cable for ESP32

 -220Ω and 10kΩ Resistor (for contrast control)

## ⚙️ Wiring Instructions
### 📌 LCD Pinout and ESP32 Connections

| LCD Pin | Name | Connect To                 |
|---------|------|-----------------------------|
| 1       | VSS  | ESP32 GND                   |
| 2       | VDD  | ESP32 5V                    |
| 3       | VO   | GND (with 10kΩ resistor)     |
| 4       | RS   | GPIO4                       |
| 5       | RW   | GND                         |
| 6       | EN   | GPIO5                       |
| 11      | D4   | GPIO18                      |
| 12      | D5   | GPIO19                      |
| 13      | D6   | GPIO21                      |
| 14      | D7   | GPIO22                      |
| 15      | LED+ | 5V (through 220Ω resistor)   |
| 16      | LED- | ESP32 GND                   |

## 📌 Button Connections

| Button |Function	|GPIO Pin|
|--------|---------|--------|
|Hour    |Increment|	GPIO32|
|Minute |Increment	|GPIO33|
|Confirm| Set?Conform|	GPIO25|
## ✅ Important Notes:

 -Do not connect VO (pin 3) directly to GND. Use a 10kΩ resistor to control contrast.

 -Always connect RW (pin 5) to GND for write-only operation.

 -Supply 5V to LCD VCC and LED+. Using 3.3V may cause dim or no display.

## 🧑‍💻 How to Use
# Step 1: Clone & Open Project

     git clone https://github.com/yourusername/esp-lcd-time.git
     cd esp-lcd-time
# Step 2: Build the Project

     idf.py build
# Step 3: Flash to ESP32

    idf.py -p /dev/ttyUSB0 flash monitor
# Step 4: Output
If wired correctly and flashed successfully, the LCD will display:


    HH:MM:SS
The time will keep updating every second.

## 🧭 Expected Output
 -On power-up: LCD backlight ON

 -After initialization: Current time will appear in the format HH:MM:SS on row 1

 -The time will continuously update without flickering.
 
 -Pressing the Confirm button enters edit mode:

 ---Use Hour and Minute buttons to adjust time.

 ---Press Confirm again to save changes and exit edit mode.

## 📸 Output Pictures and Video

### 📸 LCD in Serial moniter
![lcd](https://github.com/melvinjoshua-emblock/Esp_lcd_time/blob/3ec164f0cb797e5690db8dde27e65d2c4584da8e/Live%20time%20in%20serial%20moniter.jpg)

### 📸 LCD Display Output
![lcd](https://github.com/melvinjoshua-emblock/Esp_lcd_time/blob/3ec164f0cb797e5690db8dde27e65d2c4584da8e/Live%20time%20in%20LCD.jpg )

### 🎥 LCD Output Video
![▶️Watch video]([https://github.com/melvinjoshua-emblock/Esp_lcd_time/blob/3ec164f0cb797e5690db8dde27e65d2c4584da8e/Live%20time%20in%20serial%20moniter.jpg](https://github.com/melvinjoshua-emblock/Esp_lcd_time/blob/9110ff72d6986f91762f4526bfd8cf61d6935fea/Video%20of%20LCD%20ive%20time.mp4))

### 🎥 Time change button Output Video
![▶️Watch video](https://github.com/melvinjoshua-emblock/Esp_lcd_time/blob/38e65c92020b0228d628482ea014c1b3f1612520/Button%20function.mp4)


## 🔧 Troubleshooting
| Symptom             | Possible Cause                  | Solution                                      |
|---------------------|----------------------------------|-----------------------------------------------|
| Blocks (▒▒▒▒▒) only  | Contrast too high or low         | Use a 2.2kΩ resistor for VO (pin 3) adjustment |
| Random characters   | Incorrect timing or floating RW | Ground RW (pin 5)                            |
| Nothing displays    | LCD not powered or improper wiring | Double-check VCC/GND and data pin connections |
| Dim display         | Using 3.3V instead of 5V         | Use 5V from ESP32 VIN pin for LCD power supply |

# ✅ Author

Melvin Joshua

Embedded Systems Intern

April 2025

