#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX (for fingerprint sensor)
SoftwareSerial bluetooth(10, 11); // RX, TX (for Bluetooth module)

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int greenLED = 8;
int studentID;
String studentName;

void setup() {
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, LOW);

  Serial.begin(9600);
  bluetooth.begin(9600);
  finger.begin(57600);

  delay(1000);
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found.");
  } else {
    Serial.println("Fingerprint sensor not found. Check wiring!");
    while (1);
  }

  Serial.println("<<<><<=== YUSMU IT Student Fingerprint Enroll ===>><>>>");
  Serial.println("Choose option: 1. Enroll NewStudent Fingerprint  2. Verify Student Fingerprint");
}

void loop() {
  if (Serial.available()) {
    char option = Serial.read();

    if (option == '1') {
      enrollFingerprint();
    } else if (option == '2') {
      verifyFingerprint();
    }
  }
}

void enrollFingerprint() {
  Serial.println("Choose the Student ID from (1-150) :");
  while (Serial.available() == 0); 
  studentID = Serial.parseInt();   
  Serial.read(); 

  Serial.println("Enter the Student Name:");
  while (Serial.available() == 0); 
  studentName = Serial.readStringUntil('\n');
  studentName.trim(); 

  Serial.println("Place the student finger to enroll...");
  while (!getFingerprintEnroll());

  Serial.print(studentName);
  Serial.println(" successfully enrolled and sent to Bluetooth.");

  bluetooth.println(studentName);

  for (int i = 0; i < 3; i++) {
    digitalWrite(greenLED, HIGH);
    delay(200);
    digitalWrite(greenLED, LOW);
    delay(200);
  }

  Serial.println("<<<><<=== YUSMU IT Fingerprint Enrollment Done ===>><>>>");
  Serial.println("Choose option: 1. Enroll NewStudent Fingerprint  2. Verify Student Fingerprint");
}

void verifyFingerprint() {
  Serial.println("Place the Student finger to verify...");
  int result = finger.getImage();

  if (result != FINGERPRINT_OK) {
    Serial.println("Could not read finger. Try again.");
    return;
  }

  result = finger.image2Tz();
  if (result != FINGERPRINT_OK) {
    Serial.println("Failed to convert image.");
    return;
  }

  result = finger.fingerSearch();
  if (result == FINGERPRINT_OK) {
    Serial.println("The student finger was enrolled before.");
  } else {
    Serial.println("Student finger is not enrolled.");
  }

  Serial.println("<<<><<=== YUSMU IT Fingerprint System Ready ===>><>>>");
  Serial.println("Choose option: 1. Enroll NewStudent Fingerprint  2. Verify Student Fingerprint");
}

bool getFingerprintEnroll() {
  int p = -1;
  Serial.println("Waiting for valid Student finger...");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) return false;

  Serial.println("Remove finger...");
  delay(2000);
  while (finger.getImage() != FINGERPRINT_NOFINGER);

  Serial.println("Place the same Student finger again...");
  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) return false;

  p = finger.createModel();
  if (p != FINGERPRINT_OK) return false;

  p = finger.storeModel(studentID);
  if (p == FINGERPRINT_OK) return true;
  else return false;
}
