//
//  TestGraph.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 21/03/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include "Vertex.h"

using namespace std;

class TestGraph
{
public:
    TestGraph()
    {
        Graph graph;
        
        int sCount = 4;
        int dCount = 4;
        Vertex *s[sCount];
        for (int i = 0; i < sCount; i++) {
            s[i] = new Vertex(VertexTypeSource, i, 0);
            graph.sourceVertexes.push_back(s[i]);
        }
        Vertex *d[dCount];
        for (int i = 0; i < sCount; i++) {
            d[i] = new Vertex(VertexTypeDestination, i, 0);
            graph.destinationVertexes.push_back(d[i]);
        }
        
        connectEachOther(s[0], d[0]);
        connectEachOther(s[0], d[1]);
        connectEachOther(s[1], d[1]);
        connectEachOther(s[1], d[2]);
        connectEachOther(s[2], d[3]);
        connectEachOther(s[3], d[3]);
        
        tout << ":test1: " << ((graph.isConnected() == false)? "passed" : "failed") << endl;
        vector<Component> components = graph.findingComponents();
        tout << ":test2: " << ((components.size() == 4) ? "passed" : "failed") << endl;
        
        connectEachOther(s[2], d[1]);
        
        graph.connectSourcesToEachOther();
        
        components = graph.findingComponents();
        tout << ":test3: " << ((graph.isConnected() == true)? "passed" : "failed") << endl;
        tout << ":test4: " << ((components.size() == 1) ? "passed" : "failed") << endl;
        
        tout << ":test5: " << (((s[0]->connections.size() == 4) && isConnected(s[0], new Vertex*[2]{s[1], s[2]}, 2))? "passed" : "failed") << endl;
        tout << ":test6: " << (((s[1]->connections.size() == 4) && isConnected(s[1], new Vertex*[2]{s[0], s[2]}, 2))? "passed" : "failed") << endl;
        tout << ":test7: " << (((s[2]->connections.size() == 5) && isConnected(s[2], new Vertex*[3]{s[0], s[1], s[3]}, 3))? "passed" : "failed") << endl;
        tout << ":test8: " << (((s[3]->connections.size() == 2) && isConnected(s[3], new Vertex*[1]{s[2]}, 1))? "passed" : "failed") << endl;
        
        long *sd = graph.getSourceDegrees(4);
        tout << ":test9: " << (((sd[0] == 0) && (sd[1] == 1) && (sd[2] == 2) && (sd[3] == 1))? "passed" : "failed") << endl;
    }
private:
    void connectEachOther(Vertex *v1, Vertex *v2)
    {
        v1->connectToVertex(v2);
        v2->connectToVertex(v1);
    }
    bool isConnected(Vertex *main, Vertex *vertexes[], long size)
    {
        for (int i = 0; i < size; i++) {
            if (find(main->connections.begin(), main->connections.end(), vertexes[i]) == main->connections.end()) {
                return false;
            }
        }
        return true;
    }
};
