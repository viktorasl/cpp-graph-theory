//
//  Vertex.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Vertex.h"

Vertex::Vertex(VertexType type, long key)
{
    this->type = type;
    this->key = key;
}

void Vertex::connectToVertex(Vertex *vertex)
{
    connections.push_back(vertex);
}

long Vertex::getKey()
{
    return key;
}

VertexType Vertex::getType()
{
    return type;
}

long Vertex::possibleWays()
{
    return connections.size();
}

Vertex* Vertex::connectionAt(long index)
{
    return connections.at(index);
}