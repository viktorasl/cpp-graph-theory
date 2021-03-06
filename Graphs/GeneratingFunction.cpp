//
//  GeneratingFunction.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/03/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include "GeneratingFunction.h"
#include <cmath>
#include <random>
#include <iostream>

#define ARC4RANDOM_MAX      0x100000000

using namespace std;

GeneratingFunction::GeneratingFunction(double beta, long m, long n)
{
    this->beta = beta;
    this->multiplication = sqrt((double)m / (double)n);
}

double GeneratingFunction::randomizeU()
{
    return (double)arc4random() / ARC4RANDOM_MAX;
}

double GeneratingFunction::functionValueWithU(double u)
{
    return 2 * pow(u, -1 / beta);
}

double GeneratingFunction::randomizeFunctionValue()
{
    double u = randomizeU();
    if (u == 0) {
        u = randomizeU();
    }
    return functionValueWithU(u);
}

long GeneratingFunction::generateWithU(double u)
{
    return floor(functionValueWithU(u) * multiplication);
}

long GeneratingFunction::generate()
{
    double u = randomizeU();
    if (u == 0) {
        u = randomizeU();
    }
    return generateWithU(u);
}
