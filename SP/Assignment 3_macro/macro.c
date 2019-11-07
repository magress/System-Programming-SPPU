//write a program to implement micro processor(AIF,AGO not expected ,nested macro call not expected) 
//with error handling macro duplicaiton handling, parameter miss-matching
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MNT
{
	char mname[10];
	int pp;
	int kp;
	int ev;
	char *kpdtp;
	char *evtp;
	char *mdtp;
	
};
typedef struct MNT mnt;

struct PNTAB
{
	char name[10];
};
typedef struct PNTAB pntab;

struct EVTAB
{
	int value;
};
typedef struct EVTAB evtab;

struct EVNTAB
{
	char name[10];
};
typedef struct EVNTAB evntab;

struct KPDTAB
{
	char name[10];
};
typedef struct KPDTAB kpdtab;

struct SSNTAB
{
	int index;
	char name[10];
	int opcode;
};
typedef struct SSNTAB ssntab;
struct APDTAB
{
	char name[10];
};
typedef struct APDTAB apdtab;

mnt mnt1;
pntab pntab1[20];
evtab evtab1[20];
evntab evntab1[20];
ssntab ssntab1[20];
kpdtab kpdtab1[20];
apdtab apdtab1[20];
int a,err;

int spntab(char str[])
{
	int i;
	for(i=0;i<mnt1.pp;i++)
	{
		int k = strcmp(str,pntab1[i].name);
		if(k == 0) return i;
	}
	return -1;
}
int skpdtab(char str[])
{
	int i;
	for(i=0;i<mnt1.kp;i++)
	{
		int k = strcmp(str,kpdtab1[i].name);
		if(k == 0) return i;
	}
	return -1;
}
void display()
{
	FILE *fp;
	char ch;
	printf("\n\n");
	fp = fopen("macro.txt","r");	
	while(!feof(fp))
	{
		ch = getc(fp);
		printf("%c",ch);
	}
	fclose(fp);
}
void output()
{
	FILE *fp;
	char ch;	
	printf("\n");
	fp = fopen("output.txt","r");	
	while(!feof(fp))
	{
		ch = getc(fp);
		printf("%c",ch);
	}
	fclose(fp);
}
void mdtDisplay()
{
	FILE *fp;
	char ch;	
	printf("\n");
	fp = fopen("mdt.txt","r");	
	while(!feof(fp))
	{
		ch = getc(fp);
		printf("%c",ch);
	}
	fclose(fp);
}
void error()
{
	FILE *fp;
	char ch;
	printf("\n");
	fp = fopen("error.txt","r");	
	while(!feof(fp))
	{
		ch = getc(fp);
		printf("%c",ch);
	}
	fclose(fp);
}
void macro(FILE **f1, FILE **f2, FILE **f3)
{
	FILE *f4 = fopen("mdt.txt","w");
	char str[10],ch;
	int i = 0;
	while(1)
	{
		ch = getc(*f1);
		str[i++] = ch;
		if(ch == '\n' || ch == ' ')
		{
			str[--i] = '\0';
			strcpy(mnt1.mname,str);
			break;
		}
	}
	i = 0;
	while(1)
	{
		ch = getc(*f1);
		str[i++] = ch;
		if(ch == '\n' || ch == ' ' || ch == ',')
		{
			str[--i] = '\0';
			i = 0;
			int l = strlen(str);
			if(isalpha(str[l-1]) || str[l-1] == '=' ) strcpy(pntab1[mnt1.pp++].name,str);
			if(str[l-1] == '=' ) strcpy(kpdtab1[mnt1.kp++].name,str);
			if(ch == '\n') break;
		}
	}
	i = 0;
	while(1)
	{
		ch = getc(*f1);
		str[i++] = ch;
		if(ch == '\n' || ch == ' ' || ch == ',')
		{
			str[--i] = '\0';
			i = 0;
			int l = strlen(str);
			if(str[0] == '&' )
			{
				int k = spntab(str);
				if(k != -1)
					fprintf(f4,"<P,%d> ",k+1);
				else
				{
					fprintf(*f3," UNDEFINE SYMBOL %s \n",str);
					err++ ;
				}
			}
			else if(isalpha(str[0])) fprintf(f4,"\n%8s ",str);
			
			if(!strcmp(str,"MEND"))	break ;
		}
	}
	fclose(f4);
}
void expand(FILE **f1, FILE **f2, FILE **f3)
{
	FILE *f4 = fopen("mdt.txt","r");
	char str[10],ch;
	int i = 0,k=-1,p=-1;
	while(1)
	{
		ch = getc(*f1);
		str[i++] = ch;
		if(ch == '\n' || ch == ' ' || ch == ',')
		{
			str[--i] = '\0';
			i = 0;
			int l = strlen(str);
			if(isalpha(str[0])) strcpy(apdtab1[a++].name,str);
			if(ch == '\n') break ;
		}
	}
	i = 0;
	while(1)
	{
		ch = getc(f4);
			str[i++] = ch;
		if(ch == ',')
		{
			str[--i] = '\0';
			p = strcmp(str,"P");
			i = 0;
		}
		else if(ch == '>')
		{
			str[--i] = '\0';
			i = 0;
			if(p == 0)
			{
				p = str[0] - 48;
				fprintf(*f2,"%5s ",apdtab1[p-1].name);
				p = -1;
			}
		}
		else if(ch == ' ' || ch == '\n')
		{
			str[--i] = '\0';
			i =0;
			if(!strcmp(str,"MEND"))	break ;
			
			if(isalpha(str[0]))	fprintf(*f2,"\n+%7s ",str);
		}
		else if(ch == '<') i = 0;
	}
	fclose(f4);
}
void stt(FILE **f1, FILE **f2, FILE **f3)
{
	char str[10],ch;
	int i = 0;
	fprintf(*f2,"\n   START ");
	while(1)
	{
		ch = getc(*f1);
		str[i++] = ch;
		if(ch == '\n' || ch == ' ')
		{
			str[--i] = '\0';
				i = 0;
			if(!strcmp(str,mnt1.mname))
			{
				expand(f1,f2,f3);
				fprintf(*f2,"\n");
				continue ;
			}
			else if(isalpha(str[0]) || isdigit(str[0])) fprintf(*f2," %7s ",str);
			
			if(ch == '\n') fprintf(*f2,"\n");
		}
		if(ch == '\n')
		{
			if(!strcmp(str,"END"))
				return ;
		}
	}
}
void convert() 
{
	FILE *f1,*f2,*f3;
	char ch;

//	fp = fopen("/home/system27/workspace/pass1/src/code.txt","r");
	f1 = fopen("macro.txt","r");
	f2 = fopen("output.txt","w");
	f3 = fopen("error.txt","w");
	int f = 1, i = 0;
	char str[10];
	while(!feof(f1))
	{
		ch = getc(f1);
		str[i++] = ch;
		if(ch == '\n' || ch == ' ')
		{
			str[--i] = '\0';
			i = 0;
			if(!strcmp(str,"MACRO"))
			{
				macro(&f1,&f2,&f3);
				f = 0;
			}
			else if(!strcmp(str,"START")) stt(&f1,&f2,&f3);

			else if(f)
			{
				err++;
				fprintf(f3,"\n MACRO NOT PRESENT ");
				break ;
			}
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
}
void tables()
{
	int i;
	printf("\n\n           MNT ");
	printf("\n MACRO NAME   #PP  #KP  #EV");
	printf("\n%9s   %5d  %3d  %3d",mnt1.mname,mnt1.pp,mnt1.kp,mnt1.ev);
	
	printf("\n\n  PNTAB ");
	for(i = 0;i<mnt1.pp;i++)	printf("\n %d : %s",i+1,pntab1[i].name);

	printf("\n\n  KPDTAB ");
	for(i = 0;i<mnt1.kp;i++)	printf("\n %d : %s",i+1,kpdtab1[i].name);
	
	printf("\n\n  APDTAB ");
	for(i = 0;i<mnt1.pp;i++) printf("\n %d : %s",i+1,apdtab1[i].name);
}
int main()
{
	convert();
	int ch;
	do
	{
		printf("\n\n 1 to print TABLES ");
		printf("\n 2 to display MACRO file ");
		printf("\n 3 to display OUTPUT file ");
		printf("\n 4 to display MDT file ");
		printf("\n 5 to print ERRORS ");
		printf("\n 6 to exit ");
		printf("\n enter yr choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1 :
				if(!err) tables();
				else printf("\n there exits error in code \n first remove errors ");
				break ;
			case 2 :
				if(!err) display();
				else printf("\n there exits error in code \n first remove errors ");
				break ;
			case 3 :
				if(!err) output();
				else printf("\n there exits error in code \n first remove errors ");
				break;
				case 4 :
				if(!err) mdtDisplay();
				else printf("\n there exits error in code \n first remove errors ");
				break;
			case 5 :
				if(err)	error();
				else printf("\n no error exits \n assembled successfully ");
		}
	}while(ch<6);
	return EXIT_SUCCESS;
}
