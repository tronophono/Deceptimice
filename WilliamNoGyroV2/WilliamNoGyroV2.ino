//======================================================================
//                               WILLIAM
//
//                        Born: January 21, 2017
//
//                       Died: A Legend Never Dies
//
//======================================================================
//                         Credits: Joseph Muniz

//=============================================================================
// START OF FLOODFILL FUNCTIONS AND GLOBALS
//=============================================================================

static const int NorthW=0b100000000000;
static const int EastW=0b1000000000000;
static const int SouthW=0b10000000000000;
static const int WestW=0b100000000000000;
static const int deadBit=0b1000000000000000;
static char entryPoint='s';

static const int mask=0b1111100000000000; //sheds the wall status flags and extracts only the cell flood value




static const short int mazeSize=8; //has to be a square maze
unsigned int mousePosy=mazeSize-1;//starts mouse at bottom left corner
unsigned int mousePosx=0;

static unsigned int stack[128]; //512 max allowed moves
int stackPointer=0;



unsigned int mazeArray[mazeSize][mazeSize]=
  {
    {7,6,5,4,3,2,1,0},
    {8,7,6,5,4,3,2,1},
    {9,8,7,6,5,4,3,2},
    {10,9,8,7,6,5,4,3},
    {11,10,9,8,7,6,5,4},
    {12,11,10,9,8,7,6,5},
    {13,12,11,10,9,8,7,6},
    {14,13,12,11,10,9,8,7}
  };


unsigned int returnx;
unsigned int returny;

void mazeInit(); //sets the outer maze walls up
void printMaze();//duhhr
void floodfill();//starts the flood fill algorithm for one cycle. it contains the code that executes the initial stage
void stage2();
void deadEndReturn();
void stage3();
void solve();
void stackSave(unsigned int feedx, unsigned int feedy);





//=============================================================================
// END OF FLOODFILL FUNCTIONS AND GLOBALS
//=============================================================================

//==================================================
//      MOVEMENT AND MAPPING FUNCTIONS AND GLOBALS
//==================================================  

bool forwardWall=false;
bool leftWall=false;
bool rightWall=false;

bool movementCalculated=false;
char nextCellDirection='n';

bool turnTrigger=false;


bool encoderTrigger=false;

bool encoderStartCount=false;

volatile const int fullRotationEncoder=42;//number of times
//encoder increments in one rotation.
volatile const int fullCellEncoder=600;//number of times encoder must //650 before
  //increment to indicate the mouse has moved forward 1 cell.

void scanForWalls(); //reads the values from the IR sensors to 
void mapWalls();//depending on the direction the mouse is facing, it will
     //map forward, left, and right,save the results from scanForWalls() into the mazeArray

void alignment(); //this function will rotate the mouse so that it will
                  //be facing the direction it needs to be in to travel
                  //to the next cell

void turnLeft();
void turnRight();
void uTurn();

void goForward();

//==========================================================================
//    HECTORRRRRR!!!!!!! (GLOBALS AND FUNCTIONS)
//==========================================================================
const int irOne = A6; 
const int irTwo = A2; 
const int irThree = A3; 
const int irFour = A1; 
//const int irFive = A6; 
const int irSix = A0; 
int irFront; 

const int motorRa = 11;
const int motorRb = 6;
const int motorLa = 10;
const int motorLb = 8;

const int encLa = 2;
const int encLb = 3;
const int encRa = 4;
const int encRb = 5;

int sensorValueOne = 0;
int sensorValueTwo = 0;
int sensorValueThree = 0;
int sensorValueFour = 0;
int sensorValueFive = 0;
int sensorValueSix = 0; 

int thresholdFront = 119;
int thresholdLeft=50;
int thresholdRight=280;
//int thresholdMinLeft=140;
//int thresholdMinRight=280;


int powerR = 100;
int powerL=100;
int power=100;


void right(int power, int powerR);
void stopp();
void forward(int power, int powerR);
void backward(int power);
void left(int power, int powerR);

void hectorPinSetup();
void getIR();

//========================================================
// ENCODERS
//===================================================

volatile unsigned long lastTime_encoder1; //this variable will be used to keep track of time using the function: millis(). millis() returns an unsigned long value that is the number of milliseconds that have passed since the device was powered on. The number of milliseconds that have passed can't be negative, hence the unsigned part and it's going to be a huge number, hence the long part. If the arduino is powered off, millis() will restart at 0. It can keep track of time for 50 days continuously, at which point it will reset back to 0.
  const int encoder_1APin =4; //this is the pin number for one of the encoder's outputs (A). The encoder has two outputs, which come from the two sensors under the rim of the tire.
  const int encoder_1BPin =7; //pin number for the encoder's other output (B).
volatile  int encoder_1Counter =0; //this variable will keep track of the number of times the wheel has rotated incrementally. There are 48 incremental rotations in one full rotation for the wheel. Basically, when this number reaches 48 the wheel made one full rotation. The number 48 comes from the fact that there are 12 teeth along the rim of the wheel. There are also 12 spaces in between the teeth. So, one sensor (A or B) can have 24 different readings in one rotation (I think HIGH corresponds to when a sensor is directly underneath one of the teeth and LOW corresponds to when the sensor is underneath one of the spaces). Because there are 2 sensors, 2*24=48. 
  
 volatile unsigned long lastTime_encoder2;
  const int encoder_2APin =8;
  const int encoder_2BPin =11;
