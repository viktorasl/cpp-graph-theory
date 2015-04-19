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

typedef vector<long> Degrees;

Component::Component(std::vector<Vertex *>vertexes, long maxSize)
{
    this->vertexes = vertexes;
    this->maxSize = maxSize;
}

vector<Vertex *> Component::getVertexes()
{
    return vertexes;
}

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
        if (current->possibleWays() == 0) {
            break;
        }
        long idx = arc4random() % current->possibleWays();
        current = current->connectionAt(idx);
        
        if (current == start) {
            gotToHome = true;
        }
    } while (!gotToHome || (uniqueVisitCount < vertexes.size()));
    
    ofstream file("random-walk-info.txt");
    file << "Reaching home:" << endl;
    Histogram::generate(Component::segmentiseByStepCount(visitsToHome, segmentSize, file), "random-walk-to-home");
    file << "Reaching home unique:" << endl;
    Histogram::generate(Component::segmentiseByStepCount(visitsToHomeUnique, segmentSize, file), "random-walk-to-home-unique");
    file << "Visiting all vertexes:" << endl;
    Histogram::generate(Component::segmentiseByStepCount(visitsAllVertexes, segmentSize, file), "random-walk-all");
    file << "Visiting all vertexes passing unique:" << endl;
    Histogram::generate(Component::segmentiseByStepCount(visitsAllVertexesUnique, segmentSize, file), "random-walk-all-unique");
    file.close();
    
    delete visitsAllVertexesUnique;
    delete visitsAllVertexes;
    delete visitsToHomeUnique;
    delete visitsToHome;
    delete visited;
}

vector<long> * Component::uniqueWalkToHome(long &totalSteps)
{
    bool *visited = new bool[vertexes.size()]{false};
    
    vector<long> *visitsToHomeUnique = new vector<long>();
    
    Vertex *start = vertexes[0];
    Vertex *current = start;
    
    do {
        totalSteps++;
        long vertexDegree = current->possibleWays();
        
        // Recording unique visits
        vector<Vertex *>::iterator it = find(vertexes.begin(), vertexes.end(), current);
        long uIdx = distance(vertexes.begin(), it);
        if (visited[uIdx] == false) {
            visited[uIdx] = true;
            visitsToHomeUnique->push_back(vertexDegree);
        }
        
        long idx = arc4random() % current->possibleWays();
        current = current->connectionAt(idx);
    } while (current != start);
    
    delete visited;
    
    return visitsToHomeUnique;
}

void Component::averageUniqueWalkToHome(long segmentSize, long repeatCount)
{
    vector<Degrees *> *segmentedDegrees = new vector<Degrees *>();
    for (long i = 0; i < repeatCount; i++) {
        long totalSteps = 0;
        Degrees *visitsToHomeUnique = uniqueWalkToHome(totalSteps);
        Degrees *segmentised = Component::segmentiseByDegree(visitsToHomeUnique, maxSize, 100);
        
        segmentedDegrees->push_back(segmentised);
        if (i == 0) {
            Histogram::generate(segmentised, "first-random-walk-to-home");
            ofstream file("average-to-home-info.txt");
            file << "Reaching home:" << endl << "\tTotal steps count: " << totalSteps;
            file.close();
        }
    }
    
    Degrees *average = new Degrees();
    long idx = 0;
    bool calculatedAverage = false;
    while (!calculatedAverage) {
        long degreesSum = 0;
        for (vector<Degrees *>::iterator dgr = segmentedDegrees->begin(); dgr != segmentedDegrees->end(); ++dgr) {
            if (idx >= (*dgr)->size()) {
                calculatedAverage = true;
                break;
            }
            degreesSum += (**dgr)[idx];
        }
        if (calculatedAverage) {
            break;
        }
        average->push_back(degreesSum / segmentedDegrees->size());
        idx++;
    }
    
    Histogram::generate(average, "average-random-walk-to-home");
    
    delete segmentedDegrees;
}

Degrees* Component::segmentiseByDegree(Degrees *degrees, long maxDegree, long segmentsCount)
{
    vector<long> *data = new vector<long>();
    for (long idx = 0; idx < segmentsCount; idx++) {
        data->push_back(0);
    }
    long segmentSize = (long)(maxDegree / segmentsCount);
    for (std::vector<long>::iterator dgr = degrees->begin(); dgr != degrees->end(); ++dgr) {
        (*data)[MIN((long)(*dgr / segmentSize), segmentsCount - 1)]++;
    }
    return data;
}

vector<long>* Component::segmentiseByStepCount(vector<long> *degrees, long stepsSegment, ofstream &output)
{
    vector<long> *segments = new vector<long>();
    long stepsCount = 0;
    long totalDegree = 0;
    long segmentDegree = 0;
    
    for (vector<long>::iterator it = degrees->begin(); it != degrees->end(); ++it) {
        stepsCount++;
        totalDegree += (*it);
        segmentDegree += (*it);
        if (stepsCount % stepsSegment == 0) {
            segments->push_back(segmentDegree / stepsSegment);
            segmentDegree = 0;
        }
    }
    
    if (stepsCount % stepsSegment != 0) {
        segments->push_back(segmentDegree / stepsSegment);
    }
    
    output << "\tVertexes count: " << degrees->size() << endl
           << "\tVertexes degrees average: " << (totalDegree / stepsCount) << endl;
    
    return segments;
}
