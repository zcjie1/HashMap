#include "../include/HashMapIterator.h"

HashMapIterator createHashMapIterator(HashMap hashMap){
    HashMapIterator iterator = newHashMapIterator();
    if(iterator == NULL) return NULL;
    iterator->hashMap = hashMap;
	iterator->count = 0;
	iterator->list_index = -1;
	iterator->entry = NULL;
	return iterator;
}


Bool hasNextHashMapIterator(HashMapIterator iterator){
    return iterator->count < iterator->hashMap->size ? True : False;
}


HashMapIterator nextHashMapIterator(HashMapIterator iterator){
    if (hasNextHashMapIterator(iterator)){
		if (iterator->entry != NULL && iterator->entry->next != NULL){
			iterator->count++;
			iterator->entry = iterator->entry->next;
			return iterator;
		}
		while (++(iterator->list_index) < iterator->hashMap->listSize){
			Entry entry = &iterator->hashMap->list[iterator->list_index];
			if (entry->key != NULL) {
				iterator->count++;
				iterator->entry = entry;
				break;
			}
		}
	}
}


void freeHashMapIterator(HashMapIterator* iterator){
    free(*iterator);
	*iterator = NULL;
}