volatile  int encoder_2Counter =0;

  volatile boolean encoder_1ALastReading=digitalRead(encoder_1APin); //this variable will store the previous value of encoder output A (HIGH or LOW). I'm using the digitalRead() function to initialize the value. The reason this variable is volatile is to protect it. If a variable isn't used in the void setup() function or the void loop() function or any custom function you've made, the compiler will erase the variable to save space. However, we do need this variable because we're using it in the ISR() function. ISR stands for Interrupt Service Routine. The ISR() function is part of the Arduino library so it does not qualify as a custom function. 
  volatile boolean encoder_1BLastReading=digitalRead(encoder_1BPin); //same as previous line but for encoder output B.
  
  volatile boolean encoder_2ALastReading=digitalRead(encoder_2APin);
  volatile boolean encoder_2BLastReading=digitalRead(encoder_2BPin);

  volatile boolean encoder1_aToggle=true; //aToggle and bToggle are only used in the ISR() function so they're also volatile to prevent the compiler from erasing them. These variables will be used to prevent false readings. I set them both to true so that either half of the ISR() function can execute initially. When we're actually building the mouse I think only one of these should be set to true initially depending on which direction we want the wheel turn.
  volatile boolean encoder1_bToggle=true;
  
  volatile boolean encoder2_aToggle=true;
  volatile boolean encoder2_bToggle=true;
  
  int encoder1_aCount=0; //the total number of times encoder output A has changed from LOW to HIGH or HIGH to LOW.
  int encoder1_bCount=0; //same as above, but for encoder output B
  
  int encoder2_aCount=0;
  int encoder2_bCount=0;


char currentCardinal='n';

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() 
{
//maze setup
 mazeInit();
 stackSave(mousePosx,mousePosy);  //save the starting position
 
  
  //to set up a wall you need to do it in pairs. For example: if a cell has an east wall then the cell to the east of the that cell has a west wall.
  //both walls would have to be set in order for it to work
//  mazeArray[7][0]|=EastW;
//  mazeArray[7][1]|=WestW;
//
//  mazeArray[6][0]|=EastW;
//  mazeArray[6][1]|=WestW;
//
//  mazeArray[5][1]|=SouthW;
//  mazeArray[6][1]|=NorthW;
//
//  mazeArray[5][1] |=EastW;
//  mazeArray[5][2] |=WestW;
//
//  mazeArray[7][7] |=NorthW;
//  mazeArray[6][7] |=SouthW;
//
//  mazeArray[7][6] |=NorthW;
//  mazeArray[6][6] |=SouthW;
//
//  mazeArray[7][5] |=NorthW;
//  mazeArray[6][5] |=SouthW;
//
//  mazeArray[6][5] |=WestW;
//  mazeArray[6][4] |=EastW;
//
//  mazeArray[6][5] |=NorthW;
//  mazeArray[5][5] |=SouthW;
//
//  mazeArray[6][6] |=NorthW;
//  mazeArray[5][6] |=SouthW;



//end maze wall setup

//mazeArray[1][1]|=NorthW+EastW;
//mazeArray[0][1]|=SouthW;
//mazeArray[1][2]|=WestW;
//
//mazeArray[2][1]|=EastW;
//mazeArray[2][2]|=WestW;
//
//mazeArray[5][0]|=NorthW;
//mazeArray[4][0]|=SouthW;
//
//mazeArray[5][1]|=EastW+SouthW;
//mazeArray[5][2]|=WestW;
//y[6][1]|=NorthW;
//
//mazeArray[7][0]|=EastW;
//mazeArray[7][1]|=WestW;

//Serial.begin(115200);
// printMaze();

 lastTime_encoder1=0; //initializes lastTime. This is the time provided by millis() the last time millis() was used. Since the arduino will execute this code when it first starts up, lastTime is 0 seconds initially.
    pciSetup(encoder_1APin); //here we're using that custom function provided on the arduino website. This will turn encoderAPin into an interrupt pin.
    pciSetup(encoder_1BPin); //here we're using that custom function provided on the arduino website. This will turn encoderBPin into an interrupt pin.
    
    lastTime_encoder2=0; //initializes lastTime. This is the time provided by millis() the last time millis() was used. Since the arduino will execute this code when it first starts up, lastTime is 0 seconds initially.
    pciSetup(encoder_2APin); //here we're using that custom function provided on the arduino website. This will turn encoderAPin into an interrupt pin.
    pciSetup(encoder_2BPin); //here we're using that custom function provided on the arduino website. This will turn encoderBPin into an interrupt pin.

// hectorPinSetup();


//Serial.begin(9600);
movementCalculated=true;
delay(1000);
//solve();


//encoderStartCount=true;
//turnRight();
//Serial.begin(9600);
solve();

}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() 
{

//  Serial.print(encoder_1Counter);
//  Serial.print("\n");
  //turnRight();

  //goForward();
  
//getIR();
//  Serial.print("\t sensor 45 left = ");
//  Serial.print(sensorValueThree);
//  Serial.print("\t sensor 45 right = ");
//  Serial.print(sensorValueFour);
//  Serial.print("\t sensor left = ");
//  Serial.print(sensorValueOne);
//  Serial.print("\t sensor right = ");
//  Serial.print(sensorValueSix);
//  Serial.print("\t sensor front = ");
//  Serial.println(irFront);
}

//================================================================
//                GYRO FUNCTIONS
//===============================================================



