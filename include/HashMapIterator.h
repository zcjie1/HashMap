#ifndef __HASHMAPITERATOR_H__
#define __HASHMAPITERATOR_H__

#include "./HashMap.h"
#include "./util.h"

typedef struct hashMapIterator{
	Entry entry;	
	uint32_t count;		
	uint32_t list_index;  //used in nextHashMapIterator
	HashMap hashMap;
}*HashMapIterator;

#define newHashMapIterator() NEW(struct hashMapIterator)

HashMapIterator createHashMapIterator(HashMap hashMap);

Bool hasNextHashMapIterator(HashMapIterator iterator);

HashMapIterator nextHashMapIterator(HashMapIterator iterator);

void freeHashMapIterator(HashMapIterator * iterator);

#endif // !_HASHMAPITERATOR

