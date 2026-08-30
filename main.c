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
    uint32_t (*compare_keys)(void* key1, void* key2 );  

} Hashmap;



//allocation
Hashmap* allocate_map(uint32_t (*hashing_function)(void* key), uint32_t (*compare_keys)(void* key1, void* key2 ));
Hashmap* allocate_buckets(uint32_t number_of_buckets, uint32_t (*hashing_function)(void* key), uint32_t (*compare_keys)(void* key1, void* key2 ));
Entry* allocate_new_entry(void* key, uint64_t hash,  void* value);
void reallocate_map(Hashmap* hashmap);
Hashmap* allocatestr();

//put
void* put_map(Hashmap* hashmap, void* key, void* value);
Hashmap* increase_threshold(uint64_t entry_count,uint32_t (*hashing_function)(void* key), uint32_t (*compare_keys)(void* key1, void* key2 ));

//get
void* get(Hashmap* hashmap, void* key);
Entry* get_entry(Hashmap* hashmap, void* key);

//traverse 
void traverse_map(Hashmap* hashmap, void(print_enrty)(void* key, void* value));

// hashing processes 
uint32_t hashing_function(void* key);
uint32_t compare_keys(void* key1, void* key2);

//free
void free_hashmap(Hashmap* hashmap);
void free_entry(Entry* hashmap);
//do one to free individual entrys




int main()
{
    printf("gulp \n");

    Hashmap* the_hash_map = allocatestr();

    put_map(the_hash_map, "key1","super cool value stored in key 1");
    put_map(the_hash_map, "key2","at 2");
    put_map(the_hash_map, "key3","at 3");
    put_map(the_hash_map, "key4","at 4");
    put_map(the_hash_map, "key5","at 5");
    put_map(the_hash_map, "key6","at 6");
    put_map(the_hash_map, "key7","at 7");
    put_map(the_hash_map, "key8","at 8");
    put_map(the_hash_map, "key9","at 9");
    put_map(the_hash_map, "key10","at 10");
    put_map(the_hash_map, "key11","at 11");
    put_map(the_hash_map, "key12","at 12");
    put_map(the_hash_map, "key13","at 13");
    put_map(the_hash_map, "key14","at 14");
    put_map(the_hash_map, "key15","at 15");
    put_map(the_hash_map, "key16","at 16");
    put_map(the_hash_map, "key17","at 17");
    put_map(the_hash_map, "key18","at 18");
    put_map(the_hash_map, "key19","at 19");
    put_map(the_hash_map, "key20","at 20");
    put_map(the_hash_map, "key21","at 21");
    put_map(the_hash_map, "key22","at 22");

    void* value1 = get(the_hash_map, "key1");
    void* value2 = get(the_hash_map, "key2");
    void* value3 = get(the_hash_map, "key3");
    void* value4 = get(the_hash_map, "key4");
    void* value5 = get(the_hash_map, "key5");
    void* value6 = get(the_hash_map, "key6");
    void* value7 = get(the_hash_map, "key7");
    void* value8 = get(the_hash_map, "key8");
    void* value9 = get(the_hash_map, "key9");
    void* value10 = get(the_hash_map, "key10");
    void* value11 = get(the_hash_map, "key11");
    void* value12 = get(the_hash_map, "key12");
    void* value13 = get(the_hash_map, "key13");
    void* value14 = get(the_hash_map, "key14");
    void* value15 = get(the_hash_map, "key15");
    void* value16 = get(the_hash_map, "key16");
    void* value17 = get(the_hash_map, "key17");
    void* value18 = get(the_hash_map, "key18");
    void* value19 = get(the_hash_map, "key19");
    void* value20 = get(the_hash_map, "key12");
    void* value21 = get(the_hash_map, "key21");
    void* value22 = get(the_hash_map, "key22");
    

    printf("\n\nkey 1: %s ", value1 ? (char*)value1 : "NULL");
    printf("\nkey 2: %s ", value2 ? (char*)value2 : "NULL");
    printf("\nkey 3: %s ", value3 ? (char*)value3 : "NULL");
    printf("\nkey 4: %s ", value4 ? (char*)value4 : "NULL");
    printf("\nkey 5: %s ", value5 ? (char*)value5 : "NULL");
    printf("\nkey 6: %s ", value6 ? (char*)value6 : "NULL");
    printf("\nkey 7: %s ", value7 ? (char*)value7 : "NULL");
    printf("\nkey 8: %s ", value8 ? (char*)value8 : "NULL");
    printf("\nkey 9: %s ", value9 ? (char*)value9 : "NULL");
    printf("\nkey 10: %s ", value10 ? (char*)value10 : "NULL");
    printf("\nkey 11: %s ", value11 ? (char*)value11 : "NULL");
    printf("\nkey 12: %s ", value12 ? (char*)value12 : "NULL");
    printf("\nkey 13: %s ", value13 ? (char*)value13 : "NULL");
    printf("\nkey 14: %s ", value14 ? (char*)value14 : "NULL");
    printf("\nkey 15: %s ", value15 ? (char*)value15 : "NULL");
    printf("\nkey 16: %s ", value16 ? (char*)value16 : "NULL");
    printf("\nkey 17: %s ", value17 ? (char*)value17 : "NULL");
    printf("\nkey 18: %s ", value18 ? (char*)value18 : "NULL");
    printf("\nkey 19: %s ", value19 ? (char*)value19 : "NULL");
    printf("\nkey 20: %s ", value20 ? (char*)value20 : "NULL");
    printf("\nkey 21: %s ", value21 ? (char*)value21 : "NULL");
    printf("\nkey 22: %s ", value22 ? (char*)value22 : "NULL");

    free_hashmap(the_hash_map);
    return 0;
}







