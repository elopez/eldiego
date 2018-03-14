//chequea que ab sea una diagonal de poly en O(n).
bool isDiagonal(pto a, pto b, vector<pto> &poly) 
{
	segm d(a,b);

	forn(i,poly.size()) if(!(poly[i]==a) and !(poly[i]==b)){
		int j = (i+1)%poly.size();
		if(poly[j]==a or poly[j]==b) continue;
		
		segm lado(poly[i],poly[j]);
		pto x = inter(d,lado);
		if(x.y != INF and !(x==a) and !(x==b)) return false; //ab corta lado
	}
	
	pto medio = (a+b)/2;
	if(! inPolygon(medio,poly)) return false; //ab afuera de poly
	
	return true;
}

//descompone un polígono (cóncavo o convexo) en triángulos en O(n^3).
vector<vector<pto>> triang(vector<pto> &poly)
{
	vector<vector<pto>> ans;
	if(poly.size() <= 3) {
		if(poly.size() == 3) ans.pb(poly); 
		return ans;
	}
	
	vector<pto> T;
	pto p=poly[0];
	pto q=poly[1];
	T.pb(p); T.pb(q);
	forr(i,2,poly.size()) {
		pto x=poly[i];
		if(isDiagonal(p,x,poly) and isDiagonal(q,x,poly)){
			T.pb(x);
			ans.pb(T);
			
			vector<pto> left,right;
			forr(j,i,poly.size()) left.pb(poly[j]);
			left.pb(poly[0]);
			forr(j,1,i+1) right.pb(poly[j]);
			
			vector<vector<pto>> ans1 = triang(left);
			for(auto t:ans1) ans.pb(t);
			ans1 = triang(right);
			for(auto t:ans1) ans.pb(t);
			
			return ans;
		}
	}
	
	return ans;
}

/*
Este algoritmo usa el teorema de que para todo lado ab del polígono existe un vértice x
tal que abx es un triángulo adentro del polígono (o sea, ax y bx son diagonales).

El teorema "ear clipping" dice que existe un par de lados consecutivos ab y bc,
tales que abc es un triángulo adentro del polígono (o sea, ac es diagonal).
*/
