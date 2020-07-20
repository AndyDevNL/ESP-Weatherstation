/*--WIFI Connection--*/
#include <ESP8266WiFi.h>

define WIFI_SSID "SECRET"
define WIFI_PASSWORD "SECRET"

/*--Firebase Connection--*/
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "smart-things-2019.firebaseio.com"
#define FIREBASE_AUTH "pHkVlRIa1jZMe6VLEyOycXYEd850xDGjiowMDvUy"
FirebaseData firebaseData;

int fbCounter = 0;

/*--Adafruit connection--*/
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "AndyDevNL"
#define AIO_KEY         "e44c4f9bff1e466dad90c65e7d161ee8"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");


/*--Student Info--*/
String studentNumber = "0876986";
String studentFirstName = "Andreas";
String studentLastName = "Sharoubim";
String studentAdress = "Roffaboi 42069";

/*--Meta-data--*/
float longitude = 4.445320;
float latitude = 51.916860;

/*--LIBRARIES--*/
// LCD Libraries
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

// DHT Libraries
#include <DHT.h>
#include <Adafruit_Sensor.h>

/*--VARIABLES--*/
// LCD Variables
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x3f, lcdColumns, lcdRows);


// DHT Variables
#define DHTPIN D3     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

float temp = 0;
float hum = 0;
int timeSinceLastRead = 0;

DHT dht(DHTPIN, DHTTYPE);

// Reed Variables
const int REED_PIN = D4; // Pin connected to reed switch
// Changables
int reedSwitchCounter = 0;
int reedState = 0;
int lastReedState = 0;
float wind = 0;
int turbineRadius = 3;
int distance = 0;
int circum = 0;

// Flame Sensor
const int flamePin = D0;
int flameState = LOW;
int flameVal = 0;

/*--Actuators--*/
//Led setup
const int redPin = D8;
const int greenPin = D7;
const int bluePin = D6;

//Buzzer setup
int buzPin = D5;
int tempo = 300;

#include "pitches.h"
#include "songs.h"

int length = 15; // the number of notes

char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };

char fireSong[] = "cacacaca "; // a space represents a rest
int fireBeats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

char wifiSong[] = "efga "; // a space represents a rest
int wifiBeats[] = { 1, 1, 1, 1, 1 };

char dbSong[] = "efed "; // a space represents a rest
int dbBeats[] = { 1, 1, 1, 1, 1 };

/*--Run Script Setup--*/
void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();

  // initialize Buzzer
  pinMode(buzPin, OUTPUT);

  // initialize RGB Led
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // initialize Serial
  Serial.begin(9600);

  // initialize Wifi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    lcd.setCursor(0, 1);
    RGB_color(0, 0, 255); // Blue
    startBuzzer("Wifi");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  lcd.setCursor(0, 0);
  lcd.print("Con with IP:   ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  // intialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  lcd.clear();
  RGB_color(255, 0, 0); // Red
  lcd.print("Firebase Init");
  Firebase.reconnectWiFi(true);

  // initialize DHT
  dht.begin();

  // initialize adafruit on/off
  mqtt.subscribe(&onoffbutton);
  lcd.clear();
  lcd.print("Starting");
  lcd.setCursor(0, 1);
  lcd.print("Weatherstation!");
}

/*--Run Script Loop--*/
void loop() {
  MQTT_connect();
  if (fbCounter < 1000) {
    RGB_color(0, 255, 0); // Green
    getFlame();
    while (flameVal != HIGH) {
      RGB_color(255, 0, 0); // Red
      startBuzzer("Fire");
      delay(0);
      flameVal = digitalRead(flamePin);
    }
    getDHT();
    getRPM();
    setDisplay();
    if (temp > 50) {
      startBuzzer("Fire");
    }
    fbCounter += 100;
  }
  else {
    RGB_color(255, 0, 255); // Magenta
    setupFirebaseData();
    fbCounter = 0;
  }
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(2000))) {
    RGB_color(255, 255, 0); // Yellow    
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      lcd.clear();
      lcd.print("Happy Song!");
      startBuzzer("Song");
    }
  }
}

void getFlame() {

  flameVal = digitalRead(flamePin);

  // print out the value you read:
  if (flameVal != HIGH) {
    if (flameState == LOW) {
      Serial.println("Flame Detected");
      flameState = HIGH;
      lcd.clear();
      lcd.print("Fire Detected!");
    }
  }
  else {
    if (flameState == HIGH) {
      Serial.println("Flame turned off");
      flameState = LOW;
      lcd.clear();
      lcd.print("Flame turned off");
    }
  }
}

