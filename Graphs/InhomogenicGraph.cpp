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
#include <sstream>

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
            }
        }
    }
}

void InhomogenicGraph::destinationsPickingHistogram(string oFileName)
{
    ofstream file(oFileName);
    for (std::vector<Vertex *>::iterator dst = destinationVertexes.begin(); dst != destinationVertexes.end(); ++dst) {
        file << "w" << (*dst)->getKey() << "\t" << (*dst)->getFactor() << "\t" << (*dst)->possibleWays() << endl;
    }
    file.close();
}

long * InhomogenicGraph::getSourceDegrees(int segments)
{
    long *data = new long[segments]{0};
    long segmentSize = (long)(sourceVertexes.size() / segments);
    
    for (std::vector<Vertex *>::iterator src = sourceVertexes.begin(); src != sourceVertexes.end(); ++src) {
        long degree = 0;
        cout << (*src)->possibleWays() << endl;
        for (long i = 0; i < (*src)->possibleWays(); i++) {
            if ((*src)->connectionAt(i)->getType() == VertexTypeSource) {
                degree++;
            }
        }
        data[MIN((long)(degree / segmentSize), segments - 1)]++;
    }
    return data;
}

void InhomogenicGraph::sourceDegreesHistogram(std::string oFileName, int segments)
{
    cout << sizeof(getSourceDegrees(segments)) << endl;
    
    stringstream outputFile;
    outputFile << oFileName << ".txt";
    ofstream file(outputFile.str());
    
    long *data = getSourceDegrees(segments);
    
    for (long i = 0; i < segments; i++) {
        file << data[i] << endl;
    }
    file.close();

    stringstream rubyExecutable;
    rubyExecutable << "ruby histogram.rb draw " << outputFile.str() << " " << oFileName;
    const char *exec = rubyExecutable.str().c_str();
    system(exec);
}
