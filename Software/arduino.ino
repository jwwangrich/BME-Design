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

void setup() {
  pinMode(D2, INPUT);
  pinMode(D10, OUTPUT);
  attachInterrupt(BUTTON_IN, button_pushed, FALLING);
//define output(PWM) pin connected to LED
}

void loop() {
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


}


void shine_led(PWM_OUT) {
  digitalOutput(magic_in_here);

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
