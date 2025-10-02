#include <SPI.h>

#include <MFRC522.h>

#define SS_PIN 5 // ESP32 pin GPIO5 
#define RST_PIN 27 // ESP32 pin GPIO27 MFRC522 
rfid(SS_PIN, RST_PIN);
String tag;
int B=0,W=0;
void setup(){
Serial.begin(9600);
SPI.begin(); // init SPI bus  
rfid.PCD_Init(); // init MFRC522               
pinMode(4,OUTPUT);
pinMode(12,OUTPUT);
pinMode(2,OUTPUT);
Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}
void loop() 
{ 
	if (rfid.PICC_IsNewCardPresent()) {// new tag is available    
	    if (rfid.PICC_ReadCardSerial()) { 
		// NUID has been readed      	  	    
        MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);      	    
        Serial.print("RFID/NFC Tag Type: ");      	    
        Serial.println(rfid.PICC_GetTypeName(piccType));      
        // print UID in Serial Monitor in the hex format        	    
        Serial.print("UID:");      
	    for (int i = 0; i < rfid.uid.size; i++) {        	
            Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");        
	        Serial.print(rfid.uid.uidByte[i], DEC);        	    
            tag += rfid.uid.uidByte[i];     
	    }       
	Serial.println();
	
    if (tag == "195231224145") {
          if(B==1)  {
	        digitalWrite(4,LOW);
	        B=0;
	        Serial.println("Turning off LED...");
	        digitalWrite(12,HIGH);
	        delay(1000);
	        digitalWrite(12,LOW);
	        return;       
          }
	    Serial.println("Access Granted!");      
	    B=1;      
	    Serial.println("Turning on the LED.");      	
        digitalWrite(12, HIGH);      
	    delay(100);      		
        digitalWrite(12, LOW);      
	    delay(100);      		
        digitalWrite(12, HIGH);      
	    delay(100);
        digitalWrite(12, LOW);
	    delay(100);
        digitalWrite(12, HIGH);
	    delay(100);
	    digitalWrite(12, LOW);      	
	    delay(100);      
	    digitalWrite(4,HIGH);    
    }
    if (tag == "29669355") {      
          if(W==1){        
	    digitalWrite(2,LOW);        	
        Serial.println("Turning off FAN...");        	
        digitalWrite(12,HIGH);        
	    delay(1000);        
	    digitalWrite(12,LOW);        
	    W=0;        
	    return;     
          }    
	Serial.println("Access Granted!");      
	W=1;      
	digitalWrite(12, HIGH);      
	delay(100);      
	digitalWrite(12, LOW);
	delay(100);      
	digitalWrite(12, HIGH);      
	delay(100);      
	digitalWrite(12, LOW);      
	delay(100);      
	digitalWrite(12, HIGH);      
	delay(100);      
	digitalWrite(12, LOW);      
	delay(100);      
	Serial.println("Turning on the FAN.");        	
    digitalWrite(2,HIGH);    
}    
tag="";      
rfid.PICC_HaltA(); // halt PICC      
rfid.PCD_StopCrypto1(); // stop encryption on PCD   
}  
}
}
