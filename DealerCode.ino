// Card dealer code

#include <Arduino.h>

// define macros
#define MAXPLAYERS 8

#define STEPPER_PIN_1 14 // To driver IN 1
#define STEPPER_PIN_2 12 // To driver IN 2
#define STEPPER_PIN_3 13 // To driver IN 3
#define STEPPER_PIN_4 15 // To driver in 4

// define global variables
bool deal = 0;

enum Games {
    POKER, // 0
    BLACKJACK, // 1
    GOFISH // 2
};

void setup(){
    Serial.begin(115200);
    pinMode(STEPPER_PIN_1, OUTPUT);
    pinMode(STEPPER_PIN_2, OUTPUT);
    pinMode(STEPPER_PIN_3, OUTPUT);
    pinMode(STEPPER_PIN_4, OUTPUT);
}

void loop(){
    // wait for a request to deal
    if(deal){
        // get amount of people being dealed in
        int players = getPlayers();
        if(players > MAXPLAYERS){
            deal = 0;
            Serial.println("Invalid player number!");
        } else {
            int cardsDealt, rounds;
            switch(getGame()){
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
                    step();
                }
            }
        }

    }
}

// temp functions to avoid errors

int getGame(){ return 0; }

int getPlayers(){ return 7; }

/*
Function will be used to rotate the stepper motor
*/
void step(){
    // rotate stepper motor once
}

/*
Function will be used to deal one card
*/
void dealCard(){
    // spin dc gear motor once
}