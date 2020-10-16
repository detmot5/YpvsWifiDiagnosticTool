//
// Created by norbe on 12/10/2020.
//

#include <ESPAsyncWebServer.h>

#include "httpController.h"
#include "rpmParser.h"
#include "main.h"
#include "DeviceCommandsService.h"



#define CORS_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN  "Access-Control-Allow-Origin"
#define CORS_HEADER_ACCESS_CONTROL_ALLOW_METHODS "Access-Control-Allow-Methods"
#define CORS_ALLOWED_METHODS "POST,GET,OPTIONS"

#define CORS_HEADER_ACCESS_CONTROL_ALLOW_HEADERS "Access-Control-Allow-Headers"
#define CORS_ALLOWED_HEADERS "Origin, X-Requested-With, Content-Type, Accept"



#define HTTP_STATUS_OK 200
#define HTTP_STATUS_BAD_REQUEST 400






static void fullCorsAllow(AsyncWebServerResponse* response){
  response->addHeader(CORS_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN, "*");
  response->addHeader(CORS_HEADER_ACCESS_CONTROL_ALLOW_METHODS, CORS_ALLOWED_METHODS);
  response->addHeader(CORS_HEADER_ACCESS_CONTROL_ALLOW_HEADERS, CORS_ALLOWED_HEADERS);
}





void HTTPSetMappings(AsyncWebServer& server) {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(HTTP_REQUEST_LED_PIN, HIGH);
    const char* json = {R"( {"name" : "YPVS WiFi Diagnostic Tool",
                             "version" : "1.0.0"
                        })"};
    AsyncWebServerResponse* response = request->beginResponse(HTTP_STATUS_OK, "application/json", json);
    fullCorsAllow(response);
    request->send(response);
  });

  server.on("/GET_RPM", HTTP_GET, [] (AsyncWebServerRequest* request){
    digitalWrite(HTTP_REQUEST_LED_PIN, HIGH);
    AsyncWebServerResponse* response = request->beginResponse(HTTP_STATUS_OK, "application/json", getRPMInJSON());
    fullCorsAllow(response);
    request->send(response);
  });

  server.on("/SET_RPM", HTTP_POST, [] (AsyncWebServerRequest* request){
    digitalWrite(HTTP_REQUEST_LED_PIN, HIGH);
    AsyncWebParameter* param = request->getParam(0);
    if(param->name().equals("rpm")){
      DeviceCommand command("AT+RPM", CommandMode::AT_PARAM, param->value().toInt());
      DeviceCommandsService::send(command);
      request->send(HTTP_STATUS_OK);
    } else {
      request->send(HTTP_STATUS_BAD_REQUEST);
    }
  });
  server.on("/test", HTTP_POST, [] (AsyncWebServerRequest* request){
    digitalWrite(HTTP_REQUEST_LED_PIN, HIGH);
    
  });


}