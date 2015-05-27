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
#include <sstream>
#include "Histogram.h"
#include "OutputInfo.h"

#define MIN(a,b) ((a) < (b) ? a : b)

using namespace std;

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
    
    Degrees *visitsToHome = new Degrees();
    Degrees *visitsToHomeUnique = new Degrees();
    Degrees *visitsAllVertexes = new Degrees();
    Degrees *visitsAllVertexesUnique = new Degrees();
    
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
    
    stringstream fileName;
    fileName << RESULTS_DIR << "/random-walk-info.txt";
    ofstream file(fileName.str());
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

Degrees * Component::uniqueWalkToHome(long &totalSteps)
{
    bool *visited = new bool[vertexes.size()]{false};
    
    Degrees *visitedDegrees = new Degrees();
    
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
            visitedDegrees->push_back(vertexDegree);
        }
        
        long idx = arc4random() % current->possibleWays();
        current = current->connectionAt(idx);
    } while (current != start);
    
    delete visited;
    
    return visitedDegrees;
}

void Component::averageUniqueWalkToHome(long segmentSize, long repeatCount)
{
    vector<Degrees *> *segmentedDegrees = new vector<Degrees *>();
    for (long i = 0; i < repeatCount; i++) {
        long totalSteps = 0;
        Degrees *visitsToHomeUnique = uniqueWalkToHome(totalSteps);
        Degrees *segmentised = Component::segmentiseByDegree(visitsToHomeUnique, maxSize, 20);
        
        segmentedDegrees->push_back(segmentised);
        if (i == 0) {
            Histogram::generate(segmentised, "first-random-walk-to-home");
            stringstream fileName;
            fileName << RESULTS_DIR << "/average-to-home-info.txt";
            ofstream file(fileName.str());
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
    Degrees *data = new Degrees();
    for (long idx = 0; idx < segmentsCount; idx++) {
        data->push_back(0);
    }
    long segmentSize = (long)(maxDegree / segmentsCount);
    for (Degrees::iterator dgr = degrees->begin(); dgr != degrees->end(); ++dgr) {
        (*data)[MIN((long)(*dgr / segmentSize), segmentsCount - 1)]++;
    }
    return data;
}

Degrees* Component::segmentiseByStepCount(Degrees *degrees, long stepsSegment, ofstream &output)
{
    Degrees *segments = new Degrees();
    long stepsCount = 0;
    long totalDegree = 0;
    long segmentDegree = 0;
    
    for (Degrees::iterator it = degrees->begin(); it != degrees->end(); ++it) {
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
