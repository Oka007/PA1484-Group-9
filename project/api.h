#include <ArduinoJson.h>
#include <HTTPClient.h>

//A funktion that takes the url, makes a api request and returns the json dokument as a string 
String getApiData(String url){
    HTTPClient http; 

    http.begin(url);

    int httpResponseCode = http.GET();
    String payload;

    if(httpResponseCode == 200) {
        payload = http.getString();
    } else {

        //Write something here to indicate that something whent wrong ikd
        http.end();
        return"";
    }

    http.end();
    return payload;
}

//This is more of a referense for myself so that i understand how to do it
/*
void Deserialization(JsonDocument &doc, String payload){

    DeserializationError error = deserializeJson(doc, payload);

    if(error){
        return;
    }
}
    */