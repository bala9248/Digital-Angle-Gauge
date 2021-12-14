/**************************************************************************************************
*@File Command_handler.c
*This file handles the supported commands entered by the user by doing the following things:
*i)  Accumulates a line
*ii) Performs lexing on the accumulated line and seperates the string into argv[]
*iii)Calls the appropriate handler to perform the command
*
*@Author Balapranesh Elango
*
*Citations : Howdy Pierce's Lecture
*
***************************************************************************************************/
#include "Command_handler.h"


typedef void (*command_handler_t)(int, char *argv[]);


//Structure for Command handling
typedef struct {
  const char *name;           //name of the command as entered by the user
  command_handler_t handler;  //the handler function for the respective command
  const char *help_string;    //The help string that needs to be printed out
} command_table_t;


#define    BUFFER_SIZE    1024                               //Size of the Accumulated line buffer
#define    MAX_LEN        640                                //Maximum length for hexdump
#define    RED_COLOR      0xFF                               //Maximum Intensity of the LED in PWM
#define    BLUE_COLOR     0xFF                               //Maximum Intensity of the LED in PWM
#define    GREEN_COLOR    0xFF                               //Maximum Intensity of the LED in PWM
#define    LED_OFF	      0x00                               //Zero intensity -> LED off
#define    abs(x)         (x < 0) ? (-x) : (x)               //Absolute value
#define    START_SCAN	  TSI0->DATA |= TSI_DATA_SWTS_MASK   //Software Trigger Start
#define    ONE_SECOND     1000                               //1 second in milli-second
#define    MAX_DEG		  180                                //Maximum angle that can measure using DAG
#define    PCT_95         0.95                               // 0.95
#define    MAX_RANGE	  100                                //Maximum range of angle for PWM for checking "flatness"
#define    MAX_STRLN	  9                                  //Maximum string length for help command
/*
 * Static Function's Declarations
 *
 * Function descriptions are present in the function itself
 */
static void process_command(char *input) ;
static void handle_set(int argc, char *argv[]);
static void handle_info(int argc, char *argv[]);
static void handle_calibrate(int argc, char *argv[]);
static void handle_author(int argc, char *argv[]);
static void handle_help(int argc, char *argv[]);


//Array of structure- each element of the array corresponds to one command
static const command_table_t commands[] = { {"author", handle_author, "Prints the name of the author"},
											{"help", handle_help, "Information on all the existing commands"},
											{"calibrate", handle_calibrate, "Set the relative 0 degree angle for the DAG"},
											{"info", handle_info, "prints out the current angle of the DAG w.r.t to relative zero, relative zero degree angle, calibration status, max measurable angle w.r.t relative zero"},
											{"set", handle_set, "to use the DAG and set the desired angle as entered by the user - Enter set <angle> (Ex: set 45)"}
										  };


static const int num_commands =  sizeof(commands) / sizeof(command_table_t); //Number of supported commands
static int relative_zero;       //To keep track of the relative zero value(calibration value)
static bool calibrate = false;  //To keep track of calibration status (True -> Calibrated / False -> Not calibrated)
static int max_measurable_angle = 180; //To keep track of the maximum measurable angle with respect to zero




/*
 * void command_line_interface()
 *
 * Receives the User input from the Serial terminal and accumulates into
 * a line buffer and sends it for lexical processing
 *
 * non_blocking_getchar() is non-blocking and allows for simultaneous reception of commands
 * and checking if the DAG is placed flat on the table
 * Parameters:
 *   none
 *
 * Returns:
 *   None
 */
