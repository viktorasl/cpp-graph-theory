//
//  main.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <iostream>
#include <chrono>
#include "Graph.h"
#include "GeneratingFunction.h"
#include "InhomogenicGraph.h"

using namespace std;

int main(int argc, const char * argv[])
{
    long n = 10000;
    long m = 20000;
    GeneratingFunction *gfn = new GeneratingFunction(1.5, m, n, 4);
    GeneratingFunction *gfm = new GeneratingFunction(1.5, m, n, 4);
    
    chrono::high_resolution_clock::time_point startT = chrono::high_resolution_clock::now();
    InhomogenicGraph graph(n, m, gfn, gfm);
//    Graph graph(n, m, gfn);
    chrono::high_resolution_clock::time_point endT = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::milliseconds>(endT - startT).count();
    cout << duration << "ms" << endl;
    
    vector<Component> components = graph.findingComponents();
    
    graph.sourceDegreesHistogram("nonhomogenic-beta=1.5beta=1.5", 100);
    
    return 0;
}
