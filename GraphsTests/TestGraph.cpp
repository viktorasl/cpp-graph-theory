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
        
        Vertex *s0 = new Vertex(VertexTypeSource, 1);
        Vertex *s1 = new Vertex(VertexTypeSource, 2);
        Vertex *d0 = new Vertex(VertexTypeDestination, 1);
        Vertex *d1 = new Vertex(VertexTypeDestination, 2);
        
        graph.sourceVertexes.push_back(s0);
        graph.sourceVertexes.push_back(s1);
        graph.destinationVertexes.push_back(d0);
        graph.destinationVertexes.push_back(d1);
        
        s0->connectToVertex(d0); d0->connectToVertex(s0);
        s0->connectToVertex(d1); d1->connectToVertex(s0);
        
        cout << __func__ << ":test1: " << ((graph.isConnected() == false)? "passed" : "failed") << endl;
        
        s1->connectToVertex(d0); d0->connectToVertex(s1);
        
        cout << __func__ << ":test2: " << ((graph.isConnected() == true)? "passed" : "failed") << endl;
    }
};
