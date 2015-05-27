//
//  OutputHelper.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 28/05/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "OutputHelper.h"
#include <sstream>

using namespace std;

string const resultsDir = "res";

string resultsPath(string file)
{
    stringstream ss;
    ss << resultsDir << "/" << file;
    return ss.str();
}

string resultsPath(string file, string ext)
{
    stringstream ss;
    ss << resultsDir << "/" << file << "." << ext;
    return ss.str();
}