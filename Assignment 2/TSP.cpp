/*
Rishabh Niranjan
1801140

The TSP problem : Given a set of cities and distances between every pair of cities, 
find the shortest way of visiting all the cities exactly once and returning to the starting city.
Assumption : Each city is connected to every other city i.e., complete graph.

Initial State: Agent in the start city and has not visited any other city
Goal State: Agent has visited all the cities and reached the start city again
Edge-cost: distance between the cities represented by the nodes, use this cost to calculate g(n).
h(n): distance to the nearest unvisited city from the current city + 
      estimated distance to travel all the unvisited cities (MST heuristic used here) + 
      nearest distance from an unvisited city to the start city. 
*/
#include<bits/stdc++.h>
#include<cstdio>
#include<cctype> 
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef vector <int>  vi;
typedef queue <int> qi;
typedef queue < char > qc;
typedef queue < string > qs;
typedef vector < char > vc;
typedef vector < string > vs;
typedef pair < int, int >  pii;
typedef pair < long long, long long >  pll;
typedef vector < pair < int, int > >  vpii;
typedef vector < pair < long long, long long > >  vpll;
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define mod 1000000007
#define INF 0x3f3f3f3f 
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); 


void checkNupdate(vector<pair<int,pii>> &open,int tc, int pc, int v){
    for(auto it = open.begin(); it != open.end(); ++it){
        if((*it).ss.ss == v){
            (*it).ss.ff = pc;
            (*it).ff = tc;
            return;
        }
    }
}
// distance to the nearest unvisited city from the current city
int h1(int *adj[], int v, vector<int> leftItems){
    int x = leftItems.size() > 1 ? INT_MAX : 0;
    for(auto it = leftItems.begin(); it != leftItems.end(); ++it){
        if(adj[v][*it] < x && *it != v){
            x = adj[v][*it];
        }
    }
    return x;
}
// nearest distance from an unvisited city to the start city
int h2(int *adj[], int v, vector<int> leftItems){
    int x = leftItems.size() > 1 ? INT_MAX : 0;
    for(auto it = leftItems.begin(); it != leftItems.end(); ++it){
        if(adj[0][*it] < x && *it != v){
            x = adj[0][*it];
        }
    }
    return x;
}

// int calcPathCost(vector<pair<int,int>> adj[], int u,int v){
//     for(auto it = adj[u].begin(); it != adj[u].end(); ++it){
//         if((*it).ff == v) return (*it).ss;
//     }
// }

int checkOpen(vector<pair<int,pii>> open,int v){
    for(auto it = open.begin(); it != open.end(); ++it){
        if((*it).ss.ss == v) return (*it).ff;
    }
}

// This structure represents a directed graph using
// adjacency list representation
struct Graph { 
	int V; //No. of vertices 
    /* Print MST using Prim's algorithm */
    int primMST();
    // In a weighted graph, we need to store vertex 
    // and weight pair for every edge
    list<pii> *edges; 
	Graph(int V) { 
        this->V = V; 
        edges = new list<pii> [V]; 
    } 
	/* function to add an edge to graph */
	void addEdge(int u, int v, int w){ 
        edges[u].pb(mp(v, w)); 
        edges[v].pb(mp(u, w)); 
    }  	 
}; 

/* Prints shortest paths from src to all other vertices */
int Graph::primMST() 
{ 
	/* Create a priority queue to store vertices that 
	 are being preinMST. This is weird syntax in C++.*/ 
	
    // Reference : http://geeksquiz.com/implement-min-heap-using-stl/
	priority_queue< pii, vector <pii> , greater<pii> > pq; 

	int src = 0; // Taking vertex 0 as source

	/* 
    Create a vector for keys and initialize all 
	keys as infinite (INF)
    */
	vector<int> key(V, INF); 

	/* To store parent array which in turn store MST*/ 
	vector<int> parent(V, -1); 

	/* To keep track of vertices included in MST */
	vector<bool> inMST(V, false); 

	/* Insert source itself in priority queue and initialize 
	 its key as 0. */
	pq.push(mp(0, src)); 
	key[src] = 0; 

	/* Looping till priority queue becomes empty */
	while (!pq.empty()) 
	{ 
		/* The ff vertex in pair is the minimum key 
		vertex, extract it from priority queue. 
		vertex label is stored in ss of pair (it 
		has to be done this way to keep the vertices 
		sorted key (key must be ff item 
		in pair) */
		int u = pq.top().ss; 
		pq.pop(); 

		inMST[u] = true; // Include vertex in MST

		/*'i' is used to get all adjacent vertices of a vertex */
		list< pair<int, int> >::iterator i; 
		for (i = edges[u].begin(); i != edges[u].end(); ++i) 
		{ 
			/* Get vertex label and weight of current adjacent 
			 of u. */
			int v = (*i).ff; 
			int weight = (*i).ss; 

			/* If v is not in MST and weight of (u,v) is smaller 
			than current key of v */
			if (inMST[v] == false && key[v] > weight) 
			{ 
				/*Updating key of v */
				key[v] = weight; 
				pq.push(mp(key[v], v)); 
				parent[v] = u; 
			} 
		} 

	} 
	int total_weigh = 0;
	//Calculate Weight of MST
	for (int i = 1; i < V; ++i) {
        for(auto k : edges[i]){
       	    if(k.ff == parent[i])
                total_weigh+=k.ss;
        }
    }

    return total_weigh;
} 

