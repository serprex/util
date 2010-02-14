//Original by Craig Stuart Sapp <craig@ccrma.stanford.edu>
//Original at http://www-ccrma.stanford.edu/~craig/utility/flip/flip.cpp
#include <stdio.h>
int main(int argc,char**argv){
	argv[0]=tmpnam(0);
	if(argv[1][0]=='-') argv[1]++;
	if(argc<3) puts("Convert newline format\n\nu NIX\nd DOS\nm MAC\n? ???\nsn \\t->n spaces\ntn n spaces->\\t");
	else for(int ch,i=2;i<argc;i++){
		FILE*rame=fopen(argv[i],"rb");
		if(!rame) printf("? %s\n",argv[i]);
		else if(argv[1][0]=='?'){
			printf("%s: ",argv[i]);
			while((ch=getc(rame))!=0xa&&ch!=0xd&&ch!=EOF);
			puts(ch==0xa?"NIX":ch==EOF?"???":(getc(rame)==0xa?"DOS":"MAC"));
			fclose(rame);
		}else{
			FILE*wame=fopen(argv[0],"wb");
			int ch0d=0,chsp='0';
			while((ch=getc(rame))!=EOF){
				switch(argv[1][0]){
				case'd':
					if(ch==0xd||(ch==0xa&&!ch0d)){
						putc(0xd,wame);
						putc(0xa,wame);
					}else if(ch!=0xa) putc(ch,wame);
				break;case'm':
					if(ch!=0xa) putc(ch,wame);
					else if(!ch0d) putc(0xd,wame);
				break;case'u':putc(ch==0xd?0xa:ch,wame);
				break;case's':
					if(ch!='\t') putc(ch,wame);
					else for(chsp=argv[1][1];chsp>'0';chsp--) putc(' ',wame);
				break;case't':
					if(ch!=' '){
						for(;chsp>'0';chsp--) putc(' ',wame);
						putc(ch,wame);
					}else if(++chsp==argv[1][1]){
						chsp='0';
						putc('\t',wame);
					}
				ch0d=ch==0xd;
				}
			}
			fclose(wame);
			fclose(rame);
			remove(argv[i]);
			rename(argv[0],argv[i]);
		}
	}
	return 0;
}
