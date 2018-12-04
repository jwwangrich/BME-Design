#define FLASH_RATE 2
#define BUTTON_IN 1
#define PWM_LED_OUT 11
#define BATT_CHECK_INPUT A0
#define BATT_CHECK_BUTTON 8
#define BATT_LED_1 5
#define BATT_LED_2 6
#define BATT_LED_3 7

// operating_mode: 0 - off, 1 - bright, 2 - mid, 3 - dim, 4 - flash
int operating_mode = 0;
int BUTTON_PUSHED = 0;
int previous_button_state = 0;
int PWM_OUT = 0;
int LED_STATE = LOW;
int PWM_MAX = 255;
int BATT_BUTTON_PUSHED = 0;
int voltage = 0;
int previousMillis = 0;
int currentMillis = 0;

void setup() {

  Serial.begin(9600);

  pinMode(BUTTON_IN, INPUT);
  pinMode(BATT_CHECK_BUTTON, INPUT);
  pinMode(PWM_LED_OUT, OUTPUT);
  pinMode(BATT_LED_1, OUTPUT);
  pinMode(BATT_LED_2, OUTPUT);
  pinMode(BATT_LED_3, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, FALLING);
  //attachInterrupt(BATT_CHECK_BUTTON, batt_button_pushed, FALLING);
}

void loop() {

  Serial.print(BUTTON_PUSHED);

  check_button_press();
  operating_mode_switch();

  if (digitalRead(BATT_CHECK_BUTTON)==HIGH){
    check_battery_button();
  }

}


void operating_mode_switch(){
switch (operating_mode) {
    case 0:
      digitalWrite(PWM_LED_OUT, LOW);
      break;
    case 1:
      PWM_OUT = PWM_MAX;
      shine_led();
      break;
    case 2:
      PWM_OUT = int(PWM_MAX/3);
      shine_led();
      break;
    case 3:
      PWM_OUT = int(PWM_MAX/8);
      shine_led();
      break;
    case 4:
      flash_the_light();
      break;
  }
}

void flash_the_light() {
  int period = 1000/(FLASH_RATE * 2);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= period) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (LED_STATE == LOW) {
      LED_STATE = HIGH;
    } else {
      LED_STATE = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(PWM_LED_OUT, LED_STATE);
  }
}

void shine_led(){
  analogWrite(PWM_LED_OUT, PWM_OUT);
}

void battery_indicator(float voltage){

  if(voltage > 8 ){
    digitalWrite(BATT_LED_1, HIGH);
    digitalWrite(BATT_LED_2, HIGH);
    digitalWrite(BATT_LED_3, HIGH);
  }
  if (voltage <= 8 && voltage > 6.5){
    digitalWrite(BATT_LED_1, HIGH);
    digitalWrite(BATT_LED_2, HIGH);
  }
  if (voltage <= 6.5 && voltage > 0){
    digitalWrite(BATT_LED_1, HIGH);
  }

}

void check_button_press() {
  if (BUTTON_PUSHED == 1){
      Serial.print("bye");
    if (operating_mode == 4){
      operating_mode = 0;
    }
    else{
      operating_mode = operating_mode + 1;
    }
  }
  BUTTON_PUSHED = 0;
}

void check_battery_button() {
   Serial.print("hi");
 // if (BATT_BUTTON_PUSHED == 1){
    unsigned int sensorValue = analogRead(BATT_CHECK_INPUT); //read the A0 pin value
    float voltage = sensorValue * (5.00 / 1023.00) * 2; //convert the value to a true voltage.
    Serial.print(voltage);
    battery_indicator(voltage);
    delay(2000); // battery indicator on for only 2 seconds

    digitalWrite(BATT_LED_1, LOW);
    digitalWrite(BATT_LED_2, LOW);
    digitalWrite(BATT_LED_3, LOW);
  //  BATT_BUTTON_PUSHED = 0;
  // }
}

void button_pushed() {
  BUTTON_PUSHED = 1;
}

void batt_button_pushed(){
  BATT_BUTTON_PUSHED = 1;
}
