// !!! TESTEAR !!!
//Baby step - giant step.
//Returns x such that a^x = b mod MOD. O(sqrt(MOD)*log(sqrt(MOD))).

// IDEA: a^x=b mod MOD <=> x = i*sqrt(MOD)+j con i,j <= sqrt(MOD)=m
// entonces guardo todos los a^j: T[a^j mod MOD]=j
// y después busco si vi T[b/(a^(i*m) mod MOD] = T[b*a^-(i*m) mod MOD], return j+i*m

#define mod(x) (((x)%MOD+MOD)%MOD)

ll discrete_log(ll a, ll b, ll MOD)
{
	a = mod(a); b = mod(b);
	unordered_map<ll,ll> T;
	ll m = min(MOD, (ll)sqrt(MOD)+5); // m >= ceil(sqrt(MOD))

	ll now = 1;
	forn(j,m){
		if(T.find(now) == T.end()) T[now] = j; //con este if da el primer x, si se saca el if sigue andando pero puede no devolver el primer x tal que a^x=b
		now = mod(now*a);
	}
	
	ll inv = inverso(now,MOD); // = a^-m
	forn(i,m){
		if(T.find(b) != T.end()) return i*m + T[b]; //found!
		b = mod(b*inv);
	}
	
	return -1; //not found
}

//con mnum
ll discrete_log(mnum a, mnum b)
{
	unordered_map<ll,ll> T;
	ll m = min(MOD, (ll)sqrt(MOD)+5); // m >= ceil(sqrt(MOD))

	mnum now = 1;
	forn(j,m){
		if(T.find(now.v) == T.end()) T[now.v] = j; //con este if da el primer x, si se saca el if sigue andando pero puede no devolver el primer x tal que a^x=b
		now = now*a;
	}
	
	mnum inv = inverso(now.v,MOD); // = a^-m
	forn(i,m){
		if(T.find(b.v) != T.end()) return i*m + T[b.v]; //found!
		b = b*inv;
	}
	
	return -1; //not found
}
