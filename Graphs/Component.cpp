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

void Component::randomWalk(long segmentSize)
{
    bool *visited = new bool[vertexes.size()]{false};
    long uniqueVisitCount = 0;
    bool gotToHome = false;
    
    vector<long> *visitsToHome = new vector<long>();
    vector<long> *visitsToHomeUnique = new vector<long>();
    vector<long> *visitsAllVertexes = new vector<long>();
    vector<long> *visitsAllVertexesUnique = new vector<long>();
    
    Vertex *start = vertexes[0];
    Vertex *current = start;
    
    do {
        long vertexDegree = current->possibleWays();
        
        // Recording unique visits
        vector<Vertex *>::iterator it = find(vertexes.begin(), vertexes.end(), current);
        long uIdx = distance(vertexes.begin(), it);
        if (visited[uIdx] == false) {
            // Unique visit
            visited[uIdx] = true;
            uniqueVisitCount++;
            
            visitsAllVertexesUnique->push_back(vertexDegree);
            
            if (!gotToHome) {
                visitsToHomeUnique->push_back(vertexDegree);
            }
        }
        
        visitsAllVertexes->push_back(vertexDegree);
        if (!gotToHome) {
            visitsToHome->push_back(vertexDegree);
        }
        
        // Moving to the next vertex
        long idx = arc4random() % current->possibleWays();
        current = current->connectionAt(idx);
        
        if (current == start) {
            gotToHome = true;
        }
    } while (!gotToHome || (uniqueVisitCount < (vertexes.size() - 1)));
    
    Histogram::generate(Component::segmentise(visitsToHomeUnique, segmentSize), "random-walk-to-home-unique");
    
    delete visitsAllVertexesUnique;
    delete visitsAllVertexes;
    delete visitsToHomeUnique;
    delete visitsToHome;
    delete visited;
}

vector<long>* Component::segmentise(vector<long> *degrees, long segmentSize)
{
    vector<long> *segments = new vector<long>();
    long stepsCount = 0;
    long totalDegree = 0;
    
    for (vector<long>::iterator it = degrees->begin(); it != degrees->end(); ++it) {
        stepsCount++;
        totalDegree += (*it);
        if (stepsCount % segmentSize == 0) {
            segments->push_back(totalDegree / segmentSize);
            totalDegree = 0;
        }
    }
    
    if (stepsCount % segmentSize != 0) {
        segments->push_back(totalDegree / segmentSize);
    }
    
    return segments;
}
