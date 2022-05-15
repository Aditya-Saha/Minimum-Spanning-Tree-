#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
struct Edge 
{
   int src, dest, weight;
};
struct Graph 
{
   int V, E;
   struct Edge* edge;
};
struct subset 
{
   int parent;
   int rank;
};

//--------------------------------------------------------------
struct Graph* createGraph(int V, int E)
{
   struct Graph* graph = (struct Graph*)(malloc(sizeof(struct Graph)));
   graph->V = V;
   graph->E = E;
   
   graph->edge = (struct Edge*)malloc(sizeof( struct Edge)*E);
   
   return graph;
}
//-----------------------------------------------------------------
int find(struct subset subsets[], int i)
{
   if (subsets[i].parent != i)
   {
      subsets[i].parent   = find(subsets, subsets[i].parent);
   }
  
   return subsets[i].parent;
}
//-------------------------------------------------------------------
void Union(struct subset subsets[], int x, int y)
{
   int xroot = find(subsets, x);
   int yroot = find(subsets, y);
   if (subsets[xroot].rank < subsets[yroot].rank)
   {
      subsets[xroot].parent = yroot;
   }
   else if (subsets[xroot].rank > subsets[yroot].rank)
   {
      subsets[yroot].parent = xroot;
   }
   else
   {
      subsets[yroot].parent = xroot;
      subsets[xroot].rank++;
   }
}

//-----------------------------------------------------------------
void sort(struct Edge arr[],int edg)
{
   struct Edge temp;
   int i, j ,flag=1;
  
   i=0;
   while(i<edg && flag==1)
   {
      flag=0;
      j=0;
      while(j<(edg-i-1))
      {
         if((arr[j].weight)>(arr[j+1].weight))//this check is done to make the array in ascending order
         {
             //swapping the elements
             temp=arr[j];
             arr[j]=arr[j+1];
             arr[j+1]=temp;
             flag=1;
         }
         j=j+1;
      }
      i=i+1;
    }
      
}

//-------------------------------------------------------------------
void KruskalMST(struct Graph* graph)
{
   int V, e, i, v, x, y, minimumCost;
   
   struct subset* subsets;

   V = graph->V;  
   struct Edge result[V]; 
   
   e = 0;
   i = 0;
  
   //sorting the edges in ascensing order
   sort(graph->edge,graph->E);
     
   subsets  = (struct subset*)malloc(V * sizeof(struct subset));
   
   //this part is same as make_set(x) function
   printf("\nno. of vertex is..=%d",V);
   for (v = 0; v < V; ++v)
   {
      subsets[v].parent = v;
      subsets[v].rank = 0;
   }
      
   while (e < V - 1 && i < graph->E) 
   {
       
      struct Edge next_edge = graph->edge[i];
      i++;
      
      //finding the root of the source and destination vertex
      x = find(subsets, next_edge.src);
       y = find(subsets, next_edge.dest);
       
      //when root/parent of the source and destination vertex is not same 
      //we add the edge into the result array which contain the MST edges
      if (x != y) 
      {         
         result[e] = next_edge;
         e++;
         Union(subsets, x, y);
      }
   }
   
   
   printf("Following are the edges in the constructed MST with %d  edges\n",e);
  minimumCost = 0;
   for (i = 0; i < e; ++i)
   {
      printf("%d -- %d == %d\n", result[i].src,
      result[i].dest, result[i].weight);
      minimumCost += result[i].weight;
   }
   printf("Minimum Cost Spanning tree : %d",minimumCost);
   return;
}
int main()
{
   /* Let us create the following weighted graph
       30
   0--------1
   | \      |
 26| 25\    |15
   |     \  |
   2--------3
       24 */
   int V = 4;
   int E = 5;
   struct Graph* graph = createGraph(V, E);
   graph->edge[0].src = 0;
   graph->edge[0].dest = 1;
   graph->edge[0].weight = 30;
   
   graph->edge[1].src = 0;
   graph->edge[1].dest = 2;
   graph->edge[1].weight = 26;
   
   graph->edge[2].src = 0;
   graph->edge[2].dest = 3;
   graph->edge[2].weight = 25;
   
   graph->edge[3].src = 1;
   graph->edge[3].dest = 3;
   graph->edge[3].weight = 35;
   
   graph->edge[4].src = 2;
   graph->edge[4].dest = 3;
   graph->edge[4].weight = 24;
   
   
   KruskalMST(graph);
   return 0;
}




/*//---------------------------------------------------------------------
int myComp(const void* a, const void* b){
   struct Edge* a1 = (struct Edge*)a;
   struct Edge* b1 = (struct Edge*)b;
   return a1->weight > b1->weight;
}








 for (v = 0; v < V; ++v)
   {
      printf("\nparent=%d",subsets[v].parent );
      printf("\nrank=%d",subsets[v].rank );
   }*/
