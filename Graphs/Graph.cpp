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

bool highToLowComponents(Component *i, Component *j)
{
    return i->vertexes.size() < j->vertexes.size();
}

using namespace std;

Graph::Graph(long n, long m, GeneratingFunction *function)
{
    for (long i = 0; i < n; i++) {
        sourceVertexes.push_back(new Vertex(i, 0));
    }
    for (long i = 0; i < m; i++) {
        destinationVertexes.push_back(new Vertex(i, 0));
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
    bool *visited = new bool[sourceVertexes.size()]{false};
    Vertex *current = sourceVertexes[0];
    long count = 0;
//    current->findChildComponents(count, visited);
    
    return count == sourceVertexes.size();
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

vector<Component *> Graph::findingComponents()
{
    bool *visited = new bool[sourceVertexes.size()]{false};
    vector<Component *> components;
    long currentIdx = 0;
    
    while (1) {
        while ((currentIdx < sourceVertexes.size()) && (visited[currentIdx] == true)) {
            currentIdx++;
        }
        if (currentIdx >= sourceVertexes.size()) {
            break;
        }
        
        Component *component = new Component();
        Vertex *current = sourceVertexes[currentIdx];
        current->findChildComponents(component->vertexes, visited);
        
        components.push_back(component);
    }
    
    sort(components.begin(), components.end(), highToLowComponents);
    
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
            degree++;
        }
        data[MIN((long)(degree / segmentSize), segments - 1)]++;
    }
    return data;
}
