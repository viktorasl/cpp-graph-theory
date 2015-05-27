//
//  Vertex.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__Vertex__
#define __Graphs__Vertex__

#include <stdio.h>
#include <vector>

typedef std::vector<long> Degrees;

class Vertex {
private:
    long key;
    double factor;
    std::vector<Vertex *> connections;
public:
    Vertex(long key, double factor);
private:
    bool connectToVertexIfNotExist(Vertex *vertex);
public:
    void connectToVertex(Vertex *vertex);
    void connectConnectionsToEachOther(bool** taken);
    long getKey();
    double getFactor();
    long possibleWays();
    Vertex *connectionAt(long index);
    void findChildComponents(std::vector<Vertex *> &vertexes, bool visited[]);
    
#ifdef __UNIT_TEST__
    friend class TestGraph;
#endif
};

#endif /* defined(__Graphs__Vertex__) */
