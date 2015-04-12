//
//  Histogram.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/04/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__Histogram__
#define __Graphs__Histogram__

#include <stdio.h>
#include <string>
#include <vector>

class Histogram
{
public:
    static void generate(std::vector<long> *segments, std::string fileName);
};

#endif /* defined(__Graphs__Histogram__) */
