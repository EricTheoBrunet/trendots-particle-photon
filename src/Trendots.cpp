#include "Trendots.h"

bool Trendots::post(char* data)
{
    request.body = data;
    
    if(isDebug) {
        Serial.print("Request body>\t: ");
        Serial.println(request.body);    
    }

    // post request
    http.post(request, response, headers);
    
    if(isDebug) {
        Serial.print("Application>\tResponse status: ");
        Serial.println(response.status);
        Serial.print("Application>\tHTTP Response Body: ");
        Serial.println(response.body);
    }
    
    if(response.status <= 0) {
        return false;
    } 
    
    return true;
}

String Trendots::macToString(byte* bytes) {
    char buffer [17];
    
    buffer[16] = 0;
    
    for(int j=0;j<8;j++)
        sprintf(&buffer[2*j], "%02X", bytes[j]);
    
    return buffer;
}

