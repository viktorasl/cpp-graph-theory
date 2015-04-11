//
//  Vertex.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Vertex.h"

using namespace std;

Vertex::Vertex(VertexType type, long key, double factor)
{
    this->type = type;
    this->key = key;
    this->factor = factor;
}

void Vertex::connectToVertex(Vertex *vertex)
{
    connections.push_back(vertex);
}

bool Vertex::connectToVertexIfNotExist(Vertex *vertex)
{
    if (*find(connections.begin(), connections.end(), vertex)) {
        return false;
    } else {
        connections.push_back(vertex);
        return true;
    }
}

void Vertex::connectConnectionsToEachOther(bool** taken)
{
    for (vector<Vertex *>::iterator it = connections.begin(); it != connections.end(); ++it) {
        for (vector<Vertex *>::iterator vertex = next(it); vertex != connections.end(); ++vertex) {
            if (*it != *vertex) {
                bool alreadyInRecord = taken[(*it)->getKey()][(*vertex)->getKey()];
                if (! alreadyInRecord) {
                    (*it)->connectToVertex(*vertex);
                    (*vertex)->connectToVertex(*it);
                    taken[(*it)->getKey()][(*vertex)->getKey()] = true;
                    taken[(*vertex)->getKey()][(*it)->getKey()] = true;
                }
            }
        }
    }
}

long Vertex::getKey()
{
    return key;
}

double Vertex::getFactor()
{
    return factor;
}

bool Vertex::isVisited()
{
    return visited;
}

void Vertex::setVisited(bool isVisited)
{
    visited = isVisited;
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

void Vertex::findChildComponents(long &count, bool visited[])
{
    count++;
    visited[getKey()] = true;
    for (vector<Vertex *>::iterator it = connections.begin(); it != connections.end(); ++it) {
        if ((*it)->type == VertexTypeSource && visited[(*it)->getKey()] == false) {
            (*it)->findChildComponents(count, visited);
        }
    }
}
