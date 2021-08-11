#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#define ArrSize 32

#pragma warning(disable : 4996)

typedef struct segments_table {
	unsigned int Base_address;
	int SegSize;
	int flag;
	int SegmentNum;

	struct segment_table* NextSeg;
} segment_table;


segment_table* parse_segment_table(char* filename);
segment_table* add_segment(int Base_address, int SegSize, int flag, int SegmentNum, segment_table** SegList);
unsigned __int32 read_base_addr(int* AddrArr);
