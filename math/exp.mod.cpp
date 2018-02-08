#define MOD 1000000007
mnum expmod (mnum b, ll e){//O(log b) e>0 !
	if(!e) return 1;
	mnum q = expmod(b,e/2); q = q*q;
	return e%2 ? b*q : q;
}
