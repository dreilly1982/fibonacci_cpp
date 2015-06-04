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

#define putchar_unlocked putchar

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
	int i;
    // Use 128-Bit integer to allow for carry over
    //u64b carryover;
	std::vector<u128b> result;
	
	/*if (vector1.size() < vector2.size()) std::swap(vector1, vector2);
	result.resize(vector1.size());
	for (i = 0; i < (int) vector2.size(); i++)
	{
		// Long addition.  Start small, then carry over to larger
		if (i == 0)
		{
			result[i] = (u128b) vector1[i] + vector2[i];
		}
		else
		{
			result[i] = (u128b) vector1[i] + vector2[i] + (result[i-1] >> 64);
		}
	}
	
	for (; i < (int) vector1.size(); ++i) result[i] = (u128b) vector1[i] + (result[i-1] >> 64);
	if (result[i-1] > (u128b) u64b_max) result.push_back(result[i-1] >> 64);*/

    if (this->v.size() < obj2.v.size() )
    {
		result.resize(obj2.v.size());
        for (i = 0; i < (int) this->v.size(); i++)
		{
			// Long addition.  Start small, then carry over to larger
			if (i == 0)
			{
				result[i] = this->v[i] + obj2.v[i];
			}
			else
			{
				result[i] = this->v[i] + obj2.v[i] + (result[i-1] >> 64);
			}
		}
		
		for (; i < (int) obj2.v.size(); ++i) result[i] = obj2.v[i] + (result[i-1] >> 64);
		if (result[i-1] > u64b_max) result.push_back(result[i-1] >> 64);
    }
    else if(this->v.size() > obj2.v.size())
    {
        result.resize(this->v.size());
        for (i = 0; i < (int) obj2.v.size(); i++)
		{
			// Long addition.  Start small, then carry over to larger
			if (i == 0)
			{
				result[i] = this->v[i] + obj2.v[i];
			}
			else
			{
				result[i] = this->v[i] + obj2.v[i] + (result[i-1] >> 64);
			}
		}
		
		for (; i < (int) this->v.size(); ++i) result[i] = this->v[i] + (result[i-1] >> 64);
		if (result[i-1] > u64b_max) result.push_back(result[i-1] >> 64);
    }
    else
    {
        result.resize(this->v.size());
        for (i = 0; i < (int) obj2.v.size(); i++)
		{
			// Long addition.  Start small, then carry over to larger
			if (i == 0)
			{
				result[i] = this->v[i] + obj2.v[i];
			}
			else
			{
				result[i] = this->v[i] + obj2.v[i] + (result[i-1] >> 64);
			}
		}
		
		if (result[i-1] > u64b_max) result.push_back(result[i-1] >> 64);
    }
    
    /*for (size_t i = 0; i < result.v.size(); i++)
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
    }*/
	
	if (this->v.size() < result.size()) this->v.resize(result.size());
    
    for (int i = 0; i < (int) result.size(); i++)
    {
        this->v[i] = result[i];
    }
	
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const bigint& n)
{
    int g = 0;
    for (int i = 0; i < (int) n.v.size(); i++)
    {
        if (n.v[i] != 0) g = i + 1;
    }
    int k = (int) floor(19.265919722494793 * g) + 1;
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

/*void print_bigint(const bigint& n) {
    
    // Split integer into an array where each element matches the proper place
    // Tens, hundreds, thousands, etc..
    for(int i = n.v.size() - 1; i > -1; i--)
    {
        u64b N = n.v[i], rev;
        int count = 0;
        rev = N;
        if (N==0) { putchar_unlocked('0'); break;}
        while ((rev % 10) == 0) { count++; rev /= 10;}
        rev = 0;
        while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}
        while (rev != 0) { putchar_unlocked(rev % 10 + '0'); rev /= 10;}
        while (count--) putchar_unlocked('0');
    }
    
    putchar_unlocked('\n');
    return;
}*/

/*void print_bigint(const bigint& n) {
    int g = 0;
    for (int i = 0; i < (int) n.v.size(); i++)
    {
        if (n.v[i] != 0) g = i + 1;
    }
    int k = (int) floor(19.265919722494793 * g) + 1;
    std::vector<int> d (k);
    int i, j;
    std::fill(d.begin(), d.end(), 0);
    
    // Split integer into an array where each element matches the proper place
    // Tens, hundreds, thousands, etc..
    for(int l = (int)n.v.size() - 1; l > -1; l--)
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
    for(; i > -1; i--) putchar_unlocked('0'+d[i]);
    putchar_unlocked('\n');
    return;
}*/