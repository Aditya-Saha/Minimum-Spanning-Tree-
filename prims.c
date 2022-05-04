// The program is
// for adjacency matrix representation of the graph


#include <limits.h>//INT_MAX is in this header file

#include <stdio.h>

/* Number of vertices in the graph
#define V 5*/


int main()
{

    int V=5;
    
    /* Let us create the following graph
        2 3
    (0)--(1)--(2)
    | / \ |
    6| 8/ \5 |7
    | /     \ |
    (3)-------(4)
            9         */
            
            
            
    int graph[5][5] = {{ 0, 2, 0, 6, 0 },{ 2, 0, 3, 8, 5 },{ 0, 3, 0, 0, 7 },{ 6, 8, 0, 0, 9 }, { 0, 5, 7, 9, 0 } };
                        
                        
                       
         
            
            
            
     // Array to store constructed MST
    int parent[V];
    // Key values used to pick minimum weight edge in cut
    int key[V];
    // To represent set of vertices included in MST
    int mstSet[V];
   
            
     //prototype of functions      
     int minKey(int key[], int mstSet[],  int V);       
     int printMST(int parent[], int graph[V][V], int V);       
     void primMST(int graph[V][V], int key[], int mstSet[], int parent[], int V);      
            
            
            
            
          
    
    // Print the solution
    primMST(graph, key , mstSet, parent, V);
 
    return 0;
}
//-----------------------------------------------
 
// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], int mstSet[],int V)
{
    // Initialize min value
    int min, min_index;
    
    min = INT_MAX;
 
    for (int v = 0; v < V; v++)
    {
        if (mstSet[v] == 0 && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    
    return min_index;
}
 //------------------------------------------------------------------
// A utility function to print the
// constructed MST stored in parent[]
int printMST(int parent[], int graph[5][5], int V)
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
    {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

 
//------------------------------------------------------------------
void primMST(int graph[5][5], int key[], int mstSet[], int parent[], int V)
{
    
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
    {
    
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
 
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet, V);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = 1;
 
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
        {
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if ((graph[u][v] != 0) && (mstSet[v] == 0 )&& (graph[u][v] < key[v]))
            {
                parent[v] = u, key[v] = graph[u][v];
    
            }
        } 
    }
    
    
 
    // print the constructed MST
    printMST(parent, graph, V);
}
 
//------------------------------------------------------------------

