    /*
     * HW: 4 led disposti a forma di croce sulla breadboard, ulteriori 3 led da associare al segnale
     * del fotoresistore, un fotoresistore, il led matrix e il joystick.
     * Il programma risponde alla direzione del joystick accendendo una corrispondente freccia sul led matrix e un led che indica la sua direazione.
     * Se le condizioni di luminosità diventano inferiori ad una certa soglia si accendono anche gli ulteriori led premium.
     * Premendo il pulsante sul Joystick i 4 led a croce si accendono simultaneamente lampeggiando.
     * Vedi video nella cartella "video" per miglior comprensione.
     */
    #include <LedControl.h>
    int rosso = 3;  //I quattro colori rappresentano le 4 direzioni del Joystick, si accendono a seconda dei movimenti del Joystick
    int blu = 4;
    int verde = 8;
    int giallo = 2;
    int blupremium= 7;  //I led premium sono 3 led aggiuntivi, non i 4 principali che rispondono ai movimenti del Joystick
    int rossopremium = 6;
    int giallopremium = 5;
    int b=1;
    int DIN= 12;
    int CS =11;
    int CLK =10;
    int PfReading; //Variabile per la lettura del valore di luminosità

    
    byte smile[8]=     {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};  //PixelToMatrix.exe per generare le coordinate dei singoli bit
    byte UP[8]=        {0x00,0x18,0x3C,0x5A,0x18,0x18,0x18,0x00};
    byte DOWN[8]=      {0x00,0x18,0x18,0x18,0x5A,0x3C,0x18,0x00};
    byte RIGHT[8]=     {0x00,0x08,0x04,0x7E,0x7E,0x04,0x08,0x00};
    byte LEFT[8]=      {0x00,0x10,0x20,0x7E,0x7E,0x20,0x10,0x00};
 
    int bottone = 13;
    int X = A1;
    int Y = A0;
    int pf = A2; //pf= photocell, sensore di luminosità dell'ambiente
    int X_let = 0;
    int Y_let = 0;
    int bottone_let = 0; //Bottone del Joystick
    
    LedControl lc=LedControl(DIN,CLK,CS,0);


    void setup() {
        lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
        lc.setIntensity(0,15);      // Set the brightness to maximum value
        lc.clearDisplay(0);         // and clear the display
        pinMode(rosso, OUTPUT);  
        pinMode(blu, OUTPUT);
        pinMode(verde, OUTPUT);
        pinMode(giallo, OUTPUT);
        pinMode(bottone, INPUT);
        pinMode(blupremium, OUTPUT);
        pinMode(rossopremium, OUTPUT);
        pinMode(giallopremium, OUTPUT);
        pinMode(X, INPUT);
        pinMode(Y, INPUT);
        digitalWrite(bottone, HIGH);
        Serial.begin(9600);
    }

    void printByte(byte character [])
    {
      for(int i=0;i<8;i++)
      {
        lc.setRow(0,i,character[i]);
      }
    }

    void loop() {

      PfReading = analogRead(pf);
      digitalWrite (b,LOW);
      //monitor seriale
        Serial.print("Bottone:  ");
        Serial.print(digitalRead(bottone));
        Serial.print("\n");
        Serial.print("Asse X: ");
        Serial.print(analogRead(X));
        Serial.print("\n");
        Serial.print("Asse Y: ");
        Serial.println(analogRead(Y));
        Serial.print("Luminosità: ");
        Serial.print(PfReading);
        Serial.print("\n\n");
        delay(100);
   
      

      if(analogRead(pf)<300) // Controllo della luminosità
      {
        digitalWrite(rossopremium, HIGH);
        digitalWrite(blupremium, HIGH);
        digitalWrite(giallopremium, HIGH);
      }else 
      {
        digitalWrite(rossopremium, LOW);
        digitalWrite(blupremium, LOW);
        digitalWrite(giallopremium, LOW);
      }
      
        X_let = analogRead(X);
        Y_let = analogRead(Y);
        bottone_let = digitalRead(bottone);
        
        if (Y_let<270) {
          digitalWrite(rosso, HIGH);
          digitalWrite(blu, LOW);
          digitalWrite(verde, LOW);
          digitalWrite(giallo, LOW);
          printByte(RIGHT);
        }
        
        if (Y_let>900) {
          digitalWrite(rosso, LOW);
          digitalWrite(blu, LOW);
          digitalWrite(verde, HIGH);
          digitalWrite(giallo, LOW);
          printByte(LEFT);
        }
        
        if (X_let<270) {
          digitalWrite(rosso, LOW);
          digitalWrite(blu, LOW);
          digitalWrite(verde, LOW);
          digitalWrite(giallo, HIGH);
          printByte(UP);
        }
        
        if (X_let>900) {
          digitalWrite(rosso, LOW);
          digitalWrite(blu, HIGH);
          digitalWrite(verde, LOW);
          digitalWrite(giallo, LOW);
          printByte(DOWN);

        }
        
        if ((X_let>=400 && X_let<=600) && (Y_let>=400 && Y_let<=600)) {
          digitalWrite(rosso, LOW);
          digitalWrite(blu, LOW);
          digitalWrite(verde, LOW);
          digitalWrite(giallo, LOW);
          printByte(smile);
        }
        
        if (bottone_let == 0) {
            for (int i=0; i<5; i++) {
              digitalWrite(rosso, HIGH);
              digitalWrite(blu, HIGH);
              digitalWrite(verde, HIGH);
              digitalWrite(giallo, HIGH);
              delay(50);
              digitalWrite(rosso, LOW);
              digitalWrite(blu, LOW);
              digitalWrite(verde, LOW);
              digitalWrite(giallo, LOW);
              delay(50);
            }
        }

        
        
        
    }
      /* Made by Dalo ----> Programmazione e componenti elettronici. */
   
