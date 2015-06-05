//
//  bigint.h
//  fibonacci
//
//  Created by Don Reilly on 5/28/15.
//  Copyright (c) 2015 Don Reilly. All rights reserved.
//

#ifndef __fibonacci__bigint__
#define __fibonacci__bigint__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdint.h>

typedef unsigned long long u64b;
typedef __uint128_t u128b;

class bigint {
    
    // Split into multiple 64-bit integers in a vector
    std::vector<u64b> normalize_long(std::vector<u64b> n);
    
public:
    std::vector<u64b> v;
    bigint (int n);
    bigint operator+(const bigint& obj);
    void operator=(const bigint& obj);
    friend std::ostream& operator<<(std::ostream& stream, const bigint& obj);
    friend void print_bigint(const bigint& n);
};

#endif /* defined(__fibonacci__bigint__) */
