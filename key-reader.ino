const int ROWS = 8;
const int COLS = 8;
const int KEYS = 78;
byte rows[8] = { 22,24,26,28,30,32,34,36};
byte cols[8] = { 23,25,27,29,31,33,35,37 };

//byte cols[COLS] = { 29, 27, 25, 23 };
//byte rows[ROWS] = { 37, 35, 33, 31 };
int keys[KEYS + 1] ;
long int times[KEYS + 1] ;

int timer ;




int buttons[ROWS][COLS] = {
 //  0  1  2  3  4  5  6  7
  { -45,-47,-48,-50,-49,-51,-46,-44}, // 0
  { -53,-55,-56,-58,-57,-59,-54,-52}, // 1
  { -61,-63,-64,-66,-65,-67,-62,-60}, // 2
  { -69,-71,-72,-74,-73,-75,-70,-68}, // 3
  { 45, 47,48,50,49,51,46,44}, // 4
  { 53,55,56,58,57,59,54,52}, // 5
  { 69,71,72,74,73,75,70,68}, // 6
  { 61,63,64,66,65,67,62,60}, // 7
};



void setup() {
  // put your setup code here, to run once:

  Serial.begin( 9600 );
  Serial.println("#What up world");
  for ( int k = 0; k <= KEYS ; k++ )
  {
    keys[k]= 1;
  }

  for ( int c = 0; c < COLS ; c++ )
  {
    pinMode( cols[c], OUTPUT );
    digitalWrite( cols[c], HIGH );
  }

  for ( int r = 0; r < ROWS ; r++ )
  {
    pinMode( rows[r], INPUT_PULLUP );
  }
}

void loop() {
  // put your main code here, to run repeatedly:
//delay(500);
 // pause on each loop to make debugging easier
 //  delay(200);
  int buttonState ;
  int key;
  for ( int c = 0; c < COLS ; c++ )
  {
    digitalWrite( cols[c], LOW );
      for ( int r = 0; r < ROWS ; r++ )
      {
        buttonState = digitalRead( rows[ r ] ) ;
        key = r * 10 + c ;

        if ( buttonState != keys[key] )
        {
          if ( buttonState == LOW )
          {

            if ( buttons[r][c] > 0 )
              times[ buttons[r][c] ] = micros();
            else if ( times[abs(buttons[r][c]) ] > 0 )
            {
              Serial.print("noteon 1 ");
              Serial.print( abs(buttons[r][c]));
              Serial.print(" ");
              Serial.print( 127 - min((micros() - times[abs(buttons[r][c])])/1000,127) );
              Serial.println("");
            }
          
          }
          else
          {
            if ( buttons[r][c] > 0 )
            {
              Serial.print("noteoff 1 ");
              Serial.println(buttons[r][c]);
          
          
            }         
          
          }
          keys[key] = buttonState;
        }
      }
    
    digitalWrite( cols[c], HIGH  );
  }

  
}
