//
//  Random.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 28/02/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__Random__
#define __Graphs__Random__

#include <stdio.h>
#include <vector>

class Random {
    bool *taken;
    long from;
    long length;
public:
    Random(long from, long length);
    ~Random();
    long nextUnique();
};

#endif /* defined(__Graphs__Random__) */
