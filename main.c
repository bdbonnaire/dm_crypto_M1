/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/29/22 00:57:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "attack.h"

int isnbr(char str[])
{
	int i = 0;
	int isN = 1;
	while (str[i] != '\0')
	{
		isN *= isdigit(str[i]);	
		i++;
	}
	return isN;
}
int main(int argc, char *argv[])
{
	if(argc == 2 && isnbr(argv[1]))
	{
		printf("Computing Collisions...\n");
		attack(atoi(argv[1]));
		printf("Done !");
		return 0;
	}	
	else
	{
		printf("Argument error. Please check your command.");
		return 1;
	}
}
