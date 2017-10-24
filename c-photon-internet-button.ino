// Import HttpClient library
#include <HttpClient.h>

// HttpClient initialization begin
HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    
    { "Content-Type", "application/json" },
    { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL

};

http_request_t request;
http_response_t response;
// HttpClient initialization end

// Declaring variables
unsigned int nextTime = 0; // Next time to contact the server
String method; // Currently only "get" and "post" are implemented
String hostname;
int port;
String path;

// Declaring buttons variables
int buttonYellow = D5;
int buttonRed = D6;
int ledPin = D7;
boolean buttonYellowActive = false;
boolean buttonYellowLongPressActive = false;
boolean buttonRedActive = false;
boolean buttonRedLongPressActive = false;
long buttonTimer = 0;
long longPressTime = 250;


// sendHttpRequest function
void sendHttpRequest(String method, String hostname, int port, String path, String body)
{
    
    request.hostname = hostname;
    request.port = port;
    request.path = path;
    request.body = body;

    Serial.print("Method: " + method + "\n");
    Serial.print("Hostname: " + hostname + "\n");
    Serial.print("Port: " + String(port) + "\n");
    Serial.print("Path: " + path + "\n");
    Serial.print("Body: " + body + "\n");

    if (method == "post") {
        
        Serial.print("\nSending http request\n");
        http.post(request, response, headers);
        Serial.print("Application>\tResponse status: ");
        Serial.println(response.status);
        Serial.print("Application>\tHTTP Response Body: ");
        Serial.println(response.body);
        
      } else if (method == "get") {
          
        Serial.print("\nSending http request\n");
        http.get(request, response, headers);
        Serial.print("Application>\tResponse status: ");
        Serial.println(response.status);
        Serial.print("Application>\tHTTP Response Body: ");
        Serial.println(response.body);
        
      } else {
          
        Serial.print("Please check your method: only post and get are currently supported");
        
    }
}

void setup() {
    Serial.begin(9600);
    pinMode( buttonRed , INPUT_PULLUP); // sets pin as input
    pinMode( buttonYellow , INPUT_PULLUP); // sets pin as input
    pinMode( ledPin , OUTPUT ); // sets pin as output

}

void loop() {
    // If not enough time has passed do not send another http request
    /*
    if (nextTime > millis()) {
        return;
    }

    // sendHttpRequest example
    //
    // Remember to send in those parameters:
    // String method, String hostname, int port, String path, String body
    //
    sendHttpRequest("post", "davidenastri.it", 8080, "/", "Ciao");
    sendHttpRequest("get", "davidenastri.it", 8080, "/", "Ciao");

    nextTime = millis() + 10000;
    */
    
    
    int buttonRedState = digitalRead( buttonRed );
    int buttonYellowState = digitalRead( buttonYellow );
    // remember that we have wired the pushbutton to
    // ground and are using a pulldown resistor
    // that means, when the button is pushed,
    // we will get a LOW signal
    // when the button is not pushed we'll get a HIGH

  // let's use that to set our LED on or off

	if (buttonRedState == LOW) {

		if (buttonRedActive == false) {

			buttonRedActive = true;
			buttonTimer = millis();

		}

		if ((millis() - buttonTimer > longPressTime) && (buttonRedLongPressActive == false)) {

			buttonRedLongPressActive = true;
			// Long press action
			sendHttpRequest("get", SERVERIP, SERVER_PORT, URL_LONG_ACTION_RED_BUTTON, "");

		}

	} else {

		if (buttonRedActive == true) {

			if (buttonRedLongPressActive == true) {

				buttonRedLongPressActive = false;

			} else {
                // Short press action
                sendHttpRequest("get", SERVERIP, SERVER_PORT, URL_SHORT_RED_BUTTON_ACTION, "");
                digitalWrite( ledPin, HIGH);
                delay(1000);
                digitalWrite( ledPin, LOW);

			}

			buttonRedActive = false;

		}

	}


}
