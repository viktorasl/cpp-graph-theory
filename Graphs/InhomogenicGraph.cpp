//
//  InhomogenicGraph.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 21/03/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "InhomogenicGraph.h"
#include <iostream>
#include "Vertex.h"
#include "GeneratingFunction.h"
#include <math.h>
#include <fstream>

#define MIN(a,b) ((a) < (b) ? a : b)

using namespace std;

InhomogenicGraph::InhomogenicGraph(long n, long m, GeneratingFunction* gfn, GeneratingFunction *gfm)
    :gf(gfn)
{
#ifdef DEBUG
    cout << n << " source vertexes, " << m << " destination vertexes." << endl;
#endif
    cout << "Generating source & destination vertexes..." << endl;
    for (long i = 0; i < n; i++) {
        sourceVertexes.push_back(new Vertex(VertexTypeSource, i, gfn->randomizeFunctionValue()));
    }
    for (long i = 0; i < m; i++) {
        destinationVertexes.push_back(new Vertex(VertexTypeDestination, i, gfm->randomizeFunctionValue()));
    }
    connectSourceAndDestinationVertexes();
    connectSourcesToEachOther();
}

void InhomogenicGraph::connectSourceAndDestinationVertexes()
{
    const double divFactor = sqrt(sourceVertexes.size() * destinationVertexes.size());
    
    int a = 0;
    for (std::vector<Vertex *>::iterator src = sourceVertexes.begin(); src != sourceVertexes.end(); ++src) {
        for (std::vector<Vertex *>::iterator dst = destinationVertexes.begin(); dst != destinationVertexes.end(); ++dst) {
            double posibility = MIN(((*src)->getFactor() * (*dst)->getFactor()) / divFactor, 1);
            
            double odd = gf->randomizeU();
            while (odd == posibility) {
                odd = this->gf->randomizeU();
            }
            
            if (odd < posibility) {
                (*src)->connectToVertex(*dst);
                (*dst)->connectToVertex(*src);
                a++;
            }
        }
    }
    cout << a << endl;
}

void InhomogenicGraph::destinationsPickingHistogram(string oFileName)
{
    ofstream file(oFileName);
    for (std::vector<Vertex *>::iterator dst = destinationVertexes.begin(); dst != destinationVertexes.end(); ++dst) {
        file << "w" << (*dst)->getKey() << "\t" << (*dst)->getFactor() << "\t" << (*dst)->possibleWays() << endl;
    }
    file.close();
}
