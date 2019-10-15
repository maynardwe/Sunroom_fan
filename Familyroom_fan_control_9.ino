//TMP36 Pin Variables

#include <LiquidCrystal.h>
#include <IRremote.h>
const int pot = 1;
int sensorSRoom = 0;
int count, readingSRoom, round_tempSR;
float voltageSRoom, tempSRoomC, tempSRoomF;

int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);

void setup()
{
  Serial.begin(9600);
  Serial.println("Familyroom_fan_control_9");
  irrecv.enableIRIn(); // Start the receiver

  pinMode(RECV_PIN, INPUT);
  pinMode(sensorSRoom, INPUT);
  pinMode(pot, INPUT);

  //Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("Fan OFF   Diff 3");
  //Move cursor to second line, first position
  lcd.setCursor(0, 0);
  lcd.print("SunR 68  FamR 67");
}

void loop()
{
  int potval = analogRead(pot);
  potval = map(potval, 0, 1023, 70, 100);
  if (irrecv.decode(&results))
  {
    count = results.rawlen;
    Serial.print("rx    "); Serial.print(count);
    count = (count / 2) + 50;
    Serial.print("    counverted   "); Serial.println(count);
    irrecv.resume(); // Receive the next value
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
  round_tempSR = (tempSRoomF + .5)*potval/100;

  Serial.print(" Sun Room: "); Serial.print(tempSRoomF);
  Serial.print("    Family Room: "); Serial.println(count);
  lcd.setCursor(5, 0);
  lcd.print(round_tempSR);
  lcd.setCursor(14, 0);
  lcd.print(count);
  delay(1000);
}