//=============================================================================
//            THE FLOOD STARTS HERE!!
//=============================================================================

void printMaze()
{
int i=0;
int j=0;


for(i;i<mazeSize;i++)
{
//checks for north walls and prints them
    for(j; j<mazeSize;j++)
      {
        if(mazeArray[i][j] & NorthW)
        {
          if(j==mazeSize-1)
          {
            Serial.print("======");
          }
          else
          {
            Serial.print("====");
          }
        }
        else
        {
          Serial.print("    ");
        }
      }
j=0;    
Serial.print("\n");

//prints rows and vertical walls.

  
    for(j; j<mazeSize;j++)
    {
      //checks for left wall
      if(mazeArray[i][j]&WestW)
      {
        Serial.print("| ");
      }
      else
      {
        Serial.print("  ");
      }
      
      //prints cell value
      if((j==mousePosx)&&(i==mousePosy))
      {
        if(currentCardinal=='n')
        {
        Serial.print(" ^");
        }
        else if(currentCardinal=='s')
        {
        Serial.print(" v");
        }
        else if(currentCardinal=='e')
        {
        Serial.print(" >");
        }
        else if(currentCardinal=='w')
        {
        Serial.print(" <");
        }
        
      }
      else if(mazeArray[i][j]&deadBit)
      {
        Serial.print(" #");
      }
      else
      {
        int masked=mazeArray[i][j]&~mask;
        if(masked<10)
        {
          Serial.print(" ");
          int masked=mazeArray[i][j]&~mask;
          Serial.print(masked);
        }
        else
        {
          int masked=mazeArray[i][j]&~mask;
          Serial.print(masked);
        }
      }

      
      //checks for right wall
      if(j==mazeSize-1)
      {
         if(mazeArray[i][j]&EastW)
          {
            Serial.print(" |");
          }
        else
          {
            Serial.print("  ");
          }
      }
    }
    Serial.print("\n");
    j=0;

//prints south wall
    
    if(i==mazeSize-1)
      {
        for(j; j<mazeSize;j++)
      {
        if(mazeArray[i][j] & SouthW)
        {
          if(j==mazeSize-1)
          {
            Serial.print("======");
          }
          else
          {
            Serial.print("====");
          }
        }
        else
        {
          Serial.print("    ");
        }
      }

      Serial.print("\n");
      j=0;
      }
    
  }

}


void mazeInit()
{
  int i=0;
  int j=0;

  //set up top north walls and bottom walls
  for(j; j<mazeSize;j++)
  {
    mazeArray[0][j]|=NorthW;
    if(j!=0)
    {
    mazeArray[mazeSize-1][j]|=SouthW;
    }
  }
  
  //sets up left and right walls
  for(i;i<mazeSize;i++)
  {
    mazeArray[i][0]|=WestW;
    mazeArray[i][mazeSize-1]|=EastW;
  }
}

void floodfill()
{ 

  movementCalculated=false;

  if((mazeArray[mousePosy][mousePosx]&~mask)!=0){
  //scan open adjacent open cells in this order: up, right, left,down
  
  //i'm sorry these if statements are massive. here's what they're checking for in order:
  //1st condition: the cell next to the current one must have a smaller flood value
  //2nd condition: there's no wall blocking the path to the next cell
  //3rd condition: that there is a 'next' cell. Basically it's making sure that it's not at the edge of the maze.
  //4th condition: the next cell must not be a dead end.

  //scans the cell to the north
  if(((mazeArray[mousePosy-1][mousePosx]&~mask)<(mazeArray[mousePosy][mousePosx]&~mask))&&((mazeArray[mousePosy][mousePosx]&NorthW)==0)&&(mousePosy-1>=0)&&!(deadBit&mazeArray[mousePosy-1][mousePosx]))
  {
    //mazeArray[mousePosy][mousePosx]&=~mouseLocation;
    //mazeArray[mousePosy-1][mousePosx]|=mouseLocation;
    mousePosy=mousePosy-1;
    stackSave(mousePosx, mousePosy);
    entryPoint='s'; //this is the entry point of the new cell. Since the mouse moves north the entry point of the next cell is to the south.
  
    movementCalculated=true;
    nextCellDirection='n';
  }


  //scans the cell to the east
  else if(((mazeArray[mousePosy][mousePosx+1]&~mask)<(mazeArray[mousePosy][mousePosx]&~mask))&&((mazeArray[mousePosy][mousePosx]&EastW)==0)&&(mousePosx+1<=(mazeSize-1))&&!(deadBit&mazeArray[mousePosy][mousePosx+1]))
  {
    //mazeArray[mousePosy][mousePosx]&=~mouseLocation;
    //mazeArray[mousePosy][mousePosx+1]|=mouseLocation;
    mousePosx=mousePosx+1;
    stackSave(mousePosx, mousePosy);
    entryPoint='w';

    movementCalculated=true;
    nextCellDirection='e';
  }

    //scans the cell to the west for walls and a smaller flood value
  else if(((mazeArray[mousePosy][mousePosx-1]&~mask)<(mazeArray[mousePosy][mousePosx]&~mask))&&((mazeArray[mousePosy][mousePosx]&WestW)==0)&&(mousePosx-1>=0)&&!(deadBit&mazeArray[mousePosy][mousePosx-1]))
  {
   // mazeArray[mousePosy][mousePosx]&=~mouseLocation;
    //mazeArray[mousePosy][mousePosx-1]|=mouseLocation;
    mousePosx=mousePosx-1;
    stackSave(mousePosx, mousePosy);
    entryPoint='e';

    movementCalculated=true;
    nextCellDirection='w';
  }

  //scans the cell to the south for walls and a smaller flood value
   else if(((mazeArray[mousePosy+1][mousePosx]&~mask)<(mazeArray[mousePosy][mousePosx]&~mask))&&((mazeArray[mousePosy][mousePosx]&SouthW)==0)&&(mousePosy+1<=(mazeSize-1))&&!(deadBit&mazeArray[mousePosy+1][mousePosx]))
  {
    //mazeArray[mousePosy][mousePosx]&=~mouseLocation;
    //mazeArray[mousePosy+1][mousePosx]|=mouseLocation;
    mousePosy=mousePosy+1;
    stackSave(mousePosx, mousePosy);
    entryPoint='n';

    movementCalculated=true;
    nextCellDirection='s';
  }

  else 
  {
    stage2(); //if there are no adjacent cells whose flood value is smaller than the current cell with no walls or dead ends, then it will check to see
              //if the current cell is a dead end.
  }


  }
  
}


