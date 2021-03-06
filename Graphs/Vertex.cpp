//
//  Vertex.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 24/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Vertex.h"

using namespace std;

Vertex::Vertex(long key, double factor)
{
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

long Vertex::possibleWays()
{
    return connections.size();
}

Vertex* Vertex::connectionAt(long index)
{
    return connections.at(index);
}

void Vertex::findChildComponents(vector<Vertex *> &vertexes, bool visited[])
{
    vertexes.push_back(this);
    visited[getKey()] = true;
    for (vector<Vertex *>::iterator it = connections.begin(); it != connections.end(); ++it) {
        if (visited[(*it)->getKey()] == false) {
            (*it)->findChildComponents(vertexes, visited);
        }
    }
}