void setDisplay() {
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C");
  lcd.print(" H:");
  lcd.print(hum);
  lcd.print("%");
  // clears the display to print new message
  // set cursor to first column, second row
  lcd.setCursor(0, 1);
  lcd.print("Windspd:");
  lcd.print(wind);
  lcd.print("m/s");
}

void getDHT() {
  if (timeSinceLastRead > 500) {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    hum = dht.readHumidity();
    // Read temperature as Celsius (the default)
    temp = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }

    // Compute heat index in Fahrenheit (the default)
    //    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(temp, hum, false);

    Serial.println("Humidity: ");
    Serial.print(hum);
    Serial.print(" %\t");
    Serial.println("Temperature: ");
    Serial.print(temp);
    Serial.print(" *C ");

    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}

void getRPM() {
  int windspeedRead = 0;
  while(windspeedRead < 10000) {
    static long now = millis();
    reedState = digitalRead(REED_PIN);
  
    if (reedState != lastReedState) {
      if (reedState == LOW) {
        reedSwitchCounter++;
      }
    }
    if (millis() > now + 10000) {
      Serial.println("number of rotations");
      Serial.println(reedSwitchCounter);
      circum = turbineRadius * 3.15;
      distance = reedSwitchCounter * circum;
      wind = distance / 10;
      reedSwitchCounter = 0;
      now = millis();
    }
    lastReedState = reedState;
    windspeedRead += 100;
  }
}

void startBuzzer(String medleyType) {
  if (medleyType == "Fire") {
    tempo = 300;
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(fireSong[i], fireBeats[i] * tempo);
        RGB_color(255, 0, 0); // Red
        RGB_color(0, 0, 0); // Red
      }

      // pause between notes
      delay(tempo / 2);
    }
  }
  if (medleyType == "Song") {
    tempo = 120;
    FurElise();
//      tempo = 90;
//      MarioMain();
//    for (int i = 0; i < length; i++) {
//      if (notes[i] == ' ') {
//        delay(beats[i] * tempo); // rest
//      } else {
//        playNote(notes[i], beats[i] * tempo);
//      }
//
//      // pause between notes
//      delay(tempo / 2);
//    }
  }
  if (medleyType == "Data") {
    tempo = 300;
    for (int i = 0; i < length; i++) {
      if (dbSong[i] == ' ') {
        delay(dbBeats[i] * tempo); // rest
      } else {
        playNote(dbSong[i], dbBeats[i] * tempo);
      }

      // pause between notes
      delay(tempo / 2);
    }
  }
  if (medleyType == "Wifi") {
    tempo = 300;
    for (int i = 0; i < length; i++) {
      if (wifiSong[i] == ' ') {
        delay(wifiBeats[i] * tempo); // rest
      } else {
        playNote(wifiSong[i], wifiBeats[i] * tempo);
      }

      // pause between notes
      delay(tempo / 2);
    }
  }  
}

void setupFirebaseData() {
  sendString("today", studentNumber + "-stream-data/meta-data/date");
  sendFloat(latitude, studentNumber + "-stream-data/meta-data/latitude");
  sendFloat(longitude, studentNumber + "-stream-data/meta-data/longitude");
  sendString("right now", studentNumber + "-stream-data/meta-data/time");
  sendFloat(hum, studentNumber + "-stream-data/sensor-data/humidity");
  sendFloat(temp, studentNumber + "-stream-data/sensor-data/temperature");
  sendFloat(wind, studentNumber + "-stream-data/sensor-data/windspeed");

  //  sendString("Soil humidity", studentNumber + "-stream-data/sensor-data/unique-
  //  sensor/sensor-type");

  //  sendFloat(0, studentNumber + "-stream-data/sensor-data/unique-sensor/sensor-
  //  value");

  sendString(studentFirstName, studentNumber + "-stream-data/student-data/first-name");

  sendString(studentNumber, studentNumber + "-stream-data/student-data/student-number");
  sendString(studentAdress, studentNumber + "-stream-data/student-data/adress");

  //  sendString("https://joshuanc.com", studentNumber + "-stream-data/student-
  //  data/website");
  Serial.println("data sent");
  lcd.clear();
  lcd.print("Firebase Sent");
//  startBuzzer("Data");
}

void sendString(String value, String path) {
  if (Firebase.setString(firebaseData, path, value)) {
    //  Serial.println(path);
    //  Serial.println("Data sent.");
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}

void sendFloat(float value, String path) {
  if (Firebase.setFloat(firebaseData, path, value)) {
    //  Serial.println(path);
    //  Serial.println("Data sent.");
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void RGB_color(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
