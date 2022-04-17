/*
 * =====================================================================================
 *
 *       Filename:  attack.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/08/22 15:29:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef ATTACK_H
#define ATTACK_H
#include <stdint.h>

/// Implementation of a multicollisions attack on Narrow Pipe MD hash
/**
 * @arg d defines the number of collisions computed. For a given d 2^d will be given.
 */

int is_equal(uint8_t *a,uint8_t *b, int size);
void rand_m(uint8_t m[16]);

void attack(int d);

/// Searches for a collision for the function tcz48_dm
void find_col(uint8_t h[6], uint8_t m1[16], uint8_t m2[16]);

#endif
