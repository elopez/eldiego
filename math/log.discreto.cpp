//Baby step - giant step.
//Returns x such that a^x = b mod MOD. O(sqrt(MOD)*log(sqrt(MOD))).
ll discrete_log(ll a, ll b, ll MOD)
{
	ll m = min(MOD, (ll)sqrt(MOD)+5); // m >= ceil(sqrt(MOD))
	unordered_map<ll,ll> T;

	ll now = 1;
	forn(j,m){
		if(T.find(now) == T.end()) T[now] = j;
		now = (now*a)%MOD;
	}
	
	ll inv = inverso(now,MOD); // = a^-m
	b %= MOD;
	forn(i,m){
		if(T.find(b) != T.end()) return i*m + T[b]; //found!
		b = (b*inv)%MOD;
	}
	
	return -1; //not found
}
