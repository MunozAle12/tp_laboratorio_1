/*
 * LinkedList.c
 *
 *  Created on: 20 jun. 2020
 *      Author: Usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
                        o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = malloc(sizeof(LinkedList));
    if(this != NULL)
    {
    	this->pFirstNode = NULL;
    	this->size = 0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                          (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* auxNode = NULL;
	int listIndex = 0;
	if(this != NULL && nodeIndex >= 0 && nodeIndex < this->size)
	{
		auxNode = this->pFirstNode;
		if(auxNode != NULL)
		{
			do
			{
				if(listIndex == nodeIndex)
				{
					break;
				}
				else
				{
					auxNode = auxNode->pNextNode;
					listIndex++;
				}
			}while(auxNode != NULL && listIndex < this->size);
		}
	}
    return auxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    int returnAux = -1;
    Node* newNode = NULL;
    Node* auxNode = NULL;
    if(this != NULL && nodeIndex >= 0 && nodeIndex <= this->size)
    {
    	newNode = (Node*)malloc(sizeof(Node));
    	if(newNode != NULL)
    	{
    		returnAux = 0;
    		this->size++;
    		newNode->pElement = pElement;
    		if(nodeIndex == 0)
    		{
    			newNode->pNextNode = this->pFirstNode;
    			this->pFirstNode = newNode;
    		}
    		else
    		{
    			auxNode = getNode(this,nodeIndex-1);
    			newNode->pNextNode = auxNode->pNextNode;
    			auxNode->pNextNode = newNode;
    		}
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = addNode(this,this->size,pElement);
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode = NULL;
    if(this != NULL && index >= 0 && index < this->size)
    {
    	auxNode = getNode(this,index);
    	if(auxNode != NULL)
    	{
        	returnAux = auxNode->pElement;
    	}
    }
    return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    Node* auxNode = NULL;
    if(this != NULL && index >= 0 && index < this->size)
    {
    	auxNode = getNode(this,index);
    	if(auxNode != NULL)
    	{
    		auxNode->pElement = pElement;
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this, int index)
{
    int returnAux = -1;
    Node* deleteNode = NULL;
    Node* auxNode = NULL;
    if(this != NULL && index >= 0 && index < this->size)
    {
		deleteNode = getNode(this,index);
		if(deleteNode != NULL)
		{
			this->size--;
			if(index == 0)
			{
				this->pFirstNode = deleteNode->pNextNode;
				free(deleteNode);
	    	}
	    	else
	    	{
	    		auxNode = getNode(this,index-1);
	    		auxNode->pNextNode = deleteNode->pNextNode;
	    		free(deleteNode);
	    	}
	    	returnAux = 0;
		}
    }
    return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(ll_len(this) > 0)
    	{
    		do
    		{
        		ll_remove(this,this->size-1);
    		}while(this->size != 0);
    	}
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(!ll_clear(this))
    	{
        	free(this);
        	returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* auxNode = NULL;
    int listIndex = 0;
    if(this != NULL)
    {
    	auxNode = this->pFirstNode;
    	if(auxNode != NULL)
    	{
    		do
    		{
    			if(auxNode->pElement == pElement)
    			{
    				returnAux = listIndex;
    				break;
    			}
    			else
    			{
    				auxNode = auxNode->pNextNode;
    				listIndex++;
    			}
    		}while(auxNode != NULL && listIndex < this->size);
    	}
	}
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(this->size > 0)
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this,int index,void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <= this->size)
    {
		returnAux = addNode(this,index,pElement);
    }
    return returnAux;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* auxNode = NULL;
	if(this != NULL && index >= 0 && index < this->size)
	{
		auxNode = getNode(this,index);
		if(auxNode != NULL)
		{
			returnAux = auxNode->pElement;
			ll_remove(this,index);
		}
	}
    return returnAux;
}

/** \brief Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
 */
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(ll_indexOf(this,pElement) >= 0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
	int returnAux = -1;
	Node* auxNodeList2 = NULL;
	int indexList2 = 0;
	if(this != NULL && this2 != NULL)
	{
		returnAux = 0;
		auxNodeList2 = this2->pFirstNode;	//TOMO EL NODO EN LA POSICIÓN 0 DE LA LISTA 2 COMO PUNTO DE PARTIDA
		if(auxNodeList2 != NULL)
		{
			returnAux = 1;
			do
			{
				if(ll_indexOf(this,auxNodeList2->pElement) == -1)
				{
					returnAux = 0;
					break;
				}
				else
				{
					indexList2++;
					auxNodeList2 = auxNodeList2->pNextNode;
				}
			}while(auxNodeList2 != NULL && indexList2 < this2->size);
		}
	}
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista).
                         	 	Si está ok, retorna el puntero a la nueva lista.
 */
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pAuxElement = NULL;
    int indexCopy = from;
    if(this != NULL && from >= 0 && from < this->size && to > from && to <= this->size)
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
    		do
    		{
        		pAuxElement = ll_get(this,indexCopy);
        		if(!ll_add(cloneArray,pAuxElement))
        		{
        			indexCopy++;
        		}
        		else if(!ll_deleteLinkedList(cloneArray))
				{
					cloneArray = NULL;
					break;
				}
    		}while(indexCopy < to);
    	}
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
 */
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    void* pAuxElement = NULL;
    int indexCopy = 0;
    if(this != NULL)
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
    		do
    		{
        		pAuxElement = ll_get(this,indexCopy);
        		if(!ll_add(cloneArray,pAuxElement))
        		{
        			indexCopy++;
        		}
        		else if(!ll_deleteLinkedList(cloneArray))
				{
					cloneArray = NULL;
					break;
				}
    		}while(indexCopy < this->size);
    	}
    }
    return cloneArray;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente
 * 				int	 [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL, (0) Si ok
 *
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void* ), int order)
{
    int returnAux = -1;
    void* pAuxNodeA = NULL;
    void* pAuxNodeB = NULL;
    void* pAuxSwap = NULL;
    int flagSwap;
    int indexList;
    int returnComparision;
    int comparisionLimit;
    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
    	returnAux = 0;
    	comparisionLimit = this->size-1;
    	do
    	{
    		flagSwap = 0;
    		for(indexList=0; indexList<comparisionLimit; indexList++)
    		{
    			pAuxNodeA = ll_get(this,indexList);
    			pAuxNodeB = ll_get(this,indexList+1);
				returnComparision = pFunc(pAuxNodeA,pAuxNodeB); /* SI RETORNA 1 EL 1° > 2°
																SI RETORNA -1 1° < 2°
																SI RETORNA 0 1° = 2° */
				if((order == 1 && returnComparision == 1) || (order == 0 && returnComparision == -1))
				{
					pAuxSwap = pAuxNodeA;
					ll_set(this,indexList,pAuxNodeB);
					ll_set(this,indexList+1,pAuxSwap);
					flagSwap = 1;
				}
				else
				{
					continue;
				}
    		}
			comparisionLimit--;
    	}while(flagSwap == 1);
    }
    return returnAux;
}
/*
============================================================================
					NUEVAS FUNCIONES DE LINKEDLIST
============================================================================
*/
/**
 * \brief Recorre la lista, analizando cada elemento para que se realice una tarea.
 *
 * \this Puntero al espacio de memoria donde se empieza la lista.
 * \pFuncGenerica Puntero al espacio de memoria donde comienza el código de dicha función.
 * \return Retorna -1 los parametros recibidos son NULL o si al menos un elemento no cumple con el criterio establecido.
 * 				   Retorna 0 si ok.
 *
 */
