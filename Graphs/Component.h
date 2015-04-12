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

typedef struct {
    std::vector<Vertex *>vertexes;
    
    void randomWalk(long segmentSize);
    static std::vector<long>* segmentise(std::vector<long> *degrees, long segmentSize);
} Component;

#endif /* defined(__Graphs__Component__) */
