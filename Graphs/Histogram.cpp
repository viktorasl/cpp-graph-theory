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

using namespace std;

void Histogram::generate(long segments, long *data, string fileName)
{
    stringstream outputFile;
    outputFile << fileName << ".txt";
    ofstream file(outputFile.str());
    
    for (long i = 0; i < segments; i++) {
        file << data[i] << endl;
    }
    file.close();
    
    stringstream rubyExecutable;
    rubyExecutable << "ruby histogram.rb draw " << outputFile.str() << " " << fileName;
    const char *exec = rubyExecutable.str().c_str();
    system(exec);
}