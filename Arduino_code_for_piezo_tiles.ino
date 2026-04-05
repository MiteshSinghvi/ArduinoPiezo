const int piezoPin = A0; 
const int threshold = 50;
int stepCount = 0;          
bool stepActive = false;
float voltage = 0;       
float average = 0;
float sum = 0;

void setup() {
  Serial.begin(9600); 
  // pinToMeasure(); // This function was undefined in your snippets, removed for safety
  Serial.println("Piezo Step Counter Initialized");
  Serial.println("Waiting for steps...");
}

void loop() {
  //Read the sensor constantly
  int sensorValue = analogRead(piezoPin);
  if (sensorValue > threshold) {
    if (!stepActive) {
      int peakValue = sensorValue;
      long startTime = millis();
      
      while(millis() - startTime < 20) { 
        int tempVal = analogRead(piezoPin);
        if (tempVal > peakValue) {
          peakValue = tempVal;
        }
      }

      // CALCULATION OF VOLTAGE
      voltage = peakValue * (5.0 / 1023.0);
      stepCount++;      
      // Average Voltage Calculation
      sum = sum + voltage;
      average = sum / stepCount;              
      stepActive = true;
      Serial.print("Step Detected! | Count: ");
      Serial.print(stepCount);
      Serial.print(" | Max Voltage: ");
      Serial.print(voltage);
      Serial.print(" V | Avg Voltage: ");
      Serial.print(average);
      Serial.println(" V");
      
      delay(100); 
    }
  } else {
    if (sensorValue < (threshold - 10)) {
      stepActive = false;
    }
  }
}
