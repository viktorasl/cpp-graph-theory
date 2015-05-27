//
//  main.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <sstream>
#include "Graph.h"
#include "GeneratingFunction.h"
#include "InhomogenicGraph.h"
#include "Histogram.h"
#include <dirent.h>
#include "OutputHelper.h"
#include <sys/stat.h>

using namespace std;

void removeResults()
{
    // These are data types defined in the "dirent" header
    struct dirent *next_file;
    DIR *theFolder;
    
    char filepath[256];
    
    theFolder = opendir(resultsDir.c_str());
    
    while ((next_file = readdir(theFolder)) != NULL)
    {
        // build the full path for each file in the folder
        sprintf(filepath, "%s/%s", resultsDir.c_str(), next_file->d_name);
        remove(filepath);
    }
}

int main(int argc, const char * argv[])
{
    long n = 1000;
    long m = 2000;
    int histogramSegments = 20;
    long relativeColumn = 300;
    double beta1 = 1.5;
    double beta2 = 3;
    GeneratingFunction *gfn = new GeneratingFunction(beta1, m, n);
    GeneratingFunction *gfm = new GeneratingFunction(beta2, m, n);
    
    InhomogenicGraph graph(n, m, gfn, gfm);
    
    removeResults();
    
    stringstream ss;
    ss << "Inhomogenic_b1=" << beta1 << "_b2=" << beta2;
    Degrees *degrees = graph.getSourceDegrees(histogramSegments);
    Histogram::generate(degrees, ss.str());
    ss << "_rlt";
    Histogram::generate(degrees, relativeColumn, ss.str());
    
    vector<Component *> components = graph.findingComponents();
    int idx = 1;
    for (vector<Component *>::iterator it = components.begin(); it != components.end(); ++it) {
        cout << "C" << idx++ << " size " << (*it)->getVertexes().size() << endl;
        if (idx == 2) {
            break;
        }
    }
    
    struct stat st = {0};
    
    int folders[] = {10, 50, 100, 200, 500};
    Vertex *vertexes[] = {
        graph.vertexHavingDegree(0, 20),
        graph.vertexHavingDegree(35, 65),
        graph.vertexHavingDegree(75, 125),
        graph.vertexHavingDegree(150, 250),
        graph.vertexHavingDegree(400, 600)
    };
    
    Component *component = components[0];
    
    for (int idx = 0; idx < 5; idx++) {
        stringstream folderName;
        folderName << "~" << folders[idx];
        if (stat(resultsPath(folderName.str()).c_str(), &st) == -1) {
            mkdir(resultsPath(folderName.str()).c_str(), 0700);
        }
        
        for (int iteration = 0; iteration < 10; iteration++) {
            stringstream filename;
            filename << folderName.str();
            Degrees *randomWalkDegrees = component->randomWalkFromVertex(vertexes[idx]);
            Degrees *randomWalkSegments = Component::segmentiseByDegree(randomWalkDegrees, n, histogramSegments);
            filename << "/" << iteration;
            Histogram::generate(randomWalkSegments, filename.str());
            filename << "_rlt";
            Histogram::generate(randomWalkSegments, relativeColumn, filename.str());
            
            delete randomWalkDegrees;
            delete randomWalkSegments;
        }
    }
    
    return 0;
}
