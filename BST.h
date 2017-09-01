#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Nodo
{
public:
	int dato;
	Nodo *izquierdo;
	Nodo *derecho;
};

class BST
{
public:
	Nodo *raiz;

	BST()
	{
		raiz = NULL;
	}

	float Inicializa(int *arr, int tamano)
	{
		cout << "número de elementos: " << tamano << endl;

		time_t tiemp = clock();
		for (int x = 0; x<tamano; x++)
		{
			//cout << "Entra al for de la inserci�n, iteraci�n: " << x << endl;
			insertarTail(raiz, arr[x]); // lama a la funci�n recursiva de inserci�n
		}
		return float(clock() - tiemp) * 1000 / CLOCKS_PER_SEC;
	}

	void insertarTail(Nodo *raiz, int numero)
	{
		//cout << "Entra a insertar Tail" << endl;
		if (raiz == NULL)
		{
			Nodo *n = new Nodo;
			n->dato = numero;
			n->izquierdo = NULL;
			n->derecho = NULL;
			raiz = n;

			//cout << "Guard� el dato " << numero << " en el �rbol" << endl;
		}
		else {
			//cout << "raiz no es NULL" << endl;
			if (numero < raiz->dato)
			{
				insertarTail(raiz->izquierdo, numero);
			}
			else {
				if (numero >= raiz->dato)
				{
					insertarTail(raiz->derecho, numero);
				}
			}
		}
	}

	void insertar(int dato)
	{
		insertarTail(raiz, dato);
	}

	void inorden(Nodo *raiz)
	{
		if (raiz == NULL)
		{
			return;
		}

		inorden(raiz->izquierdo);

		cout << raiz->dato << " - ";

		inorden(raiz->derecho);
	}

	void inordenTail(Nodo *raiz, int *arr, int x)
	{
		if (raiz == NULL)
		{
			return;
		}

		inordenTail(raiz->izquierdo, arr, x);

		arr[x] = raiz->dato;
		cout << endl << "dato transferido: " << arr[x];
		x++;

		inordenTail(raiz->derecho, arr, x);
	}
};

#endif
