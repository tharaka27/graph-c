#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue.h"


#define MAXV 100 

 
typedef enum {FALSE,TRUE} bool;

bool visited[6];
typedef struct edgenode{
    int y;
    int weight;
    struct edgenode *next;
} edgenodeT;

typedef struct {
    edgenodeT *edges[MAXV +1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed;
} graphT;

void initialize_graph(graphT *g, bool directed);
void read_graph(graphT *g,char *filename);
void insert_edge(graphT *g, int x,int y,int w);
void print_graph(graphT *g,char *name);
void free_graph(graphT *g);
void delete_edge(graphT *g, int from , int to);
void print_degree(graphT *g);
void print_complement(graphT *g ,int k);
void eliminatelinks(graphT *g, int minW, int maxW);
void differentlinks(graphT *g , graphT *c);
void commonlinks(graphT *g , graphT *c);
void dfs(graphT *myg1, int k);
void bfs(graphT *g, int k);
bool is_connected(graphT *g);
void num_of_conn_comp(graphT *g);
graphT *copy_graph(graphT *g);



int main(int argc, char *argv[]){
     graphT *myg1=NULL , *myg2 = NULL;
     if(argc <2 ){
         fprintf(stderr,"Usage: %s graph_name" , argv[0]);
         exit(-1);
     }
    myg1 = (graphT *)malloc(sizeof(graphT));
    if(myg1==NULL){
        fprintf(stderr,"Cannot allocate memory for the graph");
        exit(-1);
    }
    
    initialize_graph(myg1, FALSE);
    read_graph(myg1, argv[1]);
    print_graph(myg1, "myg1");
    
    //first implement copy_graph function and call it here
    
    myg2 = copy_graph(myg1);
    print_graph(myg2,"myg2");
  
  
  
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+   main loop starts   from here
  //+
  //+
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    while(TRUE){
    char *v ;
    char *d;
    char *quit = "quit\n";
    char input[40];
    //scanf("%s %[^\n]%*c", v,  d );
    fgets(input,40,stdin);
    
    const char space[2] = " ";
    
    v = strtok(input ,space);
    d = v + strlen(v) + 1;

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to insert nodes
  //+
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
     
    if(strcmp(v, "insert")==0){
        int l,j,k;
        char *i;
        i = strtok(d ,space);
        l =atoi(strtok(NULL ,space));
        j =atoi(strtok(NULL ,space));
        k =atoi(strtok(NULL ,space));
        if(strcmp(i,"myg1")==0){
            
            insert_edge(myg1,l,j,k);
            if(myg1->directed ==FALSE){
                     insert_edge(myg1,j, l, k);
                }
        }else{

            insert_edge(myg2,l,j,k);
            if(myg2->directed ==FALSE){
                     insert_edge(myg2,j, l, k);
                }
        }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to delete nodes
  //+
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++      
        
    }else if(strcmp(v, "delete")==0){
        int l,j;
        char *i;
        i = strtok(d ,space);
        l =atoi(strtok(NULL ,space));
        j =atoi(strtok(NULL ,space));
        
        if(strcmp(i,"myg1\n")==0){
            
            delete_edge(myg1,l,j);
            delete_edge(myg2,j,l);
            
        }else{
            delete_edge(myg1,l,j);
           delete_edge(myg2,j,l);
        }
        
    }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to print graph
  //+
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    else if(strcmp(v, "printgraph")==0){
        char *i;
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            print_graph(myg1,"myg1");
        }else{
            print_graph(myg2,"myg2");
        }

        
    }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to print degree of nodes
  //+
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    else if(strcmp(v, "printdegree")==0){
        char *i;
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            print_degree(myg1);
        }else{
            print_degree(myg2);
        }
    }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to print complement 
  //+     of a given string
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    else if(strcmp(v, "printcomplement")==0){
        char *i;
        int k ;
        k = 0;
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            print_complement(myg1,k);
            
        }else{
            
            print_complement(myg2,k);
        }
    }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to eliminate link between
  //+     two given nodes
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    else if(strcmp(v, "eliminatelinks")== 0){
        char *i;
        int k;
        int l;
        i = strtok(d ,space);
        k =atoi(strtok(NULL ,space));
        l =atoi(strtok(NULL ,space));
        if(strcmp(i,"myg1")==0){

            
            eliminatelinks(myg1,k,l);
        }else{

            
            eliminatelinks(myg2,k,l);
        }
       
    }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to print different
  //+     links of two graphs
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    else if(strcmp(v, "differentlinks")==0){
        char *i;
        char *k;
        i = strtok(d ,space);
        k = strtok(NULL ,space);
        if(strcmp(i,"myg1\n")==0){
            
            differentlinks(myg1,myg2);
        }else{
            
            differentlinks(myg2,myg1);
        }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to print common links
  //+     of two given graphs
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    }else if(strcmp(v, "commonlinks")==0){
        char *i;
        char *k;
        i = strtok(d ,space);
        k = strtok(NULL ,space);
        if(strcmp(i,"myg1\n")==0){
            
            commonlinks(myg1,myg2);
        }else{
            
            commonlinks(myg2,myg1);
        }
    }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to print 
  //+     path according to depth first search
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    
    
    else if(strcmp(v, "dfs")==0){

        
        char *i;
        int k;
        i = strtok(d ,space);
        k = atoi(strtok(NULL ,space));
       
        if(strcmp(i,"myg1\n")==0){
            
            int j ;
            for(j=1 ; j<= myg1->nvertices ; j++){
                visited[j] = FALSE;
            }
            dfs(myg1,k);
        }else{
            
            int j ;
            for(j=1 ; j<= myg2->nvertices ; j++){
                visited[j] = FALSE;
            }
            dfs(myg2,k);
        }
    }
    
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to print path according
  //+     to breadth first search
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
  else if(strcmp(v, "bfs")==0){   
        char *i;
        int k;
        i = strtok(d ,space);
        k = atoi(strtok(NULL ,space));
        
        if(strcmp(i,"myg1\n")==0){
              
            bfs(myg1,k);
        }else{
            
            bfs(myg2,k);
        }
    }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to check the connectivity
  //+
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    
    
    else if(strcmp(v, "isconnected")==0){
        
        char *i;
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            if(is_connected(myg1)){
                printf("connected");
            }else{
                printf("not - connected");
            }
            
        }else{
            
            if(is_connected(myg2)){
                printf("connected");
            }else{
                printf("not - connected");
            }
        }
    }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to get the num of 
  //+     connected components.
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    else if(strcmp(v, "numofconncomp")==0){
         
        char *i;
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            num_of_conn_comp(myg1);
            
        }else{
            
            num_of_conn_comp(myg2);
        }
        
        
    }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+  
  //+     this function will be used to quit from programme
  //+
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

    else if(strcmp(v, "quit\n")==0){
        exit(0);
    }
    else{
         printf("something wrong with command try again\n");
    }
 }
    //free_graph(myg1);

}


