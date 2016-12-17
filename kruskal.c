#include<stdio.h>
typedef int vertex;
#define maxVertices 100
#include<stdlib.h>

void printArray(int graph[][maxVertices],int size);

void AdjacencyMatrix(int graph[][maxVertices], int size){
    int i,j;
    for(i = 0;i < size; i++)
    {
        for(j = 0;j < i; j++)
        {
            graph[i][j] = graph[j][i]= rand()%50;
            if( graph[i][j]>40)
				graph[i][j]=graph[j][i]=999;

        }
    graph[i][i] = 999;
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

int root(vertex v,int parent[]){

    while(parent[v] != v)
        {v = parent[v];}

return v;
}

void union_ij(vertex i,vertex j,int parent[]){
    if(j > i)
        parent[j] = i;
    else
        parent[i] = j;
}

void kruskal(int graph[][maxVertices],int size){
    int count, i, parent[maxVertices], min, j, k, sum;
    count = k = sum = 0;
	vertex  minTree[maxVertices][maxVertices],u,v;

    for(i = 0; i < size; i++)
    {
        parent[i] = i;
    }
    while(count < size)
    {
        min = 999;
        for(i = 0; i < size; i++)
        {
            for(j = 0;j < size; j++)
            {

                if(graph[i][j] < min)
                {
                    min = graph[i][j];
                    u = i;
                    v = j;

                }
            }
        }
        if(min != 999)
        {
            i = root(u, parent);
            j = root(v, parent);
            if (i != j)
            {
                minTree[k][0] = u;
                minTree[k][1] = v;

                k++;

                sum += min;
                union_ij(i,j,parent);
            }
        graph[u][v] = graph[v][u] = 999;

        }count +=1;
    }
    if(count != size)
    {
        printf("spanning tree not exist\n");
    }
    if(count == size)
    {
        printf("\nminimal Spanning tree is\n");
        for(k = 0; k < size-1 ; k++)
        {
            printf(" %d -> %d ",minTree[k][0],minTree[k][1]);
        }
    printf("\ncost = %d \n",sum);
    }
}

int main()
{
    int graph[maxVertices][maxVertices],size;
    printf("enter the number of vertices\t");
    scanf("%d",&size);
    AdjacencyMatrix(graph,size);
    kruskal(graph,size);
    return 0;
}
