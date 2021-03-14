#pragma once
struct arguments {
    int lineNumbering = 0;  //l
    int lineOccurences = 0;  //o
    int reverseSearch = 0;  //r
    int ignoreCase = 0;  //i
};

int searchFromString();
int searchFromFile(std::string tiedostoNimi, std::string searchStr, arguments arguments);
std::ifstream fileOpen(std::string tiedostoNimi);
