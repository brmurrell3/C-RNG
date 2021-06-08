#include <iostream>
#include <random>
#include <string.h>
#include "UserGuess.h"

// DO NOT EDIT, Defines functions
int getRandomNumber(u_int, u_int);
void printGuesses(UserGuess*, int);
void addGuess(UserGuess*, int);

// Define minimum and maximum values to be generated, you may change either if range is to large
const int MIN_VALUE = 1;
const int MAX_VALUE = 100;

// ***DO NOT EDIT*** Generates random number for user to guess
const int correctGuess = getRandomNumber(MIN_VALUE, MAX_VALUE);

// Sets the static variable correctNum to our generated number, this is a static varable so this will hold for all instances of UserGuess
int UserGuess::correctNum = correctGuess;

int main(int argc, const char * argv[]) {
    
    // Print title of game
    std::cout << "*** Random Number Guessing Game ***\n";
    
    // Defines a constant variable containing the maximum number of users guesses, you may change this if you'd like more or less guesses for the user
    int maxGuesses = 5;
    
    /*
     Defines C style array (series of numbers) that will contain the values guessed by the user
     sizeof(UserGuess) * maxGuesses will find the total amount of memory needed to store UserGuess maxGuesses times (in this case it will be the space to store 5 numbers)
     malloc just tells the compiler to save this amount of space in memory because we will need it later
     Do NOT edit the code to the left of "malloc"
     You may edit the code to the right of "malloc" to change the size of memory needed
    */
    UserGuess* recordedGuesses = (UserGuess*) malloc(sizeof(UserGuess) * maxGuesses);

    
    /*
     This sets the users guess to a number (-1) that is not in range of correctGuess so there is no way the number can be correct without the user guessing
     In C++, you must initialize varibales (set the variable equal to something) at some point before performing operations on it
     If you do not, the compiler will produce an error or have strange behaivior depending on the machine running the code
     For example, if you tried
     int a;
     a = a + 1;
     the compiler may error because a is equal to nothing at the time an addition operator is performed
     
     In Java, this is not true most numerical variables are automatically set to 0 so the above code would be valid
     */
    int userInput = -1;
    
    // Defines counter varible for looping through array, arrays start at entry 0 so i is initalized to 0
    int i = 0;
    
    // Continue looping while the user guess is incorrect and our counter is less than the max guesses we give the user
    while (correctGuess != userInput && i < maxGuesses) {
        
        // Prompt user for their guess
        std::cout << "Guess a number from " << MIN_VALUE << " to " << MAX_VALUE << ": ";
        
        // Get the number guess and set equal to userGuess
        std::cin >> userInput;
        
        // Adds the userInput to the array of guessed values, see addGuess function below. Do NOT edit this line but you may edit the function below
        addGuess(&recordedGuesses[i], userInput);
        
        // If the user guessed correctly, congratulate them, print all the guesses they made and exit the program
        if (recordedGuesses[i].getCompare() == 0) {
            std::cout << "Congratulations, you guessed the correct number\n";
            printGuesses(recordedGuesses, sizeof(*recordedGuesses));
            
            
            /*
            // Program is done, we must free the memory of dynamically allocated space
            for(UserGuess* a = recordedGuesses; a < a + sizeof(recordedGuesses)/sizeof(*a); ++a) {
                free(a);
            }
             */
            
            system("pause");
            return 0;
        }
        // The user did not guess correctly so tell them if they guessed too high or too low
        else {
            if (recordedGuesses[i].getCompare() > 0){
                std::cout << "Guess was too high. ";
            }
            else {
                std::cout << "Guess was too low. ";
            }
        }
        // Increment the counter variable
        i++;
    }
    
    std::cout << "\nYou have run out of guesses\n";
    printGuesses(recordedGuesses, sizeof(*recordedGuesses));
    
    // Program is done, we must free the memory of  allocated space
    //for (int i = 0; i < maxGuesses; ++i) {
     //    delete recordedGuesses[i];
     //}
    free(recordedGuesses);
    
    system("pause");
    return 0;
}

void addGuess(UserGuess* recordedGuesses, int a) {
    /*
     Initializes a userGuess object on the heap
     This is dynamically allocated so we will need to free the memory later
     Since we need the data in our array outside the stack frame of addGuess, we cannot declare it on the stack and must declare it on the heap
     Do NOT change this line of code
     */
    UserGuess *tempGuess = new UserGuess(a);
    
    // Adds the object containing the users guess to the array at the element we specified in the parameters
    *recordedGuesses = *tempGuess;
    
    // tempGuess falls out of scope now but the memory assigned to is is now in the array
}

// DO NOT EDIT CODE BELOW THIS LINE
// Function to generate a random number with a minimum value of x and a maximum value of y
int getRandomNumber(u_int x, u_int y) {

    // Obtain a random number from hardware
    std::random_device rand;
    
    /*
     http://www.cplusplus.com/reference/random/mt19937/
     Mersenne Twister 19937 generator
     A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits
     Gives a more even distribution of numbers generated than std::rand()
     */
    std::mt19937 gen(rand());
    
    // Define the range of RNG from x-y
    std::uniform_int_distribution<> distr(x, y);
    
    // Returnd random number
    return distr(gen);
}

void printGuesses(UserGuess* recordedGuesses, int size) {
    std::cout << "Your guesses are: ";
    
    while(recordedGuesses->getGuess() != 0) {
        std::cout << recordedGuesses->getGuess() << " ";
        recordedGuesses++;
    }
    std::cout << "\n";
}
