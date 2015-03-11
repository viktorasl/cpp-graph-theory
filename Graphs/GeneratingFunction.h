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

#ifdef __UNIT_TEST__
class TestGeneratingFunction;
#endif

class GeneratingFunction
{
private:
    float beta;
    long division;
    double multiplication;
public:
    GeneratingFunction(float beta, long m, long n, int precision);
private:
    long generateWithT(double t);
public:
    long generate();
    
#ifdef __UNIT_TEST__
    friend class TestGeneratingFunction;
#endif
};

#endif /* defined(__Graphs__GeneratingFunction__) */
