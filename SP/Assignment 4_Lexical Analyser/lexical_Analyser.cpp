#include <bits/stdc++.h>
using namespace std;

string keyword[12]={"int","string","break","goto","if","else","float","char","struct","return","printf","scanf"};
string delimiter[20]={" ","\n","\t","\"","'",";",",","{","}","(",")","[","]","<",">","+","-","*","/","="};
string operators[5]={"+","-","*","/","="};

struct ust
{
	string sname;
	string type;
	int addr;
}ust[100];

struct table
{
	string name;
	int addr;
}sym[10],lit[10];

int isDelimiter(char ch)
{
	string s;
	s+=ch;
	for(int i=0;i<20;i++)
		if(delimiter[i]==s)
			return i+1;
	return 0;
}

int isOperator(char ch)
{
	string s;
	s+=ch;
	for(int i=0;i<5;i++)
		if(operators[i]==s)
			return i+1;
	return 0;
}

int isKeyword(string str)
{
	int i;
	for(i=0;i<12;i++)
		if(keyword[i]==str)
			return i+1;
	return 0;
}

int isLiteral(string str)
{
	for(int i=0;i<str.length();i++)
		if(!isdigit((int)str[i]))
			return 0;
	return 1;
}

int isValidIdentifier(string str)
{
	if(isdigit((int)str[0]) || isDelimiter(str[0]))
		return 0;
	return 1;
}

void insertInUST(string sname,string type,int addr,int ustc)
{
	ust[ustc].sname=sname;
	ust[ustc].type=type;
	ust[ustc].addr=addr;
}


int isAlreadyInLITTAB(string s,int lcnt)
{
	int i;
	for(i=1;i<lcnt;i++)
		if(lit[i].name==s)
			return i;
	return 0;
}

int isAlreadyInSYMTAB(string s,int scnt)
{
	int i;
	for(i=1;i<scnt;i++)
		if(sym[i].name==s)
			return i;
	return 0;
}

void insertInLITTAB(string s,int lcnt)
{
	lit[lcnt].name=s;
	lit[lcnt].addr=lcnt;
}

void insertInSYMTAB(string s,int scnt)
{
	sym[scnt].name=s;
	sym[scnt].addr=scnt;
}

void printUST(int ustc)
{
	for(int i=0;i<ustc;i++)
		cout<<ust[i].sname<<" "<<ust[i].type<<" "<<ust[i].addr<<endl;
}


void printTables(int scnt,int lcnt)
{
	int i;
	cout<<endl<<"Symbol Table"<<endl;
	for(i=1;i<scnt;i++)
		cout<<sym[i].name<<" "<<sym[i].addr<<endl;
	cout<<"---------------------------------------------------------------------------------";
	cout<<endl<<"Literal Table"<<endl;
	for(i=1;i<lcnt;i++)
		cout<<lit[i].name<<" "<<lit[i].addr<<endl;
	cout<<"---------------------------------------------------------------------------------";
}

void lexical(string s)
{
	int i,index,id,ustc=0,scnt=1,lcnt=1,l=0,r=0;
	int length=s.length();
	while(r<=length)
	{
		index=isDelimiter(s[r]);
		if(!index)
			r++;
		else if(index)
		{
			if(l==r)
			{
				id=isOperator(s[r]);
				if(id)
				{
					string t;
					t+=s[r];
					insertInUST(t,"operator",id,ustc);
					ustc++;
				}
				else if(s[r]!=' ' && s[r]!='\n' && s[r]!='\t')
				{
					string t;
					t+=s[r];
					insertInUST(t,"special",index,ustc);
					ustc++;
				}
				r++;
				l=r;
			}
			else if(l!=r)
			{
				string sub;
				for(i=l;i<r;i++)
					sub+=s[i];
				id=isKeyword(sub);
				if(id)
				{
					insertInUST(sub,"keyword",id,ustc);
					ustc++;
				}
				else if(isLiteral(sub))
				{
					insertInUST(sub,"literal",lcnt,ustc); 
					index=isAlreadyInLITTAB(sub,lcnt); 
					if(!index)
					{
						insertInLITTAB(sub,lcnt);
						lcnt++;
					}
					ustc++;
				}
				else if(isValidIdentifier(sub))
				{
					if(s[l-1]=='"' && s[r]=='"')
					{
						insertInLITTAB(sub,lcnt); 
						insertInUST(sub,"StringConstant",lcnt,ustc);
						lcnt++;
						ustc++;
					}
					else

					{
						index=isAlreadyInSYMTAB(sub,scnt); 
						if(index)
							insertInUST(sub,"identifier",index,ustc);
						else if(!index)
						{
							insertInUST(sub,"identifier",scnt,ustc);
							insertInSYMTAB(sub,scnt);
							scnt++;
						}
						ustc++;
					}
				}
				else
					cout<<"Invalid Identifier is "<<" "<<sub<<endl;
				r++;
				l=r;
			}
		}
	}
	printUST(ustc);
	cout<<"----------------------------------------------------------------------------"<<endl;
	printTables(scnt,lcnt);
}

int main()
{
	ifstream fin;
	string str,t;
	int i=0;
	char ch;
	fin.open("input.txt",ios::in);
	while(!fin.eof())
	{
		ch=fin.get();
		str+=ch;
		i++;
	}
	str[i-1]='\0';
	fin.close();
	cout<<str<<endl;
	cout<<"----------------------------------------------------------------------------"<<endl;
	lexical(str);

	return 0;
}
