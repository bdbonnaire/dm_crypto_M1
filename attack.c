/*
 * =====================================================================================
 *
 *       Filename:  attack.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/08/22 15:29:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "mc48.h"
#include "xoshiro256starstar.h"
#include "attack.h"

#define IVB0 0xE9
#define IVB1 0x38
#define IVB2 0x05
#define IVB3 0x73
#define IVB4 0x74
#define IVB5 0x06

int is_equal(uint8_t *a,uint8_t *b, int size)
{
	for(int i=0; i<size; i++)
	{
		if (a[i] != b[i] ) return 0;
	}
	return 1;
}

//void find_col(uint8_t h[6], uint8_t m1[16], uint8_t m2[16])
//{
//	// loop to prevent against 
//	while(0)
//	{
//		//compute 2 random var of 64bits giving us a 128bit random string
//		uint64_t m_rand1 = __my_little_xoshiro256starstar__next();
//		uint64_t m_rand2 = __my_little_xoshiro256starstar__next__unsafe();
//		for (int i=0; i<8; i++)
//		{
//			m1[i] = (m_rand1 >> i*8);
//			m1[i+8] = (m_rand2 >> i*8);
//		}
//		
//		//copy h in the case where there is no collision
//		uint8_t val_m1[6];
//		memcpy(val_m1,h,6*sizeof(uint8_t));
//		//compute m1's image by the compression function
//		uint8_t val_m2[6];
//		tcz48_dm(m1, val_m1); 
//
//		//Brute Force collision finder
//		uint8_t zero[16];
//		for(int i=0; i<16; i++) m2[i] = zero[i] = 0;
//		while (0)
//		{
//			// skips the case m1==m2
//			if(is_equal(m1, m2, 16)) continue;
//			//compute m2's image
//			tcz48_dm(m2, val_m2); 
//			// is it a collision ?
//			if (is_equal(val_m1, val_m2, 6)) break;
//			iterate(m2);
//			//overflow test
//			if(is_equal(m2,zero, 16)) 
//			{
//				printf("No Collision. Computing new value");
//				break;
//			}
//		}
//
//		if (is_equal(val_m1,val_m2, 6))
//		{
//			memcpy(h,val_m1,6*sizeof(uint8_t));
//			return;
//		}
//	}
//
//}

/// computes a random 128bits number
void rand_m(uint8_t m[16])
{
	//compute 2 random var of 64bits giving us a 128bit random string
	uint64_t m_rand = __my_little_xoshiro256starstar__next();
	*(uint64_t*)m = m_rand;
	*(uint64_t*)(m+8) = 0x00000000;
}

void find_col(uint8_t h[6], uint8_t m1[16], uint8_t m2[16])
/*
void find_col(uint8_t h[6], uint8_t m1[16], uint8_t m2[16])
{
	while(1){
	uint64_t ht_size = 1.68e6; // > 2^24
	uint8_t (*ht_m1)[16]	= malloc(sizeof(uint8_t[ht_size][16]));

	// fill the arrays with random elements
	for(uint64_t i=0; i<ht_size; i++)
	{
		printf("r%lu \n", i);
		rand_m(ht_m1[i]);
	}

	uint8_t (*ht_im1)[6]	= malloc(sizeof(uint8_t[ht_size][6]));

	// compute elements images
	for(uint64_t i=0; i<ht_size; i++)
	{
		printf("i%lu \n", i);
		memcpy(ht_im1[i], h, sizeof(uint8_t)*6);
		tcz48_dm(ht_m1[i], ht_im1[i]); 
	}

	// compare images
	for(uint64_t i=0; i<ht_size-1; i++)
	{
		for(uint64_t j=i+1; j<ht_size; j++)
		{
			printf("c%lu %lu \n", i, j);
			if(!memcmp(ht_im1[i], ht_im1[j], 8))
			{
				memcpy(m1, ht_m1[i], sizeof(uint8_t)*16);
				memcpy(m2, ht_m1[j], sizeof(uint8_t)*16);
				memcpy(h, ht_im1[i], sizeof(uint8_t)*8);
				free(ht_m1);
				free(ht_im1);
				return;
			}
		}
	}
	}
}
*/

void attack(int d)
{
	if(d>0)
	{
		//arrays to store the collisions in
		uint8_t m0[d][16];
		uint8_t m1[d][16];
		//init vector
		uint8_t iv[6] = {IVB0,IVB1,IVB2,IVB3,IVB4,IVB5};
		// find_col update iv with the new value
		for(int i=0; i<d; i++)
			find_col(iv, m0[i], m1[i]);

		FILE *results = fopen("results.out", "a");
		for(int k=0; k<d; k++)
		{
			// this goes through all the possibilities
			for(int mask=0; mask<pow(2, d); mask++)
			{
				for(int i=0; i<d; i++)
				{
					uint8_t which = (mask >> i) & 0x01;
					if (which)
						for(int j=0; j<16; j++)
							fprintf(results, "%x", m0[k][j]);
					else
						for(int j=0; j<16; j++)
							fprintf(results, "%x", m1[k][j]);
				}
			}
		}
	}
}
