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

typedef unsigned long long u64b;
typedef __uint128_t u128b;

class bigint {
    u64b exlolo;
    u64b exlomid;
    u64b exlohi;
    u64b lolo;
    u64b lomid;
    u64b lohi;
    u64b midlo;
    u64b midmid;
    u64b midhi;
    u64b hilo;
    u64b himid;
    u64b hihi;
    u64b exhilo;
    u64b exhimid;
    u128b exhihi;
    
public:
    bigint (int (&n)[15]);
    bigint operator+(const bigint& obj);
    void operator=(const bigint& obj);
    friend std::ostream& operator<<(std::ostream& stream, const bigint& obj);
};

#endif /* defined(__fibonacci__bigint__) */
