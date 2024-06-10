// Feather9x_RX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (receiver)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_TX

#include <SPI.h>
#include <RH_RF95.h>

/* for Feather32u4 RFM9x
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
*/

/* for feather m0 RFM9x */
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3


/* for shield 
#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 7
*/

/* Feather 32u4 w/wing
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     2    // "SDA" (only SDA/SCL/RX/TX have IRQ!)
*/

/* Feather m0 w/wing 
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     6    // "D"
*/

#if defined(ESP8266)
  /* for ESP w/featherwing */ 
  #define RFM95_CS  2    // "E"
  #define RFM95_RST 16   // "D"
  #define RFM95_INT 15   // "B"

#elif defined(ESP32)  
  /* ESP32 feather w/wing */
  #define RFM95_RST     27   // "A"
  #define RFM95_CS      33   // "B"
  #define RFM95_INT     12   //  next to A

#elif defined(NRF52)  
  /* nRF52832 feather w/wing */
  #define RFM95_RST     7   // "A"
  #define RFM95_CS      11   // "B"
  #define RFM95_INT     31   // "C"
  
#elif defined(TEENSYDUINO)
  /* Teensy 3.x w/wing */
  #define RFM95_RST     9   // "A"
  #define RFM95_CS      10   // "B"
  #define RFM95_INT     4    // "C"
#endif


// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Blinky on receipt
#define LED 13
#define RELAY 1

void pinModeStrong(uint8_t pin, uint8_t mode) {
  pinMode (pin, mode);
  PORT->Group[g_APinDescription[pin].ulPort].PINCFG[g_APinDescription[pin].ulPin].bit.DRVSTR = 1;
}
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinModeStrong(RELAY, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(RELAY, HIGH);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);
  //while (!Serial) {
  //  delay(1);
  //}
  delay(100);

  if (Serial)
    Serial.println("Feather LoRa RX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  if (Serial)
    Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  if (Serial)
    {Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);}

  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

int relay = !0;
int missing = 0;

uint16_t rxerror = 0;

unsigned long onmillis;
unsigned long offmillis;

void loop()
{
  unsigned long cmillis = millis();
  uint16_t want;

  if (rf95.waitAvailableTimeout(2000))
  {
    if (rf95.available())
    {
      // Should be a message for us now
      uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(buf);

      if (rf95.recv(buf, &len))
      {
        digitalWrite(LED, HIGH);

        if (Serial) {
          Serial.print("Got: ");
          Serial.println((char*)buf);
#if 0
          Serial.print("RSSI: ");
          Serial.println(rf95.lastRssi(), DEC);
#endif
        }

        rxerror = 0;
        want = !(buf[0] == 'O' && buf[1] == 'N');

        if (offmillis && (offmillis + 900000 < cmillis))
        {
          offmillis = 0;
        }

        if (offmillis && (want != !0))
        {
          if (Serial)
            Serial.println("Force off");
          want = !0;
        }

        if (onmillis && (onmillis + 900000 < cmillis)) {
          onmillis = 0;
          offmillis = cmillis;
          want = !0;
        }

        if (want != relay)
        {
          if ((want != !0) && (onmillis == 0))
            onmillis = cmillis;
          relay = want;
          digitalWrite(RELAY, relay);
        }

        // Send a reply
        uint8_t data[] = "And hello back to you";
        rf95.send(data, sizeof(data));
        rf95.waitPacketSent();
        if (Serial)
          Serial.println("Sent a reply");
        digitalWrite(LED, LOW);
        return;
      }
    }
  }

  if (Serial)
      Serial.println("No reply, is there a sender around?");

  rxerror++;

  if (rxerror > 15)
  {
    want = !0;

    if (want != relay)
    {
      relay = want;
      digitalWrite(RELAY, relay);
    }
  }
}
