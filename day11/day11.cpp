#include "../includes.h"

#define DIGITS(num) (static_cast<uint64_t>(log10(num)) + 1)

vector<int> readInput(string inputFile)
{
    auto file = openFileSafe(inputFile);
    string line;
    getline(file, line);
    return readLineIntoVector(line);
}

pair<uint64_t, uint64_t> splitStone(uint64_t number)
{
    auto digits = DIGITS(number);
    if (digits % 2 != 0 || number == 0)
    {
        cout << "WRONG NUMBER: " << digits << " for number " << number << endl;
        throw std::invalid_argument("Wrong input.");
    }

    uint64_t divisor = 1;
    for (int i = 0; i < digits / 2; ++i) divisor *= 10;

    uint64_t left = number / divisor;
    uint64_t right = number % divisor;

    return make_pair(left, right);
}

uint64_t countStones(vector<int>& input, int blinks)
{
    // Using map - theory is that we're likely to hit a lot of repeat values. Also easy erasing/etc.
    unordered_map<uint64_t, uint64_t> freq;
    for(auto& i : input)
    {
        freq[i]++;
    }

    while(blinks > 0)
    {
        unordered_map<uint64_t, uint64_t> newFreq;
        for(auto& pair : freq)
        {
            // Stones engraved with 0 become 1
            if (pair.first == 0)
            {
                newFreq[1] += pair.second;
            }
            else if (DIGITS(pair.first) % 2 == 0)
            {
                // Stones with even num digits get split
                auto [left, right] = splitStone(pair.first);
                newFreq[left] += pair.second;
                newFreq[right] += pair.second;
            }
            else
            {
                // All other stones multiplied by 2024
                if (pair.first > UINT64_MAX / 2024) 
                {
                    throw std::overflow_error("Multiplication causes overflow");
                }

                newFreq[pair.first * 2024] += pair.second;
            }
        }
        freq = newFreq; 
        blinks--;
    }

    uint64_t sumStones = 0;
    for(auto& i : freq)
    {
        sumStones += i.second;
    }

    return sumStones;
}

int main()
{
    auto input = readInput("input.txt");
    printVector(input);

    auto stones = countStones(input, 25);
    cout << "Stones after 25 blinks: " << stones << endl;
    stones = countStones(input, 75);
    cout << "Stones after 75 blinks: " << stones << endl;

    return 0;
}
