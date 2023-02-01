// PRESS RESET TO START A NEW GAME
// Eletronic componenets: 3 x switches; 1 x buzzer, 1 x RGB LED, 3 x 300 OHM resistors 

#include "pitches.h"
// The game has a total of 10 rounds
// Random generated sequence array
int random_seq[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int pre_sizes[] = {3,4,5,6,7};
int random_size = 0;
int match = 0; // Gives the final music
int choice = 0; // Stores the user´s input
// Variables for game speeding time
int x = 0; // subtracts time for perception
int counter_round = 0;
// 
void setup() {
  // LEDs setup
  randomSeed(analogRead(0));
  pinMode(1, OUTPUT); // RED
  pinMode(2, OUTPUT); // GREEN
  pinMode(3, OUTPUT); // BLUE
  // Buzzer setup
  pinMode(4, OUTPUT);
  //Switches setup
  pinMode(5, INPUT_PULLUP); // RED switch
  pinMode(6, INPUT_PULLUP); // GREEN switch
  pinMode(7, INPUT_PULLUP); // BLUE switch
}

void loop() {
     // Blink white light 2 times every new start
     digitalWrite(1, HIGH);
     digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     delay(300);
     digitalWrite(1, LOW);
     digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     delay(300);
     digitalWrite(1, HIGH);
     digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     delay(300);
     digitalWrite(1, LOW);
     digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     delay(300);
    // Giving a random size to the random sequence:
    // if is the first 7 rounds, take it easy ( it´s good to do not have a 10 size sequence, so we have a pre defined sequence
    // Then that will be random
    if (counter_round < 6)
    {
      random_size = pre_sizes[counter_round - 1];
    }
    else
    {
      random_size = random(3, 11);
    }
    for (int i = 0; i < random_size; i++)
    {
      random_seq[i] = random(1, 4);
      // Making sound and color to the new random sequence
      // if RED, or GREEN, or BLUE in order:
      if (random_seq[i] == 1)
      {
        digitalWrite(1, HIGH);
        tone(4, NOTE_C4);
      }
      else if (random_seq[i] == 2)
      {
        digitalWrite(2, HIGH);
        tone(4, NOTE_E4);
      }
      else if (random_seq[i] == 3)
      {
        digitalWrite(3, HIGH);
        tone(4, NOTE_G4);
      }
      delay(1000 - x);
      digitalWrite(1, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      noTone(4);
      delay(100);
    }
    // Checking sequence by matchin user´s input
    for (int i = 0; i < random_size; i ++)
    {
      int break_while_loop = 0;
      // Do nothing while user didn´t press anything
      while (break_while_loop == 0)
      {
        if (digitalRead(5) == LOW || digitalRead(6) == LOW || digitalRead(7) == LOW)
        {
          // Storing user´s input
          if (digitalRead(5) == LOW)
          {
            choice = 1;
          }
          else if (digitalRead(6) == LOW)
          {
            choice = 2;
          }
          else if (digitalRead(7) == LOW)
          {
            choice = 3;
          }
          break_while_loop = 1;
        }
      }
      
      // Checking if user´s choice matches
      if (random_seq[i] == choice)
      {
          if (random_seq[i] == 1)
          {
            digitalWrite(1, HIGH);
            tone(4, NOTE_C4);
          }
          else if (random_seq[i] == 2)
          {
            digitalWrite(2, HIGH);
            tone(4, NOTE_E4);
          }
          else if (random_seq[i] == 3)
          {
            digitalWrite(3, HIGH);
            tone(4, NOTE_G4);
          }
          delay(600);
          digitalWrite(1, LOW);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          noTone(4);
          delay(150);
          // Adding to match variable
          match++;
      }
      else {
        for (int j = 0; j < 50; j ++) {
          tone(4, 234);
          tone(4, 100);
          tone(4, 233);
          tone(4, 322);
          delay(10);
        }
        break;
      }
    }
    // If Victory, plays victory themes
    if (match == random_size || counter_round == 12)
    {
      // Plays definetely Victory´s theme
      if (counter_round == 10)
      {
        delay(500);
        tone(4, NOTE_C4);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_E4);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_G4);
        digitalWrite(1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(125);
        tone(4, NOTE_C5);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_E5);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_G5);
        digitalWrite(1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(125);
        tone(4, NOTE_C6);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        delay(500);
        tone(4, NOTE_D4);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_F4);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(125);
        tone(4, NOTE_A4);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        delay(125);
        tone(4, NOTE_D5);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_F5);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(125);
        tone(4, NOTE_A5);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_D6);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(500);
        tone(4, NOTE_F4);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        delay(125);
        tone(4, NOTE_A4);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_C5);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_F5);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_A5);
        digitalWrite(1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(125);
        tone(4, NOTE_C6);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        delay(125);
        tone(4, NOTE_F6);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        delay(200);
        tone(4, NOTE_C6);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(300);
        tone(4, NOTE_D6);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        delay(700);
        noTone(4);
        delay(80);
        tone(4, NOTE_C6);
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(125);
        for (int i = 0; i < 16; i ++)
        {
          tone(4, NOTE_C6);
          digitalWrite(1, HIGH);
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(1, LOW);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          noTone(4);
          delay(50);
        }
        exit(0);
      }
      // Little victory theme, but not game-over yet
      tone(4, NOTE_C4);
      delay(125);
      tone(4, NOTE_E4);
      delay(125);
      tone(4, NOTE_G4);
      delay(125);
      tone(4, NOTE_C5);
      delay(125);
      tone(4, NOTE_E5);
      delay(125);
      tone(4, NOTE_G5);
      delay(125);
      tone(4, NOTE_C6);
      delay(600);
      // Adding 5 to x
      x += 60;
      // Restart counter
      match = 0;
      // Counting round
      counter_round++;
      random_size = 0;
    }
    // Else: play Failure Music then exit program
    else if (match != random_size){
      tone(4, NOTE_E4);
      delay(750);
      noTone(4);
      delay(50);
      tone(4, NOTE_DS4);
      delay(543);
      noTone(4);
      delay(50);
      tone(4, NOTE_D4);
      delay(150);
      // Creepy vibrato effect
      for (int k = 0; k < 36; k++)
      {
        tone(4, NOTE_D4);
        delay(10);
        noTone(4);
        delay(10);
      }
      noTone(4);
      exit(1);
    }
  
}