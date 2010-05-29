#include <stdio.h>
#include <stdlib.h>
int main(int argc,char**argv){
	FILE*rand=fopen("/dev/urandom","rb"),*in=argc==1?stdin:fopen(argv[1],"r");
	char*m=malloc(65536);
	size_t mp=0,nls=1;
	for(int c;(c=getc(in))!=EOF;){
		if(c=='\n'){
			nls++;
			m[mp++]=0;
		}else m[mp++]=c;
		if(!(mp&0xFFFF)) m=realloc(m,mp+65536);
	}
	m=realloc(m,mp+1);
	m[mp]=0;
	char*nlp[nls],**np=nlp+1;
	*nlp=m;
	while(np-nlp!=nls){
		while(*m++);
		*np++=m;
	}
	for(;;){
		size_t rant;
		do fread(&rant,sizeof(rant),1,rand); while(rant==-1);
		puts(nlp[(size_t)((rant/(double)(size_t)-1)*nls)]);
	}
}
