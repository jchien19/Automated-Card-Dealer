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

byte prevState = 1;

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
        Serial.println("2 players");
        lcd.clear();
        lcd.drawString(0, 0, "2 players");
        lcd.display();

        startDeal(2);
    }else if(!b1){
        Serial.println("3 players");
        lcd.clear();
        lcd.drawString(0, 0, "3 players");
        lcd.display();

        startDeal(3);
    } else if(!b2){
        Serial.println("4 players");
        lcd.clear();
        lcd.drawString(0, 0, "4 players");
        lcd.display();

        startDeal(4);
    }

    // if(!b0 && prevState){
    //     Serial.println("Poker");
    //     lcd.clear();
    //     lcd.drawString(0, 0, "Poker");
    //     lcd.display();

    //     startDeal(getPlayers(), 0);
    // } else if(!b1 && prevState){
    //     Serial.println("Blackjack");
    //     lcd.clear();
    //     lcd.drawString(0, 0, "Blackjack");
    //     lcd.display();

    //     startDeal(getPlayers(), 1);
    // } else if(!b2 && prevState){
    //     Serial.println("Gofish");
    //     lcd.clear();
    //     lcd.drawString(0, 0, "Gofish");
    //     lcd.display();

    //     startDeal(getPlayers(), 2);
    // }
    // prevState = 1;
}

// temp function to avoid errors
int getPlayers(){ 
    // return 2 for now
    return 4;
}

/*
Function will be used to deal cards
*/
void startDeal(int players){
    switch(players){
        case 2:
            for(int k = 0; k < 2; k++){
                for(int i = 0; i < 2; i++){
                    dealCard();
                    delay(1000);
                    rotateBase2(0);
                }
            }
            break;
        case 3:
            for(int k = 0; k < 2; k++){
                for(int i = 0; i < 3; i++){
                    dealCard();
                    delay(1000);
                    rotateBase3(0);
                }
            }
            break;
        case 4:
            for(int k = 0; k < 2; k ++){
                for(int i = 0; i < 4; i++){
                    dealCard();
                    delay(1000);
                    rotateBase4(0);
                }
            }
            break;
        default:
            break;
    }
    // if(players > MAXPLAYERS){
    //     Serial.println("Invalid player number!");
    // } else {
    //     int cardsDealt, rounds;
    //     switch(game){
    //         case POKER:
    //             rounds = 2;
    //             cardsDealt = 1;
    //             break;
    //         case BLACKJACK:
    //             rounds = 1;
    //             cardsDealt = 2;
    //             break;
    //         case GOFISH:
    //             rounds = 1;
    //             cardsDealt = 7;
    //             break;
    //         default:
    //             Serial.println("Unkown game!");
    //             break;
    //     }
        
    //     // deal cards for specific game
    //     for(int r = 0; r < rounds ; r++){
    //         for(int i = 0; i < players; i++){
    //             for(int c = 0; c < cardsDealt; c++){
    //                 // delay(500);
    //                 dealCard();
    //                 Serial.println("dealt");
    //                 delay(1000);
    //             }
    //             if(i < players - 1){
    //                 // rotateBase(0);
    //                 rotateBase(1);
    //             }
    //         }
    //         // reset position back to 0
    //         for(int i = 0; i < players - 1; i++)
    //             rotateBase(1); // can change direction later
    //     }

    // }

    // for(int i = 0; i < players; i++){
    //     dealCard();
    //     rotateBase(0);
    // }
}

/*
Function to rotate base gear.
0 for counterclockwise rotation
1 for clockwise rotation
*/
void rotateBase(int dir){
    // setting l = 250 is about 1/2 a turn of the motor, 500 is about 1, etc
    for(int l = 0; l < 3200; l++){
        for(int k = 0; k < 4; k++){
            delay(2); // needs to stay at 2
            step(dir, k);
        }
    }
}

void rotateBase2(int dir){
    // setting l = 250 is about 1/2 a turn of the motor, 500 is about 1, etc
    for(int l = 0; l < 1600; l++){
        for(int k = 0; k < 4; k++){
            delay(2); // needs to stay at 2
            step(dir, k);
        }
    }
}

void rotateBase3(int dir){
    // setting l = 250 is about 1/2 a turn of the motor, 500 is about 1, etc
    for(int l = 0; l < 1067; l++){
        for(int k = 0; k < 4; k++){
            delay(2); // needs to stay at 2
            step(dir, k);
        }
    }
}

void rotateBase4(int dir){
    // setting l = 250 is about 1/2 a turn of the motor, 500 is about 1, etc
    for(int l = 0; l < 800; l++){
        for(int k = 0; k < 4; k++){
            delay(2); // needs to stay at 2
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
    Serial.println("Spun");
    // spin dc gear motor once
    // apply voltage to pin to open MOSFET
    analogWrite(MOTOR_PIN, MOTOR_ANALOG_VALUE);
    delay(125); // 150 
    analogWrite(MOTOR_PIN, LOW);
}