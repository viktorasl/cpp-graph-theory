//
//  InhomogenicGraph.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 21/03/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__InhomogenicGraph__
#define __Graphs__InhomogenicGraph__

#include <stdio.h>
#include "Graph.h"
#include <vector>

class GeneratingFunction;

class InhomogenicGraph : public Graph
{
private:
    GeneratingFunction * const gf;
public:
    InhomogenicGraph(long n, long m, GeneratingFunction* gfn, GeneratingFunction *gfm);
protected:
    void connectSourceAndDestinationVertexes();
public:
    void destinationsPickingHistogram(std::string oFileName);
    void sourceDegreesHistogram(std::string oFileName);
};

#endif /* defined(__Graphs__InhomogenicGraph__) */
