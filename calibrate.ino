const int ROWS = 16;
const int COLS = 8;
const int KEYS = 250;
byte cols[COLS] = { 2,3,4,5,6,7,8,9 };
byte rows[ROWS] = { 22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37 } ;
  
long int keys[KEYS + 1] ;
long int times[KEYS + 1] ;

long int num = 1;
int timer ;

void setup() {
  // put your setup code here, to run once:

  Serial.begin( 9600 );
  for ( int k = 0; k <= KEYS ; k++ )
  {
    keys[k] = 1;
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
  
  int buttonState ;
  int key;
  for ( int c = 0; c < COLS ; c++ )
  {
    digitalWrite( cols[c], LOW );
    for ( int r = 0; r < ROWS ; r++ )
    {
      buttonState = digitalRead( rows[ r ] ) ;
      key = r * 8 + c ;

      if ( buttonState != keys[key] )
      {

        keys[key] = buttonState;
        if ( buttonState == LOW )
        {
            Serial.print("notes[");
            Serial.print(c);
            Serial.print("][");
            Serial.print(r);
            Serial.print("] = ") ;
            Serial.print( "num++");
            Serial.println(";");
        }
      }

    }

    digitalWrite( cols[c], HIGH  );
  }
  


}
