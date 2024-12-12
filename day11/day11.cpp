#include "../includes.h"

struct StoneCount
{
    uint64_t zeroValueStones = 0;
    uint64_t evenDigitStones = 0;
    

}




vector<int> readInput(string inputFile)
{
    auto file = openFileSafe(inputFile);
    string line;
    getline(file, line);
    return readLineIntoVector(line);
}


int main()
{
    auto input = readInput("input.txt");

    printVector(input);


    return 0;
}