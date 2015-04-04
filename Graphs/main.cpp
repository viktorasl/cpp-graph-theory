//
//  main.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include "GeneratingFunction.h"
#include "InhomogenicGraph.h"

using namespace std;

int main(int argc, const char * argv[])
{
    long n = 10000;
    long m = 20000;
    GeneratingFunction *gfn = new GeneratingFunction(1.5, m, n, 4);
    GeneratingFunction *gfm = new GeneratingFunction(3, m, n, 4);
    
    InhomogenicGraph iGraph(n, m, gfn, gfm);
    
    if (iGraph.isConnected()) {
        iGraph.sourceDegreesHistogram("destinationsPickingHistogram.txt");
    } else {
        cout << "Graph is not connected" << endl;
    }
    
    return 0;
}