int h_x(int v, int *adj[], vector<int> leftItems){
    int x, y, z;
    // distance to the nearest unvisited city from the current city
    x = h1(adj,v,leftItems);
    // nearest distance from an unvisited city to the start city
    y = h2(adj,v,leftItems);

    // estimated distance to travel all the unvisited cities
    // (MST heuristic used here)
    // Create a graph and add all edges below current node
    Graph graph(leftItems.size()-1);
    int i = 0, j = 0;
    for(auto it = leftItems.begin(); it != leftItems.end(); ++it){
        if(*it != v){ j = i+1;
            for(auto jt = it+1; jt != leftItems.end(); ++jt){
                if(*jt != v){
                    graph.addEdge(i,j,adj[*it][*jt]);
                    ++j;
                }
            }
            ++i;
        }
    }
    // calculate mst_weight
    z = graph.primMST();
    return x+y+z;
}

int a_Star(int **adj, int V){
    //open list of vertices
    vector<pair<int,pii>> open;
    //close list of verices
    vector<int> close;
    //left vertices
    vector<int> leftItems;
    for(int i = 0; i < V; ++i){
        leftItems.pb(i);
    }
    //heuristic for first node
    int heur_Cost = h_x(0,adj,leftItems);
    int path_Cost = 0;
    int total_Cost = heur_Cost + path_Cost;
    int optimal_Cost = 0;

    open.pb( {total_Cost,{path_Cost,0}} );

    while(!leftItems.empty()){
        // finding min cost pair in open to expand
        auto minI = std::min_element(open.cbegin(), open.cend(), [](const auto& lhs, const auto& rhs){
            return lhs.ff < rhs.ff; 
        });
        //storing the extracted pair
        pair<int,pii> storePair = *minI;
        //removing it from open
        open.erase(minI);

        int prev_path_Cost = storePair.ss.ff;

        int city = storePair.ss.ss;
        close.pb(city);
        //removinf from left items
        leftItems.erase(find(leftItems.begin(),leftItems.end(),city));
        if(leftItems.empty()){
            optimal_Cost = prev_path_Cost + adj[0][city];
        }

        for(auto it = leftItems.begin(); it != leftItems.end(); ++it){
            heur_Cost = h_x((*it),adj,leftItems);
            path_Cost = prev_path_Cost + adj[city][*it];
            total_Cost = path_Cost + heur_Cost;
            int isTCinOpen = checkOpen(open,(*it));
            
            if(isTCinOpen != -1){
                checkNupdate(open,total_Cost,path_Cost,(*it));
            }
            else{
                open.pb({total_Cost,{path_Cost,(*it)}});
            }
        }
        
    }
    return optimal_Cost;
}
/* Driver program to test methods of graph class */
int main() 
{ 
    // taking no of vertices
    // and cost of path between each vertex
	int V,**adj;
    cout << "no. of Vertex : ";
    cin >> V;
    adj = new int *[V];
    for(int i = 0; i < V; i++)
        adj[i] = new int[V];
    cout << "Cost in adjacency matrix format : " << endl;
    for(int i = 0; i < V; ++i){
        for(int j = 0; j < V; ++j)
            cin >> adj[i][j];
    }
    int optimal_Cost = a_Star(adj,V);
    cout << "Optimal Cost : " << optimal_Cost <<'\n';
	return 0; 
} 
