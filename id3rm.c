#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#ifdef __BIG_ENDIAN__
	#define TAG 0x54414700
	#define ID3 0x49443300
	#define LEN(x) ((x&0x7F000000)>>3|(x&0x7F0000)>>2|(x&0x7F00)>>1|x&0x7F)
#else
	#define TAG 0x00474154
	#define ID3 0x00334449
	#define LEN(x) ((x&0x7F000000)>>24|(x&0x7F0000)>>9|(x&0x7F00)<<6|(x&0x7F)<<21)
#endif
int main(int argc,char**argv){
	for(char**fn=argv+1;*fn;fn++){
		FILE*f=fopen(*fn,"rb+");
		if(!f)continue;
		uint32_t buff=0,buf2=0;
		fread(&buff,3,1,f);
		if(buff==ID3){
			fseek(f,3,SEEK_CUR);
			fread(&buff,4,1,f);
			fseek(f,LEN(buff),SEEK_CUR);
			long rml=ftell(f);
			fseek(f,0,SEEK_END);
			long fln=ftell(f)-rml;
			char*temp=malloc(fln);
			fseek(f,rml,SEEK_SET);
			fread(temp,fln,1,f);
			rewind(f);
			fwrite(temp,fln,1,f);
			free(temp);
			fseek(f,-128,SEEK_CUR);
		}else fseek(f,-128,SEEK_END);
		fread(&buf2,3,1,f);
		buf2=ftell(f)+(buf2==TAG?-3:125);
		fclose(f);
		truncate(*fn,buf2);
	}
}
