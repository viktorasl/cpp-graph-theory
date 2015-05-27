//
//  main.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <sstream>
#include "Graph.h"
#include "GeneratingFunction.h"
#include "InhomogenicGraph.h"
#include "Histogram.h"

using namespace std;

int main(int argc, const char * argv[])
{
    long n = 1000;
    long m = 2000;
    int histogramSegments = 20;
    long relativeColumn = 300;
    double beta1 = 1.5;
    double beta2 = 3;
    GeneratingFunction *gfn = new GeneratingFunction(beta1, m, n);
    GeneratingFunction *gfm = new GeneratingFunction(beta2, m, n);
    
    InhomogenicGraph graph(n, m, gfn, gfm);
    
    stringstream ss;
    ss << "Inhomogenic_b1=" << beta1 << "_b2=" << beta2;
    Degrees *degrees = graph.getSourceDegrees(histogramSegments);
    Histogram::generate(degrees, ss.str());
    ss << "_rlt";
    Histogram::generate(degrees, relativeColumn, ss.str());
    
    return 0;
}
