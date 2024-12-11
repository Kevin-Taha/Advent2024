#include "../includes.h"


struct MemoryChunk
{
    int id;
    int chunkSize;
};

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

// Part 2
list<MemoryChunk> InputToMemoryChunkList(vector<int>& nums)
{
    list<MemoryChunk> chunkList;
    int curId = 0;
    bool isFile = true;

    for(auto& i : nums)
    {
        int curNum = (isFile) ? curId++ : -1;
        chunkList.emplace_back(curNum, i);
        isFile = !isFile;
    }

    return chunkList;
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

uint64_t calcCheckSum2(vector<int>& nums)
{
    auto memory = InputToMemoryChunkList(nums);

    vector<MemoryChunk*> fullChunks;
    for(auto& chunk : memory)
    {
        if (chunk.id != -1) 
        {
            fullChunks.push_back(&chunk);
        }
    }

    // Iterate through all file chunks, last to first. 
    for(auto fileIter = fullChunks.rbegin(); fileIter != fullChunks.rend(); fileIter++)
    {
        auto sizeNeeded = (*fileIter)->chunkSize;

        // Look for first empty chunk in the memory list that fits the file (and comes before it)
        for(auto chunkIter = memory.begin(); chunkIter != memory.end(); chunkIter++)
        {
            if(chunkIter->id == (*fileIter)->id) break; // We iterated after the the original file. 

            if (chunkIter->id == -1 && chunkIter->chunkSize >= sizeNeeded)
            {
                if (chunkIter->chunkSize == sizeNeeded)
                {
                    // We can use the full chunk, just transfer the id over
                    chunkIter->id = (*fileIter)->id;
                    (*fileIter)->id = -1;
                    break;
                }
                else
                {
                    // We need to split the chunk up. new chunk size = old chunk size - sizeNeeded. Old chunk size = sizeNeeded
                    memory.insert(next(chunkIter), {-1, chunkIter->chunkSize - sizeNeeded});

                    chunkIter->id = (*fileIter)->id;
                    chunkIter->chunkSize = sizeNeeded;
                    (*fileIter)->id = -1;
                    break;
                }
            }
        }
    }

    vector<int>checkSumString;
    int idx = 0;
    uint64_t checkSum = 0;
    for(auto& m : memory)
    {
        for(int i = 0; i < m.chunkSize; i++)
        {
            if(m.id != -1)
            {
                checkSum += idx * m.id;
            }
            idx++;
        }
    }

    return checkSum;
}

int main()
{
    auto numArr = readInput("input.txt");
    auto checkSum = calcCheckSum(numArr);
    cout << "Pt 1 Checksum: " << checkSum << endl;
    auto checkSum2 = calcCheckSum2(numArr);    
    cout << "Pt 2 Checksum: " << checkSum2 << endl;

    return 0;
}
