// This #include statement was automatically added by the Particle IDE.
#include "Trendots.h"
#include "HttpClient.h"
#include "application.h"

int led = D7;                       // little blue LED on your board
bool isDebug = true;                // set to false in production

Trendots trendots(isDebug);

void setup() {
    pinMode(led, OUTPUT);
      
    if(isDebug) {
        Serial.begin(9600);         // serial loggin; used for debugging
    }
}

void loop() {

    if(isDebug) {
        Serial.println();
        Serial.println("Application>\tStart of Loop.");
    }
    
    if(trendots.post("{\"valueA\": \"1\", \"valueB\": \"55\"}")) {
        
        // one long blink on success
        digitalWrite(led, HIGH);
        delay(2000);
        digitalWrite(led, LOW);
    } else {
        
        // blink twice on error
        digitalWrite(led, HIGH);
        delay(500);        
        digitalWrite(led, LOW);
        delay(500);   
        digitalWrite(led, HIGH);
        delay(500);           
        digitalWrite(led, LOW);
    }
    
    delay(10000);
}
