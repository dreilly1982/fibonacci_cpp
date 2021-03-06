//
//  main.cpp
//  fibonacci
//
//  Created by Don Reilly on 5/28/15.
//  Copyright (c) 2015 Don Reilly. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "bigint.h"
#define LIMIT 50000

int main(int argc, const char * argv[]) {
    
    bigint a (0);
    bigint b (1);
    bigint c (0);
    int d = LIMIT;

    d -= 2;
    //std::cout << "0 " << a << std::endl;
    //std::cout << "1 " << b << std::endl;
    c = a + b;
    
    while(d) {
	    
        //std::cout << LIMIT - d << " " << c << std::endl;
        a = b;
        b = c;
        c = a + b;
        d--;
    }
	//std::cout << LIMIT - d << " " << c << std::endl;
	//for (int i = 0; i < c.v.size(); i++) std::cout << c.v[i] << std::endl;
    
    return 0;
}
