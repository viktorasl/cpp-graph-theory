//
//  Component.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/04/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__Component__
#define __Graphs__Component__

#include "Vertex.h"
#include <vector>
#include <fstream>

class Component {
private:
    std::vector<Vertex *>vertexes;
    long maxSize;
public:
    Component(std::vector<Vertex *>vertexes, long maxSize);
    
    void randomWalk(long segmentSize);
    void averageUniqueWalkToHome(long segmentSize);
    std::vector<Vertex *> getVertexes();
    static std::vector<long>* segmentiseByDegree(std::vector<long> *degrees, long maxDegree, long segmentsCount, std::ofstream &output);
    static std::vector<long>* segmentiseByStepCount(std::vector<long> *degrees, long stepsSegment, std::ofstream &output);
};

#endif /* defined(__Graphs__Component__) */
