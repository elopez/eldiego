int cmp(ll a, ll b){
	if(a > b) return 1;
	else if(a == b) return 0;
	else return -1;
}

int binary(int l, int r, pto p){ //devuelve el índice del punto más lejano en dirección p de (l,r]
	while(r-l > 1){
		int m = (l+r)/2;
		if(p*S[m] > p*S[m+1]) r = m;
		else l = m;
	}
	return l+1;
}

//índice de punto más lejano de S en dirección p. (como tiene dirección puede ser negativa la distancia)
//o sea, devuelve i si S[i] es el punto con mayor proyección (con signo) sobre la recta que pasa por (0,0) y p.
int f(pto p, vector<pto>& S){ //S = convex hull
	ll sz = S.size();
	if(sz <= 2){
		ll res = 0;
		forn(i,sz) if(p*S[i] > p*S[res]) res = i;
		return res;	
	}
	
	//busco el S[a] tal que la recta con dirección perpendicular a p que pasa por S[0] divide a S en [1,a] y [a+1,sz-1]
	ll a = 1, b = sz;
	while(b-a > 1){
		ll c = (b+a)/2;
		if(cmp(p*S[0], p*S[c]) != cmp(p*S[0], p*S[1])) b = c;
		else a = c;
	}
	
	if(a == sz-1 and p*S[0] >= p*S[a]) return 0;
	if(p*S[0] < p*S[a]) return binary(0,a,p);
	else if(p*S[0] < p*S[b]) return binary(a,sz-1,p);
	return 0;
}
