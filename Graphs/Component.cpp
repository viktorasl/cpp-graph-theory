//
//  Component.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/04/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Component.h"
#include <iostream>
#include <random>
#include "Histogram.h"

#define MIN(a,b) ((a) < (b) ? a : b)

using namespace std;

void Component::visitAndReturn(long segmentSize)
{
    long segments = ceil(vertexes.size() / segmentSize);
    long totaldegrees = 0;
    long stepsCount = 0;
    long *data = new long[segments]{0};
    Vertex *start = vertexes[0];
    Vertex *current = start;
    do {
        stepsCount++;
        totaldegrees += current->possibleWays();
        data[MIN((long)(current->possibleWays() / segmentSize), segments - 1)]++;
        long idx = arc4random() % current->possibleWays();
        current = current->connectionAt(idx);
    } while (current != start);
    long degreeAverage = totaldegrees / stepsCount;
    
    Histogram::generate(segments, data, "visiting-to-home");
    cout << "average degrees count is " << degreeAverage << endl;
}
