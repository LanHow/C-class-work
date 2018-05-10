#include <iostream>
#include <string>
#include "getInputFromUser.h"
#include "ProductDot.h"
#include "getVector.h"

using namespace std;



int main()
{
    char c;
    string ui;
    string messageInputVector("Input a vector in the following format n c1 c2 ... cn:");
    string messageInputContinue("Type c<ret> to continue, <anything else><ret> to end:");
    string messageInnerProduct("inner product:");
    string messageTermination("Terminating program...");
    bool cont = true;
    while (cont) {
        printMessage(messageInputVector);
        ui = getInputFromUser();
        Vector v = extractVector(ui);
        printMessage(messageInputVector);
        ui = getInputFromUser();
        Vector u = extractVector(ui);
        int dp = product_dot(v,u);
        printMessage(messageInnerProduct);
        cout << dp << endl;
        printMessage(messageInputContinue);
        ui = getInputFromUser();
        c = extractContinue(ui);
        if(c != 'c')
            cont = false;
    }
    printMessage(messageTermination);
    return 0;
}

