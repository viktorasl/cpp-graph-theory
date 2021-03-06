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
#include "Component.h"

class Vertex;
class GeneratingFunction;

class Graph
{
private:
    GeneratingFunction *function;
protected:
    std::vector<Vertex *> sourceVertexes;
    std::vector<Vertex *> destinationVertexes;
    Graph();
public:
    Graph(long n, long m, GeneratingFunction *function);
    ~Graph();
private:
    long generateEdgesCount();
protected:
    void connectSourceAndDestinationVertexes();
    void connectSourcesToEachOther();
public:
    bool isConnected();
    /**
     * Steps count from source vertex to destination vertex
     * 
     * @param sourceIndex source vertex index
     * @param destIndex destination vertex index
     */
    long stepsCount(long sourceIndex, long destIndex);
    std::vector<Component *> findingComponents();
    void destinationsPickingHistogram(std::string oFileName);
    std::vector<long>* getSourceDegrees(int segments);
    Vertex* vertexHavingDegree(long degreeMin, long degreeMax);
    
#ifdef __UNIT_TEST__
    friend class TestGraph;
#endif
};

#endif /* defined(__Graphs__Graph__) */
