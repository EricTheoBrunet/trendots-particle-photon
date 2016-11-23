#ifndef __TRENDOTS_H___TRENDOTS_H_
#define __TRENDOTS_H_

#include "application.h"
#include "HttpClient.h"

class Trendots {
public:
    int isDebug = 0;
    
    //  constructor
    Trendots(bool isDebug = false) {
        byte mac[6]; // the MAC address of your Wifi shield
        
        request.hostname = "www.iot.trendots.com";
        request.port = 80;
        request.path = "/backend/application/index.php/api/log/create";
        
        WiFi.on();
        WiFi.macAddress(mac);
    
        // http headers
        headers[0] = { "User-Agent", "particle-photon" };
        headers[1] = { "Content-Type", "application/json" };
        headers[2] = { "Accept" , "*/*" };
        headers[3] = { "X-Interface-Key" , System.deviceID() };             // this is the "key" parameter used to identify the interface in trendots 
        headers[4] = { "X-Interface-Address" , macToString(mac) };          // the address is used in conjuction with the key to confirm we have the right interface
        headers[5] = { NULL, NULL };                                        // note: always terminate headers will NULL
    }

    bool post(char* data);

private:
    HttpClient http;
    http_header_t headers[6];
    http_request_t request;
    http_response_t response;
    
    String macToString(byte* bytes);
};

#endif /* __TRENDOTS_H_ */
