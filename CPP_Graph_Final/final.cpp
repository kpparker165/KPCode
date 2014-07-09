#include<string>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
const int namearray=20;
int nump=0;


struct node
{
string name;
node*next;
};
void init(node* listarray[])
{	for(int i=0; i<namearray; i++)
	{	listarray[i]= new node;
		listarray[i]->name ="KYLE";
		listarray[i]->next=NULL;
	}
}
void makelist (node*& friends)
{	node* head=new node; 
	head ->name="KYLE";
	head->next=NULL;
	if(friends->next==NULL)friends->next= head;
	else(makelist(friends->next));
}
void insert2(node* head, string username)
{	if(head->next==NULL)
	{node* knew=new node; 
	knew->name=username;
	knew->next=NULL;
	head->next=knew;
	}
	else(insert2(head->next,username));
}

void insertlist(node* head,string username)
{	node *temp = head;
	node *link = head;
	if(head->name=="KYLE")head->name=username;
	else
		insert2(head,username);
}

void readfile(node* listarray[])
{	string name;
	int first=0,second=0;
	string substring, friendlist;
	ifstream inf;
	inf.open("final.dat");
	while(!inf.eof())
	{	getline(inf,name);
		second=name.find(' ');
		substring=name.substr(first,second);
		insertlist(listarray[nump],substring);
		friendlist=name.substr(second+1,name.length()-1);
		while(friendlist.find(' ')!=string::npos)
		{	first=0;
			second=friendlist.find(' ');
			name=friendlist.substr(first,second);
			friendlist=friendlist.substr(second+1,friendlist.length()-1);
			insertlist(listarray[nump],name);
		}
		insertlist(listarray[nump],friendlist);
		nump++;
	}
}
void traverse2(node* list, ofstream &outf)
{	if(list!=NULL)
	{	outf << list->name << " ";
		traverse2(list->next,outf);
	}
}

void total1(node* list, int &count)
{	if(list!=NULL)
	{
		count++;
		total1(list->next,count);
	}
}
void total(node *listarray[], string username,ofstream &outf)
{	int count = -1;
	int i,j;
	bool found=false;
	for(i=0; i<nump; i++)
	{	if(listarray[i]->name==username)
		{	found=true;
			j=i;
		}
	}
	if(found==true)total1(listarray[j],count);
	outf<<count<<" people."<<endl;
}
void traverse(node *listarray[], ofstream &outf)
{	int count = 0;
	int i;
	for(i=0; i<nump; i++)
	{	outf<<listarray[i]->name<<": ";
		traverse2(listarray[i]->next,outf);
		outf<<endl;
	}
}
bool emptyList(node* list)
{
	return list==NULL;
}
void whoknows1(node*list, string friends,string &n)
{	bool yesno= false;
	if(list!=NULL)
	{	if(list->name!=friends)
		{	n="no";
			whoknows1(list->next,friends,n);
		}
		else
			yesno=true;
	}
	if(yesno==true) n="yes";
}
void whoknows(node* listarray[],string username,string friends,ofstream &outf)
{	int i,j;
	string n;
	bool found=false;
	for(i=0; i<nump; i++)
	{	if(listarray[i]->name==username)
		{	found=true;
			j=i;
		}
	}
	if(found==true)
	{	whoknows1(listarray[j],friends,n);
		outf<<n<<endl;
	}
	else
		outf<<"The user does not exists or is spelled incorrect"<<endl;
}
void whoknowsab1(node* list,string name1,string &answer)
{	bool yesno= false;
	if(list!=NULL)
	{	if(list->name!=name1)
		{	answer="no";
			whoknows1(list->next,name1,answer);
		}
		else
			yesno=true;
	}
	if(yesno==true) answer="yes";
}
void whoknowsab(node* listarray[],string name1,ofstream &outf)
{	int i;
	string answer;
	outf<<"These people know "<< name1<<" "<<endl;
	for(i=0; i<nump; i++)
	{	whoknows1(listarray[i]->next,name1,answer);
		if(answer=="yes")
		{outf<<listarray[i]->name<<" ";
		}
	}
	outf<<endl<<endl;
}
void main ()
{	node* listarray[namearray];
	init(listarray);
	ofstream outf;
	outf.open("final.out");
	readfile(listarray);
	outf << "Here is the original FACEBOOK:" << endl << endl;
	traverse(listarray,outf);
	outf<<endl<<endl;
	outf<<"A) Harry knows ";
	total(listarray,"Harry",outf);
	outf<<"C) Does Harry know Bill? : ";
	whoknows(listarray,"Harry","Bill",outf);
	outf<<"E) Who knows Harry and Cathy? : "<<endl;
	whoknowsab(listarray,"Harry",outf);
	whoknowsab(listarray,"Cathy",outf);
	outf<<"F) Does Lisa know Harry? : ";
	whoknows(listarray,"Lisa","Harry",outf);
	outf<<"G) Does Lisa know Cathy? : ";
	whoknows(listarray,"Lisa","Cathy",outf);
}