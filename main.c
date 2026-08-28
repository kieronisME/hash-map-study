#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DEFULAT_BUCKETS 16
#define THRESHOLD       0.75




typedef struct Entry
{
    void* key;               // how I will find hash
    void* value;             // value within hash
    uint64_t hash;           // the output number that can be used to access data
    struct Entry* next;      // linked list for clashes or collisions whatever they calle them

} Entry;

typedef struct Hashmap
{
    uint64_t bucket_count;
    uint64_t entry_count;

    Entry** buckets_list;          // pointer to pointer that begins linked list 

    uint32_t (*hashing_function)(void* key);        
    uint32_t (*compare_key)(void* key1, void* key2 );  

} Hashmap;



//allocation
Hashmap* allocate_map(uint32_t (*hashing_function)(void* key), uint32_t (*compare_key)(void* key1, void* key2 ));
Hashmap* allocate_buckets(uint32_t number_of_buckets, uint32_t (*hashing_function)(void* key), uint32_t (*compare_key)(void* key1, void* key2 ));
Entry* allocate_new_entry(void* key, uint64_t hash,  void* value);
Hashmap* reallocate_map(Hashmap* hashmap);

//put
Hashmap* put_map(Hashmap* hashmap, void* key, void* value);
Entry* put_with_hash(void* key, void* hash,  void* value);
Hashmap* increase_threshold(uint64_t entry_count,uint32_t (*hashing_function)(void* key), uint32_t (*compare_key)(void* key1, void* key2 ));

//get
Hashmap* get(Hashmap* hashmap, void* key);

//traverse 
void traverse_map(Hashmap* hashmap, void(print_enrty)(void* key, void* value));

// hashing processes 
uint32_t hashing_function(void* key);
uint32_t compare_key(void* key1, void* key2);

//free
void free_hashmap(Hashmap* hashmap);
void free_entry(Entry* hashmap);
//do one to free individual entrys




int main()
{
    printf("gulp \n");


    return 0;
}



Hashmap* allocate_map(uint32_t (*hashing_function)(void* key), uint32_t (*compare_key)(void* key1, void* key2 ))
{
    return allocate_buckets(DEFULAT_BUCKETS,hashing_function, compare_key);
}

Hashmap* allocate_buckets(uint32_t number_of_buckets, uint32_t (*hashing_function)(void* key), uint32_t (*compare_key)(void* key1, void* key2 ))
{
    Hashmap* hashmap;
    hashmap->bucket_count     = number_of_buckets;
    hashmap->entry_count      = 0;
    hashmap->buckets_list     = malloc(number_of_buckets * sizeof(Hashmap));
    hashmap->hashing_function = hashing_function;
    hashmap->compare_key      = compare_key;

    for(int x = 0; x < hashmap->bucket_count; x++ )
    {
        hashmap->buckets_list[x] = NULL;
    }

    return hashmap;
}

Hashmap* increase_threshold(uint64_t entry_count, uint32_t (*hashing_function)(void* key), uint32_t (*compare_key)(void* key1, void* key2 ))
{
    double entry_num   = (double)entry_count;
    double buckets_num = DEFULAT_BUCKETS;

    while(entry_num / buckets_num > THRESHOLD )
    {
        buckets_num *= 2.0;
    }

    return allocate_buckets(buckets_num, hashing_function, compare_key);

}



Hashmap* reallocate_map(Hashmap* hashmap)
{
    // grab bucket size from current hash map
    Hashmap* new_map = increase_threshold(hashmap->entry_count,hashmap->hashing_function,hashmap->compare_key);
    uint64_t new_bucket_count = new_map->bucket_count;

    for(uint64_t x =  0; x < new_bucket_count; x++)
    {
        Entry* current = hashmap->buckets_list[x];

        while(current)
        {
            put_map(new_map, current->key, current->value);
            current = current->next;
        }

    }

    Entry** tmplist = hashmap->buckets_list;
    hashmap->buckets_list = new_map->buckets_list;
    new_map->buckets_list = tmplist;

    // mapentry **tmpList = map->buckets;
    // map->buckets = ret.buckets;
    // ret.buckets = tmpList;



    new_map->bucket_count = hashmap->bucket_count;

    free_hashmap(new_map);
    hashmap->bucket_count = new_bucket_count;
    
}

Entry* allocate_new_entry(void* key, uint64_t hash,  void* value)
{
    Entry* new_map_entry =  malloc(sizeof(Entry)); 
    new_map_entry->hash  = hash;
    new_map_entry->key   = key;
    new_map_entry->value = value;  
    new_map_entry->next  = NULL;     

}


Hashmap* put_map(Hashmap* hashmap, void* key, void* value)
{
    uint64_t index = abs((uint64_t)key) % hashmap->bucket_count; // method makes sure we are within bucket 
    uint64_t hash  = hashmap->hashing_function(key);

    //the new entry
    Entry* new_map_entry =  allocate_new_entry(key, hash, value);

    // does entry index exit already within linked list?
    if(hashmap->buckets_list[index])
    {   
        Entry* current = hashmap->buckets_list[index]; // head is current. current can now access the all Entry members

        while(current->next && hash > current->hash) 
        {
            current = current->next; // take me to the spot in the list where one of the while arguments is not true
        }

        if (hash == current->hash && !hashmap->compare_key(key, current->key))
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



uint32_t hashing_function(void* key)
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

uint32_t compare_key(void* key1, void* key2)
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


void free_hashmap(Hashmap* hashmap)
{

    for (uint64_t x; x < hashmap->bucket_count; x++)
    {
        if(hashmap->buckets_list[x])
        {
            free_entry(hashmap->buckets_list[x]);
            free(hashmap->buckets_list[x]);
        }

    }

    hashmap->bucket_count = 0;
    hashmap->entry_count  = 0;
    free(hashmap->buckets_list);

}

void free_entry(Entry* entry)
{
    if(entry){
        if(entry->next)
        {
            free_entry(entry->next);
            free(entry);
        }
    }
}


void traverse_map(Hashmap* hashmap, void(print_enrty)(void* key, void* value))
{
    for(uint64_t x = 0; x < hashmap->bucket_count; x++)
    {
        Entry* current = hashmap->buckets_list[x];

        while(current)
        {
            print_enrty(current->key, current->value);
            current->next;
        }

    }

}