void stage2()
//this is where the mouse determines if it is currently at a dead end
{
  switch(entryPoint)
  {
    case 'n':
      if((mazeArray[mousePosy][mousePosx]& SouthW) && (mazeArray[mousePosy][mousePosx] &EastW) && (mazeArray[mousePosy][mousePosx] &WestW))
      {
        deadEndReturn(); //if the mouse entered the cell from the north and the other sides have walls, this will trigger the
                         //the function that makes it go back to where it came from.
        break;
      }
      else 
      {
        stage3();
        break;
      }

      

      case 's':
        if((mazeArray[mousePosy][mousePosx]& NorthW) && (mazeArray[mousePosy][mousePosx] &EastW) && (mazeArray[mousePosy][mousePosx] &WestW))

      {
        deadEndReturn();  
        break;                
      }
         else 
      {
        stage3();
        break;
      }



       case 'e':
        if((mazeArray[mousePosy][mousePosx]& SouthW) && (mazeArray[mousePosy][mousePosx] &NorthW) && (mazeArray[mousePosy][mousePosx] &WestW))

      {
        deadEndReturn();  
        break;                
      }
       else 
      {
        stage3();
        break;
      }

      

         case 'w':
        if((mazeArray[mousePosy][mousePosx]& SouthW) && (mazeArray[mousePosy][mousePosx] &EastW) && (mazeArray[mousePosy][mousePosx] &NorthW))

      {
        deadEndReturn();  
        break;                
      }
       else 
      {
        stage3();
        break;
      }
      
  }//end of switch
  
}

void deadEndReturn()
{
  mazeArray[mousePosy][mousePosx]|=deadBit;//sets the current cell to a dead end.
  stackPointer--;//removes the current cell from the stack

  switch(entryPoint)
  //checks which way it entered the dead end from and goes back one cell
  {
    case 'n':
    mousePosy--;

    movementCalculated=true;
    nextCellDirection='n';
    break;

    case 's':
    mousePosy++;

    movementCalculated=true;
    nextCellDirection='s';
    break;

    case 'e':
    mousePosx++;

    movementCalculated=true;
    nextCellDirection='e';
    break;

    case 'w':
    mousePosx--;

    movementCalculated=true;
    nextCellDirection='w';
    break;
    
  }
}


void stage3()
{
  int incrementSP=stackPointer;
if(incrementSP>=0)
{  
  for(incrementSP; incrementSP>=0; incrementSP--)
  {
    unsigned int readStack=stack[incrementSP];
    unsigned int omnomnom=0b1111111100000000;
    returnx=readStack&~omnomnom;
    returny=readStack&omnomnom;
    returny=returny>>8;



  //now we have to find the smallest value surrounding this cell in the stack and change the stack cell to that value +1 like in the previous function
  unsigned int surroundingN=10000;
  unsigned int surroundingS=10000;
  unsigned int surroundingE=10000;
  unsigned int surroundingW=10000;
  unsigned int smallestValue=0;
  //these variables will store the flood values of the surrounding cells. I made the default value high because the goal is to find the cell
  //with the smallest flood value. If a surrounding cell isn't assigned a new value (the only time this would happen is if it doesn't exist because
  //the mouse is already at the edge of the maze) then the very high value ensures that it won't be selected by the function.

  //grab the north value
  //1st condition: if the mouse is not against the north wall of the maze
  //2nd condition: and there is no north wall in the current cell
  //3rd condition: and the cell to the north hasn't been marked as a dead end
  if((returny-1>=0)&&!(mazeArray[returny][returnx]&NorthW)&&!(mazeArray[returny-1][returnx]&deadBit))
  {
    surroundingN=mazeArray[returny-1][returnx]&~mask;
  }

  //grab the south value
  if((returny+1<=(mazeSize-1))&&!(mazeArray[returny][returnx]&SouthW)&&!(mazeArray[returny+1][returnx]&deadBit))
  {
    surroundingS=mazeArray[returny+1][returnx]&~mask;
  }

  //grab the west value
  if((returnx-1>=0)&&!(mazeArray[returny][returnx]&WestW)&&!(mazeArray[returny][returnx-1]&deadBit))
  {
    surroundingW=mazeArray[returny][returnx-1]&~mask;
  }

  //grab the east value
    if((returnx+1<=(mazeSize-1))&&!(mazeArray[returny][returnx]&EastW)&&!(mazeArray[returny][returnx+1]&deadBit))
  {
    surroundingE=mazeArray[returny][returnx+1]&~mask;
  }

  //now that the values have been extracted, they have to be sorted to find the smallest value

  if((surroundingN<=surroundingS) && (surroundingN<=surroundingE) && (surroundingN<=surroundingW))
  {
    smallestValue=surroundingN;
  }
  else if((surroundingS<=surroundingN) && (surroundingS<=surroundingE) && (surroundingS<=surroundingW))
  {
    smallestValue=surroundingS;
  }
  else if((surroundingE<=surroundingN) && (surroundingE<=surroundingS) && (surroundingE<=surroundingW))
  {
    smallestValue=surroundingE;
  }
  else if((surroundingW<=surroundingN) && (surroundingW<=surroundingS) && (surroundingW<=surroundingE))
  {
    smallestValue=surroundingW;
  }

//the next lines take the smallest value, increase it by 1, then assign that value to the current position
  smallestValue++;
  mazeArray[returny][returnx]&=mask;
  mazeArray[returny][returnx]|=smallestValue;
  }

}
  
}

