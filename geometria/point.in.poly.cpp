//checks if v is inside of P, using ray casting
//works with convex and concave.
//includes boundaries, handled separately using segment.inside()
bool inPolygon(pto v, vector<pto>& P) {
	bool c = false;
	forn(i, sz(P)){
		int j=(i+1)%sz(P);
		
		segm lado(P[i],P[j]);
		if(lado.inside(v)) return true; //OJO: return true: incluye lados. return false: excluye lados.
		
		if((P[j].y > v.y) != (P[i].y > v.y) &&
		(v.x < (P[i].x-P[j].x) * (v.y-P[j].y) / (P[i].y-P[j].y) + P[j].x))
			c = !c;
	}
	return c;
}
