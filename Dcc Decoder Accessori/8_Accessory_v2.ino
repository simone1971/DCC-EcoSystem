#include <NmraDcc.h>

#define DCC_PIN 2
#define ACK_PIN 3

#define OUT_1  4
#define OUT_2  5
#define OUT_3  6
#define OUT_4  7
#define OUT_5  8
#define OUT_6  9
#define OUT_7  10
#define OUT_8  11
#define OUT_9  12
#define OUT_10 13
#define OUT_11 14
#define OUT_12 15
#define OUT_13 16
#define OUT_14 17
#define OUT_15 18
#define OUT_16 19

#define CV_DECODER_MODE     33  //1=TURNOUT 2=SINGLE OUTPUT (FOR LIGHTS) - Default value is 1

#define CV_MODE_T1          41  
#define CV_MODE_T2          42
#define CV_MODE_T3          43
#define CV_MODE_T4          44
#define CV_MODE_T5          45
#define CV_MODE_T6          46
#define CV_MODE_T7          47
#define CV_MODE_T8          48

#define CV_IMPULSE_TIME_T1  51
#define CV_IMPULSE_TIME_T2  52
#define CV_IMPULSE_TIME_T3  53
#define CV_IMPULSE_TIME_T4  54
#define CV_IMPULSE_TIME_T5  55
#define CV_IMPULSE_TIME_T6  56
#define CV_IMPULSE_TIME_T7  57
#define CV_IMPULSE_TIME_T8  58

#define MODE_BISTABLE   0
#define MODE_IMPULSE    1
#define MODE_TURNOUT    1
#define MODE_SIGNAL     2


int ActTurnoutOutput1[8] = {OUT_1, OUT_3, OUT_5, OUT_7, OUT_9, OUT_11, OUT_13, OUT_15};
int ActTurnoutOutput2[8] = {OUT_2, OUT_4, OUT_6, OUT_8, OUT_10, OUT_12, OUT_14, OUT_16};

NmraDcc Dcc;
DCC_MSG  Packet ;

struct CVPair
{
  uint16_t  CV;
  uint8_t   Value;
};

void notifyCVAck (void) {

   Serial.println("NotifyCVAck");
   digitalWrite (ACK_PIN, HIGH);
   delay ( 8 );
   digitalWrite (ACK_PIN, LOW); 
}

// Uncomment to print all DCC Packets
//#define NOTIFY_DCC_MSG
#ifdef  NOTIFY_DCC_MSG
void notifyDccMsg( DCC_MSG * Msg)
{
  Serial.print("notifyDccMsg: ") ;
  for(uint8_t i = 0; i < Msg->Size; i++)
  {
    Serial.print(Msg->Data[i], HEX);
    Serial.write(' ');
  }
  Serial.println();
}
#endif

// This function is called whenever a normal DCC Turnout Packet is received and we're in Output Addressing Mode
void notifyDccAccTurnoutOutput (uint16_t Addr, uint8_t Direction, uint8_t OutputPower) {

int FirstTurnout = (Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_LSB) + (Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_MSB) * 256));
int NumTurnout = 8;

int TURNOUT_MODE[8] = {Dcc.getCV(CV_MODE_T1), Dcc.getCV(CV_MODE_T2), Dcc.getCV(CV_MODE_T3), Dcc.getCV(CV_MODE_T4),
                       Dcc.getCV(CV_MODE_T5), Dcc.getCV(CV_MODE_T6), Dcc.getCV(CV_MODE_T7), Dcc.getCV(CV_MODE_T8)};
int IMPULSE_TIME[8] = {Dcc.getCV(CV_IMPULSE_TIME_T1), Dcc.getCV(CV_IMPULSE_TIME_T2), Dcc.getCV(CV_IMPULSE_TIME_T3), Dcc.getCV(CV_IMPULSE_TIME_T4),
                       Dcc.getCV(CV_IMPULSE_TIME_T5), Dcc.getCV(CV_IMPULSE_TIME_T6), Dcc.getCV(CV_IMPULSE_TIME_T7), Dcc.getCV(CV_IMPULSE_TIME_T8)}; 
int ActTurnout      = (Addr - FirstTurnout);

  if((Addr >= FirstTurnout) && (Addr < (FirstTurnout + NumTurnout))) {
//  if (Dcc.getCV(CV_DECODER_MDcc.getCV(CV_IMPULSE_MODE == MODE_TURNOUT) {
  if(TURNOUT_MODE[ActTurnout] == MODE_BISTABLE) {
      if(Direction == 0) {
        digitalWrite(ActTurnoutOutput1[ActTurnout], HIGH);
        digitalWrite((ActTurnoutOutput2[ActTurnout]), LOW);
      } else {
        digitalWrite(ActTurnoutOutput1[ActTurnout], LOW);
        digitalWrite((ActTurnoutOutput2[ActTurnout]), HIGH);
      }
  }
  else if (TURNOUT_MODE[ActTurnout] == MODE_IMPULSE) {
      if (Direction == 0) {
        digitalWrite(ActTurnoutOutput1[ActTurnout], HIGH);
        delay (IMPULSE_TIME[ActTurnout]);
        digitalWrite(ActTurnoutOutput1[ActTurnout], LOW);
      } else {
        digitalWrite((ActTurnoutOutput2[ActTurnout]), HIGH);
        delay (IMPULSE_TIME[ActTurnout]);
        digitalWrite((ActTurnoutOutput2[ActTurnout]), LOW);
      }
  }
  }

//  else if (Dcc.getCV(CV_DECODER_MODE == MODE_SIGNAL) {
    
