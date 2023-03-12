#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <ctype.h> 

#define MAX_CUSTOMERS 20 //macro for the max customers in the car wash
#define MAX_WASH_BAY 3 //macro for the max number of customers in wash bay

typedef struct {
    char date[11];
    char firstName[50];
    char lastName[50];
    char licensePlate[7];
    char paymentMethod[10];
    int services[6];
    float serviceCost;
    float tipAmount;
    float totalCost;
} Customer;

// Function prototypes
int mainMenu(void);
void acceptCustomerInfo(Customer* customers, int* numCustomers, int* numWashBay);
void washCar(Customer* customers, int* numCustomers, int* numWashBay);
void storeCustomerInfo(Customer *customer, Customer customers[], int *numCustomers);
void displayReturningCustomers(Customer* customers, int numCustomers);
void displayDaysSalesReport(Customer* customers, int numCustomers);

int main() {
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = 0;
    int numWashBay = 0;
    int option;
    
    // Load existing customer data from file
   FILE* fptr;
//    if (fptr != NULL) {
//        fread(&numCustomers, sizeof(int), 1, fptr);
//        fread(customers, sizeof(Customer), numCustomers, fptr);
//        fclose(fptr);
//    }
		do{
	        int choice = mainMenu();
			
	        switch (choice) 
			{
	        case 1:
	            acceptCustomerInfo(customers, &numCustomers, &numWashBay);
	            break;
	        case 2:
	            washCar(customers, &numCustomers, &numWashBay);
	            break;
	//        case 3:
	//            displayReturningCustomers(customers, numCustomers);
	//            break;
	//        case 4:
	//            displayDaysSalesReport(customers, numCustomers);
	//            break;
	        case 5:
	            // Save customer data to file before exiting
	            fptr = fopen("customers.txt", "w");
	            if (fptr != NULL) {
	                fwrite(&numCustomers, sizeof(int), 1, fptr);
	                fwrite(customers, sizeof(Customer), numCustomers, fptr);
	                fclose(fptr);
	            }
	            printf("Exiting program...\n");
	            exit(0);
	            break;
	        default:
	            printf("Invalid option. Please try again.\n");
	            break;
	        }
    	}while (1); //while true, repeat these steps

    return 0;
}


//This function works as the main menu to accept customer option on what they would like to do
int mainMenu(void){
		int option, i;
	// Display menu options
        printf("\n***Trish & Shaun's Auto Wash Services***\n\n");
        printf("1. Accept Customer Information & Payment\n");
        printf("2. Wash Car\n");
        printf("3. Display Returning Customers\n");
        printf("4. Display Day's Sales Report\n");
        printf("5. Exit Program\n");
        printf("\nEnter option: ");
	    int NaNChecker = scanf("%d", &option);
	    
	    //This validates the option entered. Number entered must be between 1 and 5 - ERROR HANDLING
//        do {
	    if (option < 1 && option > 5) {
	        printf("\n***ERROR: Invalid option selected! Please select an option between 1 and 5.\n");
	        printf("\nEnter option: ");
	    }
	    //validates if entry is a non-numeric character
	    if (NaNChecker != 1){
	        printf("\n***ERROR: Invalid data type! \nPlease enter a number: ");
	        scanf("%*[^\n]");
	        NaNChecker = scanf("%d", &option);
	    }
//	}while (option < 1 || option > 5);
				
	return option;
}

