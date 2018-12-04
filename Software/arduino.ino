//arduino

#define PUBLISH_DELAY 150000    //2.5 min b/w variable publish


#define FLASH_RATE_HZ 2
#define BUTTON_IN D1
#define PWN_LED_OUT D11
// use preprocessor directives to define constants in the code
#define PWM_MAX 255

// global variables representing "state" across all functions
//operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3- dim, 4- flash
int BUTTON_PUSHED = 0;
bool button_pushed = TRUE;
int operating_mode = 0;
int previous_button_state = 0;
int PWM_OUT = 0;
int ledState = LOW;
unsigned long previousMillis = 0;






void setup() {
  pinMode(D2, INPUT);
  pinMode(D10, OUTPUT);
  attachInterrupt(BUTTON_IN, button_pushed, FALLING);
//define output(PWM) pin connected to LED
}

void loop() {

  unsigned long currentMillis = millis();

  Serial.begin(9600);

  check_for_button_press();

  set_pwm_based_on_operating_mode();

  shine_led();

}


void set_pwm_based_on_operating_mode() {

    switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
            break;
        case 1:
            PWM_OUT = PWM_MAX;
            break;
        case 2:
            PWN_OUT = int(PWM_MAX/2);
            break;
        case 3:
            PWN_OUT = int(PWM_MAX/4);
            break;
        case 4:
            flash_the_light();
            break;
    }

}


void button_pushed(){
//BUTTON_PUSHED = 1;
  BUTTON_PUSHED = TRUE;
//void button_pushed() {
//    BUTTON_PUSHED = true;
}

void flash_the_light(){
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
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
    digitalWrite(ledPin, ledState);
  }

}


void shine_led() {
  Serial.print(operating_mode);

  delay(100);
  analogWrite(PWM_LED_OUT, outputPWM);

}
//void shine_led() {
//    analogWrite(PWM_LED_OUT, PWM_OUT);
//}

void check_button_press() {
    if (BUTTON_PUSHED == true) {
        operating_mode = operating_mode + 1;
        if (operating_mode == 5) {
            operating_mode = 0;
        }
    }

    BUTTON_PUSHED = false
}
