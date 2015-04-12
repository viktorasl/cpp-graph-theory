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
    
    vector<long> *uniqueData = new vector<long>();
    bool *visited = new bool[vertexes.size()]{false};
    long uniqueSteps = 0;
    long uniqueSegment = 0;
    
    Vertex *start = vertexes[0];
    Vertex *current = start;
    
    long segmentDegree = 0;
    do {
        stepsCount++;
        totaldegrees += current->possibleWays();
        segmentDegree += current->possibleWays();
        
        vector<Vertex *>::iterator it = find(vertexes.begin(), vertexes.end(), current);
        long uIdx = distance(vertexes.begin(), it);
        if (visited[uIdx] == false) {
            visited[uIdx] = true;
            
            uniqueSteps++;
            uniqueSegment += current->possibleWays();
            if (uniqueSteps % segmentSize == 0) {
                uniqueData->push_back(uniqueSegment / segmentSize);
                uniqueSegment = 0;
            }
        }
        
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
    
    Histogram::generate(uniqueData, "visiting-to-home-unique");
}
