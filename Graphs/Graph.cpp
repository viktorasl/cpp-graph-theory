//
//  Graph.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Graph.h"
#include "Vertex.h"
#include <vector>
#include <iostream>
#include <random>

using namespace std;

Graph::Graph(long n, long m)
{
#ifdef DEBUG
    cout << n << " source vertexes, " << m << " destination vertexes." << endl;
#endif
    cout << "Generating source & destination vertexes..." << endl;
    sourceVertexes = new vector<Vertex *>();
    for (long i = 0; i < n; i++) {
        sourceVertexes->push_back(new Vertex(VertexTypeSource, i));
    }
    
    destinationVertexes = new vector<Vertex *>();
    for (long i = 0; i < m; i++) {
        destinationVertexes->push_back(new Vertex(VertexTypeDestination, i));
    }
    
    maxToDest = destinationVertexes->size();
    connectSourceAndDestinationVertexes();
}

Graph::~Graph()
{
    //TODO: free containers
    //TODO: free vertexes
}

vector<long> Graph::possibleDestinationIndexes()
{
    vector<long> possibleIndexes;
    for (long i = 0; i < destinationVertexes->size(); i++) {
        possibleIndexes.push_back(i);
    }
    return possibleIndexes;
}

void Graph::connectSourceAndDestinationVertexes()
{
    cout << "Connecting source and destination vertexes..." << endl;
    for(std::vector<Vertex *>::iterator it = sourceVertexes->begin(); it != sourceVertexes->end(); ++it) {
        cout << "Connecting vertex " << distance(sourceVertexes->begin(), it) << endl;
        Vertex *sourceVertex = *it;
        
        long edgesCount = arc4random() % maxToDest;
#ifdef DEBUG
        cout << distance(sourceVertexes->begin(), it) << ":";
#endif
        vector<long> possibleIndexes = possibleDestinationIndexes();
#ifdef DEBUG
        cout << "[";
#endif
        for (long i = 0; i < edgesCount; i++) {
            long accessor = arc4random() % possibleIndexes.size();
            long index = possibleIndexes.at(accessor);
            possibleIndexes.erase(possibleIndexes.begin() + accessor);
#ifdef DEBUG
            cout << ((i > 0)? "," : "") << index;
#endif
            
            Vertex *destinationVertex = destinationVertexes->at(index);
            sourceVertex->connectToVertex(destinationVertex);
            destinationVertex->connectToVertex(sourceVertex);
        }
#ifdef DEBUG
        cout << "]" << endl;
#endif
    }
}

long Graph::stepsCount(long sourceIndex, long destIndex)
{
    Vertex *end = destinationVertexes->at(destIndex);
    long steps = 0;
    
    Vertex *current = sourceVertexes->at(sourceIndex);
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
