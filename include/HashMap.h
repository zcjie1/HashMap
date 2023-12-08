#ifndef _HASH_MAP_H
#define _HASH_MAP_H

#include "./DataStruct.h"
#include "./HashFunction.h"
#include "./util.h"

//key-value node
typedef struct entry{
	void* key;				
	void* value;			
	struct entry* next;	// conflict chain
}*Entry;

#define newEntry() NEW(struct entry)
#define newEntryList(length) (Entry)malloc(length * sizeof(struct entry))

//HashMap struct
typedef struct hashMap *HashMap;

#define newHashMap() NEW(struct hashMap)

// hash function
typedef int(*HashCode)(HashMap, void* key);

// is euqal?
typedef Bool(*Equal)(void* key1, void* key2);

// add node
typedef void(*Put)(HashMap hashMap, void* key, void* value);

// get value
typedef void*(*Get)(HashMap hashMap, void* key);

// devoid*e node
typedef void*(*Remove)(HashMap hashMap, void* key);

// clear HashMap
typedef void(*Clear)(HashMap hashMap);

// have key?
typedef Bool(*Exists)(HashMap hashMap, void* key);

typedef struct hashMap {
	uint32_t size;			// key-value size, -1 represents list is NULL
	uint32_t listSize;		// array size
	HashCode hashCode;	// hash function
	Equal equal;		
	Entry list;			// head node of array
	Put put;			
	Get get;			
	Remove remove;		
	Clear clear;		
	Exists exists;		
	Bool autoAssign;	// whether dynamically adjust capacity, default true
}*HashMap;

static int defaultHashCode(HashMap hashMap, void* key);

static Bool defaultEqual(void* key1, void* key2);

static void defaultPut(HashMap hashMap, void* key, void* value);

static void* defaultGet(HashMap hashMap, void* key);

static void* defaultRemove(HashMap hashMap, void* key);

// whether key exists
static Bool defaultExists(HashMap hashMap, void* key);

static void defaultClear(HashMap hashMap);

static void resetHashMap(HashMap hashMap, int listSize);

// return NULL when fail
HashMap createHashMap(HashCode hashCode, Equal equal);

#endif
