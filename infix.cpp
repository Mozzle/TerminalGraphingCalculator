#include "infix.h"
#include <cctype>
#include <cmath>
#include <string>


using namespace std;

Infix::Infix() {

}

Infix::~Infix() {

}
//----------------------------------------------------------------------------------------------
// Converts Standard Algebraic functions held in a char vector to postfix notating using the 
// Shunting Yard Algorithm
//----------------------------------------------------------------------------------------------
vector<string> Infix::Parse(vector<char> infix) {
    outputQueue.clear();
    operatorStack.clear();

    for (int i = 0; i < infix.size(); i++) {
        cout  << infix.at(i) << " ";
    }

    int dotCount;

    for (int i = 0; i < infix.size(); i++) {    //Iterate through the input char vector
        dotCount = 0;
        string fillNum = "";
        if (isdigit(infix.at(i))) { //Detect numbers and place entire number into the output queue.
            int pos = i;
            while (pos < (infix.size()) && (isdigit(infix.at(pos)) || infix.at(pos) == '.') && dotCount < 2) {  //move pos to the end of the number
                if (infix.at(pos) == '.') {
                    dotCount++;
                }
                pos++;
            }
            
            for (int j = i; j < pos; j++) { //Get the whole number and put it in the output queue.
                fillNum = fillNum + infix.at(j); 
            }
            pos--;
            i = pos;
            outputQueue.push_back(fillNum);    
        }
        else if (infix.at(i) == 'x' || infix.at(i) == 'X') { //Detect variable 'x'
            int c = i - 1;
            bool doOnce = true;
            //Detect implied multiplication. e.g: '6x' = 6 * x
            while (doOnce && c >= 0 && infix.at(c) != '+' && infix.at(c) != '-' && infix.at(c) != '/' && infix.at(c) != '^' && infix.at(c) != '*' ) {
                if (isdigit(infix.at(c))) {
                    if (!operatorStack.empty()) {
                        while ( operatorStack.back() == '^') {
                            string pop(1, operatorStack.back());
                            operatorStack.pop_back();
                            outputQueue.push_back(pop);
                        }
                    }
                    
                    operatorStack.push_back('*');
                    doOnce = false;
                }
                --c;
            }
            outputQueue.push_back("x");
        }
        else if (infix.at(i) == '+' || infix.at(i) == '-') { //Detect add/sub, if there is an operator of a higher presedence on top of he stack, pop it off and put it in the output queue.
            if (!operatorStack.empty()) {
            while (operatorStack.back() == '*' || operatorStack.back() == '/' || 
            operatorStack.back() == '^') {
                string pop(1, operatorStack.back());    //TODO: Make this a private method to pop and place
                operatorStack.pop_back();
                outputQueue.push_back(pop);
                
            }
            }
           operatorStack.push_back(infix.at(i));
        }
        else if (infix.at(i) == '*' || infix.at(i) == '/') { // Detect mult/divide, following the same rule for higher precedence.
            if (!operatorStack.empty()) {
            while ( operatorStack.back() == '^') {
                string pop(1, operatorStack.back());
                operatorStack.pop_back();
                outputQueue.push_back(pop);
            }
            }
            operatorStack.push_back(infix.at(i));
        }
        else if (infix.at(i) == '^') {  //Detect powers
            if (!operatorStack.empty()) {
            }
            operatorStack.push_back(infix.at(i));
        }
        else if (infix.at(i) == '(') {  //Detect parenthesis and give operations contained within the highest precedence.
            operatorStack.push_back(infix.at(i));
        }
        else if (infix.at(i) == ')') {
            while (operatorStack.back() != '(') {
                string pop(1, operatorStack.back());
                operatorStack.pop_back();
                outputQueue.push_back(pop);
                if (operatorStack.empty()) {
                    cout << "Parenthesis Error!";
                }
            }
        }
        else if (infix.at(i) == 'c' || infix.at(i) == 'C') {
            if (infix.at(i+1) == 'o' && infix.at(i+2) == 's' && infix.at(i+3) == '(') { // cos()
                operatorStack.push_back('c');
                operatorStack.push_back('(');
                i = i+3;
            }
        }
        else if (infix.at(i) == 's' || infix.at(i) == 'S') {
            if (infix.at(i+1) == 'i' && infix.at(i+2) == 'n' && infix.at(i+3) == '(') { //sin()
                operatorStack.push_back('s');
                operatorStack.push_back('(');
                i = i+3;
            }
            else if (infix.at(i+1) == 'q' && infix.at(i+2) == 'r' && infix.at(i+3) == 't' && infix.at(i+4) == '(') { // sqrt()
                operatorStack.push_back('r');
                operatorStack.push_back('(');
                i = i + 4;
            }
        }
        else if (infix.at(i) == 't' || infix.at(i) == 'T') {
            if (infix.at(i+1) == 'a' && infix.at(i+2) == 'n' && infix.at(i+3) == '(') { // cos()
                operatorStack.push_back('t');
                operatorStack.push_back('(');
                i = i+3;
            }
        }
        else if (infix.at(i) =='e' || infix.at(i) == 'E') {
            outputQueue.push_back("2.7182818");
        }
        else if (infix.at(i) == 'p' || infix.at(i) == 'P') {
            if (infix.at(i+1) == 'i' || infix.at(i+1) == 'I') {
                outputQueue.push_back("3.1415926");
                i = i + 1;
            }
        }
        else if (infix.at(i) == 'l' || infix.at(i) == 'L') {
            if (infix.at(i+1) == 'n' && infix.at(i+2) == '(' ) { // ln()
                operatorStack.push_back('l');
                operatorStack.push_back('(');
                i = i+2;
            }
            else if (infix.at(i+1) == 'o' && infix.at(i+2) == 'g' && infix.at(i+3) == '(') { //log()
                operatorStack.push_back('g');
                operatorStack.push_back('(');
                i = i+3;
            }
        }
        
    }

    while (operatorStack.size() > 0) {      //At the end of reading the input char vector, empty out the operator stack onto the output queue.
        string pop(1, operatorStack.back());
        operatorStack.pop_back();
        if (pop != "(") {
            outputQueue.push_back(pop);
        }
    }

    

    return outputQueue;
}

