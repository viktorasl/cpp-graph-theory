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
    return i->getVertexes().size() > j->getVertexes().size();
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
        
        
        Vertex *current = sourceVertexes[currentIdx];
        vector<Vertex *> vertexes;
        current->findChildComponents(vertexes, visited);
        
        components.push_back(new Component(vertexes, sourceVertexes.size()));
    }
    
    sort(components.begin(), components.end(), highToLowComponents);
    
    delete visited;
    return components;
}

Degrees* Graph::getSourceDegrees(int segmentsCount)
{
    Degrees *data = new Degrees();
    for (long idx = 0; idx < segmentsCount; idx++) {
        data->push_back(0);
    }
    long segmentSize = (long)(sourceVertexes.size() / segmentsCount);
    
    for (std::vector<Vertex *>::iterator src = sourceVertexes.begin(); src != sourceVertexes.end(); ++src) {
        long degree = 0;
        for (long i = 0; i < (*src)->possibleWays(); i++) {
            degree++;
        }
        (*data)[MIN((long)(degree / segmentSize), segmentsCount - 1)]++;
    }
    return data;
}

Vertex* Graph::vertexHavingDegree(long degreeMin, long degreeMax)
{
    long perfection = (degreeMax + degreeMin) / 2;
    long precision = LONG_MAX;
    Vertex *candidate = NULL;
    for (vector<Vertex *>::iterator src = sourceVertexes.begin(); src != sourceVertexes.end(); ++src) {
        long degree = (*src)->possibleWays();
        if (degree >= degreeMin && degree <= degreeMax && abs(perfection - degree) < precision) {
            precision = abs(perfection - degree);
            candidate = *src;
        }
    }
    return candidate;
}
