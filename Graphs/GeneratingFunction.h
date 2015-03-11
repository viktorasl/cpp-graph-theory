//
//  GeneratingFunction.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/03/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__GeneratingFunction__
#define __Graphs__GeneratingFunction__

#include <stdio.h>

class GeneratingFunction
{
private:
    float beta;
    long division;
    double multiplication;
public:
    GeneratingFunction(float beta, long m, long n, int precision);
    long generate();
};

#endif /* defined(__Graphs__GeneratingFunction__) */
