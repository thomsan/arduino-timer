
uint32_t years, days, hours, minutes, seconds, mill;
uint32_t last_millis, current_millis, dt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  current_millis = millis();
  dt=current_millis - last_millis;
  mill += dt;
  last_millis=current_millis;
  // TODO handle 0 overflow
  while(mill >= 1000){
    mill -= 1000;
    seconds += 1;
  }
  while(seconds >= 60){
    seconds -= 60;
    minutes += 1;
  }
  while(minutes >= 60){
    minutes -= 60;
    hours += 1;
  }
  while(hours >= 24){
    hours -= 24;
    days += 1;
  }
  while(days >= 365){
    days -= 365;
    years += 1;
  }

  Serial.print("d: ");
  Serial.print(days);
  Serial.print(", h: ");
  Serial.print(hours);
  Serial.print(", minutes: ");
  Serial.print(minutes);
  Serial.print(", s: ");
  Serial.print(seconds);
  Serial.print(", m: ");
  Serial.print(mill);
  Serial.println();
  delay(5000);
}
