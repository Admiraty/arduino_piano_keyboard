const int ROWS = 4;
const int COLS = 4;
const int KEYS = 78;
//byte cols[8] = { 5,6,7,8,9,10,11,12};
//byte rows[8] = { 22,24,26,28,30,32,34,36 };

byte cols[COLS] = { 11, 10, 9, 8 };
byte rows[ROWS] = { 7,6,5,4 };

byte keys[KEYS + 1] ;

void setup() {
  // put your setup code here, to run once:

  Serial.begin( 9600 );
  Serial.println("What up world");
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
delay(50);

  
  
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
          Serial.print( "====>" );
          Serial.print( c );
          Serial.print(" x " );
          Serial.print( r );
          Serial.print(" = ");
          Serial.println( buttonState );
          keys[key] = buttonState;
        }
      }
    
    digitalWrite( cols[c], HIGH  );
  }
 
}
