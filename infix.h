#ifndef INFIX_H
#define INFIX_H

#include <iostream>
#include <vector>

using namespace std;

class Infix {

    public:

     Infix();
     ~Infix();
     vector<string> Parse(vector<char> infix);
     double evaluate (double x);
     void graph(double xmin, double xmax, bool autoY, double ymin, double ymax);
     vector<string> getExpression();

    private:
    vector<string> outputQueue;
    vector<char> operatorStack;

};

#endif