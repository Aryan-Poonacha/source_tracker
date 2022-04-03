//Setup for Wheel Motors

#define enA 6
#define in1 7
#define in2 5
#define enB 3 
#define in3 4
#define in4 2
float s1=0;
float su1 = 0;
float su2 = 0;
float s2=0;

int skip=0;// outside leads to ground and +5V
float a = 0.9;
float m1 = 0;
float m2 = 0;
float val1 = 0;           // variable to store the value read
float val2 = 0;
float THRESHOLD = 1;
const int win_size = 100;
int t0=0;
int t1=0;
int i = 0;
float l_a[win_size];
float r_a[win_size];
float s_avg;
void go(int t) {
  analogWrite(enA, 175);
  analogWrite(enB, 175);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(t);
  stopp(250);

}

void left(int t) {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(t);
  stopp(250);
}

void right(int t) {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(t);
  stopp(250);
}

void stopp(int t) {
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  delay(t);
}

void setup() {
  Serial.begin(115200);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  stopp(250);
}

void loop()
{ 
  t1 = t0;
  t0 = micros();
  //Serial.println(t0-t1);
  i +=1;
  //if (i==win_size and skip==1){
  //  i=0;
  //  skip=0; 
  //}
  if (i==win_size){
    stopp(250);
    i=0;
    int y = 0;
    int b = 0;
    su1 = 0;
    su2 = 0;
    for (int k=0; k<win_size; k++){
        su1+=l_a[k];
        su2+=r_a[k];
        if (s1<l_a[k]) s1=l_a[k];
        if (s2<l_a[k]) s2=r_a[k];
        
      }
      su1 = su1/win_size;
      su2 = su2/win_size;
     for (int k=0; k<win_size; k++){
      Serial.print(l_a[k]-su1);
      Serial.print(" ");
      Serial.println(r_a[k]-su2);
      if (fabs(l_a[k]-su1)>THRESHOLD){
        y = 1;
      }
      if (fabs(r_a[k]-su2)>THRESHOLD){
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
      
      
      
      s_avg = (s2-s1);//s_avg*0.5 + 0.5*(s2-s1);
      //Serial.println(s_avg);
      skip=1;
      if (s_avg>0){
        //right(200);
        }
      else if (s_avg<0){
        //left(200);
      }
    }
    }
  }
  
  val1 = analogRead(0);
  val2 = analogRead(3);// read the input pin
  //m1 = m1*a+(1-a)*val1;
  //m2 = m2*a+(1-a)*val2;
  l_a[i] = (float) val1;//-m1);
  r_a[i] = (float) val2;//-m2);
  
}
