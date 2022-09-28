#define lamp1  D5
#define button1  D1

bool lamp1cur_state = false;
bool lamp1last_state = false;

void setup() {
  pinMode(lamp1,OUTPUT);
  pinMode(button1,INPUT_PULLUP);
}

void loop() {
  
  if(digitalRead(button1) && lamp1cur_state == lamp1last_state){
    lamp1cur_state = true;
    lamp1last_state = false;
  }else{
    lamp1cur_state = false;
    lamp1last_state = true;
  }

  if(lamp1cur_state){
    digitalWrite(lamp1,HIGH);
    lamp1last_state = true;
  }else{
    digitalWrite(lamp1,LOW);
    lamp1last_state = false;
  }
  
}
