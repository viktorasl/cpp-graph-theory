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

using namespace std;

GeneratingFunction::GeneratingFunction(double beta, long m, long n, int precision)
{
    this->beta = beta;
    this->precisionFactor = pow(10, precision);
    this->multiplication = sqrt((double)(m / n));
}

double GeneratingFunction::randomizeT()
{
    double t = arc4random() % precisionFactor / (double)precisionFactor; // getting u
    t = 1 - t * pow(2, -beta);
    return t;
}

double GeneratingFunction::functionValueWithT(double t)
{
    return 1 / pow(1 - t, 1 / beta);
}

double GeneratingFunction::randomizeFunctionValue()
{
    return functionValueWithT(randomizeT());
}

long GeneratingFunction::generateWithT(double t)
{
    return floor(functionValueWithT(t) * multiplication);
}

long GeneratingFunction::generate()
{
    return generateWithT(randomizeT());
}