int ll_map(LinkedList* this, int (*pFuncGenerica)(void*)) //NUEVO
{
	int respuesta = -1;
	void* pElement = NULL;
	int indexElement;
	if(this != NULL && pFuncGenerica != NULL)
	{
		respuesta = 0;
		for(indexElement=0; indexElement<this->size; indexElement++)
		{
			pElement = ll_get(this,indexElement);
			if(pFuncGenerica(pElement) < 0)
			{
				respuesta = -1;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Recorre una lista, analiza y filtra cada elemento que cumpla con un criterio para luego agregarlo a una lista.
 *
 * \param this Puntero al espacio de memoria donde se empieza la lista.
 * \param pFuncFilterBy Puntero al espacio de memoria donde comienza el código de dicha función que filtra la lista por un criterio.
 * \return Retorna un puntero a NULL si los parametros recibidos son NULL o si no se logró crear una lista filtrada.
 * 				   Retorna un puntero a la lista filtrada si ok.
 *
 */
LinkedList* ll_filter(LinkedList* this, int (*pFuncFilterBy)(void*)) //NUEVO
{
	LinkedList* filteredList = NULL; //Lista filtrada
	int indexListOriginal;
	void* pElement = NULL;
	if(this != NULL && pFuncFilterBy != NULL)
	{
		filteredList = ll_newLinkedList();
		if(filteredList != NULL)
		{
			for(indexListOriginal=0; indexListOriginal<this->size; indexListOriginal++)
			{
				pElement = ll_get(this,indexListOriginal);
				if(pFuncFilterBy(pElement))
				{
					ll_add(filteredList,pElement);
				}
			}
		}
	}
	return filteredList;
}

/**
 * \brief Recorre una lista, realizando un conteo por cada elemento que cumpla con un criterio.
 *
 * \param this Puntero al espacio de memoria donde se empieza la lista.
 * \param pFuncCountBy Puntero al espacio de memoria donde comienza el código de dicha función que realiza un conteo por cada elemento que cumpla con un criterio.
 * \return Retorna -1 si los parametros recibidos son NULL, retorna una valor entero mayor o igual a 0 si ok.
 *
 */
int ll_count(LinkedList* this, int (*pFuncCountBy)(void*)) //NUEVO
{
	int respuesta = -1;
	void* pElement = NULL;
	int indexList;
	int contador = 0;
	if(this != NULL && pFuncCountBy != NULL)
	{
		for(indexList=0; indexList<this->size; indexList++)
		{
			pElement = ll_get(this,indexList);
			if(pFuncCountBy(pElement))
			{
				contador++;
			}
		}
		respuesta = contador;
	}
	return respuesta;
}

/**
 * \brief Recorre una lista y por cada elemento realiza la acumulación de un valor Int que cumpla con un criterio.
 *
 * \param this Puntero al espacio de memoria donde se empieza la lista.
 * \param pFuncAccumulateBy Puntero al espacio de memoria donde comienza el código de dicha función que acumula un valor por cada elemento que cumpla con un criterio.
 * \return Retorna -1 si los parametros recibidos son NULL, retorna un valor mayor o igual a 0 el cual representa el valor acumulado.
 *
 */
int ll_accumulatorInt(LinkedList* this, int (*pFuncAccumulateBy)(void* ,int )) //NUEVO
{
	int respuesta = -1;
	int indexElement;
	void* pElement = NULL;
	int value = 0;
	int accumulatedValue = 0;
	if(this != NULL && pFuncAccumulateBy != NULL)
	{
		for(indexElement=0; indexElement<this->size; indexElement++)
		{
			pElement = ll_get(this,indexElement);
			value = pFuncAccumulateBy(pElement,accumulatedValue);
			accumulatedValue = accumulatedValue + value;
		}
		respuesta = accumulatedValue;
	}
	return respuesta;
}

/**
 * \brief Recorre una lista, para reducirla a un solo elemento el cual cumple con un criterio.
 *
 * \param this Puntero al espacio de memoria donde se empieza la lista.
 * \param pFuncReduceBy Puntero al espacio de memoria donde comienza el código de dicha función que reduce la lista cumpliendo con un criterio.
 * \return Retorna un puntero a NULL si los parametros recibidos son NULL, retorna un puntero al elemento reducido.
 *
 */
void* ll_reduceInt(LinkedList* this, int (*pFuncReduceBy)(void* ,int ,int ))
{
	int indexList;
	void* pElement = NULL;
	void* pElementReduced = NULL;
	int valueReduced = 0;
	int value = 0;
	if(this != NULL && pFuncReduceBy != NULL)
	{
		for(indexList=0; indexList<this->size; indexList++)
		{
			pElement = ll_get(this,indexList);
			value = pFuncReduceBy(pElement,valueReduced,indexList);
			if(value > valueReduced)
			{
				valueReduced = value;
				pElementReduced = pElement;
			}
		}
	}
	return pElementReduced;
}
