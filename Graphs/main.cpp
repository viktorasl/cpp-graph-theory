//
//  main.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, const char * argv[])
{
    long n = 10000;
    long m = 10000;
    
    Graph *graph = new Graph(n, m);
    
    long from;
    long to;
    cout << "Source index: ";
    cin >> from;
    cout << "Destination index: ";
    cin >> to;
    cout << graph->stepsCount(from, to);
    
    return 0;
}
