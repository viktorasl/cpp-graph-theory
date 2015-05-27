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
#include <map>

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
    
    Component *component = components[0];
    
    map<int, Vertex*> data;
    data[10] = graph.vertexHavingDegree(0, 20);
    data[50] = graph.vertexHavingDegree(35, 65);
    data[100] = graph.vertexHavingDegree(75, 125);
    data[200] = graph.vertexHavingDegree(150, 250);
    data[500] = graph.vertexHavingDegree(400, 600);
    
    for (map<int, Vertex*>::iterator it = data.begin(); it != data.end(); ++it) {
        // Making directory
        stringstream folderName;
        folderName << "~" << it->first;
        struct stat st = {0};
        if (stat(resultsPath(folderName.str()).c_str(), &st) == -1) {
            mkdir(resultsPath(folderName.str()).c_str(), 0700);
        }
        
        // Putting data to directory
        for (int iteration = 0; iteration < 10; iteration++) {
            stringstream filename;
            filename << folderName.str();
            Degrees *randomWalkDegrees = component->randomWalkFromVertex(it->second);
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