//This function works to accept and store the customer data, including receipt and transaction details
void acceptCustomerInfo(Customer* customers, int* numCustomers, int* numWashBay) {
    if (*numCustomers == MAX_CUSTOMERS) {
        printf("\n***Car wash is full. Please come back later.\n");
        return;
        exit(0); //leave program since car wash is full
    }

    // Get customer information
    Customer newCustomer;
    Customer customerInWashBay;
    int paymentmethod;
    system("pause");
    system("cls");
    printf("\n***Customer Information Menu***\n\n");
    printf("\nEnter transaction date [dd/mm/yyyy]: ");
    scanf("%s", newCustomer.date);
    printf("Enter customer's first name: ");
    scanf("%s", newCustomer.firstName);
    printf("Enter customer's last name: ");
    scanf("%s", newCustomer.lastName);

    // Get license plate number  
	int LicensePlateNumbers[4];
	char LicensePlateletters[2];
	int i;
	int NaNChecker = 0; //intialised as 0 to prevent undefined behavior
	
	printf("\nLicense Plate Information - Format (1234-AB)");
	printf("\n\nEnter the four digits of your license plate (Hit ENTER KEY after each number): \n");
	
	for(i = 0; i <= 3; i++){
	    printf("\n%d. Enter digit: ", i + 1);
	    NaNChecker = scanf("%d", &LicensePlateNumbers[i]); //NaNChecker will be used to check if entry is not a digit
	        
	    //validates if number entered if greater than a single digit number or less than 0 - ERROR HANDLING
	    if(LicensePlateNumbers[i] < 0 || LicensePlateNumbers[i] > 9){
	        printf("\n***ERROR: Please enter a single digit");
	        printf("\n%d. Enter digit: ", i + 1); 
	        scanf("%d", &LicensePlateNumbers[i]);
	    }
	        
	    //validates if entry is a non-numeric character
	    else if(NaNChecker != 1){
	        printf("\n***ERROR: Invalid data type! \nPlease enter a number: ");
	        scanf("%*[^\n]");
	        NaNChecker = scanf("%d", &LicensePlateNumbers[i]);
	    }
	}
	
	//This gets the two letters at end of license plate
	printf("Enter the two characters on your license plate (enter spaces between characters): ");
	scanf(" %c %c", &LicensePlateletters[0], &LicensePlateletters[1]); 
	
	//This displays what was entered by user
	printf("License plate entered: ");
	printf("%d%d%d%d-%c%c", LicensePlateNumbers[0], LicensePlateNumbers[1],LicensePlateNumbers[2],LicensePlateNumbers[3],LicensePlateletters[0],LicensePlateletters[1]);
	

	char licensePlate[7];
	//We use strcpy to format the license plate number as a string and store it in the licensePlate array.
	//The sprintf function is used to format the license plate string based on the user input, 
	//and then the strcpy function is used to copy the formatted string to the newCustomer.licensePlate array. 
	//We can then print the license plate number using printf.
	sprintf(licensePlate, "%d%d%d%d-%c%c", LicensePlateNumbers[0], LicensePlateNumbers[1], LicensePlateNumbers[2], LicensePlateNumbers[3], LicensePlateletters[0], LicensePlateletters[1]);
	strcpy(newCustomer.licensePlate, licensePlate);
	
    // Get payment method
    printf("\n\nSelect payment method: "); //enter 1 for cash, 2 for card
    printf("\n1. CASH");
    printf("\n2. CARD\n");
    printf("\nChoice: ");
    scanf("%d", &paymentmethod);
    
    // Get payment method - ERROR HANDLING
    while(paymentmethod < 1 || paymentmethod > 2){
    	if(paymentmethod < 1 || paymentmethod > 2){
		printf("***ERROR: Invalid payment type selected. Please select one of the following option.");
    	printf("\n1. CASH");
	    printf("\n2. CARD\n");
	    scanf("%d", &paymentmethod);
		}
	}

    // Get selected services and calculate service cost
    system("pause");
    system("cls");
    printf("\n***Select Service Menu***\n\n");
    
	//Displays service selection menu
    int amountOfServices = 0;
    printf("1. Basic Wash ($5.00)\n");
    printf("2. Standard Wash ($7.50)\n");
    printf("3. Deluxe Wash ($10.00)\n");
    printf("4. Basic Detail ($25.00)\n");
    printf("5. Standard Detail ($35.00)\n");
    printf("6. Deluxe Detail ($50.00)\n");
    
    //This validates the number of services entered (user cannot choose more than 6 services) - ERROR HANDLING
    do{
    	printf("\nPlease state the number of services you would like to order: ");
    	scanf("%d", &amountOfServices);
    	if(amountOfServices < 1 || amountOfServices > 6){
		printf("\n***ERROR: Please choose 6 or less services.\nYou can only choose each service ONCE.");
    	}	
	}while(amountOfServices < 1 || amountOfServices > 6);

	float serviceCost = 0;
    
    //NEEDED - DONE ALREADY
    //for loop to enter choice for each service cost
    //Validation check for choice
    //loop to check service is not already selected
    //loop and case to add costs... DONE 
    
    int choice, j;
    
    for (i = 1; i <= amountOfServices; i++) 
	{
    	printf("\n%d. Enter service (Hit Enter Key after each number): ", i);
    	NaNChecker = scanf("%d", &newCustomer.services[i]);
    	
    	choice = newCustomer.services[i];
    	
        //checks if the choice entered was already chosen - ERROR HANDLING
    	for(j=0;j<i;j++){
	    	if(newCustomer.services[j] == choice){
	    		printf("\n***ERROR: This service was already entered! \nPlease choose another service: ");
				i--;
				break;
			}
		}
    	//validates the choice entered - ERROR HANDLING
    		if (newCustomer.services[i] < 1 || newCustomer.services[i] > 6){
			printf("***ERROR: Invalid selection! Please select between 1 and 6: ");
    		scanf("%d", &newCustomer.services[i]);
		}
		//validates if entry is a non-numeric character
		    else if(NaNChecker != 1){
		        printf("\n***ERROR: Invalid data type! \nPlease enter a number: ");
		        scanf("%*[^\n]");
		        NaNChecker = scanf("%d", &LicensePlateNumbers[i]);
		}
    }
    
    //This calculates and adds to service cost based on the service selected
    printf("\n\nServices selected: ");
    for(i = 1; i <= amountOfServices; i++){
    	printf("%d ", newCustomer.services[i]);
		switch (newCustomer.services[i]) {
			case 1: 
				serviceCost += 5.00;
			    break;
			case 2:
		    	serviceCost += 7.50;
		        break;
		    case 3:
		    	serviceCost += 10.00;
		        break;
		    case 4:
		        serviceCost += 25.00;
		        break;
		    case 5:
		        serviceCost += 35.00;
		        break;
		    case 6:
		        serviceCost += 50.00;
				break;
		}
	}
    newCustomer.serviceCost = serviceCost;

    //Generation of a random response for tip using rand() function
    float tipAmount, cardTax=0.00;
    	
	printf("\n\nWould you want to tip us for our services?: ");
		
    // Seed the random number generator with the current time
	srand(time(NULL));
	    
	// Generate a random number between 0 and 1
	int random_num = rand() % 2;
	char tip;
	    
	// Print 'y' or 'n' depending on the value of the random number
	if (random_num == 0) {
		tip = 'Y';
	    printf("Y\n");
	    tipAmount = 0.02 * newCustomer.serviceCost;
	} else {
		tip = 'N';
	    printf("N\n");
	}
	
	//Card payments attract 3% fees of the total service cost
	if(paymentmethod == 2){
		cardTax = 0.03 * newCustomer.serviceCost;
	}
	
    //Calculation of total cost
    newCustomer.tipAmount = tipAmount;
    newCustomer.totalCost = serviceCost + tipAmount + cardTax;
    if (paymentmethod == 1){
    	strcpy(newCustomer.paymentMethod, "CASH");
	}else{
		strcpy(newCustomer.paymentMethod, "CARD");
	}
	
	//Display customer's receipt including their information and the costs
	system("pause");
    system("cls");
	printf("\n\n***Thank you for choosing Trish & Shaun's Auto Wash Services!***\n\nCustomer Receipt: \n\n\n\n");
	printf("Name:                %s %s", newCustomer.firstName, newCustomer.lastName);
	printf("\nTransaction Date:    %s", newCustomer.date);
	//printf("\nLicense Plate:       %d%d%d%d-%c%c", numbers[0],numbers[1],numbers[2],numbers[3],letters[0],letters[1]);
	printf("\nPayment method:      %d         ([1 for Cash] and [2 for Card])", paymentmethod);
	printf("\nServices selected:   ");
    for(i = 1; i <= amountOfServices; i++){
    	printf("%d ", newCustomer.services[i]);
    }
    printf("\n\nTip (Y/N):           % c", tip);
    printf("\nTip amount:          $ %.2f", tipAmount);
    printf("\nService cost:        $ %.2f", serviceCost);
    printf("\nAdded Card Tax:      $ %.2f", cardTax);
    printf("\nGrand Total:         $ %.2f\n\n", newCustomer.totalCost);
	

	//call the function that increments value of customers 
	storeCustomerInfo(customers, customers, numCustomers);
    system("pause");
    
    
    //Prompt user if they are ready to wash their car
    int readyToWashCar = 0;
    printf("\n\nReady to wash car?");
    printf("\n1. Yes\n2. No\nChoice: ");
    scanf("%d", &readyToWashCar);
    
	if(readyToWashCar == 1){	    
	    //call wash car function 
    	washCar(customers, numCustomers, numWashBay);
	}
//	printf("\nNumber of customers: %d", (*numCustomers));
//	printf("\nNumber of customers in wash bay: %d", (*numWashBay));
}

