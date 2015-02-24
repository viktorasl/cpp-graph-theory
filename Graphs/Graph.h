//
//  Graph.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__Graph__
#define __Graphs__Graph__

#include <stdio.h>
#include <vector>

class Vertex;

class Graph
{
private:
    std::vector<Vertex *>* sourceVertexes;
    std::vector<Vertex *>* destinationVertexes;
public:
    Graph(int n, int m);
    ~Graph();
};

#endif /* defined(__Graphs__Graph__) */
