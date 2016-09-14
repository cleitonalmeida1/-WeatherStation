/*
 * SelectionSort.h
 *
 *  Created on: 19/07/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_

class SelectionSort {
public:
	SelectionSort() {

	}
	virtual ~SelectionSort() {

	}

	void selection( unsigned short vetorDesordenado[], unsigned short tamanhoVetor )
	{
	   unsigned short i, j, posicaoValorMinimo;

	   for (i = 0; i < ( tamanhoVetor - 1 ); i++)
	   {
	      posicaoValorMinimo = i;
	      for (j = ( i + 1 ); j < tamanhoVetor; j++)
	      {
	         if( vetorDesordenado[j] < vetorDesordenado[posicaoValorMinimo] )
	         {
	           posicaoValorMinimo = j;
	         }
	       }

	       if ( i != posicaoValorMinimo )
	       {
	          trocarPosicaoValores( &vetorDesordenado[i], &vetorDesordenado[posicaoValorMinimo] );
	       }
	   }
	}

	void trocarPosicaoValores( unsigned short *posicaoA, unsigned short *posicaoB )
	{
		unsigned short temporario;
	   temporario = *posicaoA;
	   *posicaoA = *posicaoB;
	   *posicaoB = temporario;
	}

};

#endif /* SELECTIONSORT_H_ */
