int cmp(ll a, ll b){
	if(a > b) return 1;
	else if(a == b) return 0;
	else return -1;
}

int ternary(int l, int r, pto p){ //estrictamente creciente y luego decreciente en el intervalo (l,r]
	while(r > l+1){
		int m = (l+r)/2;
		if( p*S[m] > p*S[m+1])
			r = m;
		else
			l = m;
	}
	return l+1;
}

int f(pto p, vector<pto>& S){ //S = convex hull
	ll sz = S.size();
	if(sz <= 2){
		ll res = 0;
		forn(i,sz)
			if(p * S[i] > p * S[res]) res = i;
		return res;	
	}
	ll a = 1, b = sz;
	while(b-a > 1){
		ll c = (b+a)/2;
		if(cmp(p*S[0], p*S[c]) != cmp(p*S[0], p*S[1])) b = c;
		else a = c;
	}
	
	//la recta con direccion p que pasa por S[0] divide a S en [1,a] y [b,sz-1]
	if(a == sz-1 and p*S[0] >= p*S[a]) return 0;
	if(p*S[0] < p*S[a]) return ternary(0,b-1,p);
	else if(p*S[0] < p*S[b]) return ternary(a,sz-1,p);
	return 0;
}
