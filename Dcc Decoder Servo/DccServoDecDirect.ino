/* Firmware for Direct Connetion to Arduino Pins
 *this firmware can manage up to 8 servos connected to digital pins 4 to 11
 */

#include <NmraDcc.h>
#include <Servo.h>

// You can also print every DCC packet by uncommenting the "#define NOTIFY_DCC_MSG" line below
// #define NOTIFY_DCC_MSG

NmraDcc  Dcc ;

#define DCC_PIN     2
#define DccAckPin   3

#define Turnout1Pin 4
#define Turnout2Pin 5
#define Turnout3Pin 6
#define Turnout4Pin 7
#define Turnout5Pin 8
#define Turnout6Pin 9
#define Turnout7Pin 10
#define Turnout8Pin 11

#define CV_NUM_SERVOS   33
#define CV_SERVO_SPEED  34
#define CV_DUMMY_PROV   35

#define CV_POSMIN_S1    41
#define CV_POSMIN_S2    42
#define CV_POSMIN_S3    43
#define CV_POSMIN_S4    44
#define CV_POSMIN_S5    45
#define CV_POSMIN_S6    46
#define CV_POSMIN_S7    47
#define CV_POSMIN_S8    48

#define CV_POSMAX_S1    61
#define CV_POSMAX_S2    62
#define CV_POSMAX_S3    63
#define CV_POSMAX_S4    64
#define CV_POSMAX_S5    65
#define CV_POSMAX_S6    66
#define CV_POSMAX_S7    67
#define CV_POSMAX_S8    68

Servo Turnout1; Servo Turnout2; Servo Turnout3; Servo Turnout4;
Servo Turnout5; Servo Turnout6; Servo Turnout7; Servo Turnout8;

int FirstServo = Dcc.getCV(1);
int NumServos = Dcc.getCV(33);
int DefaultMinPos = 50;
int DefaultMaxPos = 100;

#define SERVOMIN  0 // Minimum Posistion For Servos in °
#define SERVOMAX  180 // Maximum Posistion For Servos in °
#define SERVO_FREQ 50 // Analog servos run at ~60 Hz updates


void slowMove(Servo ServoAct, int delayTime, int from, int to)
{
  if (to > from)
  {
    for (int i = from; i < to; i++)   
    {
      ServoAct.write(i);
      delay(delayTime);
    }
  }
  else
  {
    for (int i = from; i > to; i--)
    {
      ServoAct.write(i);
      delay(delayTime);
    }
  }
}



// This function is called by the NmraDcc library when a DCC ACK needs to be sent
// Calling this function should cause an increased 60ma current drain on the power supply for 8ms to ACK a CV Read 
void notifyCVAck(void)
{
  Serial.println("notifyCVAck") ;
  
  digitalWrite( DccAckPin, HIGH );
  delay( 8 );  
  digitalWrite( DccAckPin, LOW );
}

