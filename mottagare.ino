#include <IRLib.h>

int RECV_PIN = 11;
IRrecv My_Receiver(RECV_PIN);
IRdecode My_Decoder;

//JAAAAAAAPPPPPPPPPPPPPPP
IRTYPES codeType;          // The type of code
unsigned long codeValue;   // The data bits if type is not raw
int codeBits;              // The length of the code in bits

// These values are only stored if it's an unknown type and we are going to use
// raw codes to resend the information.
unsigned int rawCodes[RAWBUF]; // The durations if raw
int rawCount;                   //The number of interval samples

bool GotOne, GotNew; 
//JAAAAAAAAAPPPPPPPPPPPPPPP

void setup() {
  GotOne=false; GotNew=false;
  codeType=UNKNOWN; 
  codeValue=0; 
  Serial.begin(9600);
  Serial.println(F("Send a code from your remote and we will record it."));
  My_Receiver.enableIRIn(); // Start the receiver
}

// Stores the code for later playback
void storeCode(void) {
  GotNew=true;
  codeType = My_Decoder.decode_type;
  if (codeType == UNKNOWN) {
    Serial.println("Received unknown code");
  }
  else {
    Serial.print(F("Received "));
    Serial.print(Pnames(codeType));
    if (My_Decoder.value == REPEAT) {
      // Don't record a NEC repeat value as that's useless.
      Serial.println(F("repeat; ignoring."));
     }
     else {
       codeValue = My_Decoder.value;
       codeBits = My_Decoder.bits;
     }
//     Serial.print(F(" Value:0x"));
//     Serial.println(My_Decoder.value, HEX);
  }
}

void loop() {
  if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();
    GotOne=true;
    storeCode();
    Serial.println(codeValue);
    delay(1000);
    My_Receiver.resume();
  }

}
