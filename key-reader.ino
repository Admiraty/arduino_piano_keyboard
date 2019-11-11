// first note on my piano is A1, or in Midi : 33
const int FIRST_NOTE = 33;

// My piano has 16 outputs
const int ROWS = 16;

// My piano has 8 inputs
const int COLS = 8;

// The number of notes we support
const int NOTES = ROWS * COLS / 2;

// The number of buttons to find on the keyboard
const int BUTTONS = ROWS * COLS;

byte cols[COLS] = { 2,3,4,5,6,7,8,9 };
byte rows[ROWS] = { 22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37 } ;

// Conversion table between coordinates and notes
int notes[COLS][ROWS];

// When was the upper key pressed
long unsigned int times[ NOTES ];
long int buttons[ BUTTONS + 1];

void setup() {
     // put your setup code here, to run once:


     //Output to serial
          Serial.begin( 9600 );

     // Set the gain 3, because it sounds nicer on my computer
     Serial.println("gain 3");

     // Set all the button states to high 
     for ( int k = 0; k <= BUTTONS ; k++ )
     {
          buttons[k] = HIGH;
     }

     // setup outputs
     for ( int c = 0; c < COLS ; c++ )
     {
          pinMode( cols[c], OUTPUT );
          digitalWrite( cols[c], HIGH );
     }
     // setup inputs 
     for ( int r = 0; r < ROWS ; r++ )
     {
          pinMode( rows[r], INPUT_PULLUP );
     }

     // Conversion table because ( @todo : fix wiring so no lookup table is needed )  
     // This is where I pasted the output from calibrate
     int num = 0; 
     notes[2][6] = num++;
     notes[2][1] = num++;
     notes[0][6] = num++;
     notes[0][1] = num++;
     notes[5][6] = num++;
     notes[5][1] = num++;
     notes[1][6] = num++;
     notes[1][1] = num++;
     notes[4][6] = num++;
     notes[4][1] = num++;
     notes[3][6] = num++;
     notes[3][1] = num++;
     notes[7][6] = num++;
     notes[7][1] = num++;
     notes[6][6] = num++;
     notes[6][1] = num++;
     notes[2][3] = num++;
     notes[2][4] = num++;
     notes[0][3] = num++;
     notes[0][4] = num++;
     notes[5][3] = num++;
     notes[5][4] = num++;
     notes[1][3] = num++;
     notes[1][4] = num++;
     notes[4][3] = num++;
     notes[4][4] = num++;
     notes[3][3] = num++;
     notes[3][4] = num++;
     notes[7][3] = num++;
     notes[7][4] = num++;
     notes[6][3] = num++;
     notes[6][4] = num++;
     notes[2][5] = num++;
     notes[2][0] = num++;
     notes[0][5] = num++;
     notes[0][0] = num++;
     notes[5][5] = num++;
     notes[5][0] = num++;
     notes[1][5] = num++;
     notes[1][0] = num++;
     notes[4][5] = num++;
     notes[4][0] = num++;
     notes[3][5] = num++;
     notes[3][0] = num++;
     notes[7][5] = num++;
     notes[7][0] = num++;
     notes[6][5] = num++;
     notes[6][0] = num++;
     notes[2][7] = num++;
     notes[2][2] = num++;
     notes[0][7] = num++;
     notes[0][2] = num++;
     notes[5][7] = num++;
     notes[5][2] = num++;
     notes[1][7] = num++;
     notes[1][2] = num++;
     notes[4][7] = num++;
     notes[4][2] = num++;
     notes[3][7] = num++;
     notes[3][2] = num++;
     notes[7][7] = num++;
     notes[7][2] = num++;
     notes[6][7] = num++;
     notes[6][2] = num++;
     notes[2][13] = num++;
     notes[2][12] = num++;
     notes[0][13] = num++;
     notes[0][12] = num++;
     notes[5][13] = num++;
     notes[5][12] = num++;
     notes[1][13] = num++;
     notes[1][12] = num++;
     notes[3][13] = num++;
     notes[3][12] = num++;
     notes[7][13] = num++;
     notes[7][12] = num++;
     notes[6][13] = num++;
     notes[6][12] = num++;
     notes[4][13] = num++;
     notes[4][12] = num++;
     notes[2][14] = num++;
     notes[2][10] = num++;
     notes[0][14] = num++;
     notes[0][10] = num++;
     notes[5][14] = num++;
     notes[5][10] = num++;
     notes[1][14] = num++;
     notes[1][10] = num++;
     notes[3][14] = num++;
     notes[3][10] = num++;
     notes[7][14] = num++;
     notes[7][10] = num++;
     notes[6][14] = num++;
     notes[6][10] = num++;
     notes[4][14] = num++;
     notes[4][10] = num++;
     notes[2][15] = num++;
     notes[2][8] = num++;
     notes[0][15] = num++;
     notes[0][8] = num++;
     notes[5][15] = num++;
     notes[5][8] = num++;
     notes[1][15] = num++;
     notes[1][8] = num++;
     notes[3][15] = num++;
     notes[3][8] = num++;
     notes[7][15] = num++;
     notes[7][8] = num++;
     notes[6][15] = num++;
     notes[6][8] = num++;
     notes[4][15] = num++;
     notes[4][8] = num++;
     notes[2][9] = num++;
     notes[2][11] = num++;
     notes[0][9] = num++;
     notes[0][11] = num++;
     notes[5][9] = num++;
     notes[5][11] = num++;
     notes[2][9] = num++;
     notes[1][9] = num++;
     notes[1][11] = num++;
     notes[3][9] = num++;
     notes[3][11] = num++;
     notes[7][9] = num++;
     notes[7][11] = num++;
     notes[6][9] = num++;
     notes[6][11] = num++;
     notes[4][9] = num++;
     notes[4][11] = num++;
}

