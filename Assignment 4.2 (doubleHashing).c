#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
    int comparison=0;
    int index = hash1(key);
    int increment = hash2(key);
    int emptyIndex = -1;
    int test;

    for(test=0;test<TABLESIZE;test++){
        if(hashTable[test].key == key && hashTable[test].indicator == USED) return -1;
    }
    
    int i = index;
    while(hashTable[index].indicator!=EMPTY){
        if(hashTable[index].indicator==USED){
            comparison++;
            if(hashTable[index].key == key) return -1;
        }
        if(hashTable[index].indicator!=USED && emptyIndex == -1){
            emptyIndex = index;
        }
        index = (index + increment) % TABLESIZE;
        if(i==index) break;
    }
    if(emptyIndex!=-1){
        hashTable[emptyIndex].key = key;
        hashTable[emptyIndex].indicator = USED;
        return comparison;
    }


    if (hashTable[index].indicator != USED) {
        hashTable[index].key = key;
        hashTable[index].indicator = USED;
        return comparison;
    }

    while (comparison<TABLESIZE) {        
        index = (index + increment) % TABLESIZE;
        comparison++;
        if (hashTable[index].indicator != USED) {
            hashTable[index].key = key;
            hashTable[index].indicator = USED;
            return comparison;
        }
    }
    return TABLESIZE;
}

int HashDelete(int key, HashSlot hashTable[])
{
    int collisions=1;
    int index = hash1(key);
    int increment = hash2(key);

    if (hashTable[index].key == key && hashTable[index].indicator == USED) {
        hashTable[index].indicator = DELETED;
        return collisions;
    }

    while (collisions<TABLESIZE) {
        index = (index + increment) % TABLESIZE;
        collisions++;
        
        if(hashTable[index].key == key && hashTable[index].indicator == USED){
            hashTable[index].indicator = DELETED;
            return collisions;
        }

        if(hashTable[index].indicator == EMPTY) return -1;
    }
    return -1;   
}
