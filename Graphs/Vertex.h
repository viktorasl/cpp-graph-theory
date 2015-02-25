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

class Vertex {
private:
    std::vector<Vertex *> connections;
public:
    void connectToVertex(Vertex *vertex);
};

#endif /* defined(__Graphs__Vertex__) */
