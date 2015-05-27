//
//  OutputHelper.h
//  Graphs
//
//  Created by Viktoras Laukevičius on 28/05/15.
//  Copyright (c) 2015 Viktoras Laukevicius. All rights reserved.
//

#ifndef __Graphs__OutputHelper__
#define __Graphs__OutputHelper__

#include <stdio.h>
#include <string>

extern std::string const resultsDir;
extern std::string resultsPath(std::string file);
extern std::string resultsPath(std::string file, std::string ext);

#endif /* defined(__Graphs__OutputHelper__) */
