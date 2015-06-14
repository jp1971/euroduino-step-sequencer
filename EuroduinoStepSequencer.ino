/*
    Telekinetic
                   n
        |\   |  or
       _| \-/ic
      /    un
    //    ~ + \
   //         |
  //    \      \
 |||     | .  .|
///     / \___/

*/

/* Euroduino Step Sequencer - 06/07/15
 * ---------------------------------------
 * TKTKTKTK
 */

/*  Copyright 2015 JP1971 (jameson@jp1971.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

// These constants won't change.  They're used to give names
// to the pins used:
const int analogIn1Pin = A0;  // Analog Input 1
const int analogIn2Pin = A1; // Analog Input 2
const int analogPot1Pin = A2;  // Pot 1
const int analogPot2Pin = A3; // Pot 2
const int analogOut1Pin = 5;  // Analog Output 1
const int analogOut2Pin = 6; // Analog Output 2
const int DigitalIn1Pin = 8;  // Digital Input 1
const int DigitalIn2Pin = 9;  // Digital Input 2
const int DigitalOut1Pin = 3;  // Digital Output 1
const int DigitalOut2Pin = 4;  // Digital Output 2
const int Switch1Up = A4;  // Switch 1 Up
const int Switch1Dwn = A5;  // Switch 1 Dwn
const int Switch2Up = 7;  // Switch 2 Up
const int Switch2Dwn = 2;  // Switch 2 Dwn

// Declare variables
int v1 = 0;
int v2 = 0;
int v3 = 0;
int v4 = 0;
int v5 = 0;
int v6 = 0;
int v7 = 0;
int v8 = 0;
int previousState = 0;
int currentState = 0;
int step = 1;

void setup() {
  /* Set up I/O pins */
  pinMode( DigitalIn1Pin, INPUT );
  pinMode( DigitalIn2Pin, INPUT );
  pinMode( DigitalOut1Pin, OUTPUT );
  pinMode( DigitalOut2Pin, OUTPUT );
  pinMode( Switch1Up, INPUT_PULLUP );
  pinMode( Switch1Dwn, INPUT_PULLUP );
  pinMode( Switch2Up, INPUT_PULLUP );
  pinMode( Switch2Dwn, INPUT_PULLUP );
  Serial.begin(9600);
}

void loop() {

  currentState = digitalRead( DigitalIn1Pin );

  if ( analogRead( analogPot1Pin ) > 511 ) {
    if ( digitalRead( Switch1Up ) == LOW) {
      if ( digitalRead( Switch2Up ) == LOW) {
        v1 = analogRead( analogPot2Pin );
        v1 = map( v1, 0, 1023, 255, 0 );
        analogWrite( analogOut1Pin, v1 );
      } else if ( digitalRead( Switch2Dwn ) == LOW ) {
        v2 = analogRead( analogPot2Pin );
        v2 = map( v2, 0, 1023, 255, 0 );
        analogWrite( analogOut1Pin, v2 );
      } else {
        v3 = analogRead( analogPot2Pin );
        v3 = map( v3, 0, 1023, 255, 0 );
        analogWrite( analogOut1Pin, v3 );
      }
    }
  } else {
    if ( currentState == 1 && previousState == 0 ) {
      if ( step == 1 ) {
        analogWrite( analogOut1Pin, v1 );
        previousState = 1;
        step = 2;
      } else if ( step == 2 ) {
        analogWrite( analogOut1Pin, v2 );
        previousState = 1;
        step = 3;
      } else if ( step == 3 ) {
        analogWrite( analogOut1Pin, v3 );
        previousState = 1;
        step = 1;
      }
    } else if ( currentState == 0 && previousState == 1 ) {
      previousState = 0;
    }
  }
}
