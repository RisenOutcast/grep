// search.cpp: contains functions related to string searches and file opening/closing
// Author: M.Metsola
// Edited: 13.3.2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "search.h"
#include "main.h"

//If no arguments were given ask the user to input the string to search for and where to search
int searchFromString() {
    std::string searchStr;
    std::string textStr;

    std::cout << "Give a string from which to search for: ";
    std::getline(std::cin, textStr);

    std::cout << "Give search string: ";
    std::getline(std::cin, searchStr);

    std::size_t sijainti = textStr.find(searchStr);
    if (sijainti != std::string::npos)
        std::cout << '"' << searchStr << '"' << " found in " << '"' << textStr << '"' << " in position " << sijainti << "\n";
    else
        std::cout << '"' << searchStr << '"' << " NOT found in " << '"' << textStr << '"' << "\n";
    return 0;
}

//Main search function. Search from file the given string with the criteria given.
int searchFromFile(std::string tiedostoNimi, std::string searchStr, arguments arguments) {
    std::ifstream tiedosto = fileOpen(tiedostoNimi);

    std::stringstream  streamtextFromFile;
    streamtextFromFile << tiedosto.rdbuf();
    std::string textFromFile = streamtextFromFile.str();
    if (arguments.ignoreCase == 1) {
        std::transform(searchStr.begin(), searchStr.end(), searchStr.begin(),
            [](unsigned char c) { return std::tolower(c); });
        std::transform(textFromFile.begin(), textFromFile.end(), textFromFile.begin(),
            [](unsigned char c) { return std::tolower(c); });
    }
    std::size_t sijainti = textFromFile.find(searchStr);
    std::string line;
    int numberofLines = 0; //sum of the lines containing 
    int lineNumber = 0; //The number of the line

    while (std::getline(streamtextFromFile, line)) //Roll through the lines in the file
    {
        lineNumber++;

        std::string ogLine = line; //Take the original non-lowercasered line

        if (arguments.ignoreCase == 1) { //Turn into lowercase if ignore lowercase was given
            std::transform(line.begin(), line.end(), line.begin(),
                [](unsigned char c) { return std::tolower(c); });
        }
        if (arguments.reverseSearch != 1) {
            if (line.find(searchStr) != std::string::npos) //If the line matches the search term go ahead and print it
            {
                if (arguments.lineNumbering == 1)
                    std::cout << lineNumber << ":";
                std::cout << ogLine << std::endl;
                numberofLines += 1;
            }
        }
        else {
            if (line.find(searchStr) == std::string::npos) //If the line doesnt match the search term go ahead and print it
            {
                if (arguments.lineNumbering == 1)
                    std::cout << lineNumber << ":";
                std::cout << ogLine << std::endl;
                numberofLines += 1;
            }
        }
    }
    if (arguments.lineOccurences == 1) {
        if (arguments.reverseSearch == 1)
            std::cout << "Occurrences of lines NOT containing " << '"' << searchStr << '"' << ": " << numberofLines;
        else
            std::cout << "Occurrences of lines containing " << '"' << searchStr << '"' << ": " << numberofLines;
    }
    tiedosto.close();

    return 0;
}

//Function for opening the file
std::ifstream fileOpen(std::string tiedostoNimi) {
    std::ifstream tiedosto;

    tiedosto.open(tiedostoNimi);
    if (!tiedosto) {
        std::cout << "An exception occurred. Exception Nr. -1\n";
        std::cout << "Could not find out the size of file: " << '"' << tiedostoNimi << '"';
        exit(1);
    }

    return tiedosto;
}
