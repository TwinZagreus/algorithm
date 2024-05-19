#pragma once
#include "chain.h"
using namespace std;


struct studentRecord
{
    int score;
    string* name;

    int operator !=(studentRecord x) const
    {
        return (score != x.score);
    }
};

ostream& operator<<(ostream& out, const studentRecord& x)
{
    out << x.score << ' ' << *x.name << endl; return out;
}


void binSort(chain<studentRecord>& theChain, int range)
{// Sort by score.

   // initialize the bins
    chain<studentRecord>* bin = new chain<studentRecord>[range + 1];

    // distribute student records from theChain to bins
    int numberOfElements = theChain.size();
    for (int i = 1; i <= numberOfElements; i++)
    {
        studentRecord x = theChain.get(0);
        theChain.erase(0);
        bin[x.score].insert(0, x);
    }

    // collect elements from bins
    for (int j = range; j >= 0; j--)
        while (!bin[j].empty())
        {
            studentRecord x = bin[j].get(0);
            bin[j].erase(0);
            theChain.insert(0, x);
        }

    delete[] bin;
}