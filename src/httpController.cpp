//
// Created by norbe on 12/10/2020.
//

#include <ESPAsyncWebServer.h>

#include "httpController.h"
#include "rpmParser.h"
#include "main.h"


#define CORS_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN  "Access-Control-Allow-Origin"
#define CORS_HEADER_ACCESS_CONTROL_ALLOW_METHODS "Access-Control-Allow-Methods"
#define CORS_ALLOWED_METHODS "POST,GET,OPTIONS"

#define CORS_HEADER_ACCESS_CONTROL_ALLOW_HEADERS "Access-Control-Allow-Headers"
#define CORS_ALLOWED_HEADERS "Origin, X-Requested-With, Content-Type, Accept"



static void fullCorsAllow(AsyncWebServerResponse* response){
  response->addHeader(CORS_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN, "*");
  response->addHeader(CORS_HEADER_ACCESS_CONTROL_ALLOW_METHODS, CORS_ALLOWED_METHODS);
  response->addHeader(CORS_HEADER_ACCESS_CONTROL_ALLOW_HEADERS, CORS_ALLOWED_HEADERS);
}





void HTTPSetMappings(AsyncWebServer& server) {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(HTTP_REQUEST_LED_PIN, HIGH);
    const char* json = {R"( {"name" : "YPVS WiFi Debugger",
                             "version" : "1.0.0"
                        })"};
    AsyncWebServerResponse* response = request->beginResponse(200, "application/json", json);
    fullCorsAllow(response);
    request->send(response);
  });

  server.on("/GET_RPM", HTTP_GET, [] (AsyncWebServerRequest* request){
    digitalWrite(HTTP_REQUEST_LED_PIN, HIGH);
    AsyncWebServerResponse* response = request->beginResponse(200, "application/json", getRPMInJSON());
    fullCorsAllow(response);
    request->send(response);
  });


}