void initialize_graph(graphT *g,bool directed){
    int i;
    g->nvertices =0;
    g->nedges =0;
    g->directed = directed ;
    for(i=1; i<=MAXV ; i++){
        g->edges[i] = NULL;
    }
    for(i=1; i<=MAXV ; i++){
        g->degree[i] = 0;
    }

}

void read_graph(graphT *g,char *filename){
    int i;
    int n,m, dir;
    int x,y,w;
    FILE *fp;
    if((fp = fopen(filename,"r"))==NULL){
        fprintf(stderr,"Cannot open the graph file");
        exit(-1);
    }
    fscanf(fp,"%d %d %d",&n,&m,&dir);
    g->nvertices = n;
    g->nedges = 0;
    g->directed = dir;
    for(i=1;i<=m;i++){
        fscanf(fp,"%d %d %d",&x , &y , &w);
        insert_edge(g,x,y,w);
        if(dir==FALSE){
            insert_edge(g,y,x,w);
        }
    }
    fclose(fp);
}

void insert_edge(graphT *g,int x,int y,int w){
    edgenodeT *pe;
    pe = malloc(sizeof(edgenodeT));
    if(pe==NULL){
        fprintf(stderr,"Cannot allocate memory for the node" );
        exit(-1);
    }

    pe->weight = w ;
    pe->y = y;
    
    // insert_edge has modified in way even if the user inputs
    // in different orer to make the linked list in order
    if(g->edges[x] == NULL){
        
        pe->next = g->edges[x];
        g->edges[x] = pe;
    }else{

        //if this node already exists we should not ad it again a value
        // so
        edgenodeT *checker;
        checker = g->edges[x];
        while(checker != NULL){
            if( checker->y == y){
                return ;
            }
            checker = checker->next;
        }

        // if there is no node there , then we can add that node

        edgenodeT *qe;
        qe = g->edges[x];
        
        if(qe->y > pe->y){
           pe->next = qe;
           g->edges[x] = pe;
        }else{
            while((qe->next !=NULL) && ((qe->next->y) < (pe->y))){
                qe = qe->next;
            }
          pe->next = qe->next;
          qe->next = pe;
        }
    }
    g->degree[x]++;
    g->nedges++;
}


