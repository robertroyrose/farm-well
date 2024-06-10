You can use the Makefile, just type make

cd Feather9x_RX
arduino-cli compile --build-path buildRx -v -b adafruit:samd:adafruit_feather_m0 Feather9x_RX.ino

cd ..
cd Feather9x_TX
arduino-cli compile --build-path buildTx -v -b adafruit:samd:adafruit_feather_m0 Feather9x_TX.ino


# Notes

The Lora Board
https://www.adafruit.com/product/3178

Schematic for the board
https://cdn-learn.adafruit.com/assets/assets/000/032/914/original/feather_schem.png?1465421956

5 volt 1 W solar panel Open-circuit voltage 8.2V
https://www.seeedstudio.com/1W-Solar-Panel-80X100.html?gclid=CjwKCAjw1uiEBhBzEiwAO9B_Hfy4V-f8nFneI5MxLgFuXy-O7XE6bFXBNgUx9UuKDMcamKedUEMgNRoCAX0QAvD_BwE

Chips on the Lora Board:

Charger chip on the Lora Board
MCP73831/2
https://ww1.microchip.com/downloads/en/DeviceDoc/MCP73831-Family-Data-Sheet-DS20001984H.pdf

Regulator
AP2112K-3.3
https://www.diodes.com/assets/Datasheets/AP2112.pdf

CPU
ATSAMD21G18_QNF
https://ww1.microchip.com/downloads/en/DeviceDoc/SAM-D21DA1-Family-Data-Sheet-DS40001882G.pdf

256K Flash 32K SRAM


Diode MBR120




Water Sensor
https://www.amazon.com/gp/product/B08LGJ1L7X/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1

Led
        (2) blue +5                     1.15 volt drop 10mA   (for 3.3 volts should be 215 ohm (220 ohm)
        (4) red 390 ohm then ground
Optical
        (1) white +5
        (3) yellow output and 4.7 ohm to ground

        (1) and (2) black
        (3) yellow wire then 4.7k then ground
        (4) 220 ohm then ground

      White Blue Yellow  Red
       (1)   (2)  (3)     (4)
        |     |    |       |
        +--+--+    |      R220
           |       |       |
           |       |       |
           |       +-R4.7K-+
           |       |       |
          Red    Yellow  Black
          +3.3    D1     Gnd

Solar Panel
        Sunnytech 2w 6v USB Mini Solar Panel Module DIY Polysilicon Solar Epoxy Cell Charger B032
        6.9 v
        330 mA


Well
    Solid state relay
    G3VM-41AY1
        3.3v 220 Ohm  1 4  Relay
        D1    Black   2 3  Relay

    On led (pin 1 and 2) want 10mA, get 1.27Volt drop R = (3.3-1.27)/.01 = 200 ohm
    
