#include "HX710B.h"
#define SCK_PIN 3
#define SDI_PIN 4

const int RELAY_ENABLE = 8;

HX710B air_press(SCK_PIN, SDI_PIN);

void setup()
{
    Serial.begin(115200);
    pinMode(RELAY_ENABLE, OUTPUT);
    
    if (!air_press.init()) 
    { 
        Serial.println(F("HX710B not Found !"));
        while (1);
    }
}

uint32_t time_update = 0;
void loop()
{
    uint32_t rollOver = millis();
    if (rollOver < time_update)
        time_update = rollOver;
    
    if (millis() - time_update >= 2000UL) 
    {
        uint32_t data_raw = 0;
        if (air_press.read(&data_raw, 1000UL) != HX710B_OK)
        {
            Serial.println(F("-----"));
        }
        else
        {
            Serial.print(F("Data raw of ADC is : "));
            Serial.println((unsigned long) data_raw);
            
            if (data_raw > 10500000) 
            {
                digitalWrite(RELAY_ENABLE, LOW);
            }
            else 
            {
                digitalWrite(RELAY_ENABLE, HIGH);
            }
        }
        time_update = millis();            
    }
}
