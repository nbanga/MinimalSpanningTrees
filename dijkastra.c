#include<stdio.h>
#include<stdlib.h>

void AdjacencyMatrix( int graph[ ][ 100 ], int size )
{
	int i , j ;
	printf("\n");

	for(i = 0; i < size; i++)
	{
		for(j = 0;j < i; j++)
		{
			graph[ i ][ j ] = rand( ) % 100; /* GENERATE RANDOM NUMBERS */
			graph[ j ][ i ] = rand( ) % 50;
		}
			graph[ i ][ i ] = 0;
	}
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			if( graph[ i ][ j ] != 0)
			printf("%d -> %d\t", i, j); /* WRITE TO FILE */
		}
	}
}

void dijkastra( int size, int graph[ ][ 100 ],int source,int des, int *distance,int *parent,int *visited)
{
	int i, j, u, v, min; /* LOCAL VARIABLES */

	for(i = 0; i < size; i++) /* INITIALIZE ALL ARRAYS */
	{
		distance[ i ] = graph[ source ][ i ];
		visited[ i ] = 0;
		parent[ i ] = source;
	}

	visited[ source ] = 1; /* INITIALIZE S[SOURCE] TO 1 */

	for(i = 1; i < size;i++)
	{
		min = 99;
		u =- 1;
		for(j = 0; j < size; j++)
		{
			if(visited[ j ] == 0) /* IF NODE NOT VISITED */
			{
				if(distance[ j ] < min) /* IS ANY DIRECT PATH FROM SOURCE TO DESTINATION */
				{
					min = distance[ j ]; /* IF TRUE CHANGE MIN TI distance[j] */
					u = j;
				}
			}
		}

	}

	if(u == -1) return ; /* IF DESTINATION IS REACHED THE RETURN FROM FUNCTION*/

	visited[ u ] = 1; /* MARK u AS VISITED */

	if( u == des) return;

	for( v = 0; v < size; v++) /* CONSIDER U AS INTERMIDIATE NODE AND GO TO NEXT */
	{
		if(visited[ v ] == 0) /* V WHICH IS REACHABLE FROM U */
		{
			if(distance[ u ] + graph[ u ][ v ] < distance[ v ])
			{
				distance[ v ] = distance[ u ] + graph[ u ][ v ]; /* CHANGE SHORTEST DISTANCE */
				parent[ v ] = u;
			}
		}
	}
}


void print(int graph[ ][ 100 ],int size,int *distance,int *parent,int *visited)
{
	int i,source,des,p=0;
	int max[100]={-1},dia[100]={-1};
	for(source = 0; source < size; source++) /* SOURCE VARIES FROM 0 TO N */
	{
		int j=0;
		for(des = 0;des < size; des++) /* DESTINATION VARIES FROM 0 TO N */
		{
			dijkastra( size, graph, source, des, distance, parent, visited); /* CALL FUNCTION TO FIND SHORTEST PATH FROM SOURCE */
			{ /* TO DESTINATION */
				if(distance[ des ] == 99) /* IF NO PATH FROM GIVEN SOURCE TO DESTINATION */
					printf("destination is not reachable from %d to %d \n",source,des);

				else
				{
					printf("\n");
					i = des;
					while( i != source) /* REPEATEDLY PRINT PATH FROM SOURCE TO DESTINATION */
					{
						printf("%d<-", i);
						i = parent[ i ];
					}
					printf("%d of lenght %d\t\t\t", i, distance[ des ]);
					//dia[j++]=distance[des];
				}
			}
		}
		/*int k;
		for (k=0; k<j;k++)
		{
			if(max[p]<dia[k])
				max[p]=dia[k];
		}
		p++;
	}
	int maxd=-1;
	for(i=0;i<p;i++)
	{
		if (maxd<max[i])
			maxd=max[i];
	}
	printf("diameter of the tree is: %d\t",maxd);*/
}
}

void printArray(int graph[][100],int size)
{
	int i, j;
	//printf("\n");
	for(i = 0;i < size; i++)
	{
		for(j = 0;j < size; j++)
			{
				printf("\t%d", graph[ i ][ j ]);
			}
		printf("\n");
	}
}

int main()
{
	int size,graph[100][100],i,j,*parent,*distance,*visited;

	printf("Enter the no vertices of the digraph\t");
	scanf("%d",&size); /* READ REQUIRED NUMBER OF VERTICES IN THE DIGRAPH */

	visited = (int *) malloc (size * sizeof(int)); /* ALLOCATE MEMORY */
	distance = (int *) malloc (size * sizeof(int));
	parent = (int *) malloc (size * sizeof(int));

	AdjacencyMatrix( graph, size);

	printf("\n\n\tAdjacency Matrix of the graph\n"); /* PRINT ADJACENCY MATRIX */

	printArray(graph,size);

	print(graph,size,distance,parent,visited);

	return 0;

}