//-----------------------------------------------------------------------------------------------
// Evaluates the postfix algebraic function at a given value. This method is called by graph() for determining the
// Y values of the function on the graph
//----------------------------------------------------------------------------------------------- 
double Infix::evaluate (double x) {
    vector<string> equation = outputQueue;

    for (int i = 0; i < equation.size(); i++) { //Replace X values in the function with the value being evaluated.
        if (equation.at(i) == "x") {
            equation.at(i) = to_string(x);
        }
    }

    
    while (equation.size() >= 2) { //Question to self: why did I make this 2? Test 0 as a value.
        for (int i = 0; i < equation.size(); i++) {  //Reading the equation from left to right, when an operator is read, the previous 2 numbers are evaluated.
                                                     //Then, the operator in the equation is replaced with evaluated number, and the operands are deleted from the equation.
            if (equation.at(i) == "^") {
                equation.at(i) = to_string(pow(stof(equation.at(i - 2)) , (stof(equation.at(i - 1)))));
                equation.erase(equation.begin() + i -1);
                equation.erase(equation.begin() + i -2);
                i = i-2;
            }
            else if (equation.at(i) == "*") {
                equation.at(i) = to_string(stof(equation.at(i- 2)) * (stof(equation.at(i- 1))));
                equation.erase(equation.begin() + i -1);
                equation.erase(equation.begin() + i -2);
                i = i-2;
            }
            else if (equation.at(i) == "/") {
                equation.at(i) = to_string(stof(equation.at(i- 2)) / (stof(equation.at(i- 1))));
                equation.erase(equation.begin() + i -1);
                equation.erase(equation.begin() + i -2);
                i = i-2;
            }
            else if (equation.at(i) == "+") {
                equation.at(i) = to_string(stof(equation.at(i- 2)) + (stof(equation.at(i- 1))));
                equation.erase(equation.begin() + i -1);
                equation.erase(equation.begin() + i -2);
                i = i-2;
            }
            else if (equation.at(i) == "-") {
                equation.at(i) = to_string(stof(equation.at(i- 2)) - (stof(equation.at(i- 1))));
                equation.erase(equation.begin() + i -1);
                equation.erase(equation.begin() + i -2);
                i = i-2;
            }
            else if (equation.at(i) == "c") {
                equation.at(i) = to_string(cos(stof(equation.at(i-1))));
                equation.erase(equation.begin() + i - 1);
                i = i - 1;
            }
            else if (equation.at(i) == "s") {
                equation.at(i) = to_string(sin(stof(equation.at(i-1))));
                equation.erase(equation.begin() + i - 1);
                i = i - 1;
            }
            else if (equation.at(i) == "r") {
                if (stof(equation.at(i-1)) < 0) {
                                                                        //ERROR, NONREAL ANSWER
                } 
                equation.at(i) = to_string(sqrt(stof(equation.at(i-1))));
                equation.erase(equation.begin() + i - 1);
                i = i - 1;
            }
            else if (equation.at(i) == "t") {
                equation.at(i) = to_string(tan(stof(equation.at(i-1))));
                equation.erase(equation.begin() + i - 1);
                i = i - 1;
            }
            else if (equation.at(i) == "l") {
                equation.at(i) = to_string(log(stof(equation.at(i-1))));
                equation.erase(equation.begin() + i - 1);
                i = i - 1;
            }
            else if (equation.at(i) == "g") {
                equation.at(i) = to_string(log10(stof(equation.at(i-1))));
                equation.erase(equation.begin() + i - 1);
                i = i - 1;
            }

        
        }
    }
    return stof(equation.at(0));
}
//------------------------------------------------------------------------------------------------
// Graphs the provided equation between the two given xvalues in a 100 Wide x 40 Tall character graph.
//------------------------------------------------------------------------------------------------
void Infix::graph(double xmin, double xmax, bool autoY, double ymin, double ymax) {
    //TODO: Organize this mess.

    string graphDefault = "    |                                                                                                    |";
    //double ymin;
    //double ymax;
    string xminSide = to_string(int(xmin / 2));
    int xminSideIndex;
    string xmaxSide = to_string(int(xmax / 2));
    int xmaxSideIndex;
    int zeroLocation;
    int yminSide;
    int ymaxSide;

    vector<double> yValues;
    //For calculating each value along the x
    for (float i = 0.01; i < 1.01; i = i + 0.01) {
        double tmp = evaluate(xmin + (xmax - xmin) * i);
        if (isinf(tmp) || isnan(tmp)) { //Check if value is infinity or NaN
            tmp = 0;
        }
        yValues.push_back(tmp);
    }

    string topLine =   "     ____________________________________________________________________________________________________";
    string finalLine = "    |____________________________________________________________________________________________________|";
    string xLabels   = "                                                                                                          ";

    //If the user selects automatic y-range calculatoin
    if (autoY == true) {
        //Find minimum and maximum y values
        ymin = yValues.at(0);
        ymax = yValues.at(0);
        for (int j = 0; j < yValues.size(); j++) {
            if (yValues.at(j) < ymin && (ymin - yValues.at(j)) < 5000) {
                ymin = yValues.at(j);
            }
            if (yValues.at(j) > ymax && (yValues.at(j) - ymax) < 5000) {
                ymax = yValues.at(j);
            }
        }

        //If the y range is too small, I need to manually set the range so that the graph makes sense. For example, without this if statement
        //graphing the identity "y = 4" would yield a maximum y range of the graph of 4 and a minimum of 4.
        if ((ymax - ymin) <= ((xmax - xmin) * 0.1)) {
            ymax = ymax + ((xmax - xmin) * 0.25);
            ymin = ymin - ((xmax - xmin) * 0.25);
        }
        /* if ((ymax - ymin) >= ((xmax - xmin) * 120)) {
            ymax = ymax + ((xmax - xmin) * 0.25);
            ymin = ymin - ((xmax - xmin) * 0.25);
        } */

        
    }

    yminSide = floor(ymin / 2);
    ymaxSide = floor(ymax / 2);

    //cout << "xmin: " << xmin << "  xmax: " << xmax << "  ymin: " << ymin << "  ymax: " << ymax << "   yminSide: " << yminSide << "  ymaxSide: " << ymaxSide << endl << endl;
    cout << endl << endl;

        //Make y-axis maximum and minimum labels.
        for (int i = 0; i < to_string((ymax)).length(); i++) {
            if (i < 4) {
                topLine[i] = to_string((ymax))[i];
            }
        }
        if (topLine[3] == '.') {
            topLine[3] = ' ';
        }
        for (int i = 0; i < to_string((ymin)).length(); i++) {
            if (i < 4) {
                finalLine[i] = to_string((ymin))[i];
            }
        }
        if (finalLine[3] == '.') {
            finalLine[3] = ' ';
        }

    //Print the topmost line of the graph.
    cout << topLine << endl;

    //------------------------------------------------------------------------------------------------------------------------------------------------
    //Iterate down the graph, line by line, then scan each 'pixel' left to right to determine if the graph (\, _, -, /, |) or the origin (|) lies within the pixel.
    for (int y = 39; y >= 0; y--) {
        string graphLine = graphDefault;
        //Calculate the minimum and maximum y values that lie within each line.
        double lineRangeMax = (((ymax - ymin) / 40) * (1 + float(y))) + ymin;
        double lineRangeMin = ((((ymax - ymin) / 40) * (0.00001 + float(y)))) + ymin;

        //If the y=0 origin line lies within the line, draw a horizontal origin line.
        if ((0 <= lineRangeMax) && (0 >= lineRangeMin)) {
            if ( 0 <= (lineRangeMax + lineRangeMin) * (1.0 / 2.0)) {
                //graphLine = " 0 |____________________________________________________________________________________________________|";
                graphLine = "0   |....................................................................................................|";
            }
            else { // ((0 > (lineRangeMax + lineRangeMin) * (1.0/3.0)) && (0 < (lineRangeMax + lineRangeMin)) * (2.0/3.0)) {
               //graphLine = " 0 |----------------------------------------------------------------------------------------------------|";
              graphLine = "0   |====================================================================================================|";
            }
     
        }
        // Calculate which line to place the 'middle' Y-axis labels (the two that aren't the max, min or origin) 
        else if (ymaxSide > lineRangeMin && ymaxSide < lineRangeMax) {
            for (int i = 0; i < to_string(ymaxSide).size(); i++) {
                graphLine[i] = to_string(ymaxSide)[i];
            }
            graphLine[5] = '-';
        }
        else if (yminSide > lineRangeMin && yminSide < lineRangeMax) {
            for (int i = 0; i < to_string(yminSide).size(); i++) {
                graphLine[i] = to_string(yminSide)[i];
            }
            graphLine[5] = '-';
        }
        //-------------------------------------------------------------------------------------------------------------------------------
        //Iterate through each 'pixel' from left to right on each line, detecting whether or not parts of the graph lie within each pixel.
        for (int x = 0; x < yValues.size(); x++) {
            
            //Detect if the x=0 origin lies within the pixel, if it does, draw a vertical origin line in the pixel.
            if (((((xmax - xmin) * ((double(x) / yValues.size()))) + xmin) <= 0) && (((xmax - xmin) * ((double(x + 1) / yValues.size()))) + xmin) > 0) {
                graphLine[x + 5] = '|';
                zeroLocation = x + 5;
                if (xmin != 0 && xmax != 0) { //Avoid writing '0' labels twice, if xmin or xmax are already 0
                    xLabels[x+5] = '0';
                }
            }

            //Detect if the graph passes through the pixel, if it does, draw an appropriate character to represent the graph at that point.
            if (yValues.at(x) <= lineRangeMax && (yValues.at(x) >= lineRangeMin)) {
                if (x < 100) {
                    //Do symbolic differentiation/find slope of the graph in the pixel, then normalize the slope to the x:y scale of the graph, and then draw an appropriate character.
                    float scaledSlope = ((yValues.at(x+1) - yValues.at(x)) / ((xmax - xmin) / yValues.size())) * ((xmax - xmin) / (ymax - ymin));
                    if (scaledSlope >= 4.5 || scaledSlope <= -4.5) {
                        graphLine[x+5] = '|';
                    }
                    else if(scaledSlope >= 2.0) {
                        graphLine[x+5] = '/';
                    }
                    else if (scaledSlope <= -2.0) {
                        graphLine[x+5] = '\\';
                    }
                    else if (yValues.at(x) <= (lineRangeMax + lineRangeMin) * (1.0 / 2.0)) {
                        graphLine[x+5] = '_';
                    }
                    else {
                        graphLine[x+5] = '-';
                    }
                }
                else {
                graphLine[x + 5] = '*';
                }
            }
            
        }

        cout << graphLine << endl;
    }
    //Create 'middle' x-axis labels.
    for (int x = 0; x < yValues.size(); x++) {
        if (floor(xmin / 2) >= (xmin + ((xmax - xmin) * (double(x) / yValues.size()))) && (floor(xmin / 2) <= (xmin + ((xmax - xmin) * double(double(x+1) / yValues.size()))))) {
                finalLine[x+5] = '|';
                xminSideIndex = x+5;
            }
            if (floor(xmax / 2) >= (xmin + ((xmax - xmin) * double(double(x) / yValues.size()))) && (floor(xmax / 2) <= (xmin + ((xmax - xmin) * double(double(x+1) / yValues.size()))))) {
                finalLine[x+5] = '|';
                xmaxSideIndex = x + 5;
            }
    }
    //Put x-axis origin line on the final line.
    finalLine[zeroLocation] = '|';

    //Place numeric labels for the x-axis
    for (int i = 0; i < xminSide.length(); i++)  {
        if (stof(xminSide) != xmin) {
            xLabels[xminSideIndex + i] = xminSide[i];
        }
    }
    for (int j = 0; j < xmaxSide.length(); j++) {
        if (stof(xmaxSide) != xmax) {
        xLabels[xmaxSideIndex + j] = xmaxSide[j];
        }
    }
    for (int k = 0; k < to_string(int(xmin)).length(); k++) {
        xLabels[4 + k] = to_string(int(xmin))[k];
    }
    for (int k = 0; k < to_string(int(xmax)).length(); k++) {
        xLabels[104 + k] = to_string(int(xmax))[k];
    }


    cout << finalLine<< endl;
    cout << xLabels << endl;;

    
}

vector<string> Infix::getExpression() {
    return outputQueue;
}
