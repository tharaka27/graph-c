# graph-c

This is a code of a graph implemented in C.

<strong>What you can do with this graph ?</strong>
  
1). <u>initialize graph</u>

read_graph(graphT *g,char *filename);
insert_edge(graphT *g, int x,int y,int w);
print_graph(graphT *g,char *name);
free_graph(graphT *g);
delete_edge(graphT *g, int from , int to);
print_degree(graphT *g);
print_complement(graphT *g ,int k);
eliminatelinks(graphT *g, int minW, int maxW);
differentlinks(graphT *g , graphT *c);
commonlinks(graphT *g , graphT *c);
dfs(graphT *myg1, int k);
bfs(graphT *g, int k);
is_connected(graphT *g);
num_of_conn_comp(graphT *g);
copy_graph(graphT *g);
