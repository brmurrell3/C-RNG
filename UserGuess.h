#ifndef UserGuess_h
#define UserGuess_h

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

#endif /* UserGuess_h */