void print_graph(graphT *g,char *name){
    edgenodeT *pe;
    int i;
    if(!g) {
        
       return;
    }
    printf("Graph Name: %s\n",name);
    for(i=1;i<=g->nvertices;i++){
        printf("Node %d: ",i);
        pe = g->edges[i];
        while(pe ){
            printf(" %d(w=%d),", pe->y,pe->weight);
            pe = pe->next;
        }
    printf("\n");
    }
}

void free_graph(graphT *g){
    edgenodeT *pe, *olde;
    int i;
    for(i=1;i<=g->nvertices;i++){
        printf("Node %d: ",i);
        pe = g->edges[i];
        while(pe){
            olde = pe;
            pe = pe->next;
            free(olde);
        }
    free(g);
    }
}

void delete_edge(graphT *g, int from , int to){
    edgenodeT *pe;
    
    pe = g->edges[from];

    if(g->edges[from] == NULL){
        return ;
    }else{
        if( pe->y == to){
            g->edges[from] = NULL;
        }else{
            while(pe->next->y != to){
                pe = pe->next;
            if(pe->next->next == NULL){
                    pe->next = NULL;
            }else{
                pe->next = pe->next->next;
            }
        }
    }
    g->degree[from]--;
    g->nedges--;
    }
}
graphT *copy_graph(graphT *g){
    graphT *newg;
    edgenodeT *gn ; 
    edgenodeT *cn ; 
    int i ;
    newg = (graphT *)malloc(sizeof(graphT));
    // I simply return the same graph as a copy
    // but you really need to dynamically create
    // another copy f the given graph
    initialize_graph(newg, g->directed);
 
    newg->nedges = g->nedges;
    newg->nvertices = g->nvertices;

    for( i = 1 ; i <= g->nvertices ; i++){
        gn = g->edges[i];
        if(gn == NULL){
            
            newg->edges[i] = NULL;
        }
        else{

            while(gn != NULL){
                insert_edge(newg, i, gn->y,gn->weight);
                if(g->directed ==FALSE){
                     insert_edge(newg,gn->y, i, gn->weight);
                }
                gn = gn->next;
            }
        }
    }
    return newg;
}

void print_degree(graphT *g){
    int i;
    if(g->directed == FALSE){
        //for an directed graph
        for(i=1 ; i<= g->nvertices ; i++){
            printf("number of vertices in node %d is %d\n", i , g->degree[i]);
        }
    }else{
        //for an directed graph
        for(i=1 ; i<= g->nvertices ; i++){
            printf("number of vertices in node %d is %d\n", i , g->degree[i]);
        }
    }

}
void print_complement(graphT *g , int p){ 

//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +     we create a new instance of the
//  +     new graph. and compare this graph with 
//  +     given g graph using differentlinks(cg,g);
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

     int i , k;   
     graphT *cg ;
     edgenodeT *ge;
     cg = (graphT *)malloc(sizeof(graphT));
     if(cg == NULL){
         fprintf(stderr,"Cannot allocate memory for the graph" );
         exit(-1);
     }
     initialize_graph(cg , g->directed);
    cg->directed = g->directed;
    cg->nedges = g->nedges;
    cg->nvertices = g->nvertices;
    for(i = 1  ; i <= g->nvertices; i++){
        for(k =1 ; k <= g->nvertices; k++){
            insert_edge(cg,i,k,1);
        }
    }
    differentlinks(cg, g);
    //print_graph(cg,"complement");  //free_graph(cg); 
}

