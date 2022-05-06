


char command; 
int state;
int previous = 0;
int count = 0;


//define motor pins

//motor right
int motor1Pin1 = 5;
int motor1Pin2 = 6;

//motor left
int motor2Pin1 = 10;
int motor2Pin2 = 9;

void setup() {
 
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  Serial.begin(2000000);

}

void loop() {

  if (Serial.available()) {
    command = Serial.read();

    
    // Count for controlling moving, python sended data have latency, so this way contorl over moving
    //move forward
    
    if(command == 'F') {
      if(previous == 1 && count < 3){  
        state = 1;
        count += 1;
        
      } else if (previous != 1) {
        state = 1;
        count = 0;
        
      } else {
        count += 1;
        state = 5;
      }
      previous = 1; 
    }
    
    //move backward
    
    if(command == 'B'){
      if(previous == 2 && count < 3){
        state = 2;
        count += 1;
        
      } else if (previous != 2) {
        state = 2;
        count = 0;
        
      } else {
        count += 1;
        state = 5;
      }
      previous = 2;
    }
    
    //turn right
    
    if(command == 'R'){
      if(previous == 3 && count < 1){
        state = 3;
        count += 1;
        
      } else if (previous != 3) {
        state = 3;
        count = 0;
 
      } else {
        count += 1;
        state = 5;
      } 
      previous = 3; 
    }
      
       
    //turn left
    
    if(command == 'L'){
      if(previous == 4 && count < 1){
        state = 4;
        count += 1;
        
      } else if (previous != 4) {
        state = 4;
        count = 0;
        
      } else {
        count += 1;
        state = 5;
      }
      previous = 4;
    }
    
    // turn left little
   
    if(command == 'A'){
      if(previous == 6 && count < 3){
        state = 6;
        count += 1;
        
      } else if (previous != 6) {
        state = 6;
        count = 0;
        
      } else {
        count += 1;
        state = 5;
      }
      previous = 6;
    }

    // turn right little
   
    if(command == 'C'){
      if(previous == 7 && count < 3){
        state = 7;
        count += 1;
        
      } else if (previous != 7) {
        state = 7;
        count = 0;
        
      } else {
        count += 1;
        state = 5;
      }
      previous = 7;
    }

    //Go back little

    if(command == 'D'){
      if(previous == 8 && count < 3){
        state = 8;
        count += 1;
        
      } else if (previous != 8) {
        state = 8;
        count = 0;
        
      } else {
        count += 1;
        state = 5;
      }
      previous = 8;
    }

    //Go forward little

    if(command == 'D'){
      if(previous == 9 && count < 3){
        state = 9;
        count += 1;
        
      } else if (previous != 9) {
        state = 9;
        count = 0;
        
      } else {
        count += 1;
        state = 5;
      }
      previous = 9;
    }
    
    //do nothing
    
    if(command == 'S'){
      state = 5;
      count = 0;
      previous = 5;
    }
    
  }

  //STATE 1: move forward
  
    if (state == 1) {
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(300); 
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
  
    }

  
    //STATE 2: move backward
    
    if (state == 2) {
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(300);
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
       
     }
     
      //STATE 3: move right
    if (state == 3) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(250);

      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(150);
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);

    }
    
    //STATE 4: move left
    
    if (state == 4) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      delay(250);

      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(150);
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      
    }
    
    //STATE 5: do nothing
    
    if (state == 5) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    }

     //STATE 6: move right little
    if (state == 6) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      delay(100);

      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(100);
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);

    }

    //STATE 7: move right little
    if (state == 7) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(100);

      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(100);
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);

    }

     //STATE 2: move backward little
    
    if (state == 8) {
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(200);
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
       
     }

    //STATE 9: move forward little
  
    if (state == 9) {
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(200); 
      
      analogWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      analogWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
  
    }

}
