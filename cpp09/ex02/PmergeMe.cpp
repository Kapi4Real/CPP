#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace
{
struct SortValue
{
    int value;
    std::size_t id;

    SortValue() : value(0), id(0)
    {
    }

    SortValue(int number, std::size_t identifier)
        : value(number), id(identifier)
    {
    }

    bool operator<(const SortValue& other) const
    {
        return value < other.value;
    }
};

struct PairRecord
{
    SortValue small;
    SortValue large;
};

std::vector<SortValue> fordJohnsonVector(
    const std::vector<SortValue>& input)
{
    const std::size_t noOwner = std::numeric_limits<std::size_t>::max();
    if (input.size() <= 1)
        return input;

    std::vector<PairRecord> pairs;
    std::vector<SortValue> maxima;
    std::vector<SortValue>::const_iterator current = input.begin();
    bool hasStraggler = false;
    SortValue straggler;

    while (current != input.end())
    {
        SortValue first = *current;
        ++current;
        if (current == input.end())
        {
            hasStraggler = true;
            straggler = first;
            break;
        }

        SortValue second = *current;
        ++current;
        PairRecord pair;
        if (second < first)
        {
            pair.small = second;
            pair.large = first;
        }
        else
        {
            pair.small = first;
            pair.large = second;
        }
        pairs.push_back(pair);
        maxima.push_back(pair.large);
    }

    std::vector<SortValue> sortedMaxima = fordJohnsonVector(maxima);
    std::size_t largestIdentifier = 0;
    std::size_t pairIndex = 0;
    while (pairIndex < pairs.size())
    {
        if (pairs[pairIndex].large.id > largestIdentifier)
            largestIdentifier = pairs[pairIndex].large.id;
        ++pairIndex;
    }
    std::vector<std::size_t> pairForIdentifier(largestIdentifier + 1, noOwner);
    pairIndex = 0;
    while (pairIndex < pairs.size())
    {
        pairForIdentifier[pairs[pairIndex].large.id] = pairIndex;
        ++pairIndex;
    }

    std::vector<PairRecord> orderedPairs;
    std::vector<SortValue>::const_iterator maximum = sortedMaxima.begin();
    while (maximum != sortedMaxima.end())
    {
        orderedPairs.push_back(pairs[pairForIdentifier[maximum->id]]);
        ++maximum;
    }

    std::vector<SortValue> chain;
    std::vector<std::size_t> ownerByPosition;
    pairIndex = 0;
    while (pairIndex < orderedPairs.size())
    {
        chain.push_back(orderedPairs[pairIndex].large);
        ownerByPosition.push_back(pairIndex);
        ++pairIndex;
    }

    std::vector<SortValue> pending;
    pairIndex = 0;
    while (pairIndex < orderedPairs.size())
    {
        pending.push_back(orderedPairs[pairIndex].small);
        ++pairIndex;
    }
    if (hasStraggler)
        pending.push_back(straggler);
    if (pending.empty())
        return chain;

    chain.insert(chain.begin(), pending[0]);
    ownerByPosition.insert(ownerByPosition.begin(), noOwner);

    std::size_t pendingCount = pending.size();
    std::size_t groupStart = 1;
    std::size_t jacobsthalPrevious = 1;
    std::size_t jacobsthalCurrent = 3;
    while (groupStart < pendingCount)
    {
        std::size_t groupEnd = jacobsthalCurrent - 1;
        if (groupEnd >= pendingCount)
            groupEnd = pendingCount - 1;

        std::size_t cursor = groupEnd + 1;
        while (cursor > groupStart)
        {
            std::size_t pendingIndex = cursor - 1;
            std::size_t searchLimit = chain.size();
            if (pendingIndex < orderedPairs.size())
            {
                std::size_t position = 0;
                while (position < ownerByPosition.size())
                {
                    if (ownerByPosition[position] == pendingIndex)
                    {
                        searchLimit = position;
                        break;
                    }
                    ++position;
                }
            }

            std::size_t low = 0;
            std::size_t high = searchLimit;
            while (low < high)
            {
                std::size_t middle = low + (high - low) / 2;
                if (chain[middle] < pending[pendingIndex])
                    low = middle + 1;
                else
                    high = middle;
            }

            std::vector<SortValue>::iterator insertionPoint = chain.begin();
            std::size_t offset = 0;
            while (offset < low)
            {
                ++insertionPoint;
                ++offset;
            }
            chain.insert(insertionPoint, pending[pendingIndex]);
            ownerByPosition.insert(ownerByPosition.begin() + low, noOwner);
            --cursor;
        }

        if (groupEnd == pendingCount - 1)
            break;
        std::size_t oldBoundary = jacobsthalCurrent;
        jacobsthalCurrent += 2 * jacobsthalPrevious;
        jacobsthalPrevious = oldBoundary;
        groupStart = oldBoundary;
    }
    return chain;
}

std::deque<SortValue> fordJohnsonDeque(const std::deque<SortValue>& input)
{
    const std::size_t noOwner = std::numeric_limits<std::size_t>::max();
    if (input.size() <= 1)
        return input;

    std::vector<PairRecord> pairs;
    std::deque<SortValue> maxima;
    std::deque<SortValue>::const_iterator current = input.begin();
    bool hasStraggler = false;
    SortValue straggler;

    while (current != input.end())
    {
        SortValue first = *current;
        ++current;
        if (current == input.end())
        {
            hasStraggler = true;
            straggler = first;
            break;
        }

        SortValue second = *current;
        ++current;
        PairRecord pair;
        if (second < first)
        {
            pair.small = second;
            pair.large = first;
        }
        else
        {
            pair.small = first;
            pair.large = second;
        }
        pairs.push_back(pair);
        maxima.push_back(pair.large);
    }

    std::deque<SortValue> sortedMaxima = fordJohnsonDeque(maxima);
    std::size_t largestIdentifier = 0;
    std::size_t pairIndex = 0;
    while (pairIndex < pairs.size())
    {
        if (pairs[pairIndex].large.id > largestIdentifier)
            largestIdentifier = pairs[pairIndex].large.id;
        ++pairIndex;
    }
    std::vector<std::size_t> pairForIdentifier(largestIdentifier + 1, noOwner);
    pairIndex = 0;
    while (pairIndex < pairs.size())
    {
        pairForIdentifier[pairs[pairIndex].large.id] = pairIndex;
        ++pairIndex;
    }

    std::vector<PairRecord> orderedPairs;
    std::deque<SortValue>::const_iterator maximum = sortedMaxima.begin();
    while (maximum != sortedMaxima.end())
    {
        orderedPairs.push_back(pairs[pairForIdentifier[maximum->id]]);
        ++maximum;
    }

    std::deque<SortValue> chain;
    std::vector<std::size_t> ownerByPosition;
    pairIndex = 0;
    while (pairIndex < orderedPairs.size())
    {
        chain.push_back(orderedPairs[pairIndex].large);
        ownerByPosition.push_back(pairIndex);
        ++pairIndex;
    }

    std::deque<SortValue> pending;
    pairIndex = 0;
    while (pairIndex < orderedPairs.size())
    {
        pending.push_back(orderedPairs[pairIndex].small);
        ++pairIndex;
    }
    if (hasStraggler)
        pending.push_back(straggler);
    if (pending.empty())
        return chain;

    chain.insert(chain.begin(), pending[0]);
    ownerByPosition.insert(ownerByPosition.begin(), noOwner);

    std::size_t pendingCount = pending.size();
    std::size_t groupStart = 1;
    std::size_t jacobsthalPrevious = 1;
    std::size_t jacobsthalCurrent = 3;
    while (groupStart < pendingCount)
    {
        std::size_t groupEnd = jacobsthalCurrent - 1;
        if (groupEnd >= pendingCount)
            groupEnd = pendingCount - 1;

        std::size_t cursor = groupEnd + 1;
        while (cursor > groupStart)
        {
            std::size_t pendingIndex = cursor - 1;
            std::size_t searchLimit = chain.size();
            if (pendingIndex < orderedPairs.size())
            {
                std::size_t position = 0;
                while (position < ownerByPosition.size())
                {
                    if (ownerByPosition[position] == pendingIndex)
                    {
                        searchLimit = position;
                        break;
                    }
                    ++position;
                }
            }

            std::size_t low = 0;
            std::size_t high = searchLimit;
            while (low < high)
            {
                std::size_t middle = low + (high - low) / 2;
                if (chain[middle] < pending[pendingIndex])
                    low = middle + 1;
                else
                    high = middle;
            }

            std::deque<SortValue>::iterator insertionPoint = chain.begin();
            std::size_t offset = 0;
            while (offset < low)
            {
                ++insertionPoint;
                ++offset;
            }
            chain.insert(insertionPoint, pending[pendingIndex]);
            ownerByPosition.insert(ownerByPosition.begin() + low, noOwner);
            --cursor;
        }

        if (groupEnd == pendingCount - 1)
            break;
        std::size_t oldBoundary = jacobsthalCurrent;
        jacobsthalCurrent += 2 * jacobsthalPrevious;
        jacobsthalPrevious = oldBoundary;
        groupStart = oldBoundary;
    }
    return chain;
}

bool parsePositiveInteger(const char* text, int& value)
{
    std::string token(text);
    std::string::size_type index = 0;
    while (index < token.size())
    {
        if (token[index] < '0' || token[index] > '9')
            return false;
        ++index;
    }
    if (token.empty())
        return false;

    errno = 0;
    char* end = 0;
    long parsed = std::strtol(token.c_str(), &end, 10);
    if (errno == ERANGE || end == token.c_str() || *end != '\0'
        || parsed < 1 || parsed > INT_MAX)
        return false;
    value = static_cast<int>(parsed);
    return true;
}

void printInput(const std::vector<int>& values)
{
    std::cout << "Before: ";
    std::vector<int>::const_iterator current = values.begin();
    while (current != values.end())
    {
        std::cout << *current;
        ++current;
        if (current != values.end())
            std::cout << ' ';
    }
    std::cout << std::endl;
}

void printSorted(const std::vector<SortValue>& values)
{
    std::cout << "After:  ";
    std::vector<SortValue>::const_iterator current = values.begin();
    while (current != values.end())
    {
        std::cout << current->value;
        ++current;
        if (current != values.end())
            std::cout << ' ';
    }
    std::cout << std::endl;
}

double sortWithVector(const std::vector<int>& source,
    std::vector<SortValue>& sorted)
{
    std::clock_t start = std::clock();
    std::vector<SortValue> values;
    std::vector<int>::const_iterator current = source.begin();
    std::size_t identifier = 0;
    while (current != source.end())
    {
        values.push_back(SortValue(*current, identifier));
        ++current;
        ++identifier;
    }
    sorted = fordJohnsonVector(values);
    std::clock_t finish = std::clock();
    return static_cast<double>(finish - start) * 1000000.0
        / static_cast<double>(CLOCKS_PER_SEC);
}

double sortWithDeque(const std::vector<int>& source,
    std::deque<SortValue>& sorted)
{
    std::clock_t start = std::clock();
    std::deque<SortValue> values;
    std::vector<int>::const_iterator current = source.begin();
    std::size_t identifier = 0;
    while (current != source.end())
    {
        values.push_back(SortValue(*current, identifier));
        ++current;
        ++identifier;
    }
    sorted = fordJohnsonDeque(values);
    std::clock_t finish = std::clock();
    return static_cast<double>(finish - start) * 1000000.0
        / static_cast<double>(CLOCKS_PER_SEC);
}

bool sameValues(const std::vector<SortValue>& left,
    const std::deque<SortValue>& right)
{
    if (left.size() != right.size())
        return false;
    std::size_t index = 0;
    while (index < left.size())
    {
        if (left[index].value != right[index].value)
            return false;
        ++index;
    }
    return true;
}
}

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _input(other._input)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
        _input = other._input;
    return *this;
}

PmergeMe::~PmergeMe()
{
}

int PmergeMe::run(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    int argumentIndex = 1;
    while (argumentIndex < argc)
    {
        int number = 0;
        if (!parsePositiveInteger(argv[argumentIndex], number))
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        _input.push_back(number);
        ++argumentIndex;
    }

    std::vector<SortValue> sortedVector;
    double vectorTime = sortWithVector(_input, sortedVector);

    std::deque<SortValue> sortedDeque;
    double dequeTime = sortWithDeque(_input, sortedDeque);
    if (!sameValues(sortedVector, sortedDeque))
    {
        std::cerr << "Error: containers produced different results." << std::endl;
        return 1;
    }

    printInput(_input);
    printSorted(sortedVector);
    std::cout << "Time to process a range of " << _input.size()
              << " elements with std::vector: " << std::fixed
              << std::setprecision(5) << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _input.size()
              << " elements with std::deque:  " << std::fixed
              << std::setprecision(5) << dequeTime << " us" << std::endl;
    return 0;
}
