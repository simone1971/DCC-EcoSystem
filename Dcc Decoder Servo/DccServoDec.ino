/* Servo rottion Angle is proportional to the PWM ON time from 0,5 and 2,5 milliseconds
 * CALCULATIONS.
 * PWM Frequencz = 60Hz  -> Cycle = 1000 / 60 = 16.66ms
 * PWM Resolution = 4096 -> 1 tick = 16.66 / 4096 = 0.004096ms
 * 
 * PWM Value for 0.5ms Pulse = 0.5 / 0.004096 = 122.8
 * PWM Value for 2.5ms Pulse = 2.5 / 0.004096 = 614.4
 */

#include <NmraDcc.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// This Example shows how to use the library as a DCC Accessory Decoder or a DCC Signalling Decoder
// It responds to both the normal DCC Turnout Control packets and the newer DCC Signal Aspect packets 
// You can also print every DCC packet by uncommenting the "#define NOTIFY_DCC_MSG" line below

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

NmraDcc  Dcc ;

#define DCC_PIN     2
#define DccAckPin   3

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
#define CV_POSMIN_S9    49
#define CV_POSMIN_S10   50
#define CV_POSMIN_S11   51
#define CV_POSMIN_S12   52
#define CV_POSMIN_S13   53
#define CV_POSMIN_S14   54
#define CV_POSMIN_S15   55
#define CV_POSMIN_S16   56

#define CV_POSMAX_S1    61
#define CV_POSMAX_S2    62
#define CV_POSMAX_S3    63
#define CV_POSMAX_S4    64
#define CV_POSMAX_S5    65
#define CV_POSMAX_S6    66
#define CV_POSMAX_S7    67
#define CV_POSMAX_S8    68
#define CV_POSMAX_S9    69
#define CV_POSMAX_S10   70
#define CV_POSMAX_S11   71
#define CV_POSMAX_S12   72
#define CV_POSMAX_S13   73
#define CV_POSMAX_S14   74
#define CV_POSMAX_S15   75
#define CV_POSMAX_S16   76

int FirstServo = Dcc.getCV(1);
int NumServos = Dcc.getCV(33);

#define SERVOMIN  0 // Minimum Posistion For Servos in °
#define SERVOMAX  180 // Maximum Posistion For Servos in °
#define SERVO_FREQ 60 // Analog servos run at ~60 Hz updates


void slowMove(int servoNum, int delayTime, int from, int to)
{
  if (to > from)
  {
    for (int i = from; i < to; i++)   
    {
      pwm.setPWM(servoNum, 0, i);
      delay(delayTime);
    }
  }
  else
  {
    for (int i = from; i > to; i--)
    {
      pwm.setPWM(servoNum, 0, i);
      delay(delayTime);
    }
  }
}



// This function is called by the NmraDcc library when a DCC ACK needs to be sent
// Calling this function should cause an increased 60ma current drain on the power supply for 6ms to ACK a CV Read 
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

int POSMIN_S1 = map(Dcc.getCV(CV_POSMIN_S1), 0, 180, 125, 615);int POSMIN_S2 = map(Dcc.getCV(CV_POSMIN_S2), 0, 180, 125, 615);
int POSMIN_S3 = map(Dcc.getCV(CV_POSMIN_S3), 0, 180, 125, 615);int POSMIN_S4 = map(Dcc.getCV(CV_POSMIN_S4), 0, 180, 125, 615);
int POSMIN_S5 = map(Dcc.getCV(CV_POSMIN_S5), 0, 180, 125, 615);int POSMIN_S6 = map(Dcc.getCV(CV_POSMIN_S6), 0, 180, 125, 615);
int POSMIN_S7 = map(Dcc.getCV(CV_POSMIN_S7), 0, 180, 125, 615);int POSMIN_S8 = map(Dcc.getCV(CV_POSMIN_S8), 0, 180, 125, 615);
int POSMIN_S9 = map(Dcc.getCV(CV_POSMIN_S9), 0, 180, 125, 615);int POSMIN_S10 = map(Dcc.getCV(CV_POSMIN_S10), 0, 180, 125, 615);
int POSMIN_S11 = map(Dcc.getCV(CV_POSMIN_S11), 0, 180, 125, 615);int POSMIN_S12 = map(Dcc.getCV(CV_POSMIN_S12), 0, 180, 125, 615);
int POSMIN_S13 = map(Dcc.getCV(CV_POSMIN_S13), 0, 180, 125, 615);int POSMIN_S14 = map(Dcc.getCV(CV_POSMIN_S14), 0, 180, 125, 615);
int POSMIN_S15 = map(Dcc.getCV(CV_POSMIN_S15), 0, 180, 125, 615);int POSMIN_S16 = map(Dcc.getCV(CV_POSMIN_S16), 0, 180, 125, 615);