void stackSave(unsigned int feedx, unsigned int feedy)
//takes 2 values, the mouse x position and y position, then combines them into a single value that is then saved into the stack.
//the least significant 8 bits are the x position and the most significant 8 bits are the y position.
{
  unsigned int omnomnom=0b1111111100000000;
  unsigned int stackInsert=0;
  stackInsert=(feedx & ~omnomnom);
  unsigned int temp=(feedy & ~omnomnom);
  temp=temp<<8;
  stackInsert|=temp;
  stack[stackPointer]=stackInsert;
  stackPointer++;
}


void solve()
{
 while((mazeArray[mousePosy][mousePosx]&~mask)!=0)
{
//  floodfill();
//  printMaze();
//  alignment();
//  goForward();
//  printMaze();

  //here's the actual flow:
  //delay(200);
  scanForWalls();
  printMaze();
  floodfill();
  alignment();
  if(movementCalculated)
  {
    goForward();
  }
 // delay(1000);
  //and that's it! 1600+ lines of code for those 4 functions. Friggin Ridiculous......DID YOU KNOW THAT 15 MINUTES COULD SAVE YOU 15 OERCENT OR MORE ON CAR INSURANCE??!?!!?
  
}
//stopp();
//printMaze();
//Serial.print("Done!");
}


//===================================================================
//THE FLOOD STOPS HERE!!
//===================================================================

//=================================================================
// HECTOR!!!! FUNCTIONS
//==================================================================

void hectorPinSetup()
{
  pinMode(irOne, INPUT); 
  pinMode(irTwo, INPUT); 
  pinMode(irThree, INPUT); 
  pinMode(irFour, INPUT); 
  pinMode(irSix, INPUT); 
  
  pinMode(motorLa, OUTPUT); 
  pinMode(motorLb, OUTPUT); 
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);  
}


void stopp()
{

  analogWrite(motorRa, 0); 
  analogWrite(motorLa, 0);
  analogWrite(motorRb, 0); 
  analogWrite(motorLb, 0);
}

void forward(int power, int powerR)
{
    analogWrite(motorRa, powerR); 
    analogWrite(motorLa, power);
    analogWrite(motorRb, 0); 
    analogWrite(motorLb, 0);
}

void backward(int power)
{
    analogWrite(motorRa, 0); 
    analogWrite(motorLa, 0);
    analogWrite(motorRb, power); 
    analogWrite(motorLb, power);
}

void left(int power, int powerR)
{
    analogWrite(motorRa, powerR); 
    analogWrite(motorLa, 0);
    analogWrite(motorRb, 0); 
    analogWrite(motorLb, power);
}

void right(int power, int powerR)
{
    analogWrite(motorRa, 0); 
    analogWrite(motorLa, power);
    analogWrite(motorRb, powerR); 
    analogWrite(motorLb, 0);
}

void getIR()
{
  sensorValueOne = analogRead(irOne);
  sensorValueTwo = analogRead(irTwo);
  sensorValueThree = analogRead(irThree);
  sensorValueFour = analogRead(irFour);
  //sensorValueFive = analogRead(irFive);
  sensorValueSix = analogRead(irSix);
  irFront = sensorValueTwo;
}


//======================================================
//        Movement and Scanning Functions
//======================================================

void scanForWalls()
{
  forwardWall=false;
  leftWall=false;
  rightWall=false;

  
  getIR();

  //check sensor values to see if the exceed their threshold
  if(irFront>=thresholdFront)
  {
    forwardWall=true;
  }

  if(sensorValueOne>=thresholdLeft)
  {
    leftWall=true;
  }

  if(sensorValueSix>=thresholdRight)
  {
    rightWall=true;
  }

   mapWalls();
  
}

