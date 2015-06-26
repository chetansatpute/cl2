#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

class Q{
    int data[30],R,F;
    public:
    Q(){
        R=F=-1;
    }

    int empty(){
    	if(R==-1)
            return 1;
        return 0;
    }

    void insert(int x){
        if(empty())
            R=F=0;
        else
            R=R+1;
        data[R]=x;
    }

    int Delete(){
        int x=data[F];
        if(R==F)
            R=F=-1;
        else
            F=F+1;
        return(x);
    }
};

struct node{
	node *next;
	int vertex;
};

class graph{
    int visited[20];
    node *G[20];  					
    int n;         					
    void insert(int vi,int vj);   	
    void DFS1(int);					
    public:
        graph(){
            n=0;
        }
		void readgraph(string);
		void BFS(int);
		void DFS(int);
};

void graph::DFS(int start){
    for(int i=0;i<n;i++)
        visited[i]=0;
    DFS1(start);
}

void graph::DFS1(int i){
    node *p;
    cout<<"\nVisit:"<<i;
    p=G[i];
    visited[i]=1;
    while(p!=NULL){
        i=p->vertex;
        if(!visited[i])
            DFS1(i);
        p=p->next;
    }
}

void graph::BFS(int v){
    int i,w;
    Q q;
    node *p;
    for(i=0;i<n;i++)
        visited[i]=0;
    q.insert(v);
    cout<<"\nVisit:"<<v;
    visited[v]=1;
    while(!q.empty()){
        v=q.Delete();
        for(p=G[v];p!=NULL;p=p->next){
            w=p->vertex;
            if(visited[w]==0){
                q.insert(w);
                visited[w]=1;
                cout<<"\nVisit:"<<w;
            }
        }
    }
}

void graph::readgraph(string filename){
	ifstream infile;
	infile.open(filename.c_str());
	int count=0;
	char i,j;
    for(int x=0;x<20;x++)
        G[x]=NULL;
	int vi,vj;
	while(infile>>i>>j){
		if(count == 0){
			
			n = i - '0';
			cout << n;
			count++;
		}else{
			vi = i - '0';
			vj = j - '0';
			
			insert(vi,vj);
			insert(vj,vi);
		}
	}
}

void graph::insert(int vi,int vj){
    node *p,*q;
    q=new node;
    q->vertex=vj;
    q->next=NULL;
    if(G[vi]==NULL)				
        G[vi]=q;
    else{						
        p=G[vi];
        while(p->next!=NULL)
            p=p->next;
        p->next=q;
    }
}

int main(){
	int op,start;
    graph g;
    string filename;
    cout<<"\nEnter File Name:";
    cin>>filename;
    g.readgraph(filename);
    do{
        cout<<"\n\nEnter Your Choice:\n1)BFS\n2)DFS\n0)Quit";
        cin >> op;
        switch(op){
            case 1: cout<<"\nEnter starting node:";
					cin>>start;
					g.BFS(start); break;
            case 2: cout<<"\nEnter starting node:";
                	cin>>start;
                	g.DFS(start); break;
            case 0: cout<<"Exiting..";	exit(0);
            default: cout<<"\nIncorrect choice..\n";
            		break;
        }
	}while(op != 4);
    return 0;
}
