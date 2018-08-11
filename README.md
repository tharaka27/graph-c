# graph-c

<strong>This is a code of a graph implemented in C.</strong>

# How to use this graph ?

First of all yo have to allocate memory for the graph. which you can do with following.

```c
graphT *myg1=NULL , *myg2 = NULL;
     if(argc <2 ){
         fprintf(stderr,"Usage: %s graph_name" , argv[0]);
         exit(-1);
     }
    myg1 = (graphT *)malloc(sizeof(graphT));
```
They you can use following method to implement the graph as you wish.


### 1.Initialize the graph.
This will initialize the graph. There are two parameters which you should pass.
One is the graph *myg1* second is the directionality of the graph.
*TRUE* if directed *FALSE* if undirected.
```c
void initialize_graph(graphT *g, bool directed);
```
Example :
```c
initialize_graph(myg1, FALSE);
```


### 2.Read the graph.
This will read the graph from given file. We have added an example file so you can have a
idea about how data should be presented in graph
```c
void read_graph(graphT *g,char *filename);
```
Example :
```c
read_graph(myg1, argv[1]);
```


### 3. Insert an edge.
This will insert an edge with weight *w* to graph g from *x* to *y*. 
```c
void insert_edge(graphT *g, int x,int y,int w);
```
Example :
```c
insert_edge(myg1,1, 2, 10);
```


### 4. Delete an edge.
This will delete the edge of graph 
```c
void delete_edge(graphT *g, int from , int to);
```
Example :
```c
delete_edge(myg1,1,2);
```


### 5. Print graph.
This function can be used to print the graph. Name of the graph should be *name*
```c
void print_graph(graphT *g,char *name);
```
Example :
```c
print_graph(myg1, "myg1");
```


### 6.Print degree.
This function will print the degree of the given graph
```c
print_degree(graphT *g);
```
Example :
```c
print_degree(myg1);
```

### 7.Print Complement.
This function will print the compliment grpah of given grpah. set the k value for 1. 
```c
void print_complement(graphT *g ,int k);
```
Example :
```c
print_complement(myg1,1);
```


### 8.Eliminate links.
This function will eliminate the links which have a weight less than *minW* or more than *maxW*
```c
void eliminatelinks(graphT *g, int minW, int maxW);
```
Example :
```c
eliminatelinks(myg1,2,5);
```


### 9.Different Links.
This will find the different links between graph *g* and *c*. graph *g* will be given priority
so this will print the links of *g* which are not in *c*
```c
void differentlinks(graphT *g , graphT *c);
```
Example :
```c
differentlinks(myg1,myg2);
```

### 10.Common Links.
This will find and print the common links of graph *g* and graph *c*
```c
void commonlinks(graphT *g , graphT *c);
```
Example :
```c
commonlinks(myg2,myg1);
```

### 11. Depth First Search.
This function will perform the Depth First Search starting from node *k*
```c
void dfs(graphT *myg1, int k);
```
Example :
```c
dfs(myg1,1);
```

### 12.Breadth First Search.
This function will perform the Breadth First Search starting from node *k*
```c
void bfs(graphT *g, int k);
```
Example :
```c
bfs(myg1,1);
```

### 13.Check the connectivity of a graph.
This will return *True* if the graph is connected of *False* if not
```c
bool is_connected(graphT *g);
```
Example :
```c
bool connected;
connected = is_connected(myg1);
```




### 13.Check the number of connected components.
This will print the number of connected components in the graph
```c
void num_of_conn_comp(graphT *g);
```
Example :
```c
num_of_conn_comp(myg1);
```


### 13.Copy a graph.
This will copy the give graph and will return the pointer to the newly created graph 
```c
graphT *copy_graph(graphT *g);
```
Example :
```c
myg2 = copy_graph(myg1);
```


