//arduino

#define PUBLISH_DELAY 150000    //2.5 min b/w variable publish


#define FLASH_RATE_HZ 2
#define BUTTON_IN D1
#define PWN_LED_OUT D11


//operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3- dim, 4- flash
int BUTTON_PUSHED = 0;
bool button_pushed = TRUE;
int operating_mode = 0;
int previous_button_state = 0;
int PWM_OUT = 0;

void setup() {
attachInterrupt(BUTTON_IN, button_pushed, FALLING);
//define output(PWM) pin connected to LED

}

void loop() {
check_button_press();

set_pwm_based_on_operating_mode();

switch (operating_mode){
  case 0:
    PWM_OUT = 0;
  case 1:
    PWM_OUT = PWM_MAX //255;
  case 2:
    PWM_OUT = int (PWM_MAX/2) //128;
  case 3:
    PWM_OUT = int (PWM_MAX/4); //64;
  case 4:
    flash_the_light();

}

shine_led(PWM_OUT) {

}

void button_pushed(){
BUTTON_PUSHED = 1;
# BUTTON_PUSHED = TRUE;

}

void flash_the_light(){


}


void shine_led(PWM_OUT) {
  digitalOutput(magic_in_here);

}

check_button_press(){
//set operating mode
// reset previous button press state, interrupt catch, etc..

}
