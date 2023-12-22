int left_far; int left_near; int center; int right_near; int right_far;

int error=0, prev_error=0;
int Kp=1.5, Ki=2, Kd=1;
int P=0, I=0, D=0;  

bool actual_run = 0;

void read_sensors(){
  right_far = digitalRead(A0);
  right_near = digitalRead(A1);
  center = digitalRead(A2);
  left_near = digitalRead(A3);
  left_far = digitalRead(A4);
}

void print_readings(){
  Serial.print(left_far); Serial.print(" "); Serial.print(left_near); Serial.print(" "); Serial.print(center); Serial.print(" "); Serial.print(right_near); Serial.print(" "); Serial.print(right_far); Serial.println(" ");
}

void set_speed(int left_speed, int right_speed){
  if(left_speed>0){
    analogWrite(6, left_speed); analogWrite(5, 0);
  }
  else{    
    analogWrite(6, 0); analogWrite(5, -left_speed);
  }
  if(right_speed>0){
    analogWrite(10, right_speed); analogWrite(9, 0);
  }
  else{   
    digitalWrite(10, 0); digitalWrite(9, -right_speed);
  }}

char maze[100] = {0};
int index=0;

void setup() {
  Serial.begin(9600);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
}

void loop() {
  read_sensors();
  if((left_far==0 && right_far==0) && (left_near==1 || center==1 || right_near==1)){
    while(true){
      read_sensors();
      if((left_far==1 && center==1 && right_far==0) || (left_far==0 && center==1 && right_far==1)){
        break;
      } 
      else if(left_far==0 && left_near==0 && center==0 && right_near==0 && right_far==1){
        error = -4;
      }
      else if(left_far==0 && left_near==0 && center==0 && right_near==1 && right_far==1){
        error = -3;
      }
      else if(left_far==0 && left_near==0 && center==0 && right_near==1 && right_far==0){
        error = -2;
      }
      else if(left_far==0 && left_near==0 && center==1 && right_near==1 && right_far==0){
        error = -1;
      }
      else if(left_far==0 && left_near==0 && center==1 && right_near==0 && right_far==0){
        error = 0;
      }
      else if(left_far==0 && left_near==1 && center==1 && right_near==0 && right_far==0){
        error = 1;
      }
      else if(left_far==0 && left_near==1 && center==0 && right_near==0 && right_far==0){
        error = 2;
      }
      else if(left_far==1 && left_near==1 && center==0 && right_near==1 && right_far==0){
        error = 3;
      }
      else if(left_far==1 && left_near==0 && center==0 && right_near==1 && right_far==0){
        error = 4;
      }
      P=error; I=I+error; D=prev_error;
      int PID = Kp*P + Ki*I + Kd*D;
      set_speed(constrain(255-PID, -255, 255), constrain(255+PID, -255, 255));
      prev_error = error;
      if(error==0){
        error=0; prev_error=0;
        P=0; I=0; D=0;      
        break;
      }
    }
  }  
  read_sensors();
  if(left_far==1 && center==1 && right_far==0){ //left hand solving robot
    maze[index]=1; index=index+1;   
    set_speed(150, 150);
    delay(750);
    set_speed(-100, 100);
    delay(500);
    while(true){
      read_sensors();
      if(center==1){ 
        set_speed(150, 150);
        break;
      }      
    }
  }
  read_sensors();
  if(left_far==0 && center==1 && right_far==1){
    set_speed(150, 150);
    delay(750);
    read_sensors();
    if(left_far==0 && center==1 && right_far==0){
      maze[index]=2; index=index+1;
      set_speed(150,150);                      
    }  
    else{  
      maze[index]=3; index=index+1;
      set_speed(100, -100);
      delay(500);
      while(true){
        read_sensors();
        if(center==1 && left_near==1){
          set_speed(150, 150);  
          break;
        }      
      }
    }          
  }
  read_sensors();
  if(left_far==0 && left_near==0 && center==0 && right_far==0 && right_near==0){
    maze[index]=4; index=index+1;
    set_speed(150,150);
    delay(750);    
    set_speed(100,-100);
    delay(500);
    while(true){
      read_sensors();
      if(center==1 && left_near == 1 && right_near == 0){
        set_speed(150, 150);  
        break;
      }      
    }
  }   
  if(left_far==1 && left_near==1 && center==1 && right_far==1 && right_near==1){
    set_speed(150, 150);
    delay(750);
    read_sensors();
    if(left_far==1 && left_near==1 && center==1 && right_far==1 && right_near==1){
      maze[index]=5; index=index+1;
      set_speed(0,0); actual_run=1;      
      delay(10000);      
    }
    else if(left_far==0 && left_near==0 && center==0 && right_far==0 && right_near==0){
      maze[index]=1; index=index+1;
      set_speed(-100, 100);
      delay(500);
      while(true){
        read_sensors();
        if(center==1 && right_near==1){ 
          set_speed(150, 150);
          break;
        }      
      } 
    }    
  }   
}
