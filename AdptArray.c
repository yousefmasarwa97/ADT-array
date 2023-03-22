#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    COPY_FUNC copy;
    DEL_FUNC delete;
    PRINT_FUNC print;
    int size;
    PElement *element;
}AdptArray;


//function that create a new array 
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete,PRINT_FUNC print){
    PAdptArray adapter=(PAdptArray)malloc(sizeof(AdptArray));
    if(adapter==NULL){
        return NULL;
    }
    adapter->copy=copy;
    adapter->delete=delete;
    adapter->size=0;
    adapter->print=print;
    adapter->element=NULL;
    return adapter;

}

void DeleteAdptArray(PAdptArray adapter){
    for (int i = 0; i < adapter->size; i++)
    {
        if (adapter->element[i]!=NULL)
        {
           adapter->delete(adapter->element[i]);
        }
        
    }
    free(adapter->element);
    free(adapter);

}
Result SetAdptArrayAt(PAdptArray adapter, int index, PElement element_new)
{
	PElement* element1;
	if (adapter == NULL)
		return FAIL;

	if (index >adapter->size)
	{
		if ((element1 = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
        {
            return FAIL;
        }
			
		memcpy(element1, adapter->element,(adapter->size)* sizeof(PElement));
		free(adapter->element);
		adapter->element = element1;
        adapter->size=index+1;
	}

	if(adapter->element[index]!=NULL){
	    adapter->delete((adapter->element)[index]);
    }
	(adapter->element)[index] = adapter->copy(element_new);

	
	return SUCCESS;
    
}
PElement GetAdptArrayAt(PAdptArray adapter, int index)
{
     if(adapter->element[index]==NULL)
    {
        return NULL;
    }
    PElement elemntAt;
    elemntAt=adapter->copy(adapter->element[index]);
    return  elemntAt;
}

int GetAdptArraySize(PAdptArray adapter){
    if(adapter==NULL){
        return -1;
    }
    return adapter->size;
}


void PrintDB(PAdptArray adapter){
    
    for (int i = 0; i < adapter->size ; i++)
    {
        if (adapter->element[i]!=NULL)
        {
           adapter->print(adapter->element[i]); 
        }
        
        
    }  
}
