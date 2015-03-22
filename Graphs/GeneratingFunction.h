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
    double beta;
    long precisionFactor;
    double multiplication;
public:
    /**
     * @param beta      positive exponential constant
     * @param m         destinations count
     * @param n         sources count
     * @param precision generated random number from 0 to 1 precision
     */
    GeneratingFunction(double beta, long m, long n, int precision);
private:
    double randomizeT();
    double functionValueWithT(double t);
    long generateWithT(double t);
public:
    double randomizeFunctionValue();
    long generate();
    
#ifdef __UNIT_TEST__
    friend class TestGeneratingFunction;
#endif
};

#endif /* defined(__Graphs__GeneratingFunction__) */
