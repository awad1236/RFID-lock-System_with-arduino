
#include <string.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>

#define SS_PIN 10
#define RST_PIN 9
const String UID = "73 6B 31 BE";
const String password = "6704";
byte lock = 1;

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

const byte rows[4] = { 5, 6, 7, 8 };
const byte cols[4] = { A0, A1, A2, A3 };
char keys[4][4] = {

  { 'D', 'C', 'B', 'A' },
  { '#', '9', '6', '3' },
  { '0', '8', '5', '2' },
  { '*', '7', '4', '1' },
};
byte klb[] = 
{
  B00000,
  B00000,
  B01010,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100
};

Keypad mykeypad = Keypad(makeKeymap(keys), rows, cols, 4, 4);
char ctr;
char ctr_wrong;
char time = 2;
String enteredPassword = "";
bool flag = true;
char i;
int pos=0;
bool flg=true;
String ID;
void setup() {

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    servo.attach(3);
    SPI.begin();
    rfid.PCD_Init();
    pinMode(4, OUTPUT);
    lcd.createChar(10, klb);
}

void loop() {
  if(flg)
  {
     for (pos = 10; pos <= 160; pos += 1) { 
    servo.write(pos);             
    delay(13);  
    flg=false;                     
  }
  }
  flag = true;
  lcd.setCursor(3, 0);
  lcd.print("Welcome");
  lcd.write(10);
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if (!rfid.PICC_IsNewCardPresent())  // if there are no card the program return
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  ID = "";
  read_card();
  time = 10;
  check_card();
}


void read_card() /*reading the id of the card*/
{
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();
}
void check_card() /*check if the card is the right one*/
{
  if (ID.substring(1) == UID && lock == 0) {
    look_door();
  } else if (ID.substring(1) == UID && lock == 1) {
    open_door();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    delay(1500);
    lcd.clear();
    ctr++;
    ctr_wrong = 0;

    while (ctr == 3) {
      e7ramy();
      lcd.clear();
      lcd.setCursor(0, 0);
      delay(500);
      lcd.print("Enter Password:");
      getPass();
      lcd.clear();
      check_pass();
      lcd.clear();
    }
  }
}
void open_door(void) { /*open door function*/
  for (pos = 160; pos >= 10; pos -= 1) { 
    servo.write(pos);              
    delay(13);                      
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Door is open");
  digitalWrite(4, 1);
  delay(40);
  digitalWrite(4, 0);
  delay(1500);
  lcd.clear();
  lock = 0;
  ctr = 0;
}
void look_door() { /*look door function*/
  for (pos = 10; pos <= 160; pos += 1) { 
    servo.write(pos);              
    delay(10);                   
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Door is locked");
  for (int i = 0; i < 2; i++) {
    digitalWrite(4, 1);
    delay(50);
    digitalWrite(4, 0);
    delay(150);
  }
  delay(1500);
  lcd.clear();
  lock = 1;
  ctr = 0;
}
void e7ramy() { /*Alarm bell function*/
 for (pos = 10; pos <= 160; pos += 1) { 
    servo.write(pos);         
    delay(13);                   
  }
  for (int i = time; i > 0; i--) {
    if (ctr_wrong != 3 && !flag) break;
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("emsk 7ramaaaaai");
    lcd.setCursor(7, 1);

    if (i < 10) {
      lcd.setCursor(8, 1);
      lcd.print(i);
      lcd.setCursor(7, 1);
      lcd.print(0);
    } else {
      lcd.print(i);
    }
    digitalWrite(4, 1);
    delay(500);
    digitalWrite(4, 0);

    lcd.clear();
    lcd.setCursor(0, 0);
    if (i == 1) {
      ctr_wrong = 0;
      flag = false;
    }
  }
}
void delet_char() { /*deleting last char of the user input using 'D'*/

  int length = enteredPassword.length();
  enteredPassword.remove(i - 1, 1);
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  i--;
  for (int j = 0; j < i; j++) {
    lcd.print('*');
  }
}
void getPass() { /*getting password from the user*/
  enteredPassword = "";
  i = 0;
  while (enteredPassword.length() < 4) {
    char key = mykeypad.getKey();
    if (key != NO_KEY) {
      digitalWrite(4, 1);
      delay(50);
      digitalWrite(4, 0);
      if (key == 'D') {
        delet_char();
        continue;
      }
      // if(key == 'A')break;
      enteredPassword += key;
      Serial.println(key);
      Serial.println(enteredPassword);
      lcd.setCursor(i, 1);
      i++;
      lcd.print("*");
    }
  }
}
void check_pass() { /*check if the password is correct or wrong*/
  if (enteredPassword == password) {

    lcd.print("Password Correct");
    delay(1500);
  open_door();
  } else {
    lcd.print("Wrong Password!");
    ctr_wrong++;
    delay(1500);
  }
}

