# State_machine
this example is not coded with the best practice in mind but will give you an idea of how the state machine operates in a simple form without delays in the loop
you will need two bread board wires. install one from GND to D17 and one from GND to either D11 or D17 while the program is running to see the input status change in the serial monitor
the inputs are pulled up and when grounded will change state. this is a good practice to control unwanted EMI from interferring with pin state
the time_interval values can be changed to control whens fuctions are scanned loop_interval, time_Interval_input_1, time_Interval_input_2, operation_interupt_interval
download the program to the board. I used a MEGA 2560 but this should work on an classic board.
deleted the leading // to add input_1(); and input_2(); functions
once the arduino resets open the serial monitor - upper right corner button with the magnifier circle looking thingy 
make sure to uncheck the autoscroll, move the slider up to the top of the output screen and hit the reset button on the arduino to see the first line of output
a loop counter shows how changes affect the loop rate as more functions are added
