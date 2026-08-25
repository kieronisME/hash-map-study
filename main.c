#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define DEFULAT_BUCKETS 16
typedef struct 
{
    void* key;               // how I will find hash
    void* value;             // value within hash
    uint64_t hash;           // the output number that can be used to access data
    struct Entry* next;      // linked list for clashes or collisions whatever they calle them

} Entry;


typedef struct 
{
    uint64_t bucket_count;
    uint64_t entry_count;

    Entry** buckets_list;          // pointer to pointer that begins linked list 

    uint32_t (*hasingFunction)(void* key);        
    uint32_t (*checkKey)(void* key1, void* key2 );  

} Hashmap;

Hashmap* allocate_map(uint32_t (*hasingFunction)(void* key), uint32_t (*checkKey)(void* key1, void* key2 ));
Hashmap* allocate_buckets(uint32_t number_of_buckets, uint32_t (*hasingFunction)(void* key), uint32_t (*checkKey)(void* key1, void* key2 ));
Entry* allocate_new_entry(void* key, void* hash,  void* value);
Hashmap* reallocate_map(Hashmap* hashmap);
Entry* put_with_hash(void* key, void* hash,  void* value);
Hashmap* change(uint64_t entry_count,uint32_t (*hasingFunction)(void* key), uint32_t (*checkKey)(void* key1, void* key2 ));
Hashmap* get(Hashmap* hashmap, void* key);
Hashmap* put_map(Hashmap* hashmap, void* key, void* value);
Hashmap* free_hashmap(Hashmap* hashmap);
uint32_t hasingFunction(void* key);
uint32_t checkKey(void* key1, void* key2);












int main()
{
    printf("gulp \n");
    uint32_t keying  = checkKey("damn", "damner");
    uint32_t hashing = hasingFunction("hashmykeyplease");
    printf("key is %d\n hashed key %d", keying,hashing );

    return 0;
}










Hashmap* allocate_map(uint32_t (*hasingFunction)(void* key), uint32_t (*checkKey)(void* key1, void* key2 ))
{
    return allocate_buckets(DEFULAT_BUCKETS,hasingFunction, checkKey);
}

Hashmap* allocate_buckets(uint32_t number_of_buckets, uint32_t (*hasingFunction)(void* key), uint32_t (*checkKey)(void* key1, void* key2 ))
{
    Hashmap* hashmap;
    hashmap->bucket_count   = number_of_buckets;
    hashmap->entry_count    = 0;
    hashmap->buckets_list   = malloc(number_of_buckets * sizeof(Hashmap));
    hashmap->hasingFunction = hasingFunction;
    hashmap->checkKey       = checkKey;

    for(int x = 0; x < hashmap->bucket_count; x++ )
    {
        hashmap->buckets_list[x] = NULL;
    }

    return hashmap;
}

Hashmap* change(uint64_t entry_count,uint32_t (*hasingFunction)(void* key), uint32_t (*checkKey)(void* key1, void* key2 ))
{
    double 

}



Hashmap* reallocate_map(Hashmap* hashmap)
{
    // grab bucket size from current hash map
    Hashmap* new_map = change(hashmap->entry_count,hashmap->hasingFunction,hashmap->checkKey)
    uint64_t new_bucket_count = hashmap->bucket_count;

    //traverse the hashmap and doi what.???

    for(uint64_t x =  0; x < hashmap->bucket_count; x++)
    {
        Entry* current = new_map->buckets_list[x];

        while(current)
        {
            put_map(&new_map, current->key, current->value);
            current = current->next;
        }

    }

    Entry** tmplist = hashmap->buckets_list;
    hashmap->buckets_list = new_map->buckets_list;
    new_map->buckets_list = tmplist;
    new_map->bucket_count = hashmap->bucket_count;

    free_hashmap//do this later


    
}

Entry* allocate_new_entry(void* key, void* hash,  void* value)
{
    Entry* new_map_entry =  malloc(sizeof(Entry)); 
    new_map_entry->hash  = hash;
    new_map_entry->key   = key;
    new_map_entry->value = value;  
    new_map_entry->next  = NULL;     

}


Hashmap* put(Hashmap* hashmap, void* key, void* value)
{
    uint64_t index = abs(key) % hashmap->bucket_count; // method makes sure we are within bucket 
    uint64_t hash  = hashmap->hasingFunction(key);

    //the new entry
    Entry* new_map_entry =  allocate_new_entry(key, hash, value);

    // does entry index exit already within linked list?
    if(hashmap->buckets_list[index])
    {   
        Entry* current = hashmap->buckets_list[index]; // head is current. current can now access the all Entry members

        while(current->next && hash > current->hash) 
        {
            current = current->next; // take me to the top of the list
        }

        if (hash == current->hash && !hashmap->checkKey(key, current->key))
        {   
            // Update
            current->value = value; 
        }
        else
        {
            // Insert
            Entry* temp   = current->next;
            current->next = new_map_entry;
            new_map_entry = temp;

            hashmap->entry_count++;

        }
        
    }
    else
    {
        hashmap->buckets_list[index] = new_map_entry;
        hashmap->bucket_count++;
    }
    
    //check if 75% threshold has been passed 
    double loadfactor = hashmap->entry_count;
    loadfactor       /= (double)hashmap->bucket_count;
    if(loadfactor > DEFULAT_BUCKETS)
    {
        reallocate_map(hashmap);
    }

}

// Hashmap* get(Hashmap* hashmap, void* key)
// {
// // cooked  
// }


Hashmap* free(Hashmap* hashmap)
{

    for (uint64_t x; x < hashmap->bucket_count; x++)
    {
        free(hashmap->buckets_list[x])

    }


}

uint32_t hasingFunction(void* key)
{
    printf("hashing %d\n", key);
    uint32_t the_key = 0;
    if(!key)
    {
        printf("key cannot be %d ending hash\n", key);
        return -1;
    }

    //java hashing method
    char* key_string = (char*) key;
    int strlength    = strlen(key_string);
    for (int x = 0; x < strlength; x++ )
    {
        the_key = key_string[x] + 31 * the_key;
    }

    return the_key;
}

uint32_t checkKey(void* key1, void* key2)
{
    if(!key1)
    {
        if(!key2)
        {
            printf("both keys are empty\n");
            return 0;
        }
    }

    char* key_one = (char*) key1;
    char* key_two = (char*) key2;
    return strcmp(key_one, key_two);
}