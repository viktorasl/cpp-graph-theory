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
    void recursivelyCheckConnection(Vertex *current, long &visitedCount);
    long generateEdgesCount();
    long * getSourceDegrees(int segments);
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
    void destinationsPickingHistogram(std::string oFileName);
    void sourceDegreesHistogram(std::string oFileName, int segments);
    
#ifdef __UNIT_TEST__
    friend class TestGraph;
#endif
};

#endif /* defined(__Graphs__Graph__) */
