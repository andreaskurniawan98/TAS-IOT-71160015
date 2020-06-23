#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define SS_PIN          2          // Configurable, see typical pin layout above
#define RST_PIN         0           // Configurable, see typical pin layout above

#define FIREBASE_HOST "https://tas71160015.firebaseio.com/"
#define FIREBASE_AUTH "HTnHO3MooAa8uhC6BEyJneg1UjFCqSF2Nxj8DPlJ"
#define WIFI_SSID "God Bless"
#define WIFI_PASSWORD "GodAlmighty"

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;
LiquidCrystal_I2C lcd(0x27,16,2);

FirebaseData firebaseData;
String path = "/node1";
int sensor = 13;
int LRD = A0;
int angle = 0;
int pinSer = 16;

/**
 * Initialize.
 */

Servo myservo; 
void setup() {
    delay(3000);
    Serial.begin(9600);
    while (!Serial);

    myservo.attach(pinSer);
    
    
    SPI.begin();
    mfrc522.PCD_Init();
    mfrc522.PCD_DumpVersionToSerial();
    
    lcd.init();
    
    // Turn on the backlight.
    lcd.backlight();
    
    // Move the cursor characters to the right and
    // zero characters down (line 1).
    lcd.setCursor(5, 0);
    
    // Print HELLO to the screen, starting at 5,0.
    lcd.print("SELAMAT");
    
    // Move the cursor to the next line and print
    // WORLD.
    lcd.setCursor(5, 1);      
    lcd.print("DATANG");

}

void loop() {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    
    // Halt PICC
    mfrc522.PICC_HaltA();

    for(int angle = 0; angle < 180; angle += 1) { 
      myservo.write(angle);
      Serial.println(angle) ;
      delay(60); }
    {                                                    
    } 

}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
