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

GeneratingFunction::GeneratingFunction(float beta, long m, long n, int precision)
{
    this->beta = beta;
    this->division = pow(10, precision);
    this->multiplication = sqrt((float)(m / n));
}

long GeneratingFunction::generateWithT(double t)
{
    return floor(pow(1 - t, -1/beta) * multiplication);
}

long GeneratingFunction::generate()
{
    double t = arc4random() % (division - 1) / (double)division;
    return generateWithT(t);
}
