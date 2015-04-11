//
//  Component.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/04/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Component.h"
#include <iostream>
#include <random>

using namespace std;

void Component::visitAndReturn()
{
    Vertex *current = start;
    long stepsCount = 0;
    do {
        stepsCount++;
        long idx = arc4random() % current->possibleWays();
        current = current->connectionAt(idx);
    } while (current != start);
    cout << stepsCount << endl;
}