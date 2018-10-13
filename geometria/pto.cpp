const double EPS=1e-9;
typedef double tipo; //OJO con EPS si es int o ll en < y ==
struct pto{
	tipo x, y;
	pto(tipo x=0, tipo y=0):x(x),y(y){}
	pto operator+(pto a){return pto(x+a.x, y+a.y);}
	pto operator-(pto a){return pto(x-a.x, y-a.y);}
	pto operator+(double a){return pto(x+a, y+a);}
	pto operator*(double a){return pto(x*a, y*a);}
	pto operator/(double a){return pto(x/a, y/a);}
	//dot product, producto interno:
	//Significado: a*b = a.norm * b.norm * cos(ang).
	tipo operator*(pto a){return x*a.x+y*a.y;}
	//module of the cross product or vectorial product:
	//if a is less than 180 clockwise from b, a^b>0. Significado: abs(a^b) = area del paralelogramo.
	tipo operator^(pto a){return x*a.y-y*a.x;}
	//returns true if this is at the left side of line qr
	bool left(pto q, pto r){return ((q-*this)^(r-*this))>0;}
	bool operator<(const pto &a) const{return x<a.x-EPS || (abs(x-a.x)<EPS && y<a.y-EPS);}
	bool operator==(pto a){return abs(x-a.x)<EPS && abs(y-a.y)<EPS;}
	double norm(){return sqrt(x*x+y*y);}
	tipo norm_sq(){return x*x+y*y;}
};
double dist(pto a, pto b){return (b-a).norm();}
tipo dist_sq(pto a, pto b){return (b-a).norm_sq();}
typedef pto vec;

//positivo si aob están en sentido antihorario con un ángulo <180º
double angle(pto a, pto o, pto b){ //devuelve radianes! (-pi,pi)
	pto oa=a-o, ob=b-o;
	return atan2(oa^ob, oa*ob);}

//rotate p by theta rads CCW w.r.t. origin (0,0)
pto rotate(pto p, double theta){
	return pto(p.x*cos(theta)-p.y*sin(theta),
	p.x*sin(theta)+p.y*cos(theta));}
