int bluePin = 5;
int greenPin = 6;
int redPin = 7;
float hue = 0;
int blueBrightness = 0;
int greenBrightness = 0;
int redBrightness = 0;

void h2rgb(float h, int &R, int &G, int &B);

void setup() {
  // Setting Up the COM Port
  Serial.begin(9600);
  // Changing PIN modes to OUTPUT
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  /*
  if(Serial.available() >= 4) {
   if(Serial.read() == 0xff) {
    // 0, 0, 0 is Black
    // 255, 255, 255 is White
    redBrightness = Serial.read();
    greenBrightness = Serial.read();
    blueBrightness = Serial.read();
   } 
  }
  */
  
  /*
   Since the RGB LED has cathode pins for 
   RGB we need to deduct value from 255 
   meaning if the brightness is 255 from the 
   PC for a color we need to give 0 so that it
   will eluminate brightly
  */
  h2rgb(hue,redBrightness, greenBrightness, blueBrightness);
  hue += 0.0001;
  if(hue>1) {
    hue = 0;
  }
  Serial.println(hue);
  analogWrite(bluePin, 255 - blueBrightness);
  analogWrite(greenPin, 255 - greenBrightness);
  analogWrite(redPin, 255 - redBrightness);
  delay(10); 
}

void h2rgb(float H, int& R, int& G, int& B) {

  int var_i;
  float S=1, V=1, var_1, var_2, var_3, var_h, var_r, var_g, var_b;

  if ( S == 0 )                       //HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      //H must be < 1
    var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if      ( var_i == 0 ) {
      var_r = V     ;
      var_g = var_3 ;
      var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
      var_r = var_2 ;
      var_g = V     ;
      var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
      var_r = var_1 ;
      var_g = V     ;
      var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
      var_r = var_1 ;
      var_g = var_2 ;
      var_b = V     ;
    }
    else if ( var_i == 4 ) {
      var_r = var_3 ;
      var_g = var_1 ;
      var_b = V     ;
    }
    else                   {
      var_r = V     ;
      var_g = var_1 ;
      var_b = var_2 ;
    }

    R = (1-var_r) * 255;                  //RGB results = 0 ÷ 255
    G = (1-var_g) * 255;
    B = (1-var_b) * 255;
  }
}