void eliminatelinks(graphT *g, int minW, int maxW){
    edgenodeT *temp , *prev;
    int i;
    for(i = 1; i <= 6 ; i++){
        printf("%d", i);
        temp = g->edges[i];
        while (temp != NULL && (temp->weight < minW || temp->weight > maxW)){
            g->edges[i] = temp->next;// Changed head
            free(temp); //free old head
            temp = g->edges[i]; //change temp
        }
         
        // delete occurence rather than the head
        while(temp != NULL){
         
            // Search for the node to be deleted, 
            // keep track of the previous node as we 
            // need to change 'prev->next'
            while(temp!= NULL  && (temp->weight >= minW && temp->weight <= maxW)){
                prev = temp;
                temp = temp->next;
            }

            // If required value node was not present
            // in linked list
            if(  temp == NULL){
                break;
            }

            // Unlink the node from linked list
            prev->next = temp->next;
            g->degree[i]--;
            free(temp);

            // Update Temp for next iteration of 
            // outer loop
            temp  = prev->next;

        }

    }
}

void differentlinks(graphT *g , graphT *c){
    edgenodeT *gn , *cn;
    int i ;
    for(i = 1  ; i <= g->nvertices; i++){
        gn = g->edges[i];
        cn = c->edges[i];
        printf("Node %d: ",i);
        
        if(gn == NULL){
           
           continue;
        }
        else{
            
            while(gn != NULL){
               bool exist = FALSE;
               while(cn != NULL){
                   if (gn->y == cn->y){
                       exist = TRUE;
                   }
                cn = cn->next;
                
               }
               if (exist == FALSE){
                    printf("%d(w=%d), ", gn->y,gn->weight );       
                }
            cn = c->edges[i];
            gn = gn->next;
            }
        }
            
    printf("\n");
    }
}
void commonlinks(graphT *g , graphT *c){
    
    edgenodeT *gn , *cn;
    int i ;
    for(i = 1  ; i <= g->nvertices; i++){
        gn = g->edges[i];
        cn = c->edges[i];
        printf("Node %d: ",i);
        
        if(gn == NULL){
           
           continue;
        }
        else{
            
            while(gn != NULL){
               bool exist = FALSE;
               while(cn != NULL){
                   if (gn->y == cn->y){
                       exist = TRUE;
                   }
                cn = cn->next;
                
               }
               if (exist){
                    printf("%d(w=%d), ", gn->y,gn->weight );       
                }
            cn = c->edges[i];
            gn = gn->next;
            }
        }      
    printf("\n");
    }
}




void dfs(graphT *g, int k){
    printf("%d->",k);
    
    edgenodeT *pe;
    pe = g->edges[k];
    visited[k]=TRUE;
    while(pe != NULL){
        k = pe->y;
        if(!visited[k]){
            dfs(g,k);
        }
        pe = pe->next;
    }
}

void bfs(graphT *g, int k){

    create();
    edgenodeT *pe;
    pe = g->edges[k];
    int i, bvisited[g->nvertices] ,w ,p;
    for(i= 1;i<=g->nvertices;i++){
        bvisited[i] = 0;
    }
    enq(k);
    bvisited[k] = 1;
    printf("\nVisited\t%d",k);

    while(queuesize() != 0){
    
        p = deq();
        pe = g->edges[p];
        while(pe != NULL){
         
            w = pe->y;
         
            if(bvisited[w]==0){
            enq(w);
            bvisited[w]=1;
            printf("-> %d",w);
            }
            pe = pe->next;
        }
    }
}

bool is_connected(graphT *g){
    if(g->directed== TRUE){
        printf("Purchase the next version of this program :)");
        return FALSE;
    } else{
        
        bool connected ;
        connected = TRUE;

        create();
        edgenodeT *pe;
        pe = g->edges[1];
        int i, bvisited[g->nvertices] ,w ,p;
        for(i= 1;i<=g->nvertices;i++){
            bvisited[i] = 0;
        }
        enq(1);
        bvisited[1] = 1;

        while(queuesize() != 0){
    
            p = deq();
            pe = g->edges[p];
            while(pe != NULL){
         
                w = pe->y;
                if(bvisited[w]==0){
                    enq(w);
                    bvisited[w]=1;
                }
                pe = pe->next;
            }
        }
        for(i= 1;i<=g->nvertices;i++){
            if(bvisited[i] == 0){
                connected =FALSE;
            }
        }
        
        return connected;
    }

}
void num_of_conn_comp(graphT *g){
    if(g->directed== TRUE){
        printf("Purchase the next version of this program :)");
    } else{
        if(is_connected(g)){
            printf("%d number of connected components.", g->nvertices);
        }
        
    }

}
