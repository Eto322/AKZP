#include "Tables.h"

segment_table* parse_segment_table(char* filename)
{
	segment_table* Head = NULL;
	segment_table* SegList = NULL;

	FILE* file = fopen(filename, "r");
	int SegNum = 0;
	char Buff[ArrSize];
	char* TablePath = (char*)malloc(sizeof(char) * ArrSize);
	while (fgets(Buff, ArrSize, file))
	{
		char* token = strtok(Buff, ";");
		unsigned int str[8] = { NULL };
		for (int i = 0; token[i]; i++)
		{
			if (((unsigned int)token[i] >= 65) && ((unsigned int)token[i] <= 70))
			{
				str[i] = (unsigned int)token[i] - 'A' + 10;
			}
			else {
				str[i] = (unsigned int)token[i] - '0';
			}
		}
		
		unsigned __int32 BaseAddr = read_base_addr(str);
		token = strtok(NULL, ";");
		char* SegSize = token;
		token = strtok(NULL, ";");
		char* Flag = token;

		add_segment(BaseAddr, atoi(SegSize), atoi(Flag), SegNum, &SegList);
		SegNum++;

		if (Head == NULL)
			Head = SegList;
	}
	fclose(file);
	return Head;
}

unsigned __int32 read_base_addr(int* AddrArr)
{
	unsigned __int32 result = 0; 
	int j = 7;
	for (int i = 0; i < 8; i++)
	{
		result += (unsigned int)AddrArr[i] * pow(16 , j);
		j--;
	}
	
	return result;
}

segment_table* add_segment(int Base_address, int SegSize, int Flag, int SegmentNum, segment_table** SegList)
{
	segment_table* Ptr = *SegList;
	if (*SegList == NULL)
		(*SegList) = (segment_table*)malloc(sizeof(segment_table));
	else
	{
		while (Ptr->NextSeg)
			Ptr = Ptr->NextSeg;
	}
	Ptr = (segment_table*)malloc(sizeof(segment_table));

	Ptr->Base_address = Base_address;
	Ptr->SegSize = SegSize;
	Ptr->flag = Flag;
	Ptr->SegmentNum = SegmentNum;
	Ptr->NextSeg = NULL;
	(*SegList)->NextSeg = Ptr;
	(*SegList) = Ptr;

	return (*SegList);
}
