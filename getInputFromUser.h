#ifndef GETINPUTFROMUSER_H_INCLUDED
#define GETINPUTFROMUSER_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

string getInputFromUser()
{
     string line;
     getline(cin, line);
     return line;
}

void printMessage(string messageInputVector)
{
    cout << messageInputVector;
}
#endif // GETINPUTFROMUSER_H_INCLUDED
