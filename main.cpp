#include "DylMath.h"
#include "infix.h"
#include <iostream>
#include <vector>
#include <ctype.h>
#include <stdio.h>
using namespace std;

int main(int argc, char** argv) {

Infix Math;

vector<char> a;
string expression;
string newExpression;
string b = "20*x";
int menu1Option;



cout << endl << endl;
cout << "       ################################     " << endl;
cout << "       ## Welcome to Dylan Collier's ##     " << endl;
cout << "       ## Math Projects Application ###     " << endl;
cout << "       ################################     " << endl << endl;

cout << "   Please enter an expression or type 'help':   y = ";

getline(cin, expression);

while (expression == "help" || expression == "Help" || expression == "HELP" || expression == "h") {
    cout << endl << "You can type any polynomial function of one variable (x) to graph or evaluate" << endl << endl;
    cout << "This programs supports the use of addition, subtraction, multiplication, division, powers '^', " << endl;
    cout << "parentheses, cos(), sin(), tan(), sqrt(), ln(), and the constants 'e' and 'pi'." << endl << endl;
    cout << "E.g.: y = 7x * (5 ^ ln(7)) + x^2" << endl << endl;

    cout << "   Please enter an expression or type 'help':   y = ";

    getline(cin, expression);
}

for (int i = 0; i < expression.size(); i++) {
    a.push_back(expression[i]);
}
Math.Parse(a);

while (menu1Option != 5) {

cout << endl << endl;
cout << "   Please type a menu option:" << endl << endl;
cout << "[1] Evaluate expression" << endl;
cout << "[2] Graph expression" << endl;
cout << "[3] Exit" << endl << endl;

cin >> menu1Option;


    //Add a get expression method, then check if the expression contains x values. Only prompt for x value if the expression contains x's
    if (menu1Option == 1) {
        bool containsX = false;
        int x;
        vector<string> output = Math.getExpression();
        for (int i = 0; i < output.size(); i++) {
            if (output.at(i) == "x") {
                containsX = true;
            }
        }
        if (containsX) {
            cout << "Evaluate at x = ";
            cin >> x;
            cout << endl << "y = " << Math.evaluate(x);
        }
        else {
            cout << endl << "y = " << Math.evaluate(0);
        }
    }
    else if (menu1Option == 2) {
        double xmin, xmax, ymin, ymax;
        string ybool;

        cout << endl << "Enter minimum X value on graph: ";
        cin >> xmin;
        cout << endl << "Enter maximum X value on graph: ";
        cin >> xmax;
        cout << endl << "Would you like the Y values on the graph to automatically scale? Enter y/n: ";
        cin >> ybool;

        if (ybool == "n" || ybool == "N" || ybool == "no" || ybool == "No") {
            cout << endl << "Enter minimum Y value on graph: ";
            cin >> ymin;
            cout << endl << "Enter maximum Y value on graph: ";
            cin >> ymax;

            Math.graph(xmin, xmax, false, ymin, ymax);
        }
        else {
            cout << endl;
            Math.graph(xmin, xmax, true, 0, 0);
        }
    } 

if (menu1Option != 3) {   
    
    cout << endl << endl << "Would you like to enter a new expression? Enter y/n: ";
    cin.ignore();
    getline(cin, newExpression);
}

if (newExpression == "y" || newExpression == "Y" || newExpression == "yes" || newExpression == "Yes") {
    cout << endl << "   Please enter an expression:   y = ";
    getline(cin, expression);
    a.clear();
    for (int i = 0; i < expression.size(); i++) {
        a.push_back(expression[i]);
    }
    Math.Parse(a);
}



}


    return 0;
}

