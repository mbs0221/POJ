#define __EDG__ 1 // 由于所用VS2015出现问题，需要加上该宏才能顺利编译文件

#include <stdio.h>
#include <string.h>

#define TOHEX(S, D)		if (S>='A'&&S<='F')D=S-'A'+10;else D=S-'0';
#define TOCHAR(S, D)	if (S>=10&&S<=15)D=S+'A'-10;else D=S+'0';
#define ADDR()			(M[PC+1]<<4)+M[PC+2]

int main(){
	size_t PC, L;
	char S[257];
	unsigned char C, B, A, M[257];
	while (gets_s(S, 257)){
		if (S[0] == '8')break;
		L=strlen(S);
		for (PC=0;PC<L;PC++) TOHEX(S[PC], M[PC]);
		B=A=PC=0x00;
		while (M[PC] != 8){
			switch (M[PC]){
			case 0:A=M[ADDR()];PC += 3;break;
			case 1:M[ADDR()]=A;PC += 3;break;
			case 2:C=A;A=B;B=C;PC++;break;
			case 3:C=A+B;B=C>>4;A=C&0x0F;PC++;break;
			case 4:A++;A &= 0x0F;PC++;break;
			case 5:A--;A &= 0x0F;PC++;break;
			case 6:if (A) PC += 3;else PC=ADDR();break;
			case 7:PC=ADDR();break;
			default:PC++;break;
			}
		}
		for (PC=0;PC < 257;PC++) TOCHAR(M[PC], S[PC]);
		S[256]=0;
		printf("%s\n", S);
	}
	return 0;
}