void mapWalls()
{
  //here we're going to map the results to the cardinal directions
  //depending on which direction the mouse is facing.

  if(currentCardinal=='n')
  {
    if(forwardWall)
    {
      mazeArray[mousePosy][mousePosx]|=NorthW;
      if(mousePosy-1>=0)
      {
        mazeArray[mousePosy-1][mousePosx]|=SouthW;
      }
    }

    if(leftWall)
    {
      mazeArray[mousePosy][mousePosx]|=WestW;
      if(mousePosx-1>=0)
      {
        mazeArray[mousePosy][mousePosx-1]|=EastW;
      }
    }
    if(rightWall)
    {
      mazeArray[mousePosy][mousePosx]|=EastW;
      if(mousePosx+1<=(mazeSize-1))
      {
        mazeArray[mousePosy][mousePosx+1]|=WestW;
      }
    }
    
  }

  else if(currentCardinal=='s')
  {
    if(forwardWall)
    {
      mazeArray[mousePosy][mousePosx]|=SouthW;
      if(mousePosy+1<=(mazeSize-1))
      {
        mazeArray[mousePosy+1][mousePosx]|=NorthW;
      }
    }

    if(leftWall)
    {
      mazeArray[mousePosy][mousePosx]|=EastW;
      if(mousePosx+1<=(mazeSize-1))
      {
        mazeArray[mousePosy][mousePosx+1]|=WestW;
      }
    }

    if(rightWall)
    {
      mazeArray[mousePosy][mousePosx]|=WestW;
      if(mousePosx-1>=0)
      {
        mazeArray[mousePosy][mousePosx-1]|=EastW;
      }
    }
  }

  else if(currentCardinal=='e')
  {
    if(forwardWall)
    {
      mazeArray[mousePosy][mousePosx]|=EastW;
      if(mousePosx+1<=(mazeSize-1))
      {
        mazeArray[mousePosy][mousePosx+1]|=WestW;
      }
    }

    if(leftWall)
    {
      mazeArray[mousePosy][mousePosx]|=NorthW;
      if(mousePosy-1>=0)
      {
        mazeArray[mousePosy-1][mousePosx]|=SouthW;
      }
    }

    if(rightWall)
    {
      mazeArray[mousePosy][mousePosx]|=SouthW;
      if(mousePosy+1<=(mazeSize-1))
      {
        mazeArray[mousePosy+1][mousePosx]|=NorthW;
      }
    }
  }

  else if(currentCardinal=='w')
  {
    if(forwardWall)
    {
      mazeArray[mousePosy][mousePosx]|=WestW;
      if(mousePosx-1>=0)
      {
        mazeArray[mousePosy][mousePosx-1]|=EastW;
      }
    }

    if(leftWall)
    {
      mazeArray[mousePosy][mousePosx]|=SouthW;
      if(mousePosy+1<=(mazeSize-1))
      {
        mazeArray[mousePosy+1][mousePosx]|=NorthW;
      }
    }

    if(rightWall)
    {
      mazeArray[mousePosy][mousePosx]|=NorthW;
      if(mousePosy-1>=0)
      {
        mazeArray[mousePosy-1][mousePosx]|=SouthW;
      }
    }
  }

  
}


void alignment()
{
  if(movementCalculated)
  {
    if(currentCardinal=='n')
    {
      if(nextCellDirection=='s')
      {
        //movementCalculated=false;
        uTurn();
      }

      else if(nextCellDirection=='e')
      {
        turnRight();
        //movementCalculated=false;
        
      }

      else if(nextCellDirection=='w')
      {
        //movementCalculated=false;
        turnLeft();
      }
    
    
    }//end of north check

    else if(currentCardinal=='s')
    {
      if(nextCellDirection=='n')
      {
        //movementCalculated=false;
        uTurn();
      }

      else if(nextCellDirection=='e')
      {
        //movementCalculated=false;
        turnLeft();
      }

      else if(nextCellDirection=='w')
      {
        //movementCalculated=false;
        turnRight();
      }

      
    }//end of south check

    else if(currentCardinal=='e')
    {
      if(nextCellDirection=='s')
      {
        //movementCalculated=false;
        turnRight();
      }

      else if(nextCellDirection=='n')
      {
        //movementCalculated=false;
        turnLeft();
      }

      else if(nextCellDirection=='w')
      {
        //movementCalculated=false;
        uTurn();
      }

      
    }//end of east check

    else if(currentCardinal=='w')
    {
        if(nextCellDirection=='s')
      {
        //movementCalculated=false;
        turnLeft();
      }

      else if(nextCellDirection=='e')
      {
       // movementCalculated=false;
        uTurn();
      }

      else if(nextCellDirection=='n')
      {
        //movementCalculated=false;
        turnRight();
      }

      
    }//end of west check

  
  }//end of movement calculated
  
}

void turnRight()
{
  int powerRightTurn=100;
  encoderStartCount=true;
      while(encoder_1Counter < 200 && encoder_2Counter < 200)
    {
      right(power, powerRightTurn);
      if(encoder_1Counter < encoder_2Counter && powerRightTurn < 120)
          powerRightTurn = powerRightTurn + 5;
      else if (encoder_1Counter > encoder_2Counter && powerRightTurn > 90)
        powerRightTurn = powerRightTurn - 5;

        //Serial.print(encoder_1Counter);
      //  Serial.print("\n");
        
    }
    stopp();
    encoder_1Counter=0;
    encoder_2Counter=0;
  currentCardinal=nextCellDirection;
}

void turnLeft()
{
  int powerLeftTurn=100;
  encoderStartCount=true;
   while(encoder_1Counter < 200 && encoder_2Counter < 200)
    {
      left(power, powerLeftTurn);
      if(encoder_1Counter < encoder_2Counter && powerLeftTurn < 120)
          powerLeftTurn = powerLeftTurn + 5;
      else if (encoder_1Counter > encoder_2Counter && powerLeftTurn > 90)
        powerLeftTurn = powerLeftTurn - 5;
    }
    stopp();
  currentCardinal=nextCellDirection;
  encoder_1Counter=0;
    encoder_2Counter=0;
}

