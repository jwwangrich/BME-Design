//#define PUBLISH_DELAY 150000    //2.5 min b/w variable publish
#define FLASH_RATE_HZ 2
//#define BUTTON_IN 2
//#define PWM_LED_OUT 10
// use preprocessor directives to define constants in the code
//#define PWM_MAX 255

// global variables representing "state" across all functions
//operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3- dim, 4- flash
const int BUTTON_IN = 2;
int BUTTON_PUSHED = 0;
const int PWM_LED_OUT = 10;
int PWM_MAX = 255;
//int button_pushed = 1;
int operating_mode = 0;
int previous_button_state = 0;
int PWM_OUT = 0;
int ledState = LOW;
unsigned long previousMillis = 0;


void setup() {
  Serial.begin(9600);

  pinMode(PWM_LED_OUT, OUTPUT);
  pinMode(BUTTON_IN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, FALLING);
//define output(PWM) pin connected to LED
}

void loop() {

  //Serial.begin(9600);

  check_button_press();

  set_pwm_based_on_operating_mode();

  //shine_led();

}


void set_pwm_based_on_operating_mode() {

    switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
            digitalWrite(PWM_LED_OUT, LOW);
            break;
        case 1:
            PWM_OUT = PWM_MAX;
            shine_led();
            break;
        case 2:
            PWM_OUT = int(PWM_MAX/2);
            shine_led();
            break;
        case 3:
            PWM_OUT = int(PWM_MAX/4);
            shine_led();
            break;
        case 4:
            flash_the_light();
            break;
    }

}


void button_pushed(){
  BUTTON_PUSHED = 1;
}

void flash_the_light(){
  int interval = 1000/(FLASH_RATE_HZ);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(PWM_LED_OUT, ledState);
  }

}

void shine_led() {
  Serial.print(operating_mode);

  delay(100);
  analogWrite(PWM_LED_OUT, PWM_OUT);

}

void check_button_press() {
    if (BUTTON_PUSHED == 1) {
        //operating_mode = operating_mode + 1;
        if (operating_mode == 4) {
            operating_mode = 0;
        }
        else {
          operating_mode = operating_mode + 1;
        }
    }
    BUTTON_PUSHED = 0;
}