void command_line_interface(){
	printf("\n\r\n\rDigital Angle Gauge - Type 'Help' to know more about the commands");
	led_con(RED_COLOR, GREEN_COLOR, BLUE_COLOR);
	bool flag = false;


	//The non_blocking_getchar() is non-blocking, so that it can simultanously receive commands and check if the DAG is flat on the table
	while(1){
		char user_input[BUFFER_SIZE]; //Buffer to store the user input
		char *input;
		char ch ;
		int position ; //To keep track of the position of the cursor
		if(flag == false){
			printf("\n");
			printf("\r");
			printf("?");
			printf(" ");
			input = &user_input[0];//Input will be taken character by character
			ch ='_';//Initializing '_' so that it enters the while loop
			position = 0; //To keep track of the position of the cursor
			flag = true;
		}

		if(ch != '\r' && ch != '\n'){  //To receive input until user hits Enter
			ch  = non_blocking_getchar(); //getting the input from the user using non blocking get char

			if(ch != '\0'){   //Checking if a valid byte has been dequeued

					if(ch == '\b'){                 //If user hits backspace,
													//pointer is decremented so that it can over-written and backspace should not work
													//when there is nothing written by the user
						if(position > 0){
							putchar(ch);//Echoing the received input
							input--;//Decrementing pointer so that it can be overwritten
							position--;//keeping track of position
							printf(" ");//Getting rid of the current character
							printf("\b");//getting rid of the above space
						}
					}
					else{
						putchar(ch);//Echoing the received input
						position++;//keeping track of position
						*input++ = ch; //character is stored and pointer is incremented
					}
				}
		}
		else
			flag = false; //If user enters 'enter'

		if(flag == false){                 //A command has been entered by the user
			*input = '\0';                 //Null terminating the string
			process_command(user_input);   //Accumulated line is sent for lexical processing
		}

		  /*Since no command is entered, we are checking if the DAG is placed perfectly flat on the table
		  If it is placed perfectly flat on the table, the red LED is lit
		  If it is not flat the color transitions from RED to GREEN using PWM depending on the angle.

		  THIS IS DONE ONLY IF THE DAG IS NOT CALIBRATED. As, we do not want to change the color
		  of the LED after it has been calibrated*/

		if(calibrate == false){  //When not calibrated
			int roll = abs(read_roll()); //Current roll
			float pct = 0.00;
			pct =  ((float)roll/(float)MAX_RANGE);  //Calculating percent for PWM
			pct = 1 - pct;

			if(pct > PCT_95) //To stabilize the output
				pct = 1;
			if(roll > MAX_RANGE)
				pct = 0;

			led_con((pct)*RED_COLOR, (1-pct)*GREEN_COLOR, LED_OFF); //PWM transition from RED to GREEN as we move away from zero degrees(not flat)
		}

	}

}




/*
 * static void process_command(char *input)
 *
 * Performs Lexical Analysis on the input string and seperates all the words and puts it
 * into argv[] and calls the appropriate handler for that command
 *
 * Parameters:
 *           none
 *
 * Returns:
 *           None
 */
static void process_command(char *input) {
  char *p = input;
  char *end;

  // find end of string
  for (end = input; *end != '\0'; end++)
    ;

  // Tokenize input in place
  bool in_token = false;
  char *argv[10]; //To hold the strings which are seperated by blankspace
  int argc = 0;//To keep track of number of argv
  bool flag = true;//To tokenize input
  memset(argv, 0, sizeof(argv));

  for (p = input; p < end; p++) {
	  if( *p != ' ' && *p != '\r' && *p != '\t') //If the current character is not a space or '\r', in_token is true
		  in_token = true;
	  else
		  in_token = false;

	  if(in_token == true && flag == true){//This is the first character of the string in that token
		  argv[argc] = p;
		  argc++;
		  flag = false;
	  }
	  else if(in_token == false && flag == false){//First white space when not in token
		  *p = '\0'; //filling the first white space with a '\0'
		  flag = true; //To put \0 in one blank space only
	  }
  }

  if (argc == 0)   // no command
    return;

  flag = false;
  for (int i=0; i < num_commands; i++) { //Dispatching commands
  		if (strcasecmp(argv[0], commands[i].name) == 0) { //Comparing user input and command name
  	      commands[i].handler(argc, argv); //command handler is called if true and flag is set
  	      flag = true; //setting the flag
  	      break;
  	    }
  }
  if(flag == false) //Unknown command check
	  printf("\n\rUnknown command: %s", argv[0]);
}

