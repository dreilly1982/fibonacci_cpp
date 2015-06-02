//
//  bigint.cpp
//  fibonacci
//
//  Created by Don Reilly on 5/28/15.
//  Copyright (c) 2015 Don Reilly. All rights reserved.
//

#include "bigint.h"
#include <math.h>
#include <algorithm>

const u64b u64b_max = 18446744073709551615ull;

bigint::bigint (int n)
{
	v.push_back(n);
}

void bigint::operator=(const bigint& obj)
{
	(*this).v = obj.v;
    return;
}

bigint bigint::operator+(const bigint& obj2)
{
    bigint result = *this;
    
    // Need to make a mutable object
	bigint object2 = obj2;
    
    // Use 128-Bit integer to allow for carry over
	std::vector<u128b> tmp_vector(1);
	
	if (result.v.size() < object2.v.size() )
    {
		result.v.resize(object2.v.size());
		tmp_vector.resize(object2.v.size());
	}
	else if(result.v.size() > object2.v.size())
    {
		object2.v.resize(result.v.size()); 
		tmp_vector.resize(object2.v.size());
	}
    else
    {
		tmp_vector.resize(result.v.size());
	}
    
	for (size_t i = 0; i < result.v.size(); i++)
    {
		// Long addition.  Start small, then carry over to larger
		if (i == 0)
        {
			tmp_vector[i] = (u128b) result.v[i] + object2.v[i];
		}
        else
        {
			tmp_vector[i] = (u128b) result.v[i] + object2.v[i] + (tmp_vector[i-1] >> 64);
		}
		
        // Resize vectors.  Double when needed to reduce number of resizes.
		if ((tmp_vector[i] > (u128b) u64b_max) && (i == (result.v.size() - 1)))
        {
			tmp_vector.resize(result.v.size() * 2);
			object2.v.resize(result.v.size() * 2);
			result.v.resize(result.v.size() * 2);
		}
	}
    
    for (size_t i = 0; i < result.v.size(); i++)
    {
		result.v[i] = tmp_vector[i];
	}
    return result;
}

std::ostream& operator<<(std::ostream& stream, const bigint& n)
{
    int k = (int) floor(19.265919722494793 * n.v.size()) + 1;
	std::vector<int> d (k);
	int i, j;
	std::fill(d.begin(), d.end(), 0);
	
    // Split integer into an array where each element matches the proper place
    // Tens, hundreds, thousands, etc..
	for(int l = n.v.size() - 1; l > -1; l--)
    {
		if (l == 0)
        {
			for (i = 63; i > -1; i--)
            {
				if ((n.v[l] >> i) & 1) d[0]++;
				if (i > 0) for (j = 0; j < k; j++) d[j] *= 2;
				for (j = 0; j < (k-1); j++) d[j+1] += d[j]/10, d[j] %= 10;
			}
		}
        else
        {
			for (i = 63; i > -1; i--)
            {
				if ((n.v[l] >> i) & 1) d[0]++;
				for (j = 0; j < k; j++) d[j] *= 2;
				for (j = 0; j < (k - 1); j++) d[j+1] += d[j]/10, d[j] %= 10;
			}
		}
    }
	
    for (i = (k - 1); i > 0; i--) if (d[i] > 0) break;
    
    // Put characters into stream
    for(; i > -1; i--) stream.put('0'+d[i]);
    return stream;
}
