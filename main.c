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
Hashmap* get(Hashmap* hashmap, void* key);
Hashmap* put_map(Hashmap* hashmap, void* key, void* value);
Hashmap* free_map(Hashmap* hashmap);
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
    Hashmap* map;
    map->bucket_count   = number_of_buckets;
    map->entry_count    = 0;
    map->buckets_list   = malloc(number_of_buckets * sizeof(Hashmap));
    map->hasingFunction = hasingFunction;
    map->checkKey       = checkKey;

    for(int x = 0; x < map->bucket_count; x++ )
    {
        map->buckets_list[x] = NULL;
    }

    return map;
}

// Hashmap* put(Hashmap* hashmap, void* key, void* value)
// {
// // cooked 
// }

// Hashmap* get(Hashmap* hashmap, void* key)
// {
// // cooked  
// }


// Hashmap* free(Hashmap* hashmap)
// {
// // cooked    
// }

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