// This function is called whenever a normal DCC Turnout Packet is received and we're in Output Addressing Mode
void notifyDccAccTurnoutOutput( uint16_t Addr, uint8_t Direction, uint8_t OutputPower )
{

int POSMIN_S1 = Dcc.getCV(CV_POSMIN_S1); int POSMIN_S2 = Dcc.getCV(CV_POSMIN_S2);
int POSMIN_S3 = Dcc.getCV(CV_POSMIN_S3); int POSMIN_S4 = Dcc.getCV(CV_POSMIN_S4);
int POSMIN_S5 = Dcc.getCV(CV_POSMIN_S5); int POSMIN_S6 = Dcc.getCV(CV_POSMIN_S6);
int POSMIN_S7 = Dcc.getCV(CV_POSMIN_S7); int POSMIN_S8 = Dcc.getCV(CV_POSMIN_S8);

int POSMAX_S1 = Dcc.getCV(CV_POSMAX_S1); int POSMAX_S2 = Dcc.getCV(CV_POSMAX_S2);
int POSMAX_S3 = Dcc.getCV(CV_POSMAX_S3); int POSMAX_S4 = Dcc.getCV(CV_POSMAX_S4);
int POSMAX_S5 = Dcc.getCV(CV_POSMAX_S5); int POSMAX_S6 = Dcc.getCV(CV_POSMAX_S6);
int POSMAX_S7 = Dcc.getCV(CV_POSMAX_S7); int POSMAX_S8 = Dcc.getCV(CV_POSMAX_S8);
  
  Serial.print("notifyDccAccTurnoutOutput: ") ;
  Serial.print(Addr,DEC) ;
  Serial.print(',');
  Serial.print(Direction,DEC) ;
  Serial.print(',');
  Serial.println(OutputPower, HEX) ;
   
  int ACTSERVOMIN [8] =   {POSMIN_S1, POSMIN_S2, POSMIN_S3, POSMIN_S4,
                          POSMIN_S5, POSMIN_S6, POSMIN_S7, POSMIN_S8};
  int ACTSERVOMAX [8] =   {POSMAX_S1, POSMAX_S2, POSMAX_S3, POSMAX_S4,
                          POSMAX_S5, POSMAX_S6, POSMAX_S7, POSMAX_S8};
  int ActServo        =   (Addr - FirstServo); 
  
Servo ServoAct    [8] =   {Turnout1, Turnout2, Turnout3, Turnout4,
                          Turnout5, Turnout6, Turnout7, Turnout8}; 
    
  if ((Addr >= FirstServo) && (Addr < (FirstServo + NumServos))) {
    if (Direction == 0){
      Serial.print("servo No ");Serial.print(ActServo);Serial.print(" From ");Serial.print(ACTSERVOMAX[ActServo]);
      Serial.print(" To ");Serial.print(ACTSERVOMIN[ActServo]);Serial.print(" at Speed ");Serial.println(Dcc.getCV(CV_SERVO_SPEED));
      slowMove (ServoAct[ActServo], Dcc.getCV(CV_SERVO_SPEED), ACTSERVOMAX[ActServo], ACTSERVOMIN[ActServo]);
    } else {
      Serial.print("servo No ");Serial.print(ActServo);Serial.print(" From ");Serial.print(ACTSERVOMIN[ActServo]);
      Serial.print(" To ");Serial.print(ACTSERVOMAX[ActServo]);Serial.print(" at Speed ");Serial.println(Dcc.getCV(CV_SERVO_SPEED));
      slowMove (ServoAct[ActServo], Dcc.getCV(CV_SERVO_SPEED), ACTSERVOMIN[ActServo], ACTSERVOMAX[ActServo]);
  }
}
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

  Dcc.setCV(CV_NUM_SERVOS, 8);
  Dcc.setCV(CV_SERVO_SPEED, 60);
  Dcc.setCV(CV_DUMMY_PROV, 0);
  
  Dcc.setCV(CV_POSMIN_S1, DefaultMinPos); Dcc.setCV(CV_POSMIN_S2, DefaultMinPos); Dcc.setCV(CV_POSMIN_S3, DefaultMinPos); Dcc.setCV(CV_POSMIN_S4, DefaultMinPos);
  Dcc.setCV(CV_POSMIN_S5, DefaultMinPos); Dcc.setCV(CV_POSMIN_S6, DefaultMinPos); Dcc.setCV(CV_POSMIN_S7, DefaultMinPos); Dcc.setCV(CV_POSMIN_S8, DefaultMinPos);
  
  Dcc.setCV(CV_POSMAX_S1, DefaultMaxPos); Dcc.setCV(CV_POSMAX_S2, DefaultMaxPos); Dcc.setCV(CV_POSMAX_S3, DefaultMaxPos); Dcc.setCV(CV_POSMAX_S4, DefaultMaxPos);
  Dcc.setCV(CV_POSMAX_S5, DefaultMaxPos); Dcc.setCV(CV_POSMAX_S6, DefaultMaxPos); Dcc.setCV(CV_POSMAX_S7, DefaultMaxPos); Dcc.setCV(CV_POSMAX_S8, DefaultMaxPos);
  
}

