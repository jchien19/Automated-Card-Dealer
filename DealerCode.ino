// Card dealer code
#include <Arduino.h>
#include <macros.h>
#include <SSD1306Wire.h>

// define global variables

// store some games for now
enum Games {
    POKER, // 0
    BLACKJACK, // 1
    GOFISH // 2
};

SSD1306Wire lcd(0x3c, SDA, SCL);
void setup(){
    Serial.begin(115200);
    Serial.println("Starting");
    pinMode(STEPPER_PIN_1, OUTPUT);
    pinMode(STEPPER_PIN_2, OUTPUT);
    pinMode(STEPPER_PIN_3, OUTPUT);
    pinMode(STEPPER_PIN_4, OUTPUT);

    pinMode(BUTTON0, INPUT_PULLUP);
    pinMode(BUTTON1, INPUT_PULLUP); 
    pinMode(BUTTON2, INPUT_PULLUP);

    pinMode(MOTOR_PIN, OUTPUT);
    
    lcd.init();
    lcd.flipScreenVertically(); // flip the screen
    lcd.setFont(ArialMT_Plain_16);
    lcd.clear();                // clear screen
    lcd.drawString(0, 0, "Welcome!");
    lcd.display();
}

void loop(){
    // wait for a request to deal
    byte b0 = digitalRead(BUTTON0);
    byte b1 = digitalRead(BUTTON1);
    byte b2 = digitalRead(BUTTON2);

    if(!b0){
        Serial.println("Poker");
        lcd.clear();
        lcd.drawString(0, 0, "Poker");
        lcd.display();

        startDeal(getPlayers(), 0);
    } else if(!b1){
        Serial.println("Blackjack");
        lcd.clear();
        lcd.drawString(0, 0, "Blackjack");
        lcd.display();

        startDeal(getPlayers(), 1);
    } else if(!b2){
        Serial.println("Gofish");
        lcd.clear();
        lcd.drawString(0, 0, "Gofish");
        lcd.display();

        startDeal(getPlayers(), 2);
    }

}

// temp function to avoid errors
int getPlayers(){ 
    // will default to 2 if nothing is done
    return 2; // default
}

/*
Function will be used to deal cards
*/
void startDeal(int players, int game){
    if(players > MAXPLAYERS){
        Serial.println("Invalid player number!");
    } else {
        int cardsDealt, rounds;
        switch(game){
            case POKER:
                rounds = 2;
                cardsDealt = 1;
                break;
            case BLACKJACK:
                rounds = 1;
                cardsDealt = 2;
                break;
            case GOFISH:
                rounds = 1;
                cardsDealt = 7;
                break;
            default:
                Serial.println("Unkown game!");
                break;
        }
        
        // deal cards for specific game
        for(int r = 0; r < rounds ; r++){
            for(int i = 0; i < players; i++){
                for(int c = 0; c < cardsDealt; c++)
                    dealCard();
                rotateBase(0); // can change direction later
            }
            // reset position back to 0
            for(int i = 0; i < players; i++)
                rotateBase(1); // can change direction later
        }
    }
}

/*
Function to rotate base gear.
0 for counterclockwise rotation
1 for clockwise rotation
*/
void rotateBase(int dir){
    // setting l = 250 is about 1/2 a turn of the motor, 500 is about 1, etc
    for(int l = 0; l < 250; l++){
        for(int k = 0; k < 4; k++){
            // Serial.println("step value");
            delay(4);
            step(dir, k);
        }
    }
}

/*
Helper function for rotateBase, will be used to rotate the stepper motor
*/
void step(int dir, int rotNum){
    if(dir){
        switch(rotNum){
            case 0:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, HIGH);
                break;
            case 1:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, HIGH);
                digitalWrite(STEPPER_PIN_4, LOW);
                break;
            case 2:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, HIGH);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
                break;
            case 3:
                digitalWrite(STEPPER_PIN_1, HIGH);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
                break;
        }
    } else {
        switch(rotNum){
            case 0:
                digitalWrite(STEPPER_PIN_1, HIGH);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
                break;
            case 1:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, HIGH);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
                break;
            case 2:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, HIGH);
                digitalWrite(STEPPER_PIN_4, LOW);
                break;
            case 3:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, HIGH);
                break;
        }
    }
}

/*
Function will be used to deal one card
*/
void dealCard(){
    // spin dc gear motor once
    // apply voltage to pin to open MOSFET
    analogWrite(MOTOR_PIN, MOTOR_ANALOG_VALUE);
    // delay(0.2); // temp value
    analogWrite(MOTOR_PIN, 0);
}