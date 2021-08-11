#include "MainProg.h"

int main() {
	segment_table* seg = NULL;

	seg = parse_segment_table("segments.csv");
	
	data("myfile.dat", seg);
	
	return 0;
}