//
//  Graph.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Graph.h"
#include <vector>
#include <iostream>
#include <random>
#include "Random.h"
#include "Vertex.h"
#include "GeneratingFunction.h"
#include <fstream>
#include <sstream>

#define MIN(a,b) ((a) < (b) ? a : b)

using namespace std;

Graph::Graph(long n, long m, GeneratingFunction *function)
{
#ifdef DEBUG
    cout << n << " source vertexes, " << m << " destination vertexes." << endl;
#endif
    cout << "Generating source & destination vertexes..." << endl;
    for (long i = 0; i < n; i++) {
        sourceVertexes.push_back(new Vertex(VertexTypeSource, i, 0));
    }
    for (long i = 0; i < m; i++) {
        destinationVertexes.push_back(new Vertex(VertexTypeDestination, i, 0));
    }
    
    this->function = function;
    connectSourceAndDestinationVertexes();
    connectSourcesToEachOther();
}

Graph::Graph()
{
}

Graph::~Graph()
{
    for (std::vector<Vertex *>::iterator it = sourceVertexes.begin(); it != sourceVertexes.end(); ++it) {
        delete *it;
    }
    for (std::vector<Vertex *>::iterator it = destinationVertexes.begin(); it != destinationVertexes.end(); ++it) {
        delete *it;
    }
}

void Graph::connectSourceAndDestinationVertexes()
{
    cout << "Connecting source and destination vertexes..." << endl;
    int moreThanDestinations = 0;
    
    for(std::vector<Vertex *>::iterator it = sourceVertexes.begin(); it != sourceVertexes.end(); ++it) {
        cout << "Connecting vertex " << distance(sourceVertexes.begin(), it) << endl;
        Vertex *sourceVertex = *it;
        
        long edgesCount = 0;
        while ((edgesCount = function->generate()) > destinationVertexes.size()) {
            moreThanDestinations++;
        }
        
#ifdef DEBUG
        cout << distance(sourceVertexes.begin(), it) << ":";
#endif
#ifdef DEBUG
        cout << "[";
#endif
        Random rand(0, destinationVertexes.size());
        
        for (long i = 0; i < edgesCount; i++) {
            long index = rand.nextUnique();
#ifdef DEBUG
            cout << ((i > 0)? "," : "") << index;
#endif
            
            Vertex *destinationVertex = destinationVertexes.at(index);
            sourceVertex->connectToVertex(destinationVertex);
            destinationVertex->connectToVertex(sourceVertex);
        }
#ifdef DEBUG
        cout << "]" << endl;
#endif
    }
    
    cout << moreThanDestinations << " times number was generated which was bigger than destinations count" << endl;
}

void Graph::connectSourcesToEachOther()
{
    const long count = sourceVertexes.size();
    bool** taken = new bool*[count]{NULL};
    for (long i = 0; i < count; i++) {
        taken[i] = new bool[count]{false};
    }
    
    for (vector<Vertex *>::iterator it = destinationVertexes.begin(); it != destinationVertexes.end(); ++it) {
        (*it)->connectConnectionsToEachOther(taken);
    }
}

bool Graph::isConnected()
{
    // Clearing visitation
    for (vector<Vertex *>::iterator it = sourceVertexes.begin(); it != sourceVertexes.end(); ++it) {
        (*it)->setVisited(false);
    }
    for (vector<Vertex *>::iterator it = destinationVertexes.begin(); it != destinationVertexes.end(); ++it) {
        (*it)->setVisited(false);
    }
    
    Vertex *current = sourceVertexes[0];
    long connectedCount = 0;
    long totalCount = sourceVertexes.size() + destinationVertexes.size();
    recursivelyCheckConnection(current, connectedCount);
#ifdef DEBUG
    cout << connectedCount << " connected vertexes. " << totalCount << " total vertexes\n";
#endif
    return connectedCount == totalCount;
}

void Graph::recursivelyCheckConnection(Vertex *current, long &visitedCount)
{
    if (! current->isVisited()) {
        current->setVisited(true);
        (visitedCount)++;
        
        for (long idx = 0; idx < current->possibleWays(); idx++) {
            recursivelyCheckConnection(current->connectionAt(idx), visitedCount);
        }
    }
}

long Graph::stepsCount(long sourceIndex, long destIndex)
{
    Vertex *end = destinationVertexes.at(destIndex);
    long steps = 0;
    
    Vertex *current = sourceVertexes.at(sourceIndex);
    while (current != end) {
        steps++;
        if (current->possibleWays() < 1) {
            return -1;
        }
        long wayIndex = arc4random() % current->possibleWays();
        current = current->connectionAt(wayIndex);
    }
    
    return steps;
}

void Graph::destinationsPickingHistogram(string oFileName)
{
    ofstream file(oFileName);
    for (std::vector<Vertex *>::iterator dst = destinationVertexes.begin(); dst != destinationVertexes.end(); ++dst) {
        file << "w" << (*dst)->getKey() << "\t" << (*dst)->getFactor() << "\t" << (*dst)->possibleWays() << endl;
    }
    file.close();
}

long * Graph::getSourceDegrees(int segments)
{
    long *data = new long[segments]{0};
    long segmentSize = (long)(sourceVertexes.size() / segments);
    
    for (std::vector<Vertex *>::iterator src = sourceVertexes.begin(); src != sourceVertexes.end(); ++src) {
        long degree = 0;
        for (long i = 0; i < (*src)->possibleWays(); i++) {
            if ((*src)->connectionAt(i)->getType() == VertexTypeSource) {
                degree++;
            }
        }
        data[MIN((long)(degree / segmentSize), segments - 1)]++;
    }
    return data;
}

void Graph::sourceDegreesHistogram(std::string oFileName, int segments)
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