void uTurn()
{
  encoderStartCount=true;
      while(encoder_1Counter < 200 && encoder_2Counter < 200)
    {
      right(power, powerR);
      if(encoder_1Counter < encoder_2Counter && powerR < 120)
          powerR = powerR + 5;
      else if (encoder_1Counter > encoder_2Counter && powerR > 90)
        powerR = powerR - 5;

        
        
    }
    encoder_1Counter=0;
    encoder_2Counter=0;

      encoderStartCount=true;
      while(encoder_1Counter < 200 && encoder_2Counter < 200)
    {
      right(power, powerR);
      if(encoder_1Counter < encoder_2Counter && powerR < 120)
          powerR = powerR + 5;
      else if (encoder_1Counter > encoder_2Counter && powerR > 90)
        powerR = powerR - 5;

        
    }
    encoder_1Counter=0;
    encoder_2Counter=0;
  currentCardinal=nextCellDirection;
  encoder_1Counter=0;
    encoder_2Counter=0;
}

void goForward()
{
  //encoder_1Counter is right wheel
if(movementCalculated)
{
  encoderStartCount=true;
  while(encoder_1Counter<=fullCellEncoder)
  {
    
 if(encoder_1Counter< encoder_2Counter && powerR < 120)
      powerR = powerR + 5;
  else if (encoder_1Counter > encoder_2Counter && powerR > 90)
    powerR = powerR - 5;
  forward(power, powerR);
  }
  stopp();
  encoderStartCount=false;
  encoder_1Counter=0;
  encoder_2Counter=0;

}
}

