#include <iostream>
using namespace std;

#define MaxVertexNum 10
typedef char DataType;
typedef int Vertex;
typedef int WeightType;

bool Visited[MaxVertexNum]={false};

typedef struct ENode{
    Vertex V1;
    Vertex V2;
    WeightType Weight;
}*Edge;

typedef struct AdjVNode{
    Vertex AdjV;
    WeightType Weight;
    struct AdjVNode *Next;
}*AdjVN;

typedef struct VNode{
    AdjVN FirstEdge;
    DataType Data;
}AdjList[MaxVertexNum];

typedef struct GNode{
    int Nv;
    int Ne;
    AdjList G;
}*LGraph;

LGraph BuildGraph();
LGraph CreateGraph(int N);
void InsertEdge(LGraph Graph,Edge E);
void BFS(LGraph Graph,Vertex V);
void Visit(LGraph Graph,Vertex V);


int main() {
    LGraph Graph = BuildGraph();
    BFS(Graph, 1);
    return 0;
}

LGraph BuildGraph(){
    int n;
    cout<<"请输入顶点个数 : ";
    cin>>n;
    LGraph Graph = CreateGraph(n);
    
    cout<<"请输入边数 : ";
    cin>>Graph->Ne;
    if(Graph->Ne){
        Edge E = new ENode;
        cout<<"请输入各边的顶点V1,V2和权重Weight"<<endl;
        for(int i=0 ; i<Graph->Ne ; i++){
            cin>>E->V1>>E->V2>>E->Weight;
            InsertEdge(Graph, E);
        }
    }
    
    return Graph;
}

LGraph CreateGraph(int N){
    LGraph Graph = new GNode;
    Graph->Nv = N;
    Graph->Ne=0;
    
    for(int i=0 ; i<N ; i++){
        cout<<"请输入顶点"<<i<<"的名字 : ";
        cin>>Graph->G[i].Data;
        Graph->G[i].FirstEdge=NULL;
    }
    
    return Graph;
}

void InsertEdge(LGraph Graph,Edge E){       //头插法
    AdjVN t1 = new AdjVNode;
    t1->AdjV = E->V2;
    t1->Weight = E->Weight;
    
    t1->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge=t1;
/*********************************************/
    AdjVN t2 = new AdjVNode;
    t2->AdjV = E->V1;
    t2->Weight = E->Weight;
    
    t2->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge=t2;
}

void BFS(LGraph Graph,Vertex V){
    Vertex Q[MaxVertexNum];
    int front = 0;
    int rear = 0;
    
    Q[rear++]=V;
    Visit(Graph, V);
    Visited[V] = true;
    
    while(rear != front){
        Vertex X = Q[front++];
        for(AdjVN P = Graph->G[X].FirstEdge ; P ; P = P->Next){
            if(!Visited[P->AdjV]){
                Visit(Graph, P->AdjV);
                Visited[P->AdjV] = true;
                Q[rear++] = P->AdjV;
            }
        }
    }
}

void Visit(LGraph Graph,Vertex V){
    cout<<"顶点"<<V<<"--"<<Graph->G[V].Data<<" is Visited"<<endl;
}

/*
 A B C D E
 */
