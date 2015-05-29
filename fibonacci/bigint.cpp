//
//  bigint.cpp
//  fibonacci
//
//  Created by Don Reilly on 5/28/15.
//  Copyright (c) 2015 Don Reilly. All rights reserved.
//

#include "bigint.h"

bigint::bigint (int (&n)[15])
{
    exlolo = n[0];
    exlomid = n[1];
    exlohi = n[2];
    lolo = n[3];
    lomid = n[4];
    lohi = n[5];
    midlo = n[6];
    midmid = n[7];
    midhi = n[8];
    hilo = n[9];
    himid = n[10];
    hihi = n[11];
    exhilo = n[12];
    exhimid = n[13];
    exhihi = n[14];
}

void bigint::operator=(const bigint& obj) {
    (*this).exlolo = obj.exlolo;
    (*this).exlomid = obj.exlomid;
    (*this).exlohi = obj.exlohi;
    (*this).lolo = obj.lolo;
    (*this).lomid = obj.lomid;
    (*this).lohi = obj.lohi;
    (*this).midlo = obj.midlo;
    (*this).midmid = obj.midmid;
    (*this).midhi = obj.midhi;
    (*this).hilo = obj.hilo;
    (*this).himid = obj.himid;
    (*this).hihi = obj.hihi;
    (*this).exhilo = obj.exhilo;
    (*this).exhimid = obj.exhimid;
    (*this).exhihi = obj.exhihi;
    
    return;
}

bigint bigint::operator+(const bigint& obj2) {
    bigint result = *this;
    
    u128b exlolo = (u128b) result.exlolo + obj2.exlolo;
    u128b exlomid = (u128b) result.exlomid + obj2.exlomid + (exlolo >> 64);
    u128b exlohi = (u128b) result.exlohi + obj2.exlohi + (exlomid >> 64);
    u128b lolo = (u128b) result.lolo + obj2.lolo + (exlohi >> 64);
    u128b lomid = (u128b) result.lomid + obj2.lomid + (lolo >> 64);
    u128b lohi = (u128b) result.lohi + obj2.lohi + (lomid >> 64);
    u128b midlo = (u128b) result.midlo + obj2.midlo + (lohi >> 64);
    u128b midmid = (u128b) result.midmid + obj2.midmid + (midlo >> 64);
    u128b midhi = (u128b) result.midhi + obj2.midhi + (midmid >> 64);
    u128b hilo = (u128b) result.hilo + obj2.hilo + (midhi >> 64);
    u128b himid = (u128b) result.himid + obj2.himid + (hilo >> 64);
    u128b hihi = (u128b) result.hihi + obj2.hihi + (himid >> 64);
    u128b exhilo = (u128b) result.exhilo + obj2.exhilo + (hihi >> 64);
    u128b exhimid = (u128b) result.exhimid + obj2.exhimid + (exhilo >> 64);
    u128b exhihi = (u128b) result.exhihi + obj2.exhihi + (exhimid >> 64);
    
    result.exlolo = exlolo;
    result.exlomid = exlomid;
    result.exlohi = exlohi;
    result.lolo = lolo;
    result.lomid = lomid;
    result.lohi = lohi;
    result.midlo = midlo;
    result.midmid = midmid;
    result.midhi = midhi;
    result.hilo = hilo;
    result.himid = himid;
    result.hihi = hihi;
    result.exhilo = exhilo;
    result.exhimid = exhimid;
    result.exhihi = exhihi;
    
    
    return result;
}

std::ostream& operator<<(std::ostream& stream, const bigint& n) {
    int d[309] = {0}, i, j;
    
    for (i = 127; i > -1; i--) {
        if ((n.exhihi >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.exhimid >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.exhilo >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.hihi >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.himid >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.hilo >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.midhi >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.midmid >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.midlo >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.lohi >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.lomid >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.lolo >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.exlohi >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.exlomid >> i) & 1) d[0]++;
        for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 63; i > -1; i--) {
        if ((n.exlolo >> i) & 1) d[0]++;
        if (i > 0) for (j = 0; j < 309; j++) d[j] *= 2;
        for (j = 0; j < 308; j++) d[j+1] += d[j]/10, d[j] %= 10;
    }
    
    for (i = 308; i > 0; i--) if (d[i] > 0) break;
    for(; i > -1; i--) stream.put('0'+d[i]);
    return stream;
}