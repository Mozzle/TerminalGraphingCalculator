#include "DylMath.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

DylMath::DylMath(int argc, char* argv[]) {

    cout << "You have enered " << argc << " arguments: " << endl;

   /* for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
        cout << *argv[i] << endl;
    } */

    if (argc <= 1) {
        //Home screen, normal use w/o commands
    }
    else {
        string arg(argv[1]);

        if (arg == "quad") {
            if (argc < 5) {
                cout << "Invalid arguments. Please try again." << endl;
            }
            else {
           quadratic(argv[2], argv[3], argv[4]);
            }
        }
        else if (arg == "graph") {
            graph(argc, argv);
        }
        else if (arg == "help") {

        }


    }
}

//Quadratic Formula
void DylMath::quadratic(char *arg1, char* arg2, char* arg3) {
    string isA = arg1;
    string isB = arg2;
    string isC = arg3;
    float a = stof(isA);
    float b = stof(isB);
    float c = stof(isC);

    float radical = (b * b) - (4 * a * c);
    bool perfectSquare = false;
    int pfcSqr;

    cout << "The roots of " << a << "x^2 + " << b << "x + " << c << " are: " << endl;

    if (radical >= 0) { //Real roots
        cout << "x = " << ((-1 * b + sqrt(radical)) / (2*a)) << endl;
        cout << "x = " << ((-1 * b - sqrt(radical)) / (2*a)) << endl;
    }
    else {
        radical = radical * -1;
        for (int i = 0; i < 20; i++) {
            if ((radical / i) == i) {
                perfectSquare = true;
                pfcSqr = i;
            }
        }

        if (perfectSquare) {
            cout << "x = " << (-1 * b) / (2*a) << " + " << (pfcSqr / (2*a)) << "i" << endl;
            cout << "x = " << (-1 * b) / (2*a) << " - " << (pfcSqr / (2*a)) << "i" << endl;
        }
        else {
            cout << "x = " << (-1 * b) / (2*a) << " + " << "(i * sqrt(" << radical << ")) / "  << (2*a) << endl;
            cout << "x = " << (-1 * b) / (2*a) << " - " << "(i * sqrt(" << radical << ")) / "  << (2*a) << endl;
        }
    }

cout << endl << endl;
}

void DylMath::graph(int argc, char * argv[]) {

    //Shunting Yard Algorithm

    vector <char> a;
    vector <float> pows;
    for (int i = 2; i < argc; i++) {
        a.push_back(*argv[i]);
    }

    for (int q = 0; q < a.size(); q++) {
        cout << a.at(q) << " ";
    }
    cout << endl;
    for (int j = 0; j < a.size(); j++) {
        if (a.at(j) == '^') {
            if (a.at(j-1) != 'x' && a.at(j+1) != 'x') {
                a.at(j-1) = (int)a.at(j-1) * (int)a.at(j+1);
                a.erase(a.begin() + j, a.begin() + (j+1));
                j = j-1;
            }
        }
    }
    for (int w = 0; w < a.size(); w++) {
        cout << a.at(w) << " ";
    }
    cout << endl;

    for (int k = 0; k < a.size(); k++) {
        if (a.at(k) == '*') {
            if (a.at(k-1) != 'x' && a.at(k+1) != 'x') {
                a.at(k-1) = (int)a.at(k-1) * (int)a.at(k+1);
                a.erase(a.begin() + k, a.begin() + (k+1));
                k = k-1;
            }
            
        }
    }

}