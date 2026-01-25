# ArduinoPiezo
const int piezoPin = A0; 
const int threshold = 50;.
int stepCount = 0;          
bool stepActive = false;
float voltage = 0;       

void setup() {
  Serial.begin(9600); 
  pinToMeasure();   
  Serial.println("Piezo Step Counter Initialized");
  Serial.println("Waiting for steps...");
}

void loop() {
  // Read the raw analog value
  int sensorValue = analogRead(piezoPin);
  
  // Convert raw reading to Voltage
  voltage = sensorValue * (5.0 / 1023.0);

  //Step Detection
  if (sensorValue > threshold) {
    if (!stepActive) {
      stepCount++;           
      stepActive = true;
      Serial.print("Step Detected! | Count: ");
      Serial.print(stepCount);
      Serial.print(" | Voltage Generated: ");
      Serial.print(voltage);
      Serial.println(" V");
      delay(100); 
    }
  } else {
    if (sensorValue < (threshold - 10)) {
      stepActive = false;
    }
  }
}

void pinToMeasure() {
  analogRead(piezoPin);
}