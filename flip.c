// Original by Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Original at http://www-ccrma.stanford.edu/~craig/utility/flip/flip.cpp
#include <stdio.h>
int main(int argc,char**argv){
	char*temp=tmpnam(0);
	if(argc<3||(argv[1][1]!='u'&&argv[1][1]!='d'&&argv[1][1]!='t'&&argv[1][1]!='m')) puts("Convert newline format\n\n-u NIX\n -d DOS\n -m MAC\n -t ???");
	else for(int ch,i=2;i<argc;i++){
		FILE*rame=fopen(argv[i],"rb");
		if(!rame){
			printf("? %s\n",argv[i]);
			continue;
		}
		if(argv[1][1]=='t'){
			printf("%s: ",argv[i]);
			while((ch=getc(rame))!=EOF){
				if(ch==0xa){
					puts("NIX");
					goto nextt;
				}
				if(ch==0xd){
					puts(getc(rame)==0xa?"DOS":"MAC");
					goto nextt;
				}
			}
			puts("???");
			nextt:fclose(rame);
		}else{
			FILE*wame=fopen(temp,"wb");
			int ch0d=0;
			while((ch=getc(rame))!=EOF){
				if(argv[1][1]=='d'){
					if(ch==0xd){
						DOSNEWLINE:
						putc(0xd,wame);
						putc(0xa,wame);
					}else if(ch==0xa){
						if(!ch0d) goto DOSNEWLINE;
					}else putc(ch,wame);
				}else if(argv[1][1]=='u'){
					if(ch==0xa&&ch0d) goto CHOW;
					putc(ch==0xd?0xa:ch,wame);
				}else if(argv[1][1]=='m'){
					if(ch==0xa){
						if(!ch0d) putc(0xd,wame);
					}else putc(ch,wame);
				}
				CHOW:ch0d=ch==0xd;
			}
			fclose(wame);
			fclose(rame);
			remove(argv[i]);
			rename(temp,argv[i]);
		}
	}
	return 0;
}
