int Light_SensorPin= A0;
int Light_SensorPin2= A2;
void setup() {
    // put your setup code here, to run once:
    pinMode(Light_SensorPin,INPUT);
    pinMode(Light_SensorPin2,INPUT);
    Serial.begin(9600);
  }
  void loop() {
    // put your main code here, to run repeatedly:
    //Declaring variables 
    float Tsum=0.0;
    float Tsum2=0.0;
    int Output;
    float Vsensor;
    float Voltage;
    float Temperature;
    // loop to sum 10 recorded values
    for(int i=0; i<10; i++){
      Output= analogRead(Light_SensorPin);
      Voltage = Output*(5.0/1023.0);
      Vsensor = Voltage/3.71;
      Temperature = Vsensor*100.0;
      Tsum= Temperature+Tsum;
    }
    //Calculating Temperature from 5v input pin
    Output= analogRead(Light_SensorPin);
    //Converting Arduino ADC to voltage
    Voltage =Output*(5.0/1024.0);
    // Gain of opamp calculated to be 3.71
    Vsensor = Voltage/3.71;
    //For LM35 1degree=10mV
    Temperature = Vsensor*100.0;
    float Tavg= Tsum/10;

    //For 3V ADC
    //loop to sum 10 recorded values
    for(int j=0; j<10; j++){
      int Output3V= analogRead(Light_SensorPin2);
      //multiplying the voltage by two since a potental devider
      //was used and input ADC was halfed
      Output3V= 2*Output3V;
      float Voltage2 = Output3V*(5/1024.0);
      float Vsensor2 = Voltage2/3.71;
      float Temperature3V = Vsensor2*100.0;
      Tsum2= Temperature3V+Tsum2;
    
    }
    //Calculating Temperature from 3v input pin
    float Output3V= analogRead(Light_SensorPin2);
    float Voltage2 = 2*Output3V*(5/1023.0);
    float Vsensor2 = Voltage2/3.71;
    float Temperature3V = Vsensor2*100.0;
    float Tavg2= Tsum2/10;
    // Printint Measured and Calculated values on Serial monitor
    Serial.print("ADC:");
    Serial.print(Output);
    Serial.print(" ¦ ");
    Serial.print("Amp V/G:");
    Serial.print(Voltage);
    Serial.print("V ¦");
    Serial.print(" LM35 V/G:");
    Serial.print(Vsensor);
    Serial.print("V ¦");
    Serial.print(" Temp:");
    Serial.print(Temperature);
    Serial.print("°C ¦");
    Serial.print(" Average Temp:");
    Serial.print(Tavg);
    Serial.print("°C ¦");
    Serial.print(" 3V ADC:");
    Serial.print(Output3V);
    Serial.print(" ¦ ");
    Serial.print("Temp FROM 3V MC:");
    Serial.print(Temperature3V);
    Serial.print("°C  ¦");
    Serial.print(" Average Temp 3V: ");
    Serial.print(Tavg2);
    Serial.println("°C");
    //Delay 1s after every print
    delay(1000);
 }
