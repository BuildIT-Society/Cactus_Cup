# Cactus_Cup
Custom Cactus Cup lighting system.

Test Commit - Sam Bartek <br>
Test Commit - Yash Bharatula <br>
Test Commit - Itsuki Sakamoto <br>

## How to Burn Program Into Attiny85 Chip <br>
1. Follow the link for help: https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829 <br>
2. Goto Open File -> Preferences and in the Additional Boards Manager URLs give this url: <br> https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json <br> 
3. In Arduino IDE, goto File->Examples->ArduinoISP. Load the sketch to Arduino <b>with nothing connected</b>.<br>
4. Insure ATtiny Library is installed. <br>
5. Goto Tools tab and change the following: <br>
    a. Board: ATtiny85 <br>
    b. Processor: ATtiny85 <br>
    c. Clock: 8Mhz <br>
    d. Programmer: "Arduino as ISP" <br>
6. Connect custom programmer shield to Ardiuno with chip inserted correctly. <br>
7. Goto Tools->Burn Bootloader, click to run bootloader config. <br>
8. Make sketch for ATtiny85 chip, then click "Upload" to upload sketch to chip. <br>
9. Take chip out, place in bread board for testing. <br>
10. Repeat steps 6-8 for each new sketch uploaded to chip. <br>


## Troubleshooting <br>
- Make sure computer recognizes the arduino board and sees the right usb port, especially if the error look like: "avrdude: stk500_getsync(): not in sync: resp=0x00" <br>
- Make sure ATtiny85 settings are correct <br>


