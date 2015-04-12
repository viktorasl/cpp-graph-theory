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
    } while (!gotToHome || (uniqueVisitCount < vertexes.size()));
    
    ofstream file("random-walk-info.txt");
    file << "Reaching home:" << endl;
    Histogram::generate(Component::segmentise(visitsToHome, segmentSize, file), "random-walk-to-home");
    file << "Reaching home unique:" << endl;
    Histogram::generate(Component::segmentise(visitsToHomeUnique, segmentSize, file), "random-walk-to-home-unique");
    file << "Visiting all vertexes:" << endl;
    Histogram::generate(Component::segmentise(visitsAllVertexes, segmentSize, file), "random-walk-all");
    file << "Visiting all vertexes passing unique:" << endl;
    Histogram::generate(Component::segmentise(visitsAllVertexesUnique, segmentSize, file), "random-walk-all-unique");
    file.close();
    
    delete visitsAllVertexesUnique;
    delete visitsAllVertexes;
    delete visitsToHomeUnique;
    delete visitsToHome;
    delete visited;
}

vector<long>* Component::segmentise(vector<long> *degrees, long segmentSize, ofstream &output)
{
    vector<long> *segments = new vector<long>();
    long stepsCount = 0;
    long totalDegree = 0;
    long segmentDegree = 0;
    
    for (vector<long>::iterator it = degrees->begin(); it != degrees->end(); ++it) {
        stepsCount++;
        totalDegree += (*it);
        segmentDegree += (*it);
        if (stepsCount % segmentSize == 0) {
            segments->push_back(segmentDegree / segmentSize);
            segmentDegree = 0;
        }
    }
    
    if (stepsCount % segmentSize != 0) {
        segments->push_back(segmentDegree / segmentSize);
    }
    
    output << "\tVertexes count: " << degrees->size() << endl
           << "\tVertexes degrees average: " << (totalDegree / stepsCount) << endl;
    
    return segments;
}
