#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "BST.h"

using namespace std;

class Arreglo
{
private:
    int *arreglo;
    int tamano;
public:
    Arreglo(){}
    Arreglo(int n) // rellena arreglo con n cantidad de enteros aleatorios
    {

        srand(time(NULL));
        tamano = n;

        arreglo = new int[n];

        ofstream archivo;
        archivo.open("numeros.txt");

        archivo << n << endl;
        int i=0
        while(i<n)
        {
            arreglo[i] = rand()%n;
            archivo << arreglo[i] << endl;
            //cout << "Valor " << i << ": " << arreglo[i] << endl;
            i++;
        }

        archivo.close();
    }

    Arreglo(string documento) // rellena arreglo con los números del archivo, el primer elemento en el archivo determina el tamaño del arreglo
    {
        ifstream archivo;
        archivo.open(documento);

        archivo >> tamano;
        arreglo = new int[tamano];

        for(int i=0; i<tamano; i++)
        {
            archivo >> arreglo[i];
            //cout << "Elemento " << i << ": " << arreglo[i] << endl;
        }
    }

    void printArr()
    {
        for(int i=0; i<tamano; i++)
        {
            cout << "Elemento " << i << ": " << arreglo[i] << endl;
        }
    }

    int getTam()
    {
        return tamano;
    }

    void cambiar(int a, int b)
    {
        int tmp = arreglo[a];
        arreglo[a] = arreglo[b];
        arreglo[b] = tmp;
    }

    void bubbleSort()
    {
        for(int i=1; i<tamano; i++)
        {
            for(int ii=0; ii<tamano-1; ii++)
            {
                if(arreglo[ii] > arreglo[ii+1])
                {
                    cambiar(ii, ii+1);
                }
            }
        }

        cout << endl << "Bubble sort aplicado" << endl << endl;
    }

    void cocktailSort()
    {
        bool intercambiado = false;
        do
        {
            for(int i=0; i<tamano-2; i++)
            {
                if(arreglo[i] > arreglo[i+1])
                {
                    cambiar(i, i+1);
                    intercambiado = true;
                }
            }

            if(!intercambiado)
            {
                break;
            }

            intercambiado = false;

            for(int i=tamano-2; i>=0; i--)
            {
                if(arreglo[i] > arreglo[i+1])
                {
                    cambiar(i, i+1);
                    intercambiado = true;
                }
            }
        }while(intercambiado == true);

    }

    void insertionSort()
    {
        for(int i=1; i<tamano; i++)
        {
            if(arreglo[i-1] > arreglo[i])
            {
                cambiar(i-1, i);
                for(int ii=i-1; ii>=0; ii--)
                {
                    if(arreglo[ii] < arreglo[ii-1])
                    {
                        cambiar(ii, ii-1);
                    }
                }
            }
        }

    }

    void bucketSort()
    {
        vector<int> b[tamano];

        for(int i=0; i<tamano; i++)
        {
            int contador1 = (tamano*arreglo[i])%tamano;
            b[contador1].push_back(arreglo[i]);
        }

        for(int i=0; i<tamano; i++)
        {
            sort(b[i].begin(), b[i].end());
        }

        int contador2 = 0;
        for(int i=0; i<tamano; i++)
        {
            for(int ii=0; ii<b[i].size(); ii++)
            {
                arreglo[contador2++] = b[i][ii];
            }
        }

    }

    void countingSort()
    {
        int k = *max_element(arreglo, arreglo+tamano);
        int i, ii;
        int ordenado[tamano], temp[k+1];

        for (int i=0; i<=k; i++)
            temp[i] = 0;
        for (int ii=0; ii<tamano; ii++)
            temp[arreglo[ii]] = temp[arreglo[ii]] + 1;

        for (int i=1; i<k+1; i++)
            temp[i] = temp[i] + temp[i-1];

        for (int ii=tamano-1; ii>=0; ii--)
        {
            ordenado[temp[arreglo[ii]]-1] = arreglo[ii];
            temp[arreglo[ii]] = temp[arreglo[ii]] - 1;
        }
        for(int i=0; i<tamano; i++)
        {
            arreglo[i] = ordenado[i];
        }
    }

