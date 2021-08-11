#include "MainProg.h"

void data(char* filename, segment_table* SegList)
{
	FILE* file = fopen(filename, "rb");

	int i = 0;
	unsigned __int8 byte;
	char Result[ArrSize] = { NULL };

	while (fread(&byte, sizeof(byte), 1, file))
	{	
		switch (byte)
		{
		case 0x1B:
		{
			printf("%X ", byte);
			strcat(Result, "MOV ");

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);

			char tmp[ArrSize] = "";
			if (byte == 1)
			{
				unsigned __int32 Address;
				fread(&Address, sizeof(Address), 1, file);
				printf("%.8X ", Address);
				sprintf(tmp, "[0x%.8X] ", Address);
				strcat(Result, tmp);

				fread(&byte, sizeof(byte), 1, file);
				printf("%X ", byte);
				sprintf(tmp, "R%X ", byte);
				strcat(Result, tmp);

				Address = address_test(Address, SegList);
				break;
			}

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(tmp, "R%X ", byte);
			strcat(Result, tmp);

			unsigned __int32 Address;
			fread(&Address, sizeof(Address), 1, file);
			printf("%.8X ", Address);
			Address = address_test(Address, SegList);
			sprintf(tmp, "[0x%.8X] ", Address);
			strcat(Result, tmp);
			break;
		}
		case 0x20:
		{
			printf("%X ", byte);
			strcat(Result, "MUL ");

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			char tmp[ArrSize] = "";
			sprintf(tmp, "R%X ", byte);
			strcat(Result, tmp);

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(tmp, "R%X ", byte);
			strcat(Result, tmp);

			break;
		}
		case 0x22:
		{
			printf("%X ", byte);
			strcat(Result, "MUL ");

			char tmp[ArrSize] = "";
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(tmp, "R%X ", byte);
			strcat(Result, tmp);

			unsigned __int32 Address;
			fread(&Address, sizeof(Address), 1, file);
			printf("%.8X ", Address);
			Address = address_test(Address, SegList);
			sprintf(tmp, "[0x%.8X] ", Address);
			strcat(Result, tmp);
			break;
		}
		case 0x2A:
		{
			printf("%X ", byte);
			strcat(Result, "DIV ");

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			char tmp[ArrSize] = "";
			sprintf(tmp, "R%X ", byte);
			strcat(Result, tmp);

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(tmp, "R%X ", byte);
			strcat(Result, tmp);
			break;
		}
		case 0x2C:
		{
			printf("%X ", byte);
			strcat(Result, "DIV ");

			char tmp[ArrSize] = "";
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(tmp, "R%X ", byte);
			strcat(Result, tmp);

			unsigned __int32 Address;
			fread(&Address, sizeof(Address), 1, file);
			printf("%.8X ", Address);
			Address = address_test(Address, SegList);
			sprintf(tmp, "[0x%.8X] ", Address);
			strcat(Result, tmp);
			break;
		}
		case 0x1C:
		{
			printf("%X ", byte);
			strcat(Result, "MOV ");

			char tmp[ArrSize] = "";
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			
			switch (byte)
			{
			case 0:
			{
				fread(&byte, sizeof(byte), 1, file);
				printf("%X ", byte);
				sprintf(tmp, "R%X ", byte);
				strcat(Result, tmp);

				fread(&byte, sizeof(byte), 1, file);
				printf("%X ", byte);
				sprintf(tmp, "%d ", byte);
				strcat(Result, tmp);
				break;
			}
			case 1:
			{
				fread(&byte, sizeof(byte), 1, file);
				printf("%X ", byte);
				sprintf(tmp, "R%X ", byte);
				strcat(Result, tmp);

				unsigned __int16 Num_2byte;
				fread(&Num_2byte, sizeof(Num_2byte), 1, file);
				printf("%.4X ", Num_2byte);
				sprintf(tmp, "%d ", Num_2byte);
				strcat(Result, tmp);
				break;
			}
			case 2:
			{
				fread(&byte, sizeof(byte), 1, file);
				printf("%X ", byte);
				sprintf(tmp, "R%X ", byte);
				strcat(Result, tmp);

				unsigned __int32 Num_4byte;
				fread(&Num_4byte, sizeof(Num_4byte), 1, file);
				printf("%.8X ", Num_4byte);
				sprintf(tmp, "%d ", Num_4byte);
				strcat(Result, tmp);
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}

		printf(":\n\t# %s #\n", Result);
		
		for (int j = 0; Result[j]; j++)
			Result[j] = NULL;
	}
	
	fclose(file);
}