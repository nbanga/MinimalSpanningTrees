#include<stdio.h>
#include<stdlib.h>
int vertex;
#define maxVertices 100
void printArray(int graph[][maxVertices],int size);

void AdjacencyMatrix(int graph[][maxVertices], int size){
    int i,j;
    for(i = 0;i < size; i++)
    {
        for(j = 0;j < i; j++)
        {
            graph[i][j] = rand()%2;
            graph[j][i] = rand()%2;
        }
    graph[i][i] = 0;
    }
    printArray(graph,size);
}

void printArray(int graph[][maxVertices],int size){
    int i,j;
    printf("\n");
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
}

void dfs(int graph[][maxVertices],int size,int *visited,int presentVertex,int *DFTlist){

    int v;
    visited[presentVertex]=1;
    for(v = 0;v < size; v++)
    {
        if(graph[presentVertex][v] == 1 && visited[v] == 0)
        {
            DFTlist[++vertex] = v;
            dfs(graph,size,visited,v,DFTlist);
        }
    }
}
void printdfs(int graph[][maxVertices],int size,int *DFTlist){
    int i,root,visited[maxVertices];
    printf("\nEnter root less than %d: ",size);
    scanf("%d",&root);

    for(i=0;i<size;i++)
    visited[i]=0;

    DFTlist[0]=root;
    dfs(graph,size,visited,root,DFTlist);

    for(i=0;i<size;i++)
    {
        if(visited[i]!=0)
        {
        printf(" -> %d ",DFTlist[i]);
        }
    }
}

int main()
{
    int graph[maxVertices][maxVertices],size,*DFTlist;
    printf("Enter the number of vertices\t");
    scanf("%d",&size);
    DFTlist = (int *)malloc(sizeof(int)*size);
    AdjacencyMatrix(graph,size);
    printdfs(graph,size,DFTlist);
return 0;
}
