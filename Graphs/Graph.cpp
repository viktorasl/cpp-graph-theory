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
    int moreThanDestinations = 0;
    
    for(std::vector<Vertex *>::iterator it = sourceVertexes.begin(); it != sourceVertexes.end(); ++it) {
        Vertex *sourceVertex = *it;
        
        long edgesCount = 0;
        while ((edgesCount = function->generate()) > destinationVertexes.size()) {
            moreThanDestinations++;
        }
        
        Random rand(0, destinationVertexes.size());
        
        for (long i = 0; i < edgesCount; i++) {
            long index = rand.nextUnique();
            
            Vertex *destinationVertex = destinationVertexes.at(index);
            sourceVertex->connectToVertex(destinationVertex);
            destinationVertex->connectToVertex(sourceVertex);
        }
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

vector<Component> Graph::findingComponents()
{
    bool *visited = new bool[sourceVertexes.size()];
    long count = 0;
    vector<Component> components;
    
    vector<Vertex *>::iterator current = sourceVertexes.begin();
    (*current)->findChildComponents(count, visited);
    
    components.push_back(Component {
        .start = *current,
        .size = count
    });
    
    delete visited;
    return components;
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
