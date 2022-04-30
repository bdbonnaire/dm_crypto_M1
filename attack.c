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
// 20e6
#define HT_SIZE 20000000

int collision_check(uint8_t *a,uint8_t *b, uint8_t *iv, uint8_t *ha)
{
	// test if the collision is real by recomputing
	// the previous message's image
	uint8_t h_temp[6];
	// give the value of the iv
	memcpy(h_temp, iv, sizeof(uint8_t[6]));
	//compute b's image, put it in h_temp
	tcz48_dm(b, h_temp);
	if(!memcmp(h_temp, ha, sizeof(uint8_t[6])))
		return 1;
	else
		return 0;

}

/// computes a random 128bits number
void rand_m(uint8_t m[16])
{
	//compute 2 random var of 64bits giving us a 128bit random string
	uint64_t m_rand = __my_little_xoshiro256starstar__next();
	//consider the pointer to 128bits as a 64bit ptr
	*(uint64_t*)m = m_rand;
	*(uint64_t*)(m+8) = 0x0;
}

void find_col(uint8_t h[6], uint8_t m1[16], uint8_t m2[16])
{
	// array containing the messages
	uint8_t (*ht_m)[16]	= calloc(HT_SIZE, sizeof(uint8_t[16]));
	uint8_t m_temp[16];
	uint8_t zero[16] = {0};
	uint8_t h_temp[8] = {0};
	while (1)
	{
		memcpy(h_temp, h, sizeof(uint8_t[6]));
		rand_m(m_temp);
		//printf("%lu\t", *(uint64_t*)m_temp); //TEST
		tcz48_dm(m_temp, h_temp);
		//printf("%lu\n", (*(uint64_t*)h_temp) & 0xFFFFFFFFFFFF); //TEST
#define HT_MOD_ACCESS ((*(uint64_t*)h_temp) & 0xFFFFFFFFFFFF) % HT_SIZE
		if(!memcmp(ht_m[HT_MOD_ACCESS], zero, sizeof(uint8_t[16])))
		{
			memcpy(ht_m[HT_MOD_ACCESS],
				   	m_temp, sizeof(uint8_t[16]));
		}
		else
		{
			if(collision_check(m_temp, ht_m[HT_MOD_ACCESS], h, h_temp))
			{
				memcpy(m1, ht_m[HT_MOD_ACCESS], sizeof(uint8_t)*16);
				memcpy(m2, m_temp,  sizeof(uint8_t)*16);
				memcpy(h, h_temp, sizeof(uint8_t)*6);
				free(ht_m);
				return;
			}
		}
	}
}
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
		{
			find_col(iv, m0[i], m1[i]);
		}

		FILE *results = fopen("results.out", "a");
		// this goes through all the possibilities
		for(int mask=0; mask<pow(2, d); mask++)
		{
			for(int i=0; i<d; i++)
			{
				uint8_t which = (mask >> i) & 0x01;
				if (which)
					for(int j=0; j<16; j++)
						fprintf(results, "%x", m0[i][j]);
				else
					for(int j=0; j<16; j++)
						fprintf(results, "%x", m1[i][j]);
			}
			fprintf(results, "\n");
		}
		fclose(results);
	}
}
