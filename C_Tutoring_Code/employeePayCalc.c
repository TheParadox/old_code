/*
*	Programmer: Mark Pizzolatto
*	Class: CS2060-004
*	Program: Example 3.20 program.
*		This program is designed to take an employees hours, wages, and IRA 
*		contribution then display a paystub that display previously
*		listed values along with amount paid in state and federal taxes.
*		
*	Files: main.c	
*/

#include <stdio.h> //standard input/output library
#include <ctype.h> //this is used for a function called tolower - will see it later

//can either do this for true/false or use <stdbool.h>
#define TRUE 1 
#define FALSE 0 //false is not used in this example
//these allow me to define letters (in a manner of speaking) as numers 
//without have to remember what those numbers are!
//these are the decimal representations of ascii lower case 'a' through 'e'
#define A 97 
#define B 98
#define C 99
#define D 100
#define E 101

//function declarations, more on them - above the function definitions below
void displayMenu();
int program();

float handleInput();

float calculateGrossWage(float hours, float wage);
float calculateIRA(float grossWage, float iraRate, float* iraAmnt);
float calculateTaxes(float* netWage, float taxRate);

void systemPause();


//MAIN PROGRAM
int main(int argc, char* argv[]){

	//wait its only 2 lines long ?
	program();

	return 0;
}

//this is used to display the menu.
//note that you can break a printf over multiple lines.
//Nothing is required for concatination. But don't foget the newlines at the 
//end of each line you wish to print.
void displayMenu(){
	printf(
	"-----------------------------------------------\n"
	"1 or a) Enter employee hours\n"
	"2 or b) Enter employee wage\n"
	"3 or c) Enter employee IRA contribution\n"
	"4 or d) Display paystub\n"
	"5 or e) Exit program\n"
	"Input: "
	);
}

//Remember that 1 line from main? here it is!
int program(){
	//int controller is for the switch statement
	int controller = 0;
	//the variables needed for all the outputs.
	float hours = 0.0f, wage = 0.0f, iraPercent = 0.1f, 
		stateTax = 0.1f, fedTax = 0.15f, grossWage = 0.0f, iraAmount = 0.0f,
		stateAmount = 0.0f, fedAmount = 0.0f, netWage = 0.0f; 
	
	while(TRUE){//THIS IS DANGEROUS! if nothing to quit it == infinite loop
		displayMenu(); //display our menu

		controller = (int)handleInput(); //cast our input to an int for switch
		//based on the value put in we check each case.
		//switches "falldown" once the value "opens a case" i.e. it matches
		//a case IT WILL CONTINUE DOWNWARD until it reachs a break, at 
		//which point it will leave the switch.
		//this enables us to have multiple cases (must be one after the 
		//other) to results in the same code running!
		switch(controller){
			case 1:
			case A:
				printf("\n\nEnter the number of hours worked (X.00): ");
				hours = handleInput();
				break;
			case 2:
			case B:
				printf("\n\nEnter the wage (XX.00): $");
				wage = handleInput();
				break;
			case 3:
			case C:
				printf("\n\nEnter the percentage that is contributed to the IRA (0.XX): ");
				iraPercent = handleInput();
				break;
			case 4:
			case D:
				//here we call most of those functions....
				grossWage = calculateGrossWage(hours, wage);
				netWage = calculateIRA(grossWage, iraPercent, &iraAmount);
				stateAmount = calculateTaxes(&netWage, stateTax);
				fedAmount = calculateTaxes(&netWage, fedTax);
				
				//again with the multi-line printf this time with variables,
				//wait you can perform math in the printf?
				//YES - works good (best use) for something like converting the
				//percentages from 0.10 to 10% other wise store it in a variable 
				//BEFORE outputting it...
				//to escape % you MUST do %%
				printf(
					"\n\n----------\t PAYSTUB \t----------\n"
					"Hours worked: %.2f \n"
					"Hourly Wage: $%.2f \n"
					"Gross Wage: $%.2f \n"
					"IRA contribution (%.2f%%): $%.2f \n"
					"State Taxes (%.2f%%): $%.2f \n"
					"Federal Taxes (%.2f%%): $%.2f \n"
					"Pay after Deductions: $%.2f \n",
					hours,
					wage,
					grossWage,
					(iraPercent * 100), iraAmount,
					(stateTax * 100), stateAmount,
					(fedTax * 100), fedAmount,
					(netWage - stateAmount - fedAmount)
				);
				
				//here is were we call the custom systemPause()
				systemPause();
				break;
			case 5:
			case E:
				printf("\n\nThank you for using our software come back soon!\n");
				return 0;
				break;
			default:
				//we want a default JUST INCASE something happens  - we have a 
				//"fallback"
				printf("\n\nUnknown input - please check what you are typing!\n");
				break;
		}
		
	}
}