void loop() {

     // What state is the current button in
     int state ;

     // What is the current button
     int button;

     // What is the current note
     int note;

     for ( int c = 0; c < COLS ; c++ )
     {
          // Send signal onto the column c
          digitalWrite( cols[c], LOW );

          // Loop through each row
          for ( int r = 0; r < ROWS ; r++ )
          {
               // Read the state of the current row
               // @note I read some articles on the internet casting doubt on the speed of this function
               state = digitalRead( rows[ r ] ) ;

               // lookup button number
               button = notes[c][r];

               // check for state change, no change, move on
               if ( state == buttons[button] )
               {
                    continue;
               }

               // Note is half the button index rounded down to the nearest int
               note = button / 2;

               buttons[button] = state ;
               if ( state == LOW )
               {
                    // if the button is even ( evenly divisible by 2 ), it is the upper button, set the time in milliseconds
                    if ( button % 2 == 0 )
                    {
                         // Store the time as 1/100ths of a second
                         times[note] = micros() ;
                    }
                    else if ( times[note] == 0 )
                         ; // debounce
                    else
                    {
                         // Otherwise, if it's odd, it is the lower button that is being pressed, and therefore we must send the note on command
                         long int deltaT = micros() - times[note];

                         // m = -0.0007338
                         // m = 7338 / 10000000 ;

                         // b = 127;

                         // @note to future self : this is where you need to add a curve for a lighter touch
                         int velocity = max( min ( 127, -1 * deltaT * 7338 / 10000000 + 127 ), 1 );


                         // Fluid synth notation
                         Serial.print( "noteon 1 ");

                         // First note on my keyboard is note 33 ( A1 )
                         Serial.print( note + FIRST_NOTE );

                         Serial.print( " ");
                         Serial.println( velocity );
                         times[note] = 0;
                    }
               }
               else if ( button % 2 == 0 )
               {

                    Serial.print("noteoff 1 ");
                    Serial.print( FIRST_NOTE + note  );
                    Serial.println("");

               }
          }
     }

     // reset output pin
     digitalWrite( cols[c], HIGH  );
}
}
