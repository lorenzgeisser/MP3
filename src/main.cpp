#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

#define OUTPUT_PIN 2

#define STUNDEN 9
#define MINUTEN 24

// rtc objekt erstellen
DS1307 rtc;

// buffer für strings
char buf[20];

void setup()
{
    // für debuggen
    Serial.begin(9600);

    // i2c für RTC init
    Wire.begin();

    // rtc initialiseren
    rtc.begin();

    // output pin konfigurieren
    digitalWrite(OUTPUT_PIN, LOW);
    pinMode(OUTPUT_PIN, INPUT);

    // rtc auf aktuelle zeit stellen (PC)
    if (!rtc.isrunning())
    {
        rtc.adjust(DateTime(__DATE__, __TIME__));
    }
}

void loop()
{
    // rtc auslesen
    DateTime now = rtc.now();

    // zeit in string schreiben (für debuggen)
    Serial.println(now.tostr(buf));

    // zeit abfrage
    if ((now.hour() == STUNDEN) && (now.minute() == MINUTEN))
    {
        // für debuggen
        Serial.println("Start");

        // output pin für 100ms auf GND ziehen
        pinMode(OUTPUT_PIN, OUTPUT);
        delay(100);
        pinMode(OUTPUT_PIN, INPUT);

        // solange in der gleichen minute
        while ((now.hour() == STUNDEN) && (now.minute() == MINUTEN))
        {
            // rtc auslesen

            now = rtc.now();

            // für debuggen
            Serial.println(now.tostr(buf));
            delay(500);
        }

        // für debuggen
        Serial.println("Stop");
    }

    delay(500);
}