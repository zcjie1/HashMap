#include "../include/HashMap.h"
#include "../include/HashMapIterator.h"

HashMap createHashMap(HashCode hashCode, Equal equal){
    HashMap hashMap = newHashMap();
    if(hashMap == NULL){
        return NULL;
    }

    hashMap->size = 0;
	hashMap->listSize = 8;
	hashMap->hashCode = hashCode == NULL ? defaultHashCode : hashCode;
	hashMap->equal = equal == NULL ? defaultEqual : equal;
    hashMap->exists = defaultExists;
	hashMap->get = defaultGet;
	hashMap->put = defaultPut;
	hashMap->remove = defaultRemove;
	hashMap->clear = defaultClear;
	hashMap->autoAssign = True;

    hashMap->list = newEntryList(hashMap->listSize);
	if (hashMap->list == NULL){
		return NULL;
	}

    //initialization
    Entry p = hashMap->list;
	for (int i=0; i<hashMap->listSize; i++) {
		p[i].key = p[i].value = p[i].next = NULL;
	}
	return hashMap;
}


static void resetHashMap(HashMap hashMap, int listSize){

    if(listSize < 8) return;

    uint32_t length = hashMap->size;

    // data tmp
    Entry tempList = newEntryList(length);
    HashMapIterator iterator = createHashMapIterator(hashMap);
	for (int index = 0; hasNextHashMapIterator(iterator); index++) {
		iterator = nextHashMapIterator(iterator);
		tempList[index].key = iterator->entry->key;
		tempList[index].value = iterator->entry->value;
		tempList[index].next = NULL;
	}
	freeHashMapIterator(&iterator);

    // delete conflict chain and erase old data
	for (int i = 0; i < hashMap->listSize; i++) {
		Entry current = &hashMap->list[i];
		current->key = NULL;
		current->value = NULL;
		if (current->next != NULL) {
			while (current->next != NULL) {
				Entry temp = current->next->next;
				free(current->next);
				current->next = temp;
			}
		}
	}

    //reallocate
	Entry relist = (Entry)realloc(hashMap->list, listSize * sizeof(struct entry));

	if (relist != NULL){
		hashMap->list = relist;
		relist = NULL;
        hashMap->listSize = listSize;
	}

    //init
    for (int i = 0; i < hashMap->listSize; i++) {
		hashMap->list[i].key = NULL;
		hashMap->list[i].value = NULL;
		hashMap->list[i].next = NULL;
	}

    // load tmp data
    hashMap->size = 0;
    for (int i = 0; i < length; i++) {
		hashMap->put(hashMap, tempList[i].key, tempList[i].value);
	}
	free(tempList);
}


static int defaultHashCode(HashMap hashMap, void* key){
    uint8_t* k = (uint8_t*)key;
    uint16_t crc = CRC16_Calculate(k);
    return (crc % hashMap->listSize);
}


static Bool defaultEqual(void* key1, void* key2){
    return strcmp((char*)key1, (char*)key2) ? False : True;
}


static void defaultPut(HashMap hashMap, void* key, void* value){
    uint32_t index = hashMap->hashCode(hashMap, key);
    if (hashMap->list[index].key == NULL){
		hashMap->size++;
		hashMap->list[index].key = key;
		hashMap->list[index].value = value;
	}
    else{
        Entry current = &hashMap->list[index];
		while (current != NULL) {
			if (hashMap->equal(key, current->key)) {
				current->value = value;
				return;
			}
			current = current->next;
		};

        //conflict, insert node to head
        Entry entry = newEntry();
		entry->key = key;
		entry->value = value;
		entry->next = hashMap->list[index].next;
		hashMap->list[index].next = entry;
		hashMap->size++;
    }

    // enlarge capacity
    if(hashMap->autoAssign && hashMap->size >= 2*hashMap->listSize){
        resetHashMap(hashMap, hashMap->listSize * 2);
    }
}


static Bool defaultExists(HashMap hashMap, void* key){
    uint32_t index = hashMap->hashCode(hashMap, key);
	Entry entry = &hashMap->list[index];
	if (entry->key == NULL) {
		return False;
	}
	else {
		while (entry != NULL) {
			if (hashMap->equal(entry->key, key)) {
				return True;
			}
			entry = entry->next;
		}
		return False;
	}
}


static void* defaultGet(HashMap hashMap, void* key){
    if (hashMap->exists(hashMap, key)) {
		uint32_t index = hashMap->hashCode(hashMap, key);
		Entry entry = &hashMap->list[index];
		while (entry != NULL) {
			if (hashMap->equal(entry->key, key)) {
				return entry->value;
			}
			entry = entry->next;
		}
	}
	return NULL;
}


static void* defaultRemove(HashMap hashMap, void* key){
    Bool HaveKey = False;
    uint32_t index = hashMap->hashCode(hashMap, key);
	Entry entry = &hashMap->list[index];
	if (entry->key == NULL) {
		return NULL;
	}

    void *entryKey = entry->key;
    if (hashMap->equal(entry->key, key)) {
		hashMap->size--;
		if (entry->next != NULL) {
			Entry temp = entry->next;
			entry->key = temp->key;
			entry->value = temp->value;
			entry->next = temp->next;
			free(temp);
            HaveKey = True;
		}
        else {
            entry->key = NULL;
            entry->value = NULL;
        }
        HaveKey = True;
	}
    else{
        Entry pre_entry = entry;
        entry = entry->next;
        while(entry != NULL){
            if (hashMap->equal(entry->key, key)){
				hashMap->size--;
				pre_entry->next = entry->next;
				free(entry);
                HaveKey = True;
				break;
			}
            pre_entry = entry;
            entry = entry->next;
        }
    }

    if (HaveKey && hashMap->autoAssign && hashMap->size < hashMap->listSize/3){
		resetHashMap(hashMap, hashMap->listSize/2);
        return entryKey;
	}
    
    if(HaveKey) return entryKey;
    return NULL;
}


static void defaultClear(HashMap hashMap){
    for (int i = 0; i < hashMap->listSize; i++){
		Entry entry = hashMap->list[i].next;
		while (entry != NULL) {
			Entry next = entry->next;
			free(entry);
			entry = next;
		}
		hashMap->list[i].next = NULL;
	}
	free(hashMap->list);
	hashMap->list = NULL;
	hashMap->size = -1;
	hashMap->listSize = 0;
}