/*
 * static void handle_set(int argc, char *argv[])
 *
 * Handler function to handle the set command
 * Used to attain the Desired angle on the DAG
 *
 * Parameters:
 *     argc   - number of "Words"
 *     argv[] - all "words" in array
 *
 * Returns:
 *           None
 */
static void handle_set(int argc, char *argv[]){

	if(argc != 2){
		printf("\n\rInvalid Command for set -- look at help");  //User input Error handling
		return;
	}

	reset_touch(); //Reset previous touch sensor presses

	int final_angle, angle, roll;
	float pct = 0.00;

	char *temp = argv[1];

	//Input error check to make sure user entered a number and not alphabets or special characters
	for(int i = 0; i < strlen(temp); i++){
		if(temp[i] >= '0' && temp[i] <= '9')         //To check is input is a number
			continue;
		else{
			printf("\n\rEnter a number as an input");  //If the input is not a number, it is considered as an invalid input
			return;
		}

	}

	sscanf(argv[1], "%d", &final_angle);  //Converting entered string(value of the angle) to integer


	/* Check to see if entered angle is valid
	 * For example if relative zero = 160; the user can only measure a maximum of 30 degrees(180 - 160)
	 * So, if the user enters a value greater than 30, its an error
	 */
	if( final_angle > max_measurable_angle || final_angle < 0){
		printf("\n\rEnter a valid set angle!! Range: 0 - %d", max_measurable_angle ); 	//If entered angle is greater than maximum measurable angle
		return;
	}


	printf("\n\rMove the DAG towards %d\n\r", final_angle);  //The DAG must be moved towards the desired angle
	bool flag = false;       //Flag to check if angle has been set


	START_SCAN;              //Start Software trigger for touch sensor
	//User MUST press the touch sensor to come out of this loop
	reset_timer();
	while(!Touch_Scan_LH()) {

		START_SCAN;              //Start Software trigger for touch sensor

        roll = read_roll();      //Read the current roll of the sensor
        angle = abs(roll) - relative_zero; //Making the roll values relative to the calibrated value
	    angle = abs(angle);      //Converting negative readings to positive
	    pct =  ((float)(angle))/((float)(final_angle));  //Calculating the percentage for PWM with LED

	    if(flag == false && roll >= relative_zero)
	    	led_con(LED_OFF, ((1 - pct))*GREEN_COLOR , (pct)*BLUE_COLOR); //Transitions from GREEN to BLUE as we move towards the desired angle

	    if( (get_timer() > ONE_SECOND) && flag == false){ //Printing the current angle every one second so that the user understands which direction to move

	    	reset_timer();

	    	if(roll >= relative_zero) //check to see if DAG is moving in the current direction
	    		printf("\n\rCurrent Angle = %d; Final Angle = %d", angle, final_angle);
	    	else
	    		printf("\n\rWRONG DIRECTION!!!");
	    }

	    if(angle == final_angle && flag == false && roll >= relative_zero){    //When desired angle is set in the right direction

	    	printf("\n\r%d angle set successfully -- Press touch sensor to get back to the command processor", final_angle);
	    	led_con(LED_OFF, LED_OFF, BLUE_COLOR);
	    	flag = true;
	    }
	}
	led_con(RED_COLOR, GREEN_COLOR, BLUE_COLOR);  //White color is lit after the user presses the touch sensor and comes out of the loop

	/* Calibration reset */
	relative_zero = 0;
	calibrate = false;
	max_measurable_angle = MAX_DEG;
	printf("\n\rCalibrate the DAG again in-order to use it; relative zero set to %d", relative_zero);
}


