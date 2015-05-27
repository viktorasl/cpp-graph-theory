//
//  Histogram.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/04/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Histogram.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "OutputHelper.h"

using namespace std;

void Histogram::generate(vector<long> *segments, long relativeColumn, string fileName)
{
    string outputFile = resultsPath(fileName, "txt");
    ofstream file(outputFile);
    
    if (relativeColumn > 0) {
        file << relativeColumn << endl;
    }
    for (vector<long>::iterator segment = segments->begin(); segment != segments->end(); ++segment) {
        file << *segment << endl;
    }
    
    file.close();
    
    stringstream rubyExecutable;
    rubyExecutable << "ruby histogram.rb draw " << outputFile << " " << resultsDir << "/" << fileName;
    const char *exec = rubyExecutable.str().c_str();
    system(exec);
}

void Histogram::generate(vector<long> *segments, string fileName)
{
    Histogram::generate(segments, -1, fileName);
}
