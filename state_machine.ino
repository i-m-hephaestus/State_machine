//this example is not coded with the best practice in mind but will give you an idea of how the state machine operates in a simple form without delays in the loop
//you will need two bread board wires. install one from GND to D17 and one from GND to either D11 or D17 while the program is running to see the input status change in the serial monitor
//D17 input is an example of how to create and interupt in the wire is pulled.
//the inputs are pulled up and when grounded will change state. this is a good practice to control unwanted EMI from interferring with pin state
//the time_interval values can be changed to control whens fuctions are scanned loop_interval, time_Interval_input_1, time_Interval_input_2, operation_interupt_interval
//download the program to the board. I used a MEGA 2560 but this should work on an classic board.
//once the arduino resets open the serial monitor - upper right corner button with the magnifier circle looking thingy 
//make sure to uncheck the autoscroll, move the slider up to the top of the output screen and hit the reset button on the arduino to see the first line of output
//a loop counter shows how changes affect the loop rate as more functions are added

int input_1_pin = 2;    
int input_2_pin = 11;     
int input_3_pin = 17;

bool input_1_state = 0;
bool input_2_state = 0;
bool input_3_state = 0;

unsigned long loop_count = 0;
unsigned long loop_count_last = 0;

//state model timers 
//timer variables
unsigned long current_millis = 0;         //value of millis at the beginning of the loop

//check loop_rate timer
int loop_rate_count = 1;
unsigned long loop_count_now = 0;
unsigned long loop_millis_last = 0;
unsigned long loop_millis = 0;               //value of millis tracked in loop_rate
long loop_interval = 1000;              //check interval time value

//check input_1 timer

unsigned long input_1_millis = 0;               //value of millis tracked in input_1
long time_Interval_input_1 = 1500;              //check interval time value

//check input_2 timer
unsigned long input_2_millis = 0;               //value of millis tracked in input_2
long time_Interval_input_2 = 2000;              //check interval time value

//operation interupt input_3
unsigned long operation_interupt_millis = 0;       //value of millis recorded 
const long operation_interupt_interval = 500;

void setup(void)
{
  //Input 
  pinMode(input_1_pin, INPUT_PULLUP);
  pinMode(input_2_pin, INPUT_PULLUP);
  pinMode(input_3_pin, INPUT_PULLUP);
  
  //Start communication   
  Serial.begin(9600);                   // start and set the data rate for the programming and debug hardware Serial port (pins 0,1)
  delay(500);                           // only delay used and its outside the loop
}

void loop()
{
  current_millis = millis();               /* captures the value of millis - millis returns the number of milliseconds since the Arduino board began running the current
                                             program. This number will overflow (go back to zero), after approximately 50 days. */
  //Serial.print("top of the loop"); 
  if (loop_count < 1)       //shows the intialized state
    {
      Serial.println(" ");
      Serial.print("loop count at start of loop ");
      Serial.println(loop_count);
    }
  loop_count = loop_count + 1;
  
  loop_rate();           // checks loop rate and displays in serial monitor
  //input_1();             // checks the status of input_1 and displays status in serial monitor - delete // to add into loop
  //input_2();             // checks the status of input_2 and displays in serial monitor - delete // to add into loop
  operation_interupt_check();   // checks the status of input_3 and displays in serial monitor - delete // to add into loop
}
  
void loop_rate()
{ 
  if (current_millis > loop_millis + loop_interval)
  {
    //Time counter
    loop_millis = current_millis;
    Serial.println(" ");
    Serial.print("* current loop_rate count ");
    Serial.println(loop_rate_count);
    Serial.print("* current millis ");
    Serial.println(current_millis);
    
    if (loop_rate_count <= 1)
      { 
        loop_millis_last = loop_millis;
      }
    else
      {
        loop_millis_last = loop_millis / loop_rate_count;
      }
    Serial.println(" ");
    Serial.print("** milliseconds between scans ");
    Serial.println(loop_millis_last);
    loop_rate_count = loop_rate_count + 1;
    
    //loop scan rate counter
    Serial.print("** total processor loop count ");
    Serial.println(loop_count);
    Serial.println(" ");
   }
}
 
void input_1()
{
  if (current_millis > input_1_millis + time_Interval_input_1)
  {
    input_1_millis = millis();
    input_1_state = digitalRead(input_1_pin);
    Serial.println(" ");
    Serial.print("***INPUT 1 STATE ");
    Serial.println(input_1_state);
  }
}

void input_2()
{
  if (current_millis > input_2_millis + time_Interval_input_2)
  {
    input_2_millis = millis();
    input_2_state = digitalRead(input_2_pin);   // will retain value based on time_Interval_input_2 setting
    Serial.println(" ");
    Serial.print("*** INPUT 2 STATE ");
    Serial.println(input_2_state);
  }
}

void operation_interupt_check()
{
  if (current_millis - operation_interupt_millis >= operation_interupt_interval)    //
    {
      operation_interupt_millis = millis();
      input_3_state = digitalRead(input_3_pin);   // will retain value based on time_Interval_input_2 setting
      Serial.println(" ");
      Serial.print("*** INPUT 3 STATE ");
      Serial.println(input_3_state);
    }
}