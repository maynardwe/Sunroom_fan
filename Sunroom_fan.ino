//TMP36 Pin Variables

//#include <IRremote.h>
int sensorSRoom = 0;
int Btn_start_temp = 2;
int Btn_stop_temp = 3;
int ledPin = 13;
int count, readingSRoom, round_tempSR,  val;
float voltageSRoom, tempSRoomC, tempSRoomF, start_temp, stop_temp;

void setup()
{
  Serial.begin(9600);
  Serial.println("Sunroom_fan");
//  irrecv.enableIRIn(); // Start the receiver
//  pinMode(RECV_PIN, INPUT);
  pinMode(sensorSRoom, INPUT);
  pinMode(Btn_start_temp, INPUT);
  pinMode(Btn_stop_temp, INPUT);
  digitalWrite(Btn_start_temp, HIGH); //turn on internal pull-up to avoid using 10kohm pull-up resister
  digitalWrite(Btn_stop_temp, HIGH); //turn on internal pull-up to avoid using 10kohm pull-up resister
}

void loop()
{
  if (digitalRead(Btn_start_temp) == HIGH)
  {
    start_temp = tempSRoomF;
  }
  if (digitalRead(Btn_stop_temp) == HIGH)
  {
    stop_temp = tempSRoomF;
  }
  
  if (start_temp == tempSRoomF)
  {
    digitalWrite(ledPin, HIGH);
  }
    if (stop_temp == tempSRoomF)
  {
    digitalWrite(ledPin, LOW);
  }
  
  //getting the voltage reading SRoom temperature sensor
  readingSRoom = analogRead(sensorSRoom);

  // converting that reading to voltage, for 3.3v arduino use 3.3
  voltageSRoom = readingSRoom * 5.0;
  voltageSRoom /= 1024.0;
  Serial.println(readingSRoom);
  //converting from 10 mv per degree with 500 mV offset to degrees ((voltage - 500mV) times 100)
  tempSRoomC = (voltageSRoom - 0.5) * 100 ;

  // now convert to Fahrenheit
  tempSRoomF = (tempSRoomC * 9.0 / 5.0) + 32.0;

  Serial.print(" Sun Room: "); Serial.print(tempSRoomF);
  Serial.print(" Start Fan at "); Serial.print(start_temp);
  Serial.print(" Stop Fan at "); Serial.print(stop_temp);
  
  delay(1000);
}

