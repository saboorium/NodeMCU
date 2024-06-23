void setup()
{
Serial.begin(115200)
pinMode(A0, INPUT); 
pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
int pot = analogRead(A0);
Serial.println(pot);
pot = 1023 - pot;
analogWrite(LED_BUILTIN, potencia);
}
