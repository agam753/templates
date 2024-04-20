#include<bits/stdc++.h>
using namespace std;


#define MX (int)1e5+1

int N;
int LG = 20;
int depth[MX];
int parent[MX][20];
vector<int> adj[MX];


void dfs(int node, int par){
	parent[node][0] = par;

	for(auto &adjNode: adj[node]){

		if(adjNode == par) continue;
	   
	    depth[adjNode] = 1+depth[node];
		dfs(adjNode, node);
	
	}
}

void build(){
	dfs(0, -1);

	for(int i = 1; i < LG; i++){
        for(int node = 0; node < N; node++){
            if(parent[node][i-1] != -1)
                parent[node][i] = parent[parent[node][i-1]][i-1];
        }
    }
}


int getAncestor(int node, int k){
	int b = 0;

	while(k && node != -1){
		if(k&1)
			node = parent[node][b];

		k >>= 1;
		b++;
	}

	return node;
}

int LCA(int a, int b){
	if(depth[a] < depth[b])
		swap(a, b);

	int dif = depth[a] - depth[b];

	a = getAncestor(a, dif);

	if(a == b) return a;

	for(int i = LG-1; i >= 0; i--){
		if(parent[a][i] != parent[b][i]){
			a = parent[a][i];
			b = parent[b][i];
		}
	}

	// immediate parent of a and b is the LCA
	return parent[a][0];
}


int main(){

	// initialization code
	for(int i = 0; i < n; i++){
		adj[i].clear();

		depth[i] = 0;

		for(int j = 0; j < LG; j++)
			parent[i][j] = -1;
	}
	

	build();


	cout << LCA(3, 2);


	return 0;
}
