#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <assert.h>

//#ifndef _GRAPH_H_
//#define _GRAPH_H_

/* $Log$
*/

#define MAX_NUM_NODES 100
/* assuming sparse graph for the extreme case */
#define MAX_NUM_EDGES 1000

typedef struct _tagEdge{
    int head, tail;
} Edge;

typedef struct _tagGraph{
    int node[MAX_NUM_NODES];
    Edge edge[MAX_NUM_EDGES];
    int num_nodes;
    int num_edges; //keep track of the edge array
    int num_effective_edges;
} Graph;

 Graph *create_graph();
 void add_node(Graph*, int);
 void add_edge(Graph*, int, int);
 void dump_graph(Graph*);
 void remove_selfloop(Graph*);
 int remove_bridges(Graph*, int*);
 void copy_graph(Graph*, Graph*);

//#endif/*_GRAPH_H_*/

/*$Log$*/

#define STACK_DEPTH 2000

/*
#define pop (stack[--stack_pointer])
#define push(x) (stack[stack_pointer ++] = (void*)(x))
#define empty(x) ((stack_pointer == 0))
*/

 void* pop();
 void* peek();
 void push(void *x);
 int empty();
 int depth();

//#endif/*_STACK_H_*/
//worksheet.h 4/8

/*$Log$*/
//#include "graph.h"

typedef struct _tagWorksheet {
	int edge_index[MAX_NUM_EDGES];//partial spanning tree
	int size;//size of the partial spanning tree

	Graph *g;
} Worksheet;

 Worksheet *create_worksheet(Graph *);
 Worksheet *split_worksheet(Worksheet *);
 void dump_spanning_tree(Worksheet *);

//#endif/*_WORKSHEET_H_*/


//enumst.c 5/8

//[top][prev][next]
/* Enumerate spanning tree $Log$ */

int main(void)
{
  Graph *g = create_graph();
  Worksheet *w;
  int bridges[1000];
  int num_b;
  int i,j,numv,nume;

  printf("enter no. of vertices less than 100\t");
  scanf ("%d",&numv);
  printf("%d",numv);
  printf("enter no. of edges less than 1000\t");
  scanf ("%d",&nume);
  printf("%d",nume);

  for(j=0;j<numv;)
  {
        add_node(g, -1);
        j++;
  }

  j=0;
  int head,tail;
  while (j<nume)
  {
      printf("enter head of %d edge\t",j);
      scanf ("%d",&head);
      printf("%d",head);
      printf("enter tail of %d edge\t",j);
      scanf ("%d",&tail);
      printf("%d", tail);
      add_edge(g, head, tail);
      j++;
  }

  /*add_node(g, -1);
  add_node(g, -1);
  add_node(g, -1);
  add_node(g, -1);

  add_edge(g, 1, 2);
  add_edge(g, 2, 3);
  add_edge(g, 3, 4);
  add_edge(g, 4, 1);
  add_edge(g, 1, 3);
  add_edge(g, 2, 4);*/

  dump_graph(g);

  /*
  num_b = find_bridges(g, bridges);
  fprintf(stderr, "%d bridges\n", num_b);
  for(i=0; i<num_b; i++)
    fprintf(stderr, "%d ", bridges[i]);
  fprintf(stderr, "\n");
  */

  w = create_worksheet(g);
  push(w);

  do {
    w = peek();

    /*
    fprintf(stderr, "top of the stack =========\n");
    dump_graph(w->g);
    fprintf(stderr, "--------------------------\n");

    fprintf(stderr, "depth of stack: %d\n", depth());
    */

    split_worksheet(w);
    free(w);

  }while (!empty());

  return 0;
}



/* $Log$ */
/** Function: create_graph
*
* Parameters: None
*
* @return: A pointer to an empty graph, NULL if memory's out */
Graph* create_graph()
{
    Graph *g = (Graph*)malloc(sizeof(*g));

    if(!g)
	return NULL;

    g->num_nodes = 0;
    g->num_edges = 0;
    g->num_effective_edges = 0;

    return g;
}


/**************************************************
*
* Function: add_node
*
* Parameters:
* @param g Pointer to the graph the node to be added
* @param head The id of the node, if -1, the node is append to the array of nodes
* @return None
*
**************************************************/
void
add_node(Graph *g, int u)
{
    if(u == -1) {
	g->node[g->num_nodes] = g->num_nodes + 1;
	g->num_nodes ++;
	//printf("successful %d", g->num_nodes);
	//abort();
    } else {
	fprintf(stderr, "add_node: expecting -1, got %d instead\n", u);
    }
}


