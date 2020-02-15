void setup() {
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop() {
  int read;
  int readPre;
  unsigned long time_[10];
  int count = 0;
  Serial.println("Waiting Start!");

  while (true) {
    read = digitalRead(A3);
    if (read == 1 && readPre == 0) { //1つ前で遮られていなく、今回遮られている
      time_[count] = micros();
      count++;
    }
    //  Serial.println(String(count) + " " + String(readPre) + " " + String(read));
    readPre = read;
    delay(1);
    if (count == 10) break; //10回で終了
  }

  Serial.println("Calculation!");
  Serial.println("Raw result.");
  unsigned long max = 0;
  unsigned long min = 32767;
  unsigned long period;
  unsigned long  ave = 0;

  for (int i = 1; i < 10; i++) { //2つ目 - 1つ目が最初
    //  Serial.println(time_[i]);
    period = (time_[i] - time_[i - 1]) / 1000;
    Serial.println(period) ;
    ave += period;

    if (period < min)min = period;
    if (period > max)max = period;
  }
  ave /= 9;
  //結果
  Serial.println("Ave= " + String(ave));
  Serial.println("delta= " + String((max - min) / 2));
}
