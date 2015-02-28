//
//  Random.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 28/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "Random.h"
#include <random>

Random::Random(long from, long length)
{
    this->taken = new bool[length]{false};
    this->from = from;
    this->length = length;
}

Random::~Random()
{
    delete taken;
}

long Random::nextUnique()
{
    long idx = (arc4random() % length);
    while (taken[idx]) {
        idx = ++idx % length;
    }
    taken[idx] = true;
    return idx;
}