    void merge(int lo, int mid, int hi)
    {
      int arrAux[hi+1];//se crea el arreglo auxiliar en base a los datos ingresados

      for(int i=lo; i<=hi; i++)//se copian los datos
      {
        arrAux[i] = arreglo[i];
      }

      int i = lo;
      int ii = mid+1;
      int k = lo;

      while (i<=mid && ii<=hi)//ciclo que corre mientras los apuntadores i y ii estén paralelos y avancen conjuntamente
      {
        if(arrAux[i] < arrAux[ii])// si el valor del lado izquierdo es menor se pasa al arreglo final
        {
          arreglo[k] = arrAux[i];
          k++;//se suma 1 a la posición del arreglo final
          i++;//se recorre el lado izquierdo para pasar al siguiente valor
        }
        else
        {
          arreglo[k] = arrAux[ii];
          k++;//se suma 1 a la posición del arreglo final
          ii++;//se recorre el lado derecho para pasar al siguiente valor
        }
      }

      while(i <= mid)//cuando ii deja de avanzar simplemente se copian los valores restantes del lado izquierdo
      {
        arreglo[k] = arrAux[i];
        i++;// se recorre el lado izquierdo hasta terminar
        k++;// se suma 1 a la posición del arreglo final
      }

      while(ii <= hi)// cuando i deja de avanzar, los valores restantes del lado derecho se copian
      {
        arreglo[k] = arrAux[ii];
        ii++; // se recorre el lado derecho hasta terminar
        k++; // se suma 1 a la posición del arreglo final
      }
    }

    void mergeSort(int lo, int hi)
    {
      if(hi<=lo)//a menos que hi sea menor que lo no va a salirse de la recursión
      {
        return;
      }else{
        int mid = lo + ((hi - lo)/2);//se saca el punto medio

        mergeSort(lo, mid);//se ordena la parte izquierda
        mergeSort(mid+1, hi);//se ordena la parte derecha
        merge(lo, mid, hi);//se juntan ambas partes para ser ordenadas
      }
    }

    float binaryTreeSort()
    {
      BST arbol;
      return arbol.creaYOrdena(arreglo, tamano);
    }

    void countradix(int exp)
    {
      int ordenado[tamano];
      int i, temp[10] = {0};

      for (i = 0; i < tamano; i++)
          temp[ (arreglo[i]/exp)%10 ]++;

      for (i = 1; i < 10; i++)
          temp[i] += temp[i - 1];

      for (i = tamano - 1; i >= 0; i--)
      {
          ordenado[temp[ (arreglo[i]/exp)%10 ] - 1] = arreglo[i];
          temp[ (arreglo[i]/exp)%10 ]--;
      }

      for (i = 0; i < tamano; i++)
          arreglo[i] = ordenado[i];
    }

    void radixSort()
    {
      int k = *max_element(arreglo,arreglo+tamano);

      for (int exp = 1; k/exp > 0; exp *= 10)
          countradix(exp);

      cout << endl << "radixSort aplicado" << endl;
    }

    void shellSort()
    {
        for (int rango = tamano/2; rango > 0; rango /= 2)
        {

            for (int i = rango; i < tamano; i += 1)
            {
                int temp = arreglo[i];

                int ii;
                for (ii = i; ii >= rango && arreglo[ii - rango] > temp; ii -= rango)
                    arreglo[ii] = arreglo[ii - rango];

                arreglo[ii] = temp;
            }
        }
    }

