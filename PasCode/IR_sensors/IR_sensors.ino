void setup() {
  // put your setup code here, to run once:

  //float result;
  Serial.begin(9600);

}
           
void loop() {
  // put your main code here, to run repeatedly:
float result=0;
  for(int i; i<1000; i++)
  {
    result=result+analogRead(0);
  }
  result=result/1000;
  Serial.print(result);
  Serial.print ("\n");

}