int POSMAX_S1 = map(Dcc.getCV(CV_POSMAX_S1), 0, 180, 125, 615);int POSMAX_S2 = map(Dcc.getCV(CV_POSMAX_S2), 0, 180, 125, 615);
int POSMAX_S3 = map(Dcc.getCV(CV_POSMAX_S3), 0, 180, 125, 615);int POSMAX_S4 = map(Dcc.getCV(CV_POSMAX_S4), 0, 180, 125, 615);
int POSMAX_S5 = map(Dcc.getCV(CV_POSMAX_S5), 0, 180, 125, 615);int POSMAX_S6 = map(Dcc.getCV(CV_POSMAX_S6), 0, 180, 125, 615);
int POSMAX_S7 = map(Dcc.getCV(CV_POSMAX_S7), 0, 180, 125, 615);int POSMAX_S8 = map(Dcc.getCV(CV_POSMAX_S8), 0, 180, 125, 615);
int POSMAX_S9 = map(Dcc.getCV(CV_POSMAX_S9), 0, 180, 125, 615);int POSMAX_S10 = map(Dcc.getCV(CV_POSMAX_S10), 0, 180, 125, 615);
int POSMAX_S11 = map(Dcc.getCV(CV_POSMAX_S11), 0, 180, 125, 615);int POSMAX_S12 = map(Dcc.getCV(CV_POSMAX_S12), 0, 180, 125, 615);
int POSMAX_S13 = map(Dcc.getCV(CV_POSMAX_S13), 0, 180, 125, 615);int POSMAX_S14 = map(Dcc.getCV(CV_POSMAX_S14), 0, 180, 125, 615);
int POSMAX_S15 = map(Dcc.getCV(CV_POSMAX_S15), 0, 180, 125, 615);int POSMAX_S16 = map(Dcc.getCV(CV_POSMAX_S16), 0, 180, 125, 615);
  
  Serial.print("notifyDccAccTurnoutOutput: ") ;
  Serial.print(Addr,DEC) ;
  Serial.print(',');
  Serial.print(Direction,DEC) ;
  Serial.print(',');
  Serial.println(OutputPower, HEX) ;
  Serial.println(POSMIN_S1);
  
  int ACTSERVOMIN [16] = {POSMIN_S1, POSMIN_S2, POSMIN_S3, POSMIN_S4,
                          POSMIN_S5, POSMIN_S6, POSMIN_S7, POSMIN_S8,
                          POSMIN_S9, POSMIN_S10, POSMIN_S11, POSMIN_S12,
                          POSMIN_S13, POSMIN_S14, POSMIN_S15, POSMIN_S16};
  int ACTSERVOMAX [16] = {POSMAX_S1, POSMAX_S2, POSMAX_S3, POSMAX_S4,
                          POSMAX_S5, POSMAX_S6, POSMAX_S7, POSMAX_S8,
                          POSMAX_S9, POSMAX_S10, POSMAX_S11, POSMAX_S12,
                          POSMAX_S13, POSMAX_S14, POSMAX_S15, POSMAX_S16};
  int ActServo         = (Addr - FirstServo);

    
  if ((Addr >= FirstServo) && (Addr < (FirstServo + NumServos))) {
    if (Direction == 0){
      Serial.print("servo No ");Serial.print(ActServo);Serial.print(" From ");Serial.print(ACTSERVOMAX[ActServo]);
      Serial.print(" To ");Serial.print(ACTSERVOMIN[ActServo]);Serial.print(" at Speed ");Serial.println(Dcc.getCV(CV_SERVO_SPEED));
      slowMove (ActServo, Dcc.getCV(CV_SERVO_SPEED), ACTSERVOMAX[ActServo], ACTSERVOMIN[ActServo]);
    } else {
      Serial.print("servo No ");Serial.print(ActServo);Serial.print(" From ");Serial.print(ACTSERVOMIN[ActServo]);
      Serial.print(" To ");Serial.print(ACTSERVOMAX[ActServo]);Serial.print(" at Speed ");Serial.println(Dcc.getCV(CV_SERVO_SPEED));
      slowMove (ActServo, Dcc.getCV(CV_SERVO_SPEED), ACTSERVOMIN[ActServo], ACTSERVOMAX[ActServo]);
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
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, 21);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, 0);

  Dcc.setCV(CV_NUM_SERVOS, 16);
  Dcc.setCV(CV_SERVO_SPEED, 15);
  Dcc.setCV(CV_DUMMY_PROV, 0);
  
  Dcc.setCV(CV_POSMIN_S1, SERVOMIN); Dcc.setCV(CV_POSMIN_S2, SERVOMIN); Dcc.setCV(CV_POSMIN_S3, SERVOMIN); Dcc.setCV(CV_POSMIN_S4, SERVOMIN);
  Dcc.setCV(CV_POSMIN_S5, SERVOMIN); Dcc.setCV(CV_POSMIN_S6, SERVOMIN); Dcc.setCV(CV_POSMIN_S7, SERVOMIN); Dcc.setCV(CV_POSMIN_S8, SERVOMIN);
  Dcc.setCV(CV_POSMIN_S9, SERVOMIN); Dcc.setCV(CV_POSMIN_S10, SERVOMIN); Dcc.setCV(CV_POSMIN_S11, SERVOMIN); Dcc.setCV(CV_POSMIN_S12, SERVOMIN);
  Dcc.setCV(CV_POSMIN_S13, SERVOMIN); Dcc.setCV(CV_POSMIN_S14, SERVOMIN); Dcc.setCV(CV_POSMIN_S15, SERVOMIN); Dcc.setCV(CV_POSMIN_S16, SERVOMIN);

  Dcc.setCV(CV_POSMAX_S1, SERVOMAX); Dcc.setCV(CV_POSMAX_S2, SERVOMAX); Dcc.setCV(CV_POSMAX_S3, SERVOMAX); Dcc.setCV(CV_POSMAX_S4, SERVOMAX);
  Dcc.setCV(CV_POSMAX_S5, SERVOMAX); Dcc.setCV(CV_POSMAX_S6, SERVOMAX); Dcc.setCV(CV_POSMAX_S7, SERVOMAX); Dcc.setCV(CV_POSMAX_S8, SERVOMAX);
  Dcc.setCV(CV_POSMAX_S9, SERVOMAX); Dcc.setCV(CV_POSMAX_S10, SERVOMAX); Dcc.setCV(CV_POSMAX_S11, SERVOMAX); Dcc.setCV(CV_POSMAX_S12, SERVOMAX);
  Dcc.setCV(CV_POSMAX_S13, SERVOMAX); Dcc.setCV(CV_POSMAX_S14, SERVOMAX); Dcc.setCV(CV_POSMAX_S15, SERVOMAX); Dcc.setCV(CV_POSMAX_S16, SERVOMAX);

}

