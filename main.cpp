/**
 * Revision History - newest revisions first
 ***********************************************************************
 * 05/07/2022 - fixed SEGFAULT: itr not being dereferenced @ insert and erase
 * 05/06/2022 - re-wrote win loss function
 * 04/30/2022 - Initial version written for CSCI275 by Nicholas Herrick
 *
 * I pledge that this program is of my own hand for CSCI275
 *
 **/

#include <iostream>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

// PRE: at least one set contains data
// POST: prints location and contents of each set to console
void printInfo(int &location, set<string> const &nBank, set<string> const &sBank);

// PRE: at least one set contains data
// POST: returns int value for win(1), loss(-1) or continue (0)
int winLoss(int &location, set<string> const &nBank, set<string> const &sBank);

// PRE:
// POST: This program is a game where you need to move all objects from the south bank to the north.
// User wins if all make it to the north bank without loss condition being triggered (see winLoss function).
int main() {
    set<string> choices {"fox", "chicken", "grain", "none"};    // set of choices for iterator search
    set<string> northBank;                                      // northern bank declared
    set<string> southBank{"fox", "chicken", "grain"};           // southern bank initialized with values
    int farmerLocation = 0;                                     // 0 = southBank, 1 = northBank
    string userChoice;                                          // User choice string
    int winOrLose = 0;                                          // win = 1, continue = 0, loss = -1;

    // Print message and begin logic for win, loss or continue. Check if choice is present on current bank, or
    // if choice is "none", which location (south bank is location 0, north bank is 1) the farmer is in and move to
    // other shore.
    cout << "You are a farmer on the south bank of a river.\n" <<
    "You need to transport a fox, a chicken and some grain to the other side." <<
    "\nYou cannot leave the fox and chicken alone, and you cannot leave the chicken and grain alone." <<
    "\nThere is only room for one of these and/or yourself at a time.\n\n";
        while (winOrLose == 0) {
            cout << "Enter the item you wish to transport (fox, chicken, grain, none) :";
            cin >> userChoice;
            try {
            auto itr = choices.find(userChoice);
            if (itr == choices.end()) {
                throw invalid_argument(userChoice);
            }
            if (farmerLocation == 0 && userChoice != "none") {
                itr = southBank.find(userChoice);
                if (itr == southBank.end()) {
                    throw invalid_argument(userChoice);
                } else {
                northBank.insert(*itr);
                southBank.erase(*itr);
                printInfo(farmerLocation, northBank, southBank);
                farmerLocation = 1;
            }

            } else if (farmerLocation == 1 && userChoice != "none"){
                itr = northBank.find(userChoice);
                if (itr == northBank.end()) {
                    throw invalid_argument(userChoice);
                } else {
                        southBank.insert(*itr);
                        northBank.erase(*itr);
                        printInfo(farmerLocation, northBank,southBank);
                        farmerLocation = 0;
                }
            } else if (userChoice == "none"){
                if (farmerLocation == 1){
                    printInfo(farmerLocation,northBank,southBank);
                    farmerLocation = 0;
                }
                else {
                    printInfo(farmerLocation,northBank,southBank);
                    farmerLocation = 1;
                }

            }
          winOrLose = winLoss(farmerLocation, northBank, southBank);
        } catch (invalid_argument &e){
                cout << e.what() << " was not found on this shore.\n";
            }
    }
    if (winOrLose == 1){
        cout << "Congratulations, you've won!";
    } else {
        cout << "You've lost! Game over!";
    }
    return 0;
}

// PRE: at least one set contains data
// POST: prints location and contents of each set to console
void printInfo(int &location, set<string> const &nBank, set<string> const &sBank) {
    if (location == 0) {
    cout << "\nFarmer location: North bank." << "\nSouth bank contains: ";
    for (string const &s: sBank) {
        cout << s << " ";
    }
    cout << endl;
    cout << "North bank contains: ";
    for (string const &s: nBank) {
        cout << s << " ";
    }
    cout << endl;
} else {
        cout << "\nFarmer location: South bank." << "\nSouth bank contains: ";
        for (string const &s: sBank){
            cout << s << " ";
        }
        cout << endl;
        cout << "North bank contains: ";
        for (string const &s: nBank){
            cout << s << " ";
        }
        cout << endl;
    }
}

// PRE: at least one set contains data
// POST: returns int value for win(1), loss(-1) or continue (0)
// Loss conditions are chicken and fox alone on any shore, or chicken and grain alone on any shore.
int winLoss(int &location, set<string> const &nBank, set<string> const &sBank) {
    if (sBank.empty()) {
        return 1;
    } else {
        if (sBank.find("chicken") != sBank.end() && sBank.find("fox") != sBank.end()
            && sBank.find("grain") == sBank.end() && location == 1){
            return -1;
        } else if (sBank.find("chicken") != sBank.end() && sBank.find("grain") != sBank.end()
                   && sBank.find("fox") == sBank.end() && location == 1) {
            return -1;
        } else if (nBank.find("chicken") != nBank.end() && nBank.find("fox") != nBank.end()
                   && nBank.find("grain") == nBank.end() && location == 0) {
            return -1;
        } else if (nBank.find("chicken") != nBank.end() && nBank.find("grain") != nBank.end()
                   && nBank.find("fox") == nBank.end() && location == 0) {
            return -1;
        } else
            return 0;
    }
}