Hashmap* allocatestr()
{
    return allocate_map(hashing_function, compare_keys);
}
Hashmap* allocate_map(uint32_t (*hashing_function)(void* key), uint32_t (*compare_keys)(void* key1, void* key2 ))
{
    return allocate_buckets(DEFULAT_BUCKETS,hashing_function, compare_keys);
}

Hashmap* allocate_buckets(uint32_t number_of_buckets, uint32_t (*hashing_function)(void* key), uint32_t (*compare_keys)(void* key1, void* key2 ))
{
    if(!number_of_buckets)
    {
        number_of_buckets = DEFULAT_BUCKETS;
    }


    Hashmap* hashmap = malloc(sizeof(Hashmap));
    if(hashmap == NULL)
    {
        printf("malloc failed within allocate_buckets\n");
        return NULL;

    }
    hashmap->bucket_count     = number_of_buckets;
    hashmap->entry_count      = 0;
    hashmap->buckets_list     = malloc(number_of_buckets * sizeof(Entry*));
    if(hashmap->buckets_list == NULL)
    {
        printf("\nmalloc failed within allocate_buckets during hashmap->buckets_list allocation\n");
        return NULL;

    }

    hashmap->hashing_function = hashing_function;
    hashmap->compare_keys      = compare_keys;

    uint64_t count = 0;
    printf("bucket count: ");
    for(int x = 0; x < hashmap->bucket_count; x++ )
    {
        printf(" %d", count);
        hashmap->buckets_list[x] = NULL;
        count++;
    }
    return hashmap;
}

Hashmap* increase_threshold(uint64_t entry_count, uint32_t (*hashing_function)(void* key), uint32_t (*compare_keys)(void* key1, void* key2 ))
{
    double entry_num   = (double)entry_count;
    double buckets_num = DEFULAT_BUCKETS; // this is going to be a problem. after this fucntion runs once this line won't work

    while(entry_num / buckets_num > THRESHOLD )
    {
        buckets_num *= 2.0;
    }
    printf("\nincreased bucket count to %d\n", buckets_num);
    return allocate_buckets(buckets_num, hashing_function, compare_keys);

}



void reallocate_map(Hashmap* hashmap)
{
    printf("\nbucket of %d has been bocken attempting to increase bucket count", hashmap->bucket_count);
    // grab bucket size from current hash map
    Hashmap* new_map = increase_threshold(hashmap->entry_count,hashmap->hashing_function,hashmap->compare_keys);
    uint64_t new_bucket_count = new_map->bucket_count;

    for(uint64_t x =  0; x <  hashmap->bucket_count; x++)
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

    new_map->bucket_count = hashmap->bucket_count;

    free_hashmap(new_map);
    hashmap->bucket_count = new_bucket_count;

}

Entry* allocate_new_entry(void* key, uint64_t hash,  void* value)
{
    Entry* new_map_entry = malloc(sizeof(Entry)); 
    new_map_entry->hash  = hash;
    new_map_entry->key   = key;
    new_map_entry->value = value;  
    new_map_entry->next  = NULL;     
    return new_map_entry;
}


void* put_map(Hashmap* hashmap, void* key, void* value)
{
    uint64_t hash  = hashmap->hashing_function(key);
    uint64_t index = (uint64_t)hash % hashmap->bucket_count; // method makes sure we are within bucket 


    //the new entry
    Entry* new_map_entry =  allocate_new_entry(key, hash, value);

    // does entry index exist already within linked list?
    if(hashmap->buckets_list[index])
    {   
        Entry* current = hashmap->buckets_list[index]; // head is current. current can now access the all Entry members

        while(current->next && hash > current->hash) 
        {
            current = current->next; // take me to the spot in the list where one of the while arguments is not true
        }

        if (hash == current->hash && !hashmap->compare_keys(key, current->key))
        {   
            // Update
            current->value = value; 
        }
        else
        {
            // Insert
            // Entry* temp   = current->next;
            // current->next = new_map_entry;
            // new_map_entry = temp;

            new_map_entry->next = current->next;  
            current->next = new_map_entry;    
   

            hashmap->entry_count++;

        }
        
    }
    else
    {
        hashmap->buckets_list[index] = new_map_entry;
        hashmap->entry_count++;
    }
    
    //check if 75% threshold has been passed 
    double loadfactor = hashmap->entry_count;
    loadfactor       /= (double)hashmap->bucket_count;
    if(loadfactor > THRESHOLD)
    {
        reallocate_map(hashmap);
    }
}

void* get(Hashmap* hashmap, void* key)
{
    Entry* entry = get_entry(hashmap, key);

    return entry ? entry->value : NULL;

}

Entry* get_entry(Hashmap* hashmap, void* key)
{
    uint64_t hash  = hashmap->hashing_function(key);
    uint64_t index = (uint64_t)hash % hashmap->bucket_count; 

    if(hashmap->buckets_list[index])
    {
        Entry* current = hashmap->buckets_list[index];

        while(current)
        {   
            //is current still within the bucket?
            if (hash > current->hash)
            {
                current =  NULL;
                break;

            }

            //is current at the exact entry needed?
            if(hash == current->hash && !hashmap->compare_keys(key, current->key))
            {
                break;
            }

            current = current->next;

        }

        return current;

    }
    else
    {
        printf("get entry returned null due to index being %d", hashmap->buckets_list[index]);
        return NULL;
    }

}


uint32_t hashing_function(void* key)
{
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

uint32_t compare_keys(void* key1, void* key2)
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

    printf("\nfreeing hash map");
    for (uint64_t x = 0; x < hashmap->bucket_count; x++)
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
    printf("\nhash map freeded ");
}

void free_entry(Entry* entry)
{
    if(entry){
        if(entry->next)
        {
            free_entry(entry->next);
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

