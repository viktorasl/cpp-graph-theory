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
        
        int sCount = 2;
        int dCount = 2;
        Vertex *s[sCount];
        for (int i = 0; i < sCount; i++) {
            s[i] = new Vertex(VertexTypeSource, i);
            graph.sourceVertexes.push_back(s[i]);
        }
        Vertex *d[dCount];
        for (int i = 0; i < sCount; i++) {
            d[i] = new Vertex(VertexTypeDestination, i);
            graph.destinationVertexes.push_back(d[i]);
        }
        
        connectEachOther(s[0], d[0]);
        connectEachOther(s[0], d[1]);
        
        cout << __func__ << ":test1: " << ((graph.isConnected() == false)? "passed" : "failed") << endl;
        
        connectEachOther(s[1], d[0]);
        
        cout << __func__ << ":test2: " << ((graph.isConnected() == true)? "passed" : "failed") << endl;
    }
private:
    void connectEachOther(Vertex *v1, Vertex *v2)
    {
        v1->connectToVertex(v2);
        v2->connectToVertex(v1);
    }
};
