//
//  UserGuess.h
//  C++Game
//
//  Created by Brendan Murrell on 6/8/21.
//

#ifndef UserGuess_h
#define UserGuess_h

class UserGuess {
public:
    // Static int for the correct number we are trying to guess since it is the same for all UserGuess objects
    static int correctNum;
    
    // Conctructor executes all code on creation of each UserGuess object
    UserGuess(int guess) {
        // Initialize guess
        this->guess = guess;
        
        // Set compare to -1 if guess is less than correctNum, 0 if equal to correctNum, 1 if greater than correctNum
        compare = guess - correctNum;
    }
    
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
