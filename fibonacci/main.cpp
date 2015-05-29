//
//  main.cpp
//  fibonacci
//
//  Created by Don Reilly on 5/28/15.
//  Copyright (c) 2015 Don Reilly. All rights reserved.
//

#include <iostream>
#include "bigint.h"

int main(int argc, const char * argv[]) {
    int x[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int y[15] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int z[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    bigint a (x);
    bigint b (y);
    bigint c (z);
    int d = 1466;
    
    d -= 2;
    std::cout << a << "\n";
    std::cout << b << "\n";
    c = a + b;
    
    while(d) {
        std::cout << c << "\n";
        a = b;
        b = c;
        c = a + b;
        d--;
    }
    
    return 0;
}