/**************************************************
*
* Function: add_edge
*
* Parameters:
* @param g Graph to be operated
* @param head,tail The edge
*
* @return None
*
**************************************************/
void add_edge(Graph *g, int head, int tail)
{
    g->edge[g->num_edges].head = head;
    g->edge[g->num_edges].tail = tail;
    g->num_edges ++;
    g->num_effective_edges ++;
}

/**************************************************
*
* Function: dump_graph Print the graph
*
*
**************************************************/
void dump_graph(Graph *g)
{
    int i;

    printf("number of nodes: %d\n", g->num_nodes);
    printf("number of edges: %d\n", g->num_effective_edges);

    for(i=0; i<g->num_edges; ++i)
	printf("\t%d ( %d %d ) \n", i, g->edge[i].head, g->edge[i].tail);
}


/**************************************************
*
* Function: remove_selfloop Remove selfloop edges, the input graph will be
* 	modified
*
* Parameters:
* @param g The graph
*
* @return None.  The input graph will be modified in place
*
**************************************************/
void remove_selfloop(Graph *g)
{
    int i;

    for(i=0; i<g->num_edges; ++i)
    {

        if(g->edge[i].head != 0 && (g->edge[i].head == g->edge[i].tail))
        {
            /* delete this edge by assiging head=tail=0 */
            g->edge[i].head = 0;
            g->edge[i].tail = 0;
            g->num_effective_edges --;
        }

    }
}


/**************************************************
*
* Function: remove_edge
*
* Parameters:
* @param
*
* @return
*
**************************************************/
void remove_edge(Graph *g, int this_edge)
{
    g->edge[this_edge].head = 0;
    g->edge[this_edge].tail = 0;

    g->num_effective_edges --;
}


/*************************************************
*
* Function: copy_graph
* copy graph from src to dst
*
* @param src Source graph
* @param dst Destination graph
*
* @return None
*************************************************/
void copy_graph(Graph * src, Graph *dst)
{
  dst->num_nodes = src->num_nodes;
  dst->num_edges = src->num_edges;
  dst->num_effective_edges = src->num_effective_edges;

  memcpy(dst->node, src->node, sizeof(int)*src->num_nodes);
  memcpy(dst->edge, src->edge, sizeof(Edge)*src->num_edges);
}


/**************************************************
*
* Function: remove_bridges Find all the bridges in the graph
*
* Parameters:
* @param g
* @param bridges Array of bridges
*
* @return numbef of bridges
*
**************************************************/
int find_bridges(Graph *g, int *bridges)
{

    int i;
    int num_bridges = 0;

    assert(bridges);

    for(i=0; i<g->num_edges; ++i)
    {

        if(g->edge[i].head == 0)
            continue;

        if(is_bridge(g, i))
        {
            bridges[num_bridges] = i;
            ++num_bridges ;
        }
    }

    return num_bridges;
}

/*************************************************
*
* Function: is_bridge
*
* @param g The graph
* @param this_edge The edge to be
*
* @return 1 if this_edge is a bridge, 0 otherwise
*************************************************/
int is_bridge(Graph *g, int this_edge)
{
  Edge *edge = g->edge;
  int start_node = edge[this_edge].head;
  int end_node = edge[this_edge].tail;
  int *node_list = (int*)calloc(g->num_nodes,sizeof(int));
  int i;
  int node_starred;
  int iter = 0;

  node_list[start_node] = 1;

  //fprintf(stderr, "is_bridge: %d\n", this_edge);

  do {

    node_starred = 0;

    if(node_list[end_node] == 1)
      return 0;

    for(i=0; i<g->num_edges; ++i)
    {

      if(i == this_edge)
        continue;

      if((node_list[edge[i].head] == 1) && (node_list[edge[i].tail] != 1))
      {
        node_list[edge[i].tail] = 1;
        node_starred = 1;
      }

      if((node_list[edge[i].tail] == 1) && (node_list[edge[i].head] != 1))
      {
        node_list[edge[i].head] = 1;
        node_starred = 1;
      }

    }

  }while(node_starred == 1);

  free(node_list);

  return 1;
}

/*stack.c 7/8

[top][prev][next]
/**************************************************
*
*
* $Log$
*
*
**************************************************
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"*/

static int stack_pointer = 0;
static void *stack[STACK_DEPTH];

void* pop()
{
    --stack_pointer;
    if(stack_pointer < 0)
    {
        fprintf(stderr, "stack underflow\n");
        abort();
    }

    return stack[stack_pointer];
}

void push(void *x)
{
    stack[stack_pointer] = x;
    stack_pointer ++;
    if(stack_pointer == STACK_DEPTH)
    {
        fprintf(stderr, "stack overflow\n");
        abort();
    }
}

int empty()
{
    return stack_pointer == 0;
}

