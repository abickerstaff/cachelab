#include "cachelab.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

typedef struct {
    // valid bit
    int valid;
    // tag
    int tag;
    // used counter for LRU (Least recently used)
    int count;
} Line;

typedef struct {
    Line* line;

} Set;

typedef struct {
    Set* sets;
    int size_set;
    int size_line;
} Cache;

void printHelp(char* argv[]) {
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

void getSet() {

}

void getTag() {

}

void loadData(Cache *cache, int addr, int size, int setBits, int tageBits, int isVerbose) {

}

void storeData(Cache *cache, int addr, int size, int setBits, int tageBits, int isVerbose) {

}

void modifyData(Cache *cache, int addr, int size, int setBits, int tageBits, int isVerbose) {

}

int isMiss(Cache *cache, int setBits, int tagBits) {

}

void updateLRUCounter(Cache *cache, int setBits, int hitNum) {

}

int updateCache(Cache* cache, int setBits, int tagBits) {

}

int findMinLru(Cache* cache, int setBits) {

}
//misses
int misses;
//hits
int hits;
//evictions
int evictions;

void initCache(int size_set, int size_line, int size_block, Cache* cache) {

    cache->size_set = 2 << size_set;
    cache->size_line = size_line;
    cache.sets = (Set *) malloc(cache->size_set * sizeof (Set));
    if (!cache->sets) {
        printf("Set memory error!\n");
        exit(0);
    }
    //allocate memory for the lines
    for (int j = 0; j < size_set; j++) {
        size_set.Line = (Line *) malloc(sizeof (Line) * size_line);

        for (int i = 0; i < size_line; i++) {
            Line.count = 0;
            Line.tag = 0;
            Line.valid = 0;
        }
    }



}

int
main(int argc, char **argv) {
    printSummary(0, 0, 0);

    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;

    opterr = 0;


    while ((c = getopt(argc, argv, "abc:")) != -1)
        switch (c) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case '?':
                if (optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
                return 1;
            default:
                abort();
        }


    printf("aflag = %d, bflag = %d, cvalue = %s\n",
            aflag, bflag, cvalue);

    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    return 0;
}


