#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>
#include <cctype>

bool isNumeric(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

bool isAlphabetic(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

int stringToInt(const std::string& str) {
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}

int main() {
    // Arrays holding protocol names and their corresponding port numbers
    const char* protocols[] = { "HTTP", "HTTPS", "FTP", "SSH", "Telnet", "SMTP", "DNS" };
    const char* ports[] = { "80", "443", "21", "22", "23", "25", "53" };

    // Determine the size of the arrays
    int size = sizeof(protocols) / sizeof(protocols[0]);

    // Seed the random number generator
    std::srand(std::time(0));

    // Variable to store user input
    std::string userInput;
    int userPort;

    // Flag to track the current mode (protocol names as questions or port numbers as questions)
    bool protocolMode = true; // True: protocol names as questions, False: port numbers as questions

    // Loop to prompt the user until they decide to quit
    while (true) {
        // Get a random index from the protocols array
        int randomIndex = std::rand() % size;

        // Get the protocol name or port number based on the current mode
        const char* questionItem = protocolMode ? ports[randomIndex] : protocols[randomIndex];
        const char* correctAnswer = protocolMode ? protocols[randomIndex] : ports[randomIndex];
        const char* modeName = protocolMode ? "protocol name" : "port number";
        const char* oppositeModeName = protocolMode ? "port number" : "protocol name";

        // Attempt counter
        int attempts = 0;

        // Loop to keep prompting the user until the correct answer is entered
        while (true) {
            // Ask the user for the corresponding protocol name or port number
            std::cout << "Enter the " << modeName << " for the given " << oppositeModeName << " " << questionItem << " : ";
            std::cin >> userInput;

            // Check if the user wants to swap modes
            if (userInput == "swap") {
                protocolMode = !protocolMode; // Toggle mode
                std::cout << "Mode switched to " << (protocolMode ? "protocol names as questions" : "port numbers as questions") << "." << std::endl;
                break; // Exit inner loop and ask for a new item in the new mode
            }

            // Check for quitting the program ("-1")
            if (userInput == "-1") {
                std::cout << "Exiting program." << std::endl;
                return 0;
            }

            // Check if the input is alphanumeric (for protocol name mode) or numeric (for port number mode)
            if ((protocolMode && isAlphabetic(userInput)) || (!protocolMode && isNumeric(userInput))) {
                // Convert numeric input to uppercase alphanumeric string (if port number mode)
                if (protocolMode) {
                    // Convert the input to uppercase
                    for (char& c : userInput) {
                        c = std::toupper(c);
                    }
                }
                else {
                    // Check if the input is numeric and within the valid range
                    userPort = stringToInt(userInput);
                    if (userPort < 0 || userPort > 65535) {
                        std::cout << "Invalid " << oppositeModeName << ". Please enter a valid " << oppositeModeName << "." << std::endl;
                        continue; // Skip the rest of the loop and ask for input again
                    }
                }

                // Check if the user wants to quit
                if (userInput == "-1") {
                    std::cout << "Exiting program." << std::endl;
                    return 0;
                }

                // Check if the user's input is correct
                if (userInput == correctAnswer) {
                    std::cout << "Correct! The " << modeName << " for the " << oppositeModeName << " " << questionItem << " is " << userInput << "." << std::endl;
                    break;  // Exit the inner loop and go to the next question
                }
                else {
                    std::cout << "Incorrect. Please try again." << std::endl;
                    attempts++;
                    if (attempts > 3) {
                        std::cout << "Oh it seems maybe you dont know it ;p" << std::endl;
                    }
                    if (attempts > 5) {
                        std::cout << "maybe you should google it.." << std::endl;
                    }
                    if (attempts > 8) {
                        std::cout << "OK now this is just embarrassing..." << std::endl;
                    }
                    if (attempts > 12) {
                        std::cout << "You know what, we actually feel bad for ya little fella.. here just take the friggin answer.. we'll give it to ya.. not that it'll make any difference xD " << modeName << " = " << correctAnswer << std::endl;
                    }
                }
            }
            else {
                std::cout << "Invalid input. Please enter ";

                if (protocolMode) {
                    std::cout << "only letters." << std::endl;
                }
                else {
                    std::cout << "only numbers." << std::endl;
                }
            }

            // Clear the input buffer to handle invalid inputs gracefully
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
