#include<bits/stdc++.h>
using namespace std;
string str;
char ch[100];
int i=0,j;
int V();
int T();
int E();


int V()
{
	if(str[i]=='i' && str[i+1]=='d')
	{
		i+=2;
		cout<<"V -> ";
		cout<<"id -> \n";
		//cout<<i<<endl;
		//cout<<"9\n";
		return 1;
	}
	else if(str[i]=='(')
	{
		i++;
		cout<<"V -> ";
		cout<<"( -> \n";
		if(i==j)
			{
				//cout<<"Only V\n";
				return 0;
			}
		//cout<<"8\n";
		if(E())
		{
			if(str[i]==')')
			{
				cout<<"V -> ";
				cout<<") -> \n";
				//cout<<"10"<<endl;
				i++;
				return 1;
			}
		}
	}
	else
	{
		return 0;
	}
	
}

int T()
{

	
	if( V() )
	{
		
		if(i==j)
			{
				//cout<<"Only V\n";
				return 1;
			}
		else if(str[i]=='*')
		{
			//cout<<"6\n";
			cout<<"T -> ";
			cout<<"* -> \n";
			i++;
			if(i==j)
			{
				return 0;
			}
			if(T())
			{
				//cout<<"7\n";
				return 1;
			}
		}
		return 1;
	}
	
	else
	{
		return 0;
	}
}

int E()
{
	//cout<<"aman\n";
	
	
	if( T() )
	{
	//cout<<"amanu\n";
	//cout<<i<<endl;
		if(i==j && str[i]!='+')
			{
				//cout<<"Only T\n";
				
				return 1;
			}
		else if(str[i]=='+')
		{
			cout<<"E -> ";
			cout<<"+ -> \n";
			//cout<<"2\n";
			i++;
			if(i==j)
			{
				return 0;
			}
			if(E())
			{
				//cout<<"3\n";
				return 1;
			}
		}
		
		return 1;
	}
	
	else
	{
		return 0;
	}
}





int main()
{
	
	
	cout<<"Enter the grammer::";
	cin>>str;
	for(j=0;str[j]!='\0';j++)
	{
	}
	//cout<<"length"<<j<<endl;
	if(E())
	{
		cout<<"\nCorrect Expression\n";
	}
	else
	{
		cout<<"\nIncorrect Expression\n";
	}
	return 0;
}
