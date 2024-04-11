void initDrive(int s){
  analogWrite(enA, s);
  analogWrite(enB, s);
 
  // motor A CW ^ (forward)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // digitalWrite(in1, LOW);
    // digitalWrite(in2, HIGH);
    
  // motor B CW ^ (forward)
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    delay(500);

 // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);


 // motor A CCW (backwards)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // digitalWrite(in1, HIGH);
  // digitalWrite(in2, LOW);

  // motor B CCW (backwards)
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    delay(500);

 // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  String payload = "--"; 

  if (httpResponseCode>0) {
    // Serial.print("HTTP Response code: ");
    // Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
  return payload;
}