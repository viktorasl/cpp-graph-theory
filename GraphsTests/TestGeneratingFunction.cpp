//
//  TestGeneratingFunction.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/03/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "GeneratingFunction.h"
#include "Graph.h"
#include "Vertex.h"

using namespace std;

class TestGeneratingFunction
{
public:
    TestGeneratingFunction()
    {
        GeneratingFunction gf(2, 16, 4, 4);
        
        tout << ":test1: " << ((gf.generateWithU(1) == 4)? "passed" : "failed") << endl;
        tout << ":test2: " << ((gf.generateWithU(0.44) == 6)? "passed" : "failed") << endl;
        tout << ":test3: " << ((gf.generateWithU(0.0042) == 61)? "passed" : "failed") << endl;
        
        GeneratingFunction gg(2, 100, 100, 4);
        
        tout << ":test4: " << ((gg.generateWithU(3./4.) == 2)? "passed" : "failed") << endl;
        
        GeneratingFunction g3(1, 100, 100, 8);
        
        tout << ":test5: " << ((g3.generateWithU(0.0042) == 476)? "passed" : "failed") << endl;
    }
};
