#include "Address.h"
#define BIN8(x) BIN___(0##x)
#define BIN___(x)                                    \
	(                                                \
	((x / 01ul) % 010)*(2>>1) +                      \
	((x / 010ul) % 010)*(2<<0) +                     \
	((x / 0100ul) % 010)*(2<<1) +                    \
	((x / 01000ul) % 010)*(2<<2) +                   \
	((x / 010000ul) % 010)*(2<<3) +                  \
	((x / 0100000ul) % 010)*(2<<4) +                 \
	((x / 01000000ul) % 010)*(2<<5) +                \
	((x / 010000000ul) % 010)*(2<<6) +               \
	((x / 0100000000ul) % 010)*(2<<7)                \
	)

#define BIN16(x1,x2) \
    ((BIN___(x1)<<8)+BIN___(x2))

#define BIN32(x1,x2,x3,x4) \
    ((BIN___(x1)<<24)+(BIN___(x2)<<16)+(BIN___(x3)<<8)+BIN___(x4))

int address_test(unsigned __int32 VirtAddr, segment_table* SegList)
{
	segment_table* SegPtr = SegList;
	unsigned __int32 SegNum = VirtAddr;
	SegNum = (SegNum >> 8);

	if ((0 > SegNum)||(SegNum >= 7))
	{
		printf("\n!Error: Convertation of adress [0x%.8X] failed, because segment '%d' dosen't exist!", VirtAddr, SegNum);
		return VirtAddr;
	}
	else
	{
		while (SegPtr->NextSeg)
		{
			if (SegPtr->SegmentNum == SegNum)
				break;
			SegPtr = SegPtr->NextSeg;
		}
	}
	
	if (SegPtr->flag == 0)
	{
		printf("\n!Error: Convertation of adress [0x%.8X] failed, because segment is '%d' empty!", VirtAddr, SegPtr->SegmentNum);
		return VirtAddr;
	}
	else
	{
		long Shift = BIN32(000000000, 000000000, 000000000, 011111111);
		unsigned __int32 SegShift = (VirtAddr & Shift);
		SegShift += SegPtr->Base_address;

		if (SegShift > SegPtr->SegSize)
		{
			printf("\n!Error: Convertation of adress [0x%.8X] failed, because shift '%d' is too big for this segment(%d)!", VirtAddr, SegShift, SegPtr->SegSize);
			return VirtAddr;
		}
		
		return SegShift;
	}
}