//====================================================================================================
//          ENCODER FUNCTIONS
//================================================================================
void pciSetup(int pin) //this is a custom function that I found from the arduino page: http://playground.arduino.cc/Main/PinChangeInterrupt The webpage explains it better than I can. Using this function will turn a digital pin into an interrupt pin. Usually the digital pins can be inputs or outputs. An interrupt pin is a special kind of input pin. The arduino doesn't care whether an input pin changes or not. The only time it will care about its value is if digitalRead() is used. With an interrupt pin, the arduino will become sensitive to every change in the interrupt pin's state (LOW to HIGH or HIGH to LOW). If the arduino detects a change of state in the interrupt pin, the program will stop what it's doing and execute the code in the ISR() function. When all that code is finished executing, it will resume the main program where it last left off. Later in the code, we're going to use this function twice to turn encoderAPin and encoderBPin into interrupt pins.
  
  {
      *digitalPinToPCMSK(pin) |=bit(digitalPinToPCMSKbit(pin));
      PCIFR |=bit(digitalPinToPCICRbit(pin));
      PCICR |=bit(digitalPinToPCICRbit(pin));
  }

  ISR(PCINT0_vect) //this is the Interrupt Service Routine. The value inside the parenthisis corresponds to a range of pins. If you look on an Arduino uno board you'll see 3 main sections for input/output pins. The analog pins, A0-A5 are in PCINT1_vect. The digital pins, D13-D8 are in PCINT0_vect. And the digital pins, D0-D7 are in PCINT2_vect. When you're making the ISR() function you have to use one of these 3 vectors. Let's say you made digital pin 13 an interrupt pin, then you would put PCINT0_vect in the parenthesis. When pin 13's state changes, the code in your ISR() will execute immediately. If for some reason you have 2 interrupt pins and they're in different vectors, say digital pin 0 and digital pin 13, then you have to make 2 ISR() functions, one with PCINT0_vect in the parenthesis, and one with PCINT2_vect in the other. If you have 2 interrupt pins and they're in the same vector, say digital pin 13 and digital pin 12, (both in PCINT0_vect) then you only make 1 ISR() function and a change in either pin will trigger the code in ISR(PCINT0_vect)
  //in our case, here, since encoderAPin (pin 8) and encoderBPin (pin 11) are our interrupt pins and they're in the same vector, we only need to make 1 ISR() function and we use PCINT2_vect as our parameter for the function.

  {

    if(encoderStartCount){
    
    if(digitalRead(encoder_2APin)!=encoder_2ALastReading&&digitalRead(encoder_2BPin)==encoder_2BLastReading&&encoder2_aToggle) //There's 2 main parts to our ISR function (the code in the 2 if statements). The first if statement will only execute if the current encoderAPin state doesn't match the last reading (meaning encoderAPin's state just changed) AND if encoderBPin's state is the same as the previous reading (meaning encoderBPin's state didn't change) AND if aToggle is true. To understand why aToggle is neccessary, look at the truth table in this link (scroll down just a bit) http://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/ If you look at the truth table, you'll notice that at each time transition (t1 to t2, t2 to t3, t3 to t4, etc.) Only 1 output (A or B) is changing. They both can't change at the same time (that's what the first 2 conditions of the if statement are for; to make sure only 1 output is changing at a time.) Also notice how A and B take turns alternating in changes. A changes, then B changes, then A changes, etc. A can't change twice in a row. It has to wait for B change before it can change again. Same goes for B. That's what aToggle and bToggle are for. Without these two toggles, one of the outputs can be allowed to oscillate rapidly between states without the other output changing at all (this can happen when the tire is shaking or bouncing). If this behavior occurs, it will give a false reading and make the program think the wheel is rotating.
    {
      encoder_2Counter++; //increments the counter, indicating the wheel has rotated slightly.
      encoder_2ALastReading=!encoder_2ALastReading; //toggles the last reading for encoder output A. If it was HIGH, now it's LOW and vice versa.
      encoder2_aCount++; //increases aCount by 1.
      encoder2_aToggle=false; //by setting aToggle to false, this if statement can't execute again until the next if statement executes.
      encoder2_bToggle=true; //sets bToggle to true so that the next if statement can execute.
    }
  
    if(digitalRead(encoder_2BPin)!=encoder_2BLastReading&&digitalRead(encoder_2APin)==encoder_2ALastReading&&encoder2_bToggle) //The conditions for this if statement to execute are similar to the previous one except that it relies on encoderBpin changing states AND encoderApin not changing AND bToggle being true.
    {
      encoder_2Counter++; //increments the counter, indicating the wheel has rotated slightly.
      encoder_2BLastReading=!encoder_2BLastReading; //toggles the last reading for encoder output B. If it was HIGH, now it's LOW and vice versa.
      encoder2_bCount++; //increases bCount by 1.
      encoder2_aToggle=true; //sets aToggle to true so that the previous if statement can now execute again.
      encoder2_bToggle=false; //by setting bToggle to false, this if statement can't execute again until the previous if statement executes. (the 2 if statements flip flop and take turns executing)
    }

    }
  }
  
  
  ISR(PCINT2_vect) //this is the Interrupt Service Routine. The value inside the parenthisis corresponds to a range of pins. If you look on an Arduino uno board you'll see 3 main sections for input/output pins. The analog pins, A0-A5 are in PCINT1_vect. The digital pins, D13-D8 are in PCINT0_vect. And the digital pins, D0-D7 are in PCINT2_vect. When you're making the ISR() function you have to use one of these 3 vectors. Let's say you made digital pin 13 an interrupt pin, then you would put PCINT0_vect in the parenthesis. When pin 13's state changes, the code in your ISR() will execute immediately. If for some reason you have 2 interrupt pins and they're in different vectors, say digital pin 0 and digital pin 13, then you have to make 2 ISR() functions, one with PCINT0_vect in the parenthesis, and one with PCINT2_vect in the other. If you have 2 interrupt pins and they're in the same vector, say digital pin 13 and digital pin 12, (both in PCINT0_vect) then you only make 1 ISR() function and a change in either pin will trigger the code in ISR(PCINT0_vect)
  //in our case, here, since encoderAPin (pin 4) and encoderBPin (pin 7) are our interrupt pins and they're in the same vector, we only need to make 1 ISR() function and we use PCINT2_vect as our parameter for the function.
  {

    if(encoderStartCount){
    
    if(digitalRead(encoder_1APin)!=encoder_1ALastReading&&digitalRead(encoder_1BPin)==encoder_1BLastReading&&encoder1_aToggle) //There's 2 main parts to our ISR function (the code in the 2 if statements). The first if statement will only execute if the current encoderAPin state doesn't match the last reading (meaning encoderAPin's state just changed) AND if encoderBPin's state is the same as the previous reading (meaning encoderBPin's state didn't change) AND if aToggle is true. To understand why aToggle is neccessary, look at the truth table in this link (scroll down just a bit) http://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/ If you look at the truth table, you'll notice that at each time transition (t1 to t2, t2 to t3, t3 to t4, etc.) Only 1 output (A or B) is changing. They both can't change at the same time (that's what the first 2 conditions of the if statement are for; to make sure only 1 output is changing at a time.) Also notice how A and B take turns alternating in changes. A changes, then B changes, then A changes, etc. A can't change twice in a row. It has to wait for B change before it can change again. Same goes for B. That's what aToggle and bToggle are for. Without these two toggles, one of the outputs can be allowed to oscillate rapidly between states without the other output changing at all (this can happen when the tire is shaking or bouncing). If this behavior occurs, it will give a false reading and make the program think the wheel is rotating.
    {
      encoder_1Counter++; //increments the counter, indicating the wheel has rotated slightly.
      encoder_1ALastReading=!encoder_1ALastReading; //toggles the last reading for encoder output A. If it was HIGH, now it's LOW and vice versa.
      encoder1_aCount++; //increases aCount by 1.
      encoder1_aToggle=false; //by setting aToggle to false, this if statement can't execute again until the next if statement executes.
      encoder1_bToggle=true; //sets bToggle to true so that the next if statement can execute.
    }
  
    if(digitalRead(encoder_1BPin)!=encoder_1BLastReading&&digitalRead(encoder_1APin)==encoder_1ALastReading&&encoder1_bToggle) //The conditions for this if statement to execute are similar to the previous one except that it relies on encoderBpin changing states AND encoderApin not changing AND bToggle being true.
    {
      encoder_1Counter++; //increments the counter, indicating the wheel has rotated slightly.
      encoder_1BLastReading=!encoder_1BLastReading; //toggles the last reading for encoder output B. If it was HIGH, now it's LOW and vice versa.
      encoder1_bCount++; //increases bCount by 1.
      encoder1_aToggle=true; //sets aToggle to true so that the previous if statement can now execute again.
      encoder1_bToggle=false; //by setting bToggle to false, this if statement can't execute again until the previous if statement executes. (the 2 if statements flip flop and take turns executing)
    }

    }
  }


