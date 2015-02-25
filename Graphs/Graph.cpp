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
    cout << n << " source vertexed, " << m << " destination vertexes." << endl;
    sourceVertexes = new vector<Vertex *>();
    for (long i = 0; i < n; i++) {
        sourceVertexes->push_back(new Vertex());
        
    }
    
    destinationVertexes = new vector<Vertex *>();
    for (long i = 0; i < m; i++) {
        destinationVertexes->push_back(new Vertex());
    }
    
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
    for(std::vector<Vertex *>::iterator it = sourceVertexes->begin(); it != sourceVertexes->end(); ++it) {
        Vertex *vertex = *it;
        long edgesCount = arc4random() % destinationVertexes->size();
        cout << edgesCount << " edge(s) for vertex[" << distance(sourceVertexes->begin(), it) << "]" << endl;
        vector<long> possibleIndexes = possibleDestinationIndexes();
        cout << "[";
        for (long i = 0; i < edgesCount; i++) {
            long index = arc4random() % possibleIndexes.size();
            long value = possibleIndexes.at(index);
            possibleIndexes.erase(possibleIndexes.begin() + index);
            cout << ((i > 0)? "," : "") << value;
        }
        cout << "]" << endl;
    }
}
