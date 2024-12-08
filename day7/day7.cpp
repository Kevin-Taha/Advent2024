#include "../includes.h"
#define PT2

struct Equation
{
    uint64_t result;
    stack<uint64_t> operands;
};

uint64_t concat(uint64_t a, uint64_t b)  // 123  45 -> 12300 + 45 -> a * 10^(bDigits) + b
{
    int digitsB = static_cast<int>(log10(b)) + 1;
    return a * static_cast<int>(pow(10, digitsB)) + b;
}

vector<Equation> readInput(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vector<Equation> equations;
    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        Equation eq;
        ss >> eq.result;
        ss.ignore(1, ':'); // Ignore ':'
        vector<int> operands;

        uint64_t num;
        while (ss >> num)
        {
            operands.push_back(num);
        }

        for(auto it = operands.rbegin(); it != operands.rend(); it++)
        {
            eq.operands.push(*it);
        }

        equations.push_back(eq);
    }
    return equations;
}

// Best bet is recursion. Pop 2 off stack, recurse one path where we add them, one path where we mult
bool isEquationValid(Equation eq)
{
    // Base case: One element left on stack, check if its the total.
    if (eq.operands.size() == 1)
    {
        return eq.operands.top() == eq.result;
    }
    // Some safety and optimizations. All our operations increase the operands. 
    if(eq.operands.size() == 0 || eq.operands.top() > eq.result) return false;

    auto op1 = eq.operands.top();
    eq.operands.pop();
    auto op2 = eq.operands.top();
    eq.operands.pop();

    // Try adding
    eq.operands.push(op1 + op2);
    bool add = isEquationValid(eq);
    eq.operands.pop();

    // Try mult
    eq.operands.push(op1 * op2);
    bool mult = isEquationValid(eq);
    eq.operands.pop();

    // Try Concat 
    bool cc = false;
    if (concat(op1, op2) <= eq.result) // optimization
    {
        eq.operands.push(concat(op1, op2));
        cc = isEquationValid(eq);
    }

    return add || mult || cc;
}

int main()
{
    auto equations = readInput("input.txt");
    uint64_t total = 0;

    for(auto& eq : equations)
    {
        if(isEquationValid(eq))
        {
            total += eq.result;
        }
    }

    cout << "Total Calibration: " << total << endl;
    return 0;
}