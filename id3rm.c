#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#ifdef __BIG_ENDIAN__
	#define TAG 0x54414700
	#define ID3 0x49443300
	#define LEN(x) (((x&0x7F000000)>>3)|((x&0x7F0000)>>2)|((x&0x7F00)>>1)|(x&0x7F))
#else//__LITTLE_ENDIAN__
	#define TAG 0x00474154
	#define ID3 0x00334449
	#define LEN(x) (((x&0x7F000000)>>24)|((x&0x7F0000)>>9)|((x&0x7F00)<<6)|((x&0x7F)<<21))
#endif
char temp[65536];
int main(int argc,char**argv){
	for(char**fn=argv+1;*fn;fn++){
		FILE*f=fopen(*fn,"rb+");
		uint32_t buff=0;
		if(!fseek(f,-128,SEEK_END)){
			fread(&buff,3,1,f);
			if(buff==TAG) truncate(*fn,ftell(f)-3);
			rewind(f);
		}
		fread(&buff,3,1,f);
		if(buff==ID3){
			fseek(f,3,SEEK_CUR);
			fread(&buff,4,1,f);
			fseek(f,LEN(buff),SEEK_CUR);
			long rml=ftell(f),ffl=0,tpl;
			do{
				ffl+=tpl=fread(temp,1,sizeof(temp),f);
				fseek(f,-rml-tpl,SEEK_CUR);
				fwrite(temp,1,tpl,f);
				fseek(f,rml,SEEK_CUR);
			}while(tpl==sizeof(temp));
			truncate(*fn,ffl);
		}

	}
}