//this will get the users input from the console and has a few tricks
float handleInput(){
	//first declare a variable for each type of input we expect to recieve
	float fInput;
	char cInput;
	char enterKey; //this is a special case and will explain later.
	float result = 0; //after everything is said and done we will return this
	
	//SO scanf returns a value, 0 for failure and 1 for EACH input successfully
	//matched. Thus you can use that to determine IF the scanf was successful.
	//Now when you press a key and push enter, each key PLUS the enter goes 
	//into an input buffer - scanf "consumes" from the buffer.
	//i.e. it takes the value from the buffer and tries to assign it
	//to the variable. IF it fails - THE VALUE WILL REMAIN IN THE BUFFER
	//Thus the enter key can cause problems if we do not remove it from the
	//buffer, hence enterKey.
	//Now for the first if statement we are expecting a number - IF that fails
	//then the next statement trys to get the input from the buffer this time 
	//it grabs it as a character.
	if( scanf("%f%c", &fInput, &enterKey) == 2){
		result = fInput;
	} else if( scanf("%c%c", &cInput, &enterKey) == 2){
		//to ensure we do not need to check every capitalization we
		//user tolower so no matter what its the lower case variant
		//NOTE: tolower RETURNS THE ASCII DECIMAL VALUE OF THE CHARACTER!
		result = tolower(cInput);
	} else {
		//if the the input is neither a number nor a character we set it
		//to a value that we can change and use later for error checking
		result = 0.0f;
	}
	
	//and no need of fflush()!
	//this ONLY works IF we need/want numbers.
	//what if we want characters or strings?
	
	return result;
}

//This function demonstrates pass-by-value and returns a value
float calculateGrossWage(float hours, float wage){
	float overTime = 0.0f;
	
	//get the amount of overtime IF any exists
	if(hours > 40){
		overTime = hours - 40;
		hours = hours - overTime;
	} 
	
	//we can return a math statement or a variable BOTH work!
	return ((hours * wage) + (overTime * wage * 1.5));
	
}

//this will calculate the IRA and actually return two values
//even though there is only 1 return.
float calculateIRA(float grossWage, float iraRate, float* iraAmnt) {
	//iraAmnt is a pointer - the address (location) of a variable in memory.
	//by using a pointer we can change the value NO MATTER WHERE
	//it was declared - change and return it without actually needing a 
	//return statement
	*iraAmnt = (grossWage * iraRate);
	grossWage -= *iraAmnt;
	
	//as you can also see we CAN use the parameter to do math AND return it.
	//may not be a good idea - depends on the situation - but it can be done
	return grossWage;
}

//can return the expression - in this case is a pointer needed?
//answer NO - as we are not changing the value.
float calculateTaxes(float* netWage, float taxRate){
	return (*netWage * taxRate);
}


//FREE FOR USE - yes, if you wish to use this in your code you may.
//you just won't get bonus points for using it...
//feel free to change the wording however you wish.
//IF we do not remove the enter from the buffer when getting the input
//will cause issues with this. - well its should
//this SHOULD work on all systems (windows, mac, linux)
//if it does not let me know and I will investigate...
void systemPause(){
	puts("Press Enter to continue");
	getchar();
}
