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
    long n = 10000;
    long m = 20000;
    double beta1 = 1.5;
    double beta2 = 1.5;
    GeneratingFunction *gfn = new GeneratingFunction(beta1, m, n, 4);
    GeneratingFunction *gfm = new GeneratingFunction(beta2, m, n, 4);
    
    chrono::high_resolution_clock::time_point startT = chrono::high_resolution_clock::now();
    InhomogenicGraph graph(n, m, gfn, gfm);
//    Graph graph(n, m, gfn);
    chrono::high_resolution_clock::time_point endT = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::milliseconds>(endT - startT).count();
    cout << duration << "ms" << endl;
    
    vector<Component *> components = graph.findingComponents();
    int idx = 1;
    for (vector<Component *>::iterator it = components.begin(); it != components.end(); ++it) {
        cout << "C" << idx++ << " size " << (*it)->vertexes.size() << endl;
        if (idx == 2) {
            break;
        }
    }
    
    long segments = 0;
    long avg = 0;
    long *s = components[0]->visitAndReturn(100, segments, avg);
    Histogram::generate(segments, s, "visiting-to-home");
    cout << "average degrees count is " << avg << endl;
    
    stringstream ss;
    ss << "nonhomogenic-beta1=" << beta1 << "beta2=" << beta2;
    Histogram::generate(100, graph.getSourceDegrees(100), ss.str());
    
    return 0;
}