//  }
    Serial.print("Address: "); Serial.println(Addr);
    Serial.print("Direction: "); Serial.println(Direction);
    Serial.print("OutputPower: "); Serial.println(OutputPower);
    Serial.println("----------------------");
    
}

// This function is called whenever a DCC Signal Aspect Packet is received
void notifyDccSigOutputState( uint16_t Addr, uint8_t State)
{
  Serial.print("notifyDccSigOutputState: ") ;
  Serial.print(Addr,DEC) ;
  Serial.print(',');
  Serial.println(State, HEX) ;
}


void notifyCVResetFactoryDefault()  {

  Serial.println("Factory Reset!");
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, 1);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, 0);
  Dcc.setCV(CV_DECODER_MODE, MODE_TURNOUT);
  Dcc.setCV(CV_MODE_T1, MODE_IMPULSE); Dcc.setCV(CV_MODE_T2, MODE_IMPULSE); Dcc.setCV(CV_MODE_T3, MODE_IMPULSE); Dcc.setCV(CV_MODE_T4, MODE_IMPULSE);
  Dcc.setCV(CV_MODE_T5, MODE_IMPULSE); Dcc.setCV(CV_MODE_T6, MODE_IMPULSE); Dcc.setCV(CV_MODE_T7, MODE_IMPULSE); Dcc.setCV(CV_MODE_T8, MODE_IMPULSE);
  Dcc.setCV(CV_IMPULSE_TIME_T1, 100); Dcc.setCV(CV_IMPULSE_TIME_T2, 100); Dcc.setCV(CV_IMPULSE_TIME_T3, 100); Dcc.setCV(CV_IMPULSE_TIME_T4, 100);
  Dcc.setCV(CV_IMPULSE_TIME_T5, 100); Dcc.setCV(CV_IMPULSE_TIME_T6, 100); Dcc.setCV(CV_IMPULSE_TIME_T7, 100); Dcc.setCV(CV_IMPULSE_TIME_T8, 100);
}

void setup() {
 
  Serial.begin(115200);
  
// Configure the DCC CV Programing ACK pin for an output
  pinMode(ACK_PIN, OUTPUT);

//Configure all the Output Pins
  pinMode(OUT_1, OUTPUT); pinMode(OUT_2, OUTPUT); pinMode(OUT_3, OUTPUT); pinMode(OUT_4, OUTPUT);
  pinMode(OUT_5, OUTPUT); pinMode(OUT_6, OUTPUT); pinMode(OUT_7, OUTPUT); pinMode(OUT_8, OUTPUT);
  pinMode(OUT_9, OUTPUT); pinMode(OUT_10, OUTPUT); pinMode(OUT_11, OUTPUT); pinMode(OUT_12, OUTPUT);
  pinMode(OUT_13, OUTPUT); pinMode(OUT_14, OUTPUT); pinMode(OUT_15, OUTPUT); pinMode(OUT_16, OUTPUT);

  Dcc.pin(digitalPinToInterrupt(DCC_PIN), DCC_PIN, false);
  Dcc.init(MAN_ID_DIY, 2, FLAGS_DCC_ACCESSORY_DECODER | FLAGS_OUTPUT_ADDRESS_MODE, 0);

  Serial.println("Setup Complete, Decoder Running");
  Serial.print("Accessory Decoder v. ");Serial.println(Dcc.getCV(CV_VERSION_ID));
  Serial.print("First Address: ");Serial.println(Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_LSB) + (Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_MSB) * 256));
  //Serial.print("Decoder Mode: ");Serial.println(Dcc.getCV(33));
  //Serial.println("1=TURNOUT 2=SINGLE OUTPUT (FOR LIGHTS)");
}

void loop() {
  
  Dcc.process();

  if (Dcc.getCV(CV_MODE_T1) > 1) {Dcc.setCV(CV_MODE_T1, MODE_IMPULSE);} if (Dcc.getCV(CV_MODE_T2) > 1) {Dcc.setCV(CV_MODE_T2, MODE_IMPULSE);}
  if (Dcc.getCV(CV_MODE_T3) > 1) {Dcc.setCV(CV_MODE_T3, MODE_IMPULSE);} if (Dcc.getCV(CV_MODE_T4) > 1) {Dcc.setCV(CV_MODE_T4, MODE_IMPULSE);}
  if (Dcc.getCV(CV_MODE_T5) > 1) {Dcc.setCV(CV_MODE_T5, MODE_IMPULSE);} if (Dcc.getCV(CV_MODE_T6) > 1) {Dcc.setCV(CV_MODE_T6, MODE_IMPULSE);}
  if (Dcc.getCV(CV_MODE_T7) > 1) {Dcc.setCV(CV_MODE_T7, MODE_IMPULSE);} if (Dcc.getCV(CV_MODE_T8) > 1) {Dcc.setCV(CV_MODE_T8, MODE_IMPULSE);}

  if (Dcc.getCV(CV_IMPULSE_TIME_T1) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T1, 10);} if (Dcc.getCV(CV_IMPULSE_TIME_T2) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T2, 10);}
  if (Dcc.getCV(CV_IMPULSE_TIME_T3) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T3, 10);} if (Dcc.getCV(CV_IMPULSE_TIME_T4) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T4, 10);}
  if (Dcc.getCV(CV_IMPULSE_TIME_T5) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T5, 10);} if (Dcc.getCV(CV_IMPULSE_TIME_T6) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T6, 10);}
  if (Dcc.getCV(CV_IMPULSE_TIME_T7) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T7, 10);} if (Dcc.getCV(CV_IMPULSE_TIME_T8) < 10) {Dcc.setCV(CV_IMPULSE_TIME_T8, 10);}

  
}
