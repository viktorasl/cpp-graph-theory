//
//  Vertex.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Vertex.h"

void Vertex::connectToVertex(Vertex *vertex)
{
    connections.push_back(vertex);
}