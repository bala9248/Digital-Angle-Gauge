# Digital Angle Gauge (DAG)
 Code for PES Final Project. Fall - 2021

#Basic Functionality:

1.  This DAG has a UART based command proccessor in its core/
2.  Before accumulating the command in the command_line_interface(),
    I have written my own non blocking get char function which will
    allow for other functionality while accumulating a line buffer.
    This other functionality is checking if the DAG is perfectly flat
    on the table. If the DAG is flat, RED LED is lit. Otherwise the color
    is varied using PWM.
    
3.  After taking a command as an input, the command is processed. The 
    following commands are supported by the command processor.
    
    i) Calibrate - To set the relative zero degree angle with a switch.
    
    ii) Set <angle> - Lets the user choose an angle to move the DAG to 
                      and moves the DAG to the desired angle.
    
    iii) info - Gives useful insight about the DAG
 
    iV) Help - Prints out useful information about all the available commands
 
     V) Author - Prints the name of the Author
 
A detailed overview of the functionality is provided in the Functionality and Corner Cases.pdf in Digital-Angle-Gauge/Supporting Files and Video/Functionality and Corner     Cases.pdf\
Link: https://github.com/bala9248/Digital-Angle-Gauge/blob/main/Supporting%20Files%20and%20Video/Functionality%20and%20Corner%20Cases.pdf

#Technologies Used:
 1) Command Processor\
       => Interrupt based UART\
       => Circular Buffer Fifo
 
 2) Accelerometer Sensor (MMA8451Q)\
       => I2C Interface
 
 3) Interrupts\
       => GPIO Interrupt - Switch\
       => Touch Sensor Interrupt
 
 4) Pulse Width Modulation for LED
 
 5) Systick Timer to manage timing related activities
 
 #Demo Video:\
 The demo video is available in the Digital-Angle-Gauge/Supporting Files and Video/ folder in this repo.\
 Link: https://github.com/bala9248/Digital-Angle-Gauge/blob/main/Supporting%20Files%20and%20Video/Digital_Angle_Gauge_Demo.mp4
 NOTE: The wrong direction!!! comment on the UART is printed only because the current roll is lesser than the calibrated relative zero.\
 In the real world, we would start from relative zero and progress towards the desired angle. Thus, Wrong Direction!!! won't be printed\
 in the real world while using the DAG.
 
 #Testing:
 Automatic, Semi-Automatic, and Manual tests were performed. More on this in the "Digital-Angle-Gauge/Supporting Files and Video/" folder
 of this repo.
 Test Plan - How testing was carried out for each item. Also, briefly includes happy cases testing, Error cases testing, Corner cases testing.\
 Test Results - Shows all the test results for various tests done for all peripherals.\
 
 Test Plan Link: https://github.com/bala9248/Digital-Angle-Gauge/blob/main/Supporting%20Files%20and%20Video/Test%20Plan.pdf
 Test Results link: https://github.com/bala9248/Digital-Angle-Gauge/blob/main/Supporting%20Files%20and%20Video/Test%20Results.pdf
 
 #Corner Cases:
 Various Corner cases were handled. All the corner cases that were handled are written in the Functionality and Corner Cases.pdf\
 in the "Digital-Angle-Gauge/Supporting Files and Video/" folder of this repo.
 Corner Cases link: https://github.com/bala9248/Digital-Angle-Gauge/blob/main/Supporting%20Files%20and%20Video/Functionality%20and%20Corner%20Cases.pdf
 