    void SelectionSort() //método de ordenamiento selection sort
    {
        int minimo;

        for (int i=0;i<tamano ; i++) //voy recorriendo todos los elementos
        {
            minimo=i; //el mínimo elemento (por el que voy a empezar)
            for (int ii=i+1;ii<tamano; ii++) //otra vez recorro todos a partir de donde empecé
            {
                if(arreglo[ii]<arreglo[minimo]) //si encuentro un valor menor al que se encuentra donde empecé, guardaré ese índice
                {
                    minimo=ii;

                }
            }
            cambiar(i,minimo); //al final cambiar el valor mínimo que encontré por el de mi índice
        }
    }

    void MaxHeapify(int a[], int i, int n)
    {
    	int ii, temp;
    	temp = a[i];
    	ii = 2*i;

     	while (ii <= n)
    	{
    		if (ii < n && a[ii+1] > a[ii])
    		ii = ii+1;
    		// Break if parent value is already greater than child value.
    		if (temp > a[ii])
    			break;
    		// Switching value with the parent node if temp < a[ii].
    		else if (temp <= a[ii])
    		{
    			a[ii/2] = a[ii];
    			ii = 2*ii;
    		}
    	}
    	a[ii/2] = temp;
    	return;
    }

    void HeapSort()
    {
    	Build_MaxHeap(arreglo, tamano-1);

    	int i, temp;
    	for (i = tamano; i >= 2; i--)
    	{
    		// Storing maximum value at the end.
    		temp = arreglo[i];
    		arreglo[i] = arreglo[1];
    		arreglo[1] = temp;
    		// Building max heap of remaining element.
    		MaxHeapify(arreglo, 1, i - 1);
    	}
    }

    void Build_MaxHeap(int a[], int n)
    {
    	int i;
    	for(i = n/2; i >= 1; i--)
    		MaxHeapify(a, i, n);
    }

    int partition(int inicio, int fin) //método de quicksort para dividir imaginariamente
    {
      int principio, final, ref; //variables para mi principio, final y pivote.


      ref = arreglo[inicio]; //mi pivote será el primer elemento de mi arreglo
      principio = inicio; //igualo los inicios
      final = fin; //igualo los fines


      while (principio < final) //si todavía no se cruzan
      {
        for(final;arreglo[final]>ref;final--); //recorro el índice del final hacia la izquierda mientras el valor de derecha sea mayor que mi referencia
       	for(principio;principio<final&&arreglo[principio]<=ref;principio++);  //recorro el índice del inicio a la derecha mientras mi valor sea menor que mi referencia

    	  if(principio < final) //si ya se cruzaron, ya terminé de ver hasta dónde se dividen todos los menores que mi punto y todos los mayores a este
          cambiar(principio,final); //entonces cambiar mi valor del principio con el del final porque es el último que todavía era menor
      }


      cambiar(final,inicio); //cambio de lugar mi pivote

      //La nueva posición del pivote
      return final;
    }

    void quickSort(int inicio, int fin) //método de ordenamiento QuickSort
    {
      int referencia; //este es el punto con el que voy a comparar primero (pivote)
      if(inicio < fin) //si todavía no se cruzan mis índices
      {
        referencia = partition(inicio, fin); //mando a llamar el método que divide imaginariamente para sacar la nueva referencia
        quickSort(inicio, referencia - 1 );//Ordeno la primera mitad de mi arreglo
        quickSort(referencia + 1, fin );//Ordeno la segunda mitad de mi arreglo
      }
    }
};

int main()
{
    clock_t tiempo;
    Arreglo a1("numeros.txt");
    //a1.printArr();

    tiempo = clock();
    //a1.bubbleSort();
    //a1.cocktailSort();
    //a1.insertionSort();
    //a1.bucketSort();
    //a1.countingSort();
    a1.mergeSort(0, 9);
    //cout << a1.binaryTreeSort() << "ms" << endl;
    //a1.radixSort();
    //a1.shellSort();
    //a1.SelectionSort();
    //a1.HeapSort();
    //a1.quickSort(0, 9);
    tiempo = clock() - tiempo;
    cout << endl;
    //a1.printArr();
    cout << (float(tiempo))*1000/CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
