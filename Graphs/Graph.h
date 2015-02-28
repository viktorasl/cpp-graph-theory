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
    std::vector<Vertex *> sourceVertexes;
    std::vector<Vertex *> destinationVertexes;
    
    /**
     *  Maximum edges from one source vertex to destination vertexes
     */
    long maxToDest = 0;
public:
    Graph(long n, long m);
    ~Graph();
private:
    void connectSourceAndDestinationVertexes();
public:
    /**
     * Steps count from source vertex to destination vertex
     * 
     * @param sourceIndex source vertex index
     * @param destIndex destination vertex index
     */
    long stepsCount(long sourceIndex, long destIndex);
};

#endif /* defined(__Graphs__Graph__) */
