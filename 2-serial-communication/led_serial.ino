int ledPin = 13; 
int value; 

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  if (Serial.available()) { 
    value = Serial.read(); 
    Serial.print("Data yang diterima: "); 
    Serial.println(value); 

    if (value == 1) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW); 
    }
  }
}