//Original by Craig Stuart Sapp <craig@ccrma.stanford.edu>
//Original at http://www-ccrma.stanford.edu/~craig/utility/flip/flip.cpp
#include <stdio.h>
int main(int argc,char**argv){
	char*argv1,*temp=tmpnam(0);
	if(argc<3) puts("Convert whitespace\nu NIX\nd DOS\nm MAC\n? ???\nsn \\t->n spaces\ntn n spaces->\\t");
	else for(int ch,i=(argv1=argv[1]+(argv[1][0]=='-'),2);i<argc;i++){
		FILE*rame=fopen(argv[i],"rb");
		if(!rame) printf("? %s\n",argv[i]);
		else if(argv1[0]=='?'){
			while((ch=getc(rame))!=0xa&&ch!=0xd&&ch!=EOF);
			printf("%s: %s\n",argv[i],ch==0xa?"NIX":ch==EOF?"???":(getc(rame)==0xa?"DOS":"MAC"));
			fclose(rame);
		}else{
			FILE*wame=fopen(temp,"wb");
			int ch0d=0;
			while((ch=getc(rame))!=EOF){
				switch(argv1[0]){
				case'd':
					if(ch==0xd||(ch==0xa&&!ch0d)){
						putc(0xd,wame);
						putc(0xa,wame);
					}else if(ch!=0xa) putc(ch,wame);
				break;case'm':
					if(ch!=0xa) putc(ch,wame);
					else if(!ch0d) putc(0xd,wame);
				break;case'u':
					if(!ch0d) putc(ch==0xd?0xa:ch,wame);
				break;case's':
					if(ch!='\t') putc(ch,wame);
					else for(ch0d=argv1[1]-48;ch0d;ch0d--) putc(' ',wame);
				continue;case't':
					if(ch!=' '){
						for(;ch0d;ch0d--) putc(' ',wame);
						putc(ch,wame);
					}else if(++ch0d==(argv1[1]-48)){
						ch0d=0;
						putc('\t',wame);
					}
					continue;
				}
				ch0d=ch==0xd;
			}
			fclose(wame);
			fclose(rame);
			remove(argv[i]);
			rename(temp,argv[i]);
		}
	}
}
