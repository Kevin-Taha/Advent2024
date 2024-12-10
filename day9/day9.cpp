#include "../includes.h"

vector<int> readInput(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vector<int> nums;
    string line;

    while(getline(file, line))
    {
        for(char& c : line)
        {
            nums.push_back(c - '0');
        }
    }

    return nums;
}

// Converts the input format e.g 12345 to 0..111....22222, but we'll use -1 for empty spaces.
vector<int> InputToIdString(vector<int>& nums)
{
    vector<int> out;
    int curId = 0;
    bool isFile = true;

    for(auto& i : nums)
    {   
        int curNum = (isFile) ? curId++ : -1;
        for(int j = 0; j < i; j++)
        {
            out.push_back(curNum);
        }        
        isFile = !isFile;
    }
    return out;
}

uint64_t calcCheckSum(vector<int>& nums)
{
    uint64_t checkSum = 0;
    auto idString = InputToIdString(nums);

    // Two pointers - One at first empty space and another at last valid memory space
    int left = 0;
    int right = idString.size() - 1;

    while(left < right)
    {
        while (idString[left] != -1)
        {
            left++;
        }
        while (idString[right] == -1)
        {
            right--;
        }
        if(left >= right) break;

        // Swap number on right into empty spot at left pointer
        swap(idString[right], idString[left]);
    }
    //printVector(idString);

    // Compute checksum. Index * ID
    for(int i = 0; i < idString.size(); i++)
    {
        if (idString[i] != -1)
        {
            checkSum += i * idString[i];
        }
    }

    return checkSum;
}   

int main()
{
    auto numArr = readInput("input.txt");
    auto checkSum = calcCheckSum(numArr);
    cout << "Pt 1 Checksum: " << checkSum << endl;


    //vector<int> t {1,2,3,4,5};
    //auto t1 = InputToIdString(t);
    //printVector(t1);
    //calcCheckSum(t);


    return 0;
}
