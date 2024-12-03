#include "../includes.h"
#include <regex>

int mulSum(string& inputFile);
int mulSumConditional(string& inputFile);

int main()
{
    string inputFile = "input.txt";

    int mulSumResult = mulSum(inputFile);
    cout << "sum of muls: " << mulSumResult;

    int mulSumCond = mulSumConditional(inputFile);
    cout << "sum of muls w/ conditions: " << mulSumCond;
    return 0;
}

// Given string in format mul(x,y), will compute x * y. No validation so don't screw up :)
int calculateMulExp(const string& input)
{
    int result = 1;
    // Read expression into format "x,y"
    auto start = input.find('(');
    auto end = input.find(')');
    stringstream ss(input.substr(start + 1, end - 1 - start));
    
    int num;
    while(ss >> num)
    {
        result *= num;
        // Ignore the comma
        ss.ignore();
    }

    return result;
}

// Going to use RegEx. Really not worth reading this the manual way. 
int mulSum(string& inputFile)
{
    auto file = openFileSafe(inputFile);
    int result = 0;

    // Read entire file into string. Good idea? No. Safe enough for the input size? Sure, probably.
    string fullText;
    string line;
    while(getline(file, line))
    {
        fullText += line;
    }
    
    regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
    smatch res;

    for(sregex_iterator it(fullText.begin(), fullText.end(), pattern), end_it; it != end_it; ++it)
    {
        string expression(it->str());
        //cout << it->str() << endl;
        result += calculateMulExp(expression);
    }

    return result;
}


int mulSumConditional(string& inputFile)
{
    auto file = openFileSafe(inputFile);
    int result = 0;

    // Read entire file into string. Good idea? No. Safe enough for the input size? Sure, probably.
    string fullText;
    string line;
    while(getline(file, line))
    {
        fullText += line;
    }
    
    regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don\'t\\(\\)");
    smatch res;
    bool mulEnabled = true; 

    for(sregex_iterator it(fullText.begin(), fullText.end(), pattern), end_it; it != end_it; ++it)
    {
        string expression(it->str());
        
        // lazy matching
        if (expression[0] == 'm')
        {
            //cout << "MULT   " << expression;
            if (mulEnabled)
            {
                result += calculateMulExp(expression);
            }
        }
        else if (expression[3] == '\'')
        {
            //cout << "DONT   " << expression << endl;;
            mulEnabled = false;
        }
        else
        {
            //cout << "DO   " << expression << endl;
            mulEnabled = true;
        }
    }

    return result;    
}