void* peek()
{
    return stack[stack_pointer-1];
}

int depth()
{
  return stack_pointer;
}


/*worksheet.c 8/8

[top][prev][next]
/**************************************************
*
*
* $Log$
*
*
**************************************************
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "worksheet.h"
#include "stack.h" */

 static void delete_selfloops(Worksheet *);
 static void putdown_bridges(Worksheet *);
 static Worksheet *shrink_edge(Worksheet *, int);
 static Worksheet *delete_edge(Worksheet *, int);
 static int get_an_edge(Worksheet*);

Worksheet* clone_worksheet(Worksheet *w)
{
  Worksheet *new_w = (Worksheet*)malloc(sizeof(*new_w));
  Graph *g = create_graph();

  new_w->size =  w->size;
  new_w->g = g;
  copy_graph(w->g, new_w->g);
  memcpy(new_w->edge_index, w->edge_index, w->size*sizeof(int));

  return new_w;
}

Worksheet* create_worksheet(Graph *g)
{
  Worksheet *w = (Worksheet*)malloc(sizeof(*w));

  w->size = 0;
  w->g = g;

  return w;
}

dump_spanning_tree(Worksheet *w)
{
  int i/*, spanarray[w->size]*/;
   
  printf("spanning tree: ");

  for(i=0; i<w->size; ++i)
  {
	//spanarray[i]=w->edge_index[i];
    printf("%d ", w->edge_index[i]);
  }
  printf("\n");
  
  
}

/*************************************************
*
* Function: split_worksheet
*
* take one worksheet w and split it into two w1 and w2.  remove selfloops and
* bridges in w.  find an arbitrary edge.  w1 is the worksheet by shrinking this
* edge and w2 is the worksheet by deleting this edge.  Upon finish, w is popped
* from a global stack.  w1 and w2 are pushed into the stack.
*
* @param w The input worksheet
*
* @return Undefined
*
*************************************************/

Worksheet* split_worksheet(Worksheet *w)
{
    int any_edge;
    Worksheet *w1,*w2;

    delete_selfloops(w);
    putdown_bridges(w);

    if((any_edge = get_an_edge(w)) == -1)
    { //we are done for this w
        dump_spanning_tree(w);
        pop();
        return w;
    }

    w1 = shrink_edge(w, any_edge);
    w2 = delete_edge(w, any_edge);

    pop();
    push(w1);
    push(w2);

    return w;
}

/*************************************************
*
* Function: get_an_edge
* find an regular (not selfloop nor bridge) in w
*
* @param
*
*************************************************/
static int get_an_edge(Worksheet *w)
{
  Graph *g = w->g;
  int i;

  if(g->num_effective_edges <= 0)
    return -1;

  for(i=0; i<g->num_edges; i++){
    if(g->edge[i].head != 0)
      return i;
  }

  //unreachable
  assert(0);
}

static void delete_selfloops(Worksheet *w)
{
  remove_selfloop(w->g);
}

static void putdown_bridges(Worksheet *w)
{
  int *bridges = (int*)malloc(sizeof(int)*w->g->num_effective_edges);
  int num_bridges = find_bridges(w->g, bridges);
  int i;

  //fprintf(stderr, "put_down_bridges num_bridges: %d\n", num_bridges);

  //put down the bridge number on the worksheet and remove them from the graph
  for(i=0; i<num_bridges; ++i)
  {
    w->edge_index[w->size++] = bridges[i];
    remove_edge(w->g, bridges[i]);
  }

  free(bridges);
}

static Worksheet* shrink_edge(Worksheet *w, int this_edge)
{
  Worksheet *new_w = clone_worksheet(w);
  Graph *g = w->g;
  int this_u = g->edge[this_edge].head;
  int this_v = g->edge[this_edge].tail;
  int i;

  //fprintf(stderr, "shrink_edge: %d\n", this_edge);

  g = new_w->g;

  //substitue every this_v with this_u
  for(i=0; i<g->num_edges; ++i){
    if(g->edge[i].head == this_v)
      g->edge[i].head = this_u;
    if(g->edge[i].tail == this_v)
      g->edge[i].tail = this_u;
  }

  new_w->edge_index[new_w->size++] = this_edge;

  return new_w;
}

/*************************************************
*
* Function: delete_edge
* create a new worksheet by deleting this_edge from the old worksheet w
*
* @param w Old worksheet
* @param this_edge Distinguished edge
*
* @return A new worksheet
*************************************************/
static Worksheet* delete_edge(Worksheet *w, int this_edge)
{
  Worksheet *new_w = clone_worksheet(w);

  remove_edge(new_w->g, this_edge);

  return new_w;
}










