//
//  TestGeneratingFunction.cpp
//  Graphs
//
//  Created by Viktoras Laukevičius on 11/03/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#define __UNIT_TEST__ 1

#include <stdio.h>
#include <iostream>
#include "GeneratingFunction.h"

using namespace std;

class TestGeneratingFunction
{
public:
    TestGeneratingFunction() {
        GeneratingFunction gf(2, 16, 4, 4);
        
        cout << "Test1: " << ((gf.generateWithT(0.75) == 4)? "passed" : "failed") << endl;
        cout << "Test2: " << ((gf.generateWithT(0.4650) == 2)? "passed" : "failed") << endl;
        cout << "Test3: " << ((gf.generateWithT(0.9950) == 28)? "passed" : "failed") << endl;
        
        GeneratingFunction gg(2, 100, 100, 4);
        
        cout << "Test4: " << ((gg.generateWithT(3./4.) == 2)? "passed" : "failed") << endl;
    }
};