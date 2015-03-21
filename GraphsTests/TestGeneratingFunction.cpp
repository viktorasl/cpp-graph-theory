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
        
        cout << __func__ << ":test1: " << ((gf.generateWithT(0.75) == 4)? "passed" : "failed") << endl;
        cout << __func__ << ":test2: " << ((gf.generateWithT(0.4650) == 2)? "passed" : "failed") << endl;
        cout << __func__ << ":test3: " << ((gf.generateWithT(0.9950) == 28)? "passed" : "failed") << endl;
        
        GeneratingFunction gg(2, 100, 100, 4);
        
        cout << __func__ << ":test4: " << ((gg.generateWithT(3./4.) == 2)? "passed" : "failed") << endl;
    }
};
