#define MAXN 212345

set<int> G[MAXN];

set<int>::iterator it[MAXN];
int S[2][MAXN];//pila
int szS[2];//tamano de la pila
int szC[2];//tamano de la componente
bool vis[MAXN];
void dfsparalelo(int a, int b){ //O(componente mas chica)
	zero(vis);
	szS[0] = szS[1] = 0;
	szC[0] = szC[1] = 1;
	if(sz(G[a])){
		S[0][szS[0]++] = a;//.push(a);
		it[a]  = G[a].begin();
	
	}
	if(sz(G[b])){
		S[1][szS[1]++] = b;//.push(b);
		it[b] = G[b].begin();
	}
	int act = 0;
	vis[a] = vis[b] = true;

//recorre las dos componentes en paralelo	
	while(szS[act]){
		int v = S[act][szS[act]-1];//.top();
		int u = *it[v];
		it[v]++;
		if(it[v] == G[v].end()) szS[act]--;//.pop();
		if(vis[u]){act = 1 - act; continue;}
		szC[act]++;
		if(sz(G[u])>1 or *G[u].begin() != v){
			S[act][szS[act]++] = u;//.push(u);
			vis[u] = true;
			it[u] = G[u].begin();					
		}
		act = 1 - act;
	}
	//ya recorrio la toda la componente de act
	act = 1 - act;

	//sigue recorriendo la otra componente hasta que ve un elemento mas o no tiene mas elementos.		
	while(szC[act] < szC[1-act]+1 and szS[act]){
		int v = S[act][szS[act]-1];//.top();
		int u = *it[v];
		it[v]++;
		if(it[v] == G[v].end()) szS[act]--;//.pop();
		if(vis[u]) continue;
		szC[act]++;
		if(sz(G[u])>1 or *G[u].begin() != v){
			S[act][szS[act]++] = u;//.push(u);	
			vis[u] = true;
			it[u] = G[u].begin();					
		}
	}
	
}
