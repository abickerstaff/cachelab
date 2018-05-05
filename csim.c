/* Alex Bickerstaff
   Cache Lab Assignment
   Due: 5/5/18
 */

#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

struct Cache {
    long valid;
    long tag;
    long lru;
};

int hit_count = 0;
int miss_count = 0;
int evict_count = 0;

// Setup variables, no help flag as it defaults to the help menu.
// -v: Verbose flag that displays trace info
// -s <s>: Number of set index bits (S = 2s is the number of sets)
// -E <E>: Associativity (number of lines per set)
// -b <b>: Number of block bits (B = 2b is the block size)
// -t <tracefile>: Name of the valgrind trace
int v, s, E, b, size, B;


struct Cache **cache = NULL;

//Create the counter for lru and mask
long mask = 0;
long lruCounter = 0;

void fileTrace(char *fileName);
void print(char* argv);
void initCache();
void cleanCache();
void accessCache(unsigned long address);

/**
 * Run the trace of the valgrind file.
 * @param fileName the filename of the trace
 */
void fileTrace(char *fileName) {
    char buf[1024];


    FILE *fp = fopen(fileName, "r");


    if (fp == NULL) {
        printf("The file cannot be found.\n\n");
        return;
    }


    while (fgets(buf, 1024, fp)) {
        unsigned long address = 0;
        unsigned size = 0;

        //L: Load Data; S: Store Data; M: Modify Data
        if (buf[1] == 'S' || buf[1] == 'L' || buf[1] == 'M') {
            sscanf(buf + 2, "%lx,%u", &address, &size);

            if (v) {
                printf("%c %lx,%u ", buf[1], address, size);
            }

            accessCache(address);


            if (buf[1] == 'M') {
                accessCache(address);
            }

            if (v) {
                putchar('\n');
            }
        }
    }

    fclose(fp);
}

/**
 * Initiate Cache.
 */
void initCache() {
    cache = malloc(size * sizeof (*cache));


    for (int i = 0; i < size; i++) {
        cache[i] = calloc(E, sizeof (*cache[i]));
    }

    mask = size - 1;
}

void accessCache(unsigned long address) {
    long set = (address >> b) & mask;

    long tag = (address >> (b + s));

    int a = 0;

    while (a < E) {

        if (cache[set][a].tag == tag && cache[set][a].valid != 0) {
            hit_count++;
            if (v) {
                printf("hit ");
            }
            cache[set][a].lru = lruCounter++;
            return;
        } else {
            a++;
        }
    }

    miss_count++;

    long lrum = 0xFFFFFFFF;
    int evictL = 0;

    if (v) {
        printf("miss ");
    }

    int i = 0;
    while (i < E) {
        if (lrum > cache[set][i].lru) {
            evictL = i;
            lrum = cache[set][i].lru;
        }
        i++;
    }

    if (cache[set][evictL].valid == 1) {
        evict_count++;
        
        if (v) {
            printf("eviction ");
        }
    }

    cache[set][evictL].valid = 1;
    cache[set][evictL].tag = tag;
    cache[set][evictL].lru = lruCounter++;
}

void cleanCache() {
    free(cache);
}

void print(char * argv) {
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv);
    printf("Options:\n");
    printf(" -h Print this help message.\n");
    printf(" -v Optional verbose flag.\n");
    printf(" -s <num> Number of set index bits.\n");
    printf(" -E <num> Number of lines per set.\n");
    printf(" -b <num> Number of block offset bits.\n");
    printf(" -t <file> Trace file.\n");
    exit(0);
}

int main(int argc, char * argv[]) {
    char opt = 0;
    char *file = NULL;

    while ((opt = getopt(argc, argv, "s:E:b:t:vh")) != -1) {
        switch (opt) {
            case 's':
                s = atoi(optarg);

                if (s == 0) {
                    return 1;
                }
                break;
            case 'E':
                E = atoi(optarg);
                
                if (E == 0) {
                    return 1;
                }
                break;
            case 'b':
                b = atoi(optarg);
                
                if (b == 0) {
                    return 1;
                }
                break;
            case 't':
                file = optarg;
                
                if (file == 0) {
                    return 1;
                }
                break;
            case 'v':
                v = 1;
                
                break;
            default:
                print(argv[0]);
                return 1;
        }
    }

    size = 1 << s;
    B = 1 << b;

    initCache();
    fileTrace(file);
    cleanCache();

    printSummary(hit_count, miss_count, evict_count);
    return 0;
}