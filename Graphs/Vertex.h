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

enum VertexType {
    VertexTypeSource,
    VertexTypeDestination
};

class Vertex {
private:
    bool visited;
    long key;
    double factor;
    VertexType type;
    std::vector<Vertex *> connections;
public:
    Vertex(VertexType type, long key, double factor);
private:
    bool connectToVertexIfNotExist(Vertex *vertex);
public:
    void connectToVertex(Vertex *vertex);
    void connectConnectionsToEachOther(bool** taken);
    long getKey();
    double getFactor();
    bool isVisited();
    void setVisited(bool isVisited);
    VertexType getType();
    long possibleWays();
    Vertex *connectionAt(long index);
    void findChildComponents(long &count, bool visited[]);
    
#ifdef __UNIT_TEST__
    friend class TestGraph;
#endif
};

#endif /* defined(__Graphs__Vertex__) */
