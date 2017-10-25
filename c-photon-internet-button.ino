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
void sendHttpRequest(String method, String hostname, int port, String path, String body) {
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
    
    // Those rows can be used to prevent http calls flooding
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
    
    digitalWrite( ledPin, HIGH);
    delay(1000);
    digitalWrite( ledPin, LOW);
    */
    
    // Read the state of the buttons
    int buttonRedState = digitalRead( buttonRed );
    int buttonYellowState = digitalRead( buttonYellow );

        // If red button is pressed
	if (buttonRedState == LOW) {
                // If it was not in active state previously
		if (buttonRedActive == false) {
                        // Set its active state to true
			buttonRedActive = true;
			// Start counting time
			buttonTimer = millis();
		}
                // If pressing time is more than longPressTime and long press was not active
		if ((millis() - buttonTimer > longPressTime) && (buttonRedLongPressActive == false)) {
                        // We make long press active
			buttonRedLongPressActive = true;
			// And we execute the long press action
			sendHttpRequest("get", SERVER_IP, SERVER_PORT, SERVER_URL, "");
		}
	} else {
	        // If button was already in active state previously
		if (buttonRedActive == true) {
                        // If long press was active
			if (buttonRedLongPressActive == true) {
                                // We set long press active to false
				buttonRedLongPressActive = false;
			} else {
                		// Execute the short press action
                		sendHttpRequest("get", SERVER_IP, SERVER_PORT, SERVER_URL, "");
			}
                        // Set button active to false again
			buttonRedActive = false;
		}
	}
}
