struct trie{
	map<char, trie> m;
	bool end=false;
	void add(const string &s, int p=0){
		if(s[p]) m[s[p]].add(s, p+1);
		else end=true;
	}
	void dfs(){
		//Do stuff
		forall(it, m)
			it->second.dfs();
	}
};
