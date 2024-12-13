#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <array>
#include <unordered_set>
#include <stack>
#include <list>
#include <cstdint>
#include <cmath>
using namespace std;

template<typename T>
using vec2d = vector<vector<T>>;

// Helpers that i'm likely to use in multiple challenges

// Opens an input file with error checking. 
ifstream openFileSafe(string& inputFile)
{
    ifstream file(inputFile);
    if(!file.is_open())
    {
        cerr << "Fail to open file" << endl;
        throw std::exception();
    }
    return file;
}

// Reads a line of integers into a vector (e.g 1 2 3 4 5 -> {1,2,3,4,5})
vector<int> readLineIntoVector(string& line)
{
    vector<int> out;
    stringstream ss(line);
    int num;
    while (ss >> num)
    {
        out.push_back(num);
    }

    return out;
}

template<class c>
void printVector(vector<c>& vec)
{
    for(auto& i : vec)
    {
        cout << i << " ";
    }
    cout << endl;
}

template<typename T>
constexpr bool isInBounds(int x, int y, vector<vector<T>>& arr)
{
    return (x >= 0 && y >= 0 && x < arr.size() && y < arr[0].size());
}
