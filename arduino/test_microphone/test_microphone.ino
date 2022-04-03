int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3

                       // outside leads to ground and +5V
float a = 0.9;
float m1 = 0;
float m2 = 0;
float val1 = 0;           // variable to store the value read
float val2 = 0;
float THRESHOLD = 1;
const int win_size = 40; // size of the window on which we compute the delay between the microphones
int i = 0;
float l_a[win_size];
float r_a[win_size];
float t0=0;
float t1 = 0;
float s_avg = 0;
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setup() {
  Serial.begin(9600);
  // Set the Prescaler to 16 (16000KHz/16 = 1MHz)
  // WARNING: Above 200KHz 10-bit results are not reliable.
  //ADCSRA |= B00000100;
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
}

float* convolve(float h[], float x[], int lenH, int lenX, int* lenY)
{
  int nconv = lenH+lenX-1;
  (*lenY) = nconv;
  int i,j,h_start,x_start,x_end;

  float *y = (float*) calloc(nconv, sizeof(float));

  for (i=0; i<nconv; i++)
  {
    x_start = max(0,i-lenH+1);
    x_end   = min(i+1,lenX);
    h_start = min(i,lenH-1);
    for(j=x_start; j<x_end; j++)
    {
      y[i] += h[h_start--]*x[j];
    }
  }
  return y;
}
int compute_delay(float left_array[], float right_array[], float sample_rate){
  int lenY;
  float *y = convolve(left_array,right_array,win_size,win_size,&lenY);
  float d_max = 0;
  float v_max = -pow(10, 6);
  for(int k=0; k<lenY; k++){
    //Serial.println(y[k]);
    if(y[k]>v_max){
      d_max = k;
      v_max=y[k];
      
    }
  }
  free(y);
  return d_max;
}

float compute_angle(float delay){
  
  return 1.0;
}
void Lloop(){
  t1 = t0;
  t0 = micros();
  Serial.println(t0-t1);
}

void loop()
{ 
  t1 = t0;
  t0 = micros();
  //Serial.println(t0-t1);
  i +=1; 
  if (i==win_size){
    i=0;
    int y = 0;
    int b = 0;
     for (int k=0; k<win_size; k++){
      if (l_a[k]>THRESHOLD){
        y = 1;
      }
      if (r_a[k]>THRESHOLD){
        b=1;
      }
    if (y==1){
      digitalWrite(7, HIGH);
    }
    else {
      digitalWrite(7, LOW);
    }
    if (b==1){
      digitalWrite(4, HIGH);
    }
    else {
      digitalWrite(4, LOW);
    }
    if (b==1 and y==1){
      //float time_diff = compute_delay(l_a, r_a, 115200);
      
      //Serial.println(time_diff);
      float s1=0;
      float s2=0;
      for (int k=0; k<win_size; k++){
        s1 += l_a[k];
        s2 += r_a[k];
      }
      
      s_avg = s_avg*0.5 + 0.5*(s2-s1);
      Serial.println(s_avg);
    }
    }
  }
  
  val1 = analogRead(3);
  val2 = analogRead(4);// read the input pin
  m1 = m1*a+(1-a)*val1;
  m2 = m2*a+(1-a)*val2;
  l_a[i] = (float) (val1-m1);
  r_a[i] = (float) (val2-m2);
  
}
