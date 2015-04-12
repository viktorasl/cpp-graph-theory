//
//  Component.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/04/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__Component__
#define __Graphs__Component__

#import "Vertex.h"
#import <vector>

typedef struct {
    std::vector<Vertex *>vertexes;
    
    long * visitAndReturn(long segmentSize, long& segments, long& degreeAverage);
} Component;

#endif /* defined(__Graphs__Component__) */
