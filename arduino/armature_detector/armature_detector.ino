int current_pins[6] = {A0, A1, A2, A3, A4, A5};
int relay_pins[6]   = {8,  9,  10, 11, 12, 13};
float currents[6]   = {0,  0,  0,  0,  0,  0};
void setup() {
  for(auto pin : relay_pins) pinMode(pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
//  for(int i = 0; i < 6; i++) {
////    currents[i] = Read_current(current_pins[i]);
////    
////    delay(500);
////    if(currents[i] > 2.0) digitalWrite(relay_pins[i], HIGH);
////    else digitalWrite(relay_pins[i], LOW);
////    
////    Serial.print(currents[i]);
////    Serial.print(" ");
////    if(i !=0 && i != 1 && i!= 5)
//    digitalWrite(relay_pins[i == 0 ? 5 : i - 1], LOW);
//    delay(500);
//    digitalWrite(relay_pins[i], HIGH);
//    Serial.println(i);
//    delay(2000);
//  }
//  Serial.println();
  for(int i = 0; i < 6; i++) {
    currents[i] = Read_current(current_pins[i]);
    
  }
  for(int i = 0; i < 6; i++) {
    Serial.print(currents[i]);
    Serial.print(" ");
  }

  delay(1000);
//  for(auto val: currents) Serial.print(val), Serial.print(" ");
  Serial.println();
  for(int i = 0; i < 5; i++) {
    if(currents[i] > 2.0) digitalWrite(relay_pins[i], HIGH);
    else digitalWrite(relay_pins[i], LOW);
    delay(100);
  }
}

float Read_current(int _pin)
{
  float nVPP = getVPP(_pin);
  nVPP = (nVPP / 2) * 0.707 * 1000.0;    //(Vpp/2)*RMS*No. of CT windings
  float nCurrThruResistorPP = (nVPP) / 56.0;   //  56.0 ohm is R across CT
  float nCurrThruResistorRMS = (nCurrThruResistorPP); //-8.06     //minus Calibration Factor if needed
  float nCurrentThruWire = nCurrThruResistorRMS * 1000;

  if (nCurrThruResistorPP < 1.0) nCurrThruResistorPP = 0;
  
  return nCurrThruResistorPP;
}

float getVPP(int _pin)
{
  float result;
  int maxValue = 0;          // store max value here
  long int avgVal = 0;
  
  uint32_t start_time = millis();
  int i = 0;
  while ((millis() - start_time) < 100) //sample for 100 miliSec
  {
    int readValue = analogRead(_pin);
    avgVal += readValue;
    if (readValue > maxValue) maxValue = readValue;
    i++;
  }

  maxValue = (maxValue - (avgVal / i));
  result = (maxValue * 5.0) / 1024.0;

  return result;
}
