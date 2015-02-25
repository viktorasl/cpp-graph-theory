//
//  Vertex.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__Vertex__
#define __Graphs__Vertex__

#include <stdio.h>
#include <vector>

enum VertexType {
    VertexTypeSource,
    VertexTypeDestination
};

class Vertex {
private:
    long key;
    VertexType type;
    std::vector<Vertex *> connections;
public:
    Vertex(VertexType type, long key);
    void connectToVertex(Vertex *vertex);
    long getKey();
    VertexType getType();
};

#endif /* defined(__Graphs__Vertex__) */