void setup() {
  
  Serial.begin(115200);
  
  // Configure the DCC CV Programing ACK pin for an output
  pinMode( DccAckPin, OUTPUT );

  // Setup which External Interrupt, the Pin it's associated with that we're using and enable the Pull-Up
  // Many Arduino Cores now support the digitalPinToInterrupt() function that makes it easier to figure out the
  // Interrupt Number for the Arduino Pin number, which reduces confusion. 
#ifdef digitalPinToInterrupt
  Dcc.pin(DCC_PIN, 0);
#else
  Dcc.pin(0, DCC_PIN, 1);
#endif
  
  // Call the main DCC Init function to enable the DCC Receiver
  Dcc.init( MAN_ID_DIY, 1, FLAGS_DCC_ACCESSORY_DECODER | FLAGS_OUTPUT_ADDRESS_MODE, 0 );

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~60 Hz updates

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
  if (Dcc.getCV(CV_POSMIN_S9) > Dcc.getCV(CV_POSMAX_S9)) {Dcc.setCV(CV_POSMIN_S9, Dcc.getCV(CV_POSMAX_S9));} if (Dcc.getCV(CV_POSMIN_S10) > Dcc.getCV(CV_POSMAX_S10)) {Dcc.setCV(CV_POSMIN_S10, Dcc.getCV(CV_POSMAX_S10));}
  if (Dcc.getCV(CV_POSMIN_S11) > Dcc.getCV(CV_POSMAX_S11)) {Dcc.setCV(CV_POSMIN_S11, Dcc.getCV(CV_POSMAX_S11));} if (Dcc.getCV(CV_POSMIN_S12) > Dcc.getCV(CV_POSMAX_S12)) {Dcc.setCV(CV_POSMIN_S12, Dcc.getCV(CV_POSMAX_S12));}
  if (Dcc.getCV(CV_POSMIN_S13) > Dcc.getCV(CV_POSMAX_S13)) {Dcc.setCV(CV_POSMIN_S13, Dcc.getCV(CV_POSMAX_S13));} if (Dcc.getCV(CV_POSMIN_S14) > Dcc.getCV(CV_POSMAX_S14)) {Dcc.setCV(CV_POSMIN_S14, Dcc.getCV(CV_POSMAX_S14));}
  if (Dcc.getCV(CV_POSMIN_S15) > Dcc.getCV(CV_POSMAX_S15)) {Dcc.setCV(CV_POSMIN_S15, Dcc.getCV(CV_POSMAX_S15));} if (Dcc.getCV(CV_POSMIN_S16) > Dcc.getCV(CV_POSMAX_S16)) {Dcc.setCV(CV_POSMIN_S16, Dcc.getCV(CV_POSMAX_S16));}
  
 //If any Max Position is set greater than 180°, it will be set at 180°   
  if (Dcc.getCV(CV_POSMAX_S1) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S1, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S2) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S2, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S3) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S3, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S4) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S4, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S5) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S5, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S6) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S6, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S7) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S7, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S8) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S8, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S9) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S9, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S10) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S10, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S11) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S11, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S12) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S12, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S13) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S13, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S14) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S14, SERVOMAX);}
  if (Dcc.getCV(CV_POSMAX_S15) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S15, SERVOMAX);} if (Dcc.getCV(CV_POSMAX_S16) > SERVOMAX) {Dcc.setCV(CV_POSMAX_S16, SERVOMAX);}

}
