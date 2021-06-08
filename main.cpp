#include <iostream>
#include <random>
#include <climits>

class UserGuess {
public:
    // Static int for the correct number we are trying to guess since it is the same for all UserGuess objects
    static int correctNum;

    // Constructor executes all code on creation of each UserGuess object
    UserGuess(int guess) {
        // Initialize guess
        this->guess = guess;

        // Set compare < 0 if guess is less than correctNum, 0 if equal to correctNum, > 0 if greater than correctNum
        compare = guess - correctNum;
    }

    // Default constructor
    UserGuess() : guess(INT_MIN), compare(INT_MIN) {}

    int getGuess() {
        return guess;
    }

    int getCompare() {
        return compare;
    }

private:
    int guess;
    int compare;
};

// DO NOT EDIT, Defines functions
int getRandomNumber(int, int);
void printGuesses(UserGuess*, int);
void addGuess(UserGuess*, int);

// Define minimum and maximum values to be generated, you may change either if range is to large
const int MIN_VALUE = 1;
const int MAX_VALUE = 10;

// Defines a constant variable containing the maximum number of users guesses, you may change this if you'd like more or less guesses for the user
const int MAX_GUESSES = 5;

// ***DO NOT EDIT*** Generates random number for user to guess
const int correctGuess = getRandomNumber(MIN_VALUE, MAX_VALUE);

// Sets the static variable correctNum to our generated number, this is a static varable so this will hold for all instances of UserGuess
int UserGuess::correctNum = correctGuess;

int main(int argc, const char * argv[]) {
    
    // Print title of game
    std::cout << "*** Random Number Guessing Game ***\n";

    // Defines an array (series of numbers) on the heap that will contain the values guessed by the user on the heap
    // This will need to be deleted when finished to avoid memory leaks
    UserGuess* recordedGuesses = new UserGuess[MAX_GUESSES];

    /*
     This sets the users guess to a number (-1) that is not in range of correctGuess so there is no way the number can be correct without the user guessing
     In C++, you must initialize varibales (set the variable equal to something) at some point before performing operations on it
     If you do not, the compiler will produce an error or have strange behaivior depending on the machine running the code
     For example, if you tried
     int a;
     a = a + 1;
     the compiler may error because a is equal to nothing at the time an addition operator is performed
     */
    int userInput = -1;
    
    // Defines counter varible for looping through array, arrays start at entry 0 so i is initalized to 0
    int i = 0;

    // Define a flag to indicate when a correct guess has been made
    bool correct = false;
    
    // Continue looping while the user guess is incorrect and our counter is less than the max guesses we give the user
    while (!correct && i < MAX_GUESSES) {
        
        // Prompt user for their guess
        std::cout << "Guess a number from " << MIN_VALUE << " to " << MAX_VALUE << ": ";
        
        // Get the number guess and set equal to userGuess
        std::cin >> userInput;
        
        // Adds the userInput to the array of guessed values, see addGuess function below. Do NOT edit this line but you may edit the function below
        addGuess(&recordedGuesses[i], userInput);
        
        // If the user guessed correctly, congratulate them, print all the guesses they made and exit the program
        correct = (recordedGuesses[i].getCompare() == 0);
        if (correct) {
            std::cout << "Congratulations, you guessed the correct number\n";
        }
        else {
            // The user did not guess correctly so tell them if they guessed too high or too low
            if (recordedGuesses[i].getCompare() > 0){
                std::cout << "Guess was too high.\n";
            }
            else {
                std::cout << "Guess was too low.\n";
            }
        }
        // Increment the counter variable
        i++;
    }
    
    if (!correct) {
        std::cout << "\nYou have run out of guesses, the number was " << correctGuess << ".\n";
    }
    printGuesses(recordedGuesses, i);
    
    // Release the memory allocated in the heap
    delete[] recordedGuesses;
    
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
int getRandomNumber(int x, int y) {

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
    for (int i = 0; i < size; ++i) {
        std::cout << recordedGuesses[i].getGuess() << " ";
    }
    std::cout << "\n";
}


