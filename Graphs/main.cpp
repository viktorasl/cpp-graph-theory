//
//  main.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include <cmath>
#include "GeneratingFunction.h"

using namespace std;

int main(int argc, const char * argv[])
{
    long n = 10000;
    long m = 20000;
    long iterations = 100;
    GeneratingFunction *gf = new GeneratingFunction(2, m, n, 8);
    
    Graph graph(n, m, gf);
    
    long from;
    long to;
    
    while (from != -1) {
        cout << "Source index: ";
        cin >> from;
        cout << "Destination index: ";
        cin >> to;
        if (from >= 0 && to >= 0) {
            
            long sum = 0;
            long max = 0;
            long min = INT32_MAX;
            for (int i = 0; i < iterations; i++) {
                long stepsCount = graph.stepsCount(from, to);
                if (stepsCount < min) {
                    min = stepsCount;
                }
                if (stepsCount > max) {
                    max = stepsCount;
                }
                sum += stepsCount;
            }
            
            cout << "Average: " << (sum / iterations) << "; Min: " << min << "; Max: " << max << endl;
            
        }
    }
    
    return 0;
}