//This function checks if there are any vehicles at the washbay area and the car wash on a whole.
//NEEDS TO BE DONE:
//Open file
//Check if the customer[index] have paid for car wash service (ask them to enter their license plat # and use that to check)
//if they have allow them to wash
//if not, tell them to choose option one from MAIN MENU so they can pay and get wash service

//NEEDS TO BE DONE: Incorporate a method of clearing washed cars from the washbay
//Idea: create a module that decrements the number of cars in washbay after a certain timespan (using time.h)

void washCar(Customer* customers, int* numCustomers, int* numWashBay){

	//this checks if there are any customers in the system. if not, then they did not eneter their information and did not pay
	//NEEDS TO BE CHANGED!!
	if (*numCustomers == 0){
		printf("\nSorry, you cannot select this service. \nPlease first select option 1 to enter your information in the MAIN MENU SCREEN.\n");
		return;
	}
	//this checks if the maximum number of customers have been met in the wash bay area
	if (*numWashBay >= MAX_WASH_BAY) {
        printf("\n***Car wash is full. Please come back later.***\n");
        printf("\nNumber of customers: %d", (*numCustomers));
        printf("\nNumber of customers in wash bay: %d\n\n", (*numWashBay));
        system("pause");
        system("cls");
    }else{
    //If the above snippet of code was not met, then the customer can enter wash bay area. 
    //Num of customers in wash area is incremented
    	printf("Thank you! Your car will be washed shortly...\n\n");
    	(*numWashBay)++; //increments number of persons in wash bay
    	printf("\nNumber of customers: %d", (*numCustomers));
    	printf("\nNumber of customers in wash bay: %d\n\n", (*numWashBay));
    	system("pause");
    	system("cls");
	}
}

/*
This functionality searches the file for all customers that appear more than once. It then displays their
names, the total amount spent at the car wash, and the frequency of visits. Ensure this feature is
available only if a vehicle is at the car wash.
*/
void displayReturningCustomers(Customer* customers, int numCustomers){
	
}

//this helper function stores the customer's information
void storeCustomerInfo(Customer *customer, Customer customers[], int *numCustomers) {
    if (*numCustomers < MAX_CUSTOMERS) {
        customers[*numCustomers] = *customer;
        (*numCustomers)++;
	}
}
        