void setup() {
  
  Serial.begin(115200);
  
  // Configure the DCC CV Programing ACK pin for an output
  pinMode( DccAckPin, OUTPUT );
  
  // Configure te Servo Output Pins
  pinMode(Turnout1Pin, OUTPUT); pinMode(Turnout2Pin, OUTPUT); pinMode(Turnout3Pin, OUTPUT); pinMode(Turnout4Pin, OUTPUT);
  pinMode(Turnout5Pin, OUTPUT); pinMode(Turnout6Pin, OUTPUT); pinMode(Turnout7Pin, OUTPUT); pinMode(Turnout8Pin, OUTPUT);
  
  Turnout1.attach(Turnout1Pin); Turnout2.attach(Turnout2Pin); Turnout3.attach(Turnout3Pin); Turnout4.attach(Turnout4Pin);
  Turnout5.attach(Turnout5Pin); Turnout6.attach(Turnout6Pin); Turnout7.attach(Turnout7Pin); Turnout8.attach(Turnout8Pin);
  
  // Setup which External Interrupt, the Pin it's associated with that we're using and enable the Pull-Up
  // Many Arduino Cores now support the digitalPinToInterrupt() function that makes it easier to figure out the
  // Interrupt Number for the Arduino Pin number, which reduces confusion. 
#ifdef digitalPinToInterrupt
  Dcc.pin(DCC_PIN, 0);
#else
  Dcc.pin(0, DCC_PIN, 1);
#endif
  
  // Call the main DCC Init function to enable the DCC Receiver
  Dcc.init( MAN_ID_DIY, 2, FLAGS_DCC_ACCESSORY_DECODER | FLAGS_OUTPUT_ADDRESS_MODE, 0 );


  Serial.println("Setup Complete, Decoder Running");
  Serial.print("Servomotor Decoder v. ");Serial.println(Dcc.getCV(CV_VERSION_ID));
  Serial.print("First Address: ");Serial.println(Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_LSB) + (Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_MSB) * 256));
  Serial.print("Number of Declared Servos: ");Serial.println(Dcc.getCV(33));
}

void loop() {
  
 // You MUST call the NmraDcc.process() method frequently from the Arduino loop() function for correct library operation
  Dcc.process();

 //If any Min Position is set greater than respective Max Position, it will be set as Max position
  if (Dcc.getCV(CV_POSMIN_S1) > Dcc.getCV(CV_POSMAX_S1)) {Dcc.setCV(CV_POSMIN_S1, Dcc.getCV(CV_POSMAX_S1));} if (Dcc.getCV(CV_POSMIN_S2) > Dcc.getCV(CV_POSMAX_S2)) {Dcc.setCV(CV_POSMIN_S2, Dcc.getCV(CV_POSMAX_S2));}
  if (Dcc.getCV(CV_POSMIN_S3) > Dcc.getCV(CV_POSMAX_S3)) {Dcc.setCV(CV_POSMIN_S3, Dcc.getCV(CV_POSMAX_S3));} if (Dcc.getCV(CV_POSMIN_S4) > Dcc.getCV(CV_POSMAX_S4)) {Dcc.setCV(CV_POSMIN_S4, Dcc.getCV(CV_POSMAX_S4));}
  if (Dcc.getCV(CV_POSMIN_S5) > Dcc.getCV(CV_POSMAX_S5)) {Dcc.setCV(CV_POSMIN_S5, Dcc.getCV(CV_POSMAX_S5));} if (Dcc.getCV(CV_POSMIN_S6) > Dcc.getCV(CV_POSMAX_S6)) {Dcc.setCV(CV_POSMIN_S6, Dcc.getCV(CV_POSMAX_S6));}
  if (Dcc.getCV(CV_POSMIN_S7) > Dcc.getCV(CV_POSMAX_S7)) {Dcc.setCV(CV_POSMIN_S7, Dcc.getCV(CV_POSMAX_S7));} if (Dcc.getCV(CV_POSMIN_S8) > Dcc.getCV(CV_POSMAX_S8)) {Dcc.setCV(CV_POSMIN_S8, Dcc.getCV(CV_POSMAX_S8));}
    
 //If any Max Position is set greater than 180°, it will be set at 180°   
  if (Dcc.getCV(CV_POSMAX_S1) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S1, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S2) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S2, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S3) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S3, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S4) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S4, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S5) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S5, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S6) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S6, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S7) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S7, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S8) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S8, SERVOMAX);}
  
}
