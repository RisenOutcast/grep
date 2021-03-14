// main.cpp: Includes the main function and functions related to argument management
// Author: M.Metsola
// Edited: 13.3.2021

#include <iostream>
#include <string>
#include <vector>
#include "search.h"
#include "main.h"

int main(int argc, char** argv)
{
    std::vector<std::string> all_args;

    if (argc > 1) {
        std::string argument1 = argv[1];
        all_args.assign(argv + 1, argv + argc);

        std::string argument2 = argv[2];
        if (checkIfcommand(argument1) == 1) {
            struct arguments newArguments = createArguments(argument1.substr(2, argument1.size() - 2)); //Take out the "-o" before checking arguments
            std::string argument3 = argv[3];
            searchFromFile(argument3, argument2, newArguments);
        }
        else {
            std::string noArguments = "0";
            struct arguments newArguments = createArguments(noArguments);
            searchFromFile(argument2, argument1, newArguments);
        }
    }
    else {
        searchFromString();
    }

    return 0;
}

//Find out what arguments were given and either mark them as active (1) or non-active (0)
arguments createArguments(std::string userArguments) {
    struct arguments uudetArgumentit;
    uudetArgumentit.lineNumbering = checkIfargument(userArguments, "l");
    uudetArgumentit.lineOccurences = checkIfargument(userArguments, "o");
    uudetArgumentit.reverseSearch = checkIfargument(userArguments, "r");
    uudetArgumentit.ignoreCase = checkIfargument(userArguments, "i");

    return uudetArgumentit;
}

//Check if -o = options argument were given
int checkIfcommand(std::string argument) {
    std::size_t sijainti = argument.find("-o");
    if (sijainti != std::string::npos)
        return 1;
    else
        return 0;
}

//If argument was given mark it active and vice-versa
int checkIfargument(std::string userArguments, std::string argumentLooking) {
    std::size_t sijainti = userArguments.find(argumentLooking);
    if (sijainti != std::string::npos)
        return 1;
    else
        return 0;
}
