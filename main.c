/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/17/22 11:42:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "attack.h"
#include "mc48.h"

#define IVB0 0xE9
#define IVB1 0x38
#define IVB2 0x05
#define IVB3 0x73
#define IVB4 0x74
#define IVB5 0x06

int main()
{
	uint8_t iv[6] = {IVB0,IVB1,IVB2,IVB3,IVB4,IVB5};
	uint8_t h[6] = {IVB0,IVB1,IVB2,IVB3,IVB4,IVB5};
	uint8_t h1[6] = {IVB0,IVB1,IVB2,IVB3,IVB4,IVB5};
	uint8_t h2[6] = {IVB0,IVB1,IVB2,IVB3,IVB4,IVB5};
	uint8_t m1[16], m2[16];
	uint8_t val_m1[6], val_m2[6];
	find_col(h, m1, m2);
	tcz48_dm(m1, h1); 
	tcz48_dm(m2, h2); 

	printf("m1 = ");
	for(int i =15; i>=0; i--)
	{
		printf("%x", m1[i]);
	}
	printf("\n m2 = ");
	for(int i =15; i>=0; i--)
	{
		printf("%x", m2[i]);
	}
	printf("\nm1_val = %lu", (*(uint64_t*)h1) & 0xFFFFFFFFFFFF);
//	for(int i =5; i>=0; i--)
//	{
//		printf("%x", h1[i]);
//	}
	printf("\nm2_val = %lu", (*(uint64_t*)h2) & 0xFFFFFFFFFFFF);
//	for(int i =5; i>=0; i--)
//	{
//		printf("%x", h2[i]);
//	}

	
	return 0;
}
