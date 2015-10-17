//Original http://www-ccrma.stanford.edu/~craig/utility/flip/flip.cpp
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(int argc,char**argv){
	if(argc<3){
		puts("u NIX\nd DOS\nm MAC\n? ???\nsn \\t->n spaces\ntn n spaces->\\t");
		return 0;
	}
	const char*argv1=argv[1]+(argv[1][0]=='-');
	if(!*argv1)return 0;
	const char a0=*argv1,a1=argv1[1]-48;
	if(a0!='?'&&a0!='u'&&a0!='s'&&a0!='t'&&a0!='d'&&a0!='m')return 0;
	else for(int ch,i=2;i<argc;i++){
		FILE*rame=fopen(argv[i],"rb");
		if(!rame)printf("? %s\n",argv[i]);
		else if(a0=='?'){
			while((ch=getc(rame))!=0xa&&ch!=0xd&&ch!=EOF);
			printf("%s: %s\n",argv[i],ch==0xa?"NIX":ch==EOF?"???":(getc(rame)==0xa?"DOS":"MAC"));
			fclose(rame);
		}else{
			fseek(rame,0,SEEK_END);
			long rlen=ftell(rame);
			char *tmp=malloc(rlen),*tp=tmp;
			fseek(rame,0,SEEK_SET);
			int ch0d=0;
			while((ch=getc(rame))!=EOF){
				switch(a0){
				case'd':
					if(ch==0xd||(ch==0xa&&!ch0d)){
						*tp++=0xd;
						*tp++=0xa;
					}else if(ch!=0xa)*tp++=ch;
				break;case'm':
					if(ch!=0xa)*tp++=ch;
					else if(!ch0d)*tp++=0xd;
				break;case'u':
					if(!ch0d)*tp++=(ch==0xd?0xa:ch);
					else if (ch==0xd)*tp++=0xa;
				break;case's':
					if(ch!='\t')*tp++=ch;
					else{
						memset(tp,' ',a1);
						tp+=a1;
					}
				continue;case't':
					if(ch!=' '){
						if (ch0d){
							memset(tp,' ',ch0d);
							tp+=ch0d;
							ch0d=0;
						}
						*tp++=ch;
					}else if(++ch0d==a1){
						ch0d=0;
						*tp++='\t';
					}
					continue;
				default:__builtin_unreachable();
				}
				ch0d=ch==0xd;
			}
			fclose(rame);
			rame=fopen(argv[i],"wb");
			fwrite(tmp,1,tp-tmp,rame);
			fclose(rame);
			free(tmp);
		}
	}
}