/*
 * static void handle_info(int argc, char *argv[])
 *
 * Handler function to handle the info command
 * Gives information on : 1) Calibration status
 *                        2) Relative Zero Degree angle
 *                        3) Angle with respect to the Relative Zero Degree Angle
 *
 * Parameters:
 *     argc   - number of "Words"
 *     argv[] - all "words" in array
 *
 * Returns:
 *           None
 */
static void handle_info(int argc, char *argv[]){
	if(argc != 1){
		printf("\n\rInvalid Command for info -- look at help"); //User input Error handling
		return;
	}
	int roll;
	roll = read_roll();
	printf("\n\rRelative Zero = %d; Current Angle W.r.t to Relative zero = %d",relative_zero, (abs(roll) - relative_zero) );
	printf("\n\rDAG Calibration Status = ");
	printf("%s", calibrate ? "TRUE" : "FALSE");  //If calibrate is true, TRUE is printed otherwise FALSE is printed
	printf("\n\rMaximum Measurable Angle = %d", max_measurable_angle);
}



/*
 * static void handle_calibrate(int argc, char *argv[])
 *
 *  Handler function to handle the calibrate command
 *  Used to calibrate the DAG to the required relative zero angle
 *
 * Parameters:
 *     argc   - number of "Words"
 *     argv[] - all "words" in array
 *
 * Returns:
 *           None
 */
static void handle_calibrate(int argc, char *argv[]){
	if(argc != 1){
		printf("\n\rInvalid Command for calibrate -- look at help"); //User input Error handling
		return;
	}

	restart_switch();  //Clear previous switch presses and only check for switch press beyond this point
	calibrate = true;
	printf("\n\rPlace the DAG in the position where you want to set it as 0 degrees and press the switch");
	led_con(RED_COLOR, GREEN_COLOR, BLUE_COLOR); //White LED is lit before the DAG is calibrated
	while( !gpio_button_pressed() )
	    ; //Wait till the switch is pressed

	int roll;
	roll = read_roll();                   //Read current roll
	relative_zero = abs(roll);            //Relative zero is set as the absolute value of roll
	led_con(LED_OFF,GREEN_COLOR,LED_OFF); //Green led is lit after calibration

	printf("\n\rCalibrated Successfully\n\r");
	printf("\n\rRelative zero = %d", relative_zero);
	max_measurable_angle = (MAX_DEG - relative_zero);
	printf("\n\rMaximum Angle that can be measure = %d", max_measurable_angle);
}



/*
 * static void handle_author(int argc, char *argv[])
 *
 * Handler function to handle the author command
 * Prints the Author
 *
 * Parameters:
 *   *input - Accumulated Line
 *
 * Returns:
 *   None
 */
static void handle_author(int argc, char *argv[]){
	if (argc == 1)
		printf("\n\rBalapranesh Elango"); //Prints the name of the author
	else
		printf("\n\rInvalid input for author -- Check help"); //User input Error handling
}




/*
 * static void handle_help(int argc, char *argv[])
 *
 * Handler function to handle the help command
 * Prints out useful information on all available commands
 *
 * Parameters:
 *   argc   - number of "Words"
 *   argv[] - all "words" in array
 *
 * Returns:
 *   None
 */
static void handle_help(int argc, char *argv[]){
	if(argc != 1){//argc should be 1 for help
		printf("\n\rInvalid input for help -- Check help"); //User input Error handling
		return;
	}

	printf("\n\r********Information on all supported commands************");
	for(int i = 0; i < num_commands; i++){
		if(strlen(commands[i].name) < MAX_STRLN)   //To make sure /t aligns properly
			printf("\n\r%s\t - \t%s",commands[i].name, commands[i].help_string ); //printing the help string
		else
			printf("\n\r%s- \t%s",commands[i].name, commands[i].help_string ); //printing the help string
	}

	printf("\n\r**********************************************************");
}





