#include "stdio.h"
#include "stdlib.h"

int main()
{
	FILE *f = fopen("dump.bin", "rb");

	if(f != NULL)
	{
		fseek(f, 0, SEEK_END);
		long len;
		fgetpos(f, &len);
		fseek(f, 0, SEEK_SET);

		unsigned long long *memData = malloc(len);
		fread(memData, 1, len, f);

		unsigned long long pos = 0;
		unsigned long long expected_len = 0;
		while(pos < len / 8)
		{
			if(memData[pos] == 0xDEADBEEFCAFEBABE){
				if(memData[pos + 2] != 0xDEADBEEFCAFEBABE)printf("Error: Offset %x Header\n", pos * 8);
				
				expected_len = memData[pos + 1];
				printf("Found Valid Header: %x, Length: %x\n", pos * 8, expected_len);

				if(memData[pos + expected_len/8 + 3] != 0xDEADC0DEB00B1EE5 | memData[pos + expected_len/8 + 5] != 0xDEADC0DEB00B1EE5 | memData[pos + expected_len/8 + 4] != expected_len)
				{
					printf("Error: Offset %x Footer\n", 8 * pos + expected_len + 3 * 8);
				}else{
					pos = pos + expected_len/8 + 5;
					printf("Found Valid Footer: %x, Length: %x\n", pos * 8 - 24, expected_len);
				}
			}
			else pos++;
		}


		fclose(f);
	}

	return 0;
}