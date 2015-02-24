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

using namespace std;

Graph::Graph(int n, int m)
{
    this->sourceVertexes = new vector<Vertex *>();
    for (int i = 0; i < n; i++) {
        this->sourceVertexes->push_back(new Vertex());
    }
    
    this->destinationVertexes = new vector<Vertex *>();
    for (int i = 0; i < n; i++) {
        this->destinationVertexes->push_back(new Vertex());
    }
}

Graph::~Graph()
{
    //TODO: free vertexes
}