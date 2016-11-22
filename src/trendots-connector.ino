#include "HttpClient.h"
#include "application.h"

#define LOGGING

unsigned int nextTime = 0;                          // next time to contact the server
HttpClient http;

int led = D7;                                       //  little blue LED on your board

// http headers
http_header_t headers[] = {
    { "User-Agent", "particle-photon" },
    { "Content-Type", "application/json" },
    { "Accept" , "*/*" },
    { "X-Interface-Key" , System.deviceID() },      // this is the "key" parameter used to identify the interface in trendots 
    { "X-Interface-Address" , WiFi.macAddress() },  // the address is used in conjuction with the key to confirm we have the right interface
    { NULL, NULL }                                  // note: always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup() {
    pinMode(led, OUTPUT);
      
    // serial loggin; used for debugging
    Serial.begin(9600);
}

void loop() {
    if (nextTime > millis()) {
        return;
    }

    Serial.println();
    Serial.println("Application>\tStart of Loop.");
    
    request.hostname = "www.iot.trendots.com";
    request.port = 80;
    request.path = "/backend/application/index.php/api/log/create";
    request.body = "{\"value\": \"1\"}";            // many values can be sent and mapped throught the trendots interface configuration
    
    Serial.print("Request body>\t: ");
    Serial.println(request.body);    

    // post request
    http.post(request, response, headers);
    Serial.print("Application>\t Response status: ");
    Serial.println(response.status);
    
    if(response.status > 0) {
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

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);

    nextTime = millis() + 10000;
}
