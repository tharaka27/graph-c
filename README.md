# graph-c

## This is a code of a graph implemented in C.

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
