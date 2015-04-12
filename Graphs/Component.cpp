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
    long totaldegrees = 0;
    long stepsCount = 0;
    vector<long> *data = new vector<long>();
    
    Vertex *start = vertexes[0];
    Vertex *current = start;
    
    long segmentDegree = 0;
    do {
        stepsCount++;
        totaldegrees += current->possibleWays();
        segmentDegree += current->possibleWays();
        
        if (stepsCount % segmentSize == 0) {
            data->push_back(segmentDegree / segmentSize);
            segmentDegree = 0;
        }
        
        long idx = arc4random() % current->possibleWays();
        current = current->connectionAt(idx);
    } while (current != start);
    
    if (stepsCount % segmentSize != 0) {
        data->push_back(segmentDegree / (stepsCount % segmentSize));
    }
    
    long degreeAverage = totaldegrees / stepsCount;
    
    Histogram::generate(data, "visiting-to-home");
    cout << "average degrees count is " << degreeAverage << endl;
}
