#include <FirebaseESP8266.h>

#define FIREBASE_HOST "smart-things-2019.firebaseio.com"
#define FIREBASE_AUTH "pHkVlRIa1jZMe6VLEyOycXYEd850xDGjiowMDvUy"
FirebaseData firebaseData;

setupFirebaseData();
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
lcd.clear();
RGB_color(255, 0, 0); // Red
lcd.print("Firebase Init");
Firebase.reconnectWiFi(true);

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
