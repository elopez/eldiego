bool comp(tipo a, tipo b, tipo c, tipo d){//a*d < b*c
    int s1 = signo(a)*signo(d), s2 = signo(b)*signo(c);
    if(s1 == 0) return s2 > 0;
    if(s2 == 0) return s1 < 0;
    if(s1 > 0 and s2 < 0) return false;
    if(s1 < 0 and s2 > 0) return true;
    if(a / b != c / d) return a/b < c/d; //asume que b y d son positivos
    a %= b, c %= d;
    /*O(1) pero con double:
    long double d1 = ((long double)(a))/(b), d2 = ((long double)(c))/(d);
		return d1 + EPS < d2;
    */
    return comp(d, c, b, a);
}

tipo mcd(tipo a, tipo b){ return a ? mcd(b%a,a) : b; }
struct frac{
	tipo p,q;
	frac(tipo p=0, tipo q=1):p(p),q(q) {norm();}
	void norm(){
		tipo a = mcd(p,q);
		if(a) p/=a, q/=a;
		else q=1;
		if (q<0) q=-q, p=-p;}
	frac operator+(const frac& o){
		tipo a = mcd(q,o.q);
		return frac(p*(o.q/a)+o.p*(q/a), q*(o.q/a));}
	frac operator-(const frac& o){
		tipo a = mcd(q,o.q);
		return frac(p*(o.q/a)-o.p*(q/a), q*(o.q/a));}
	frac operator*(frac o){
		tipo a = mcd(q,o.p), b = mcd(o.q,p);
		return frac((p/b)*(o.p/a), (q/a)*(o.q/b));}
	frac operator/(frac o){
		tipo a = mcd(q,o.q), b = mcd(o.p,p);
		return frac((p/b)*(o.q/a),(q/a)*(o.p/b));}
	bool operator<(const frac &o) const{return p*o.q < o.p*q;}//usar comp cuando el producto puede dar overflow
	bool operator==(frac o){return p==o.p&&q==o.q;}
};
