#include <bits/stdc++.h>
typedef long long ll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct order_cost_update
{
	typedef struct { ll order, cost; } metadata_type;

	typedef typename Node_CItr::value_type const_iter;
	typedef typename Node_CItr::value_type iter;

	virtual Node_CItr node_begin() const = 0;
	virtual Node_CItr node_end() const = 0;

	inline void operator()(Node_Itr it, Node_CItr end_it) const {
		auto &im = it.get_metadata();
		auto &order = const_cast<ll&>(im.order);
		auto &cost = const_cast<ll&>(im.cost);

		order = (*it)->second;
		cost = (*it)->first * order;

		auto l = it.get_l_child();
		if(l != end_it) {
			auto &lm = l.get_metadata();
			order += lm.order;
			cost += lm.cost;
		}

		auto r = it.get_r_child();
		if(r != end_it) {
			auto &rm = r.get_metadata();
			order += rm.order;
			cost += rm.cost;
		}
	}

	// permite calcular costo de n comprar los n primeros items
	inline pair<const_iter,metadata_type> get_kth(ll x) {
		metadata_type d = {};
		auto it = node_begin();
		const_iter last = *node_end();

		while(it != node_end())
		{
			metadata_type lm = {};
			auto l = it.get_l_child();
			if (l != node_end()) {
				auto &lm2 = l.get_metadata();
				lm.order = lm2.order;
				lm.cost = lm2.cost;
			}

			if (!Cmp_Fn()(lm.order, x)) {
				it = l; // contenido a la izq
			} else if (!Cmp_Fn()(lm.order + (*it)->second, x)) {
				d.order += x;  // contenido en este
				d.cost += lm.cost + (x-lm.order) * (*it)->first;
				return make_pair(*it, d);
			} else { // contiene este y más
				d.order += lm.order + (*it)->second;
				d.cost += lm.cost + (*it)->first * (*it)->second;

				x -= lm.order + (*it)->second;
				last = *it;
				it =  it.get_r_child();
			}
		}

		return make_pair(last,d);
	}
};

// OJO! no actualizar elementos ni usar map[x]=y, siempre
// usar find() + erase() + insert()
// map.insert({cost,qty})
typedef tree<ll, ll, less<ll>, rb_tree_tag, order_cost_update> rb_map;


// problema Global Elephant Market
// 2013-2014 ACM-ICPC, NEERC, Moscow Subregional Contest
// http://codeforces.com/gym/100257/attachments
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	rb_map wtb, wts;

	string cmd;

	while (cin >> cmd) {
		if (cmd[0] == 'b') {
			ll qty, price;
			cin >> qty >> price;
			auto it = wtb.find(-price);
			if (it != wtb.end()) {
				qty += it->second;
				wtb.erase(it);
			}
			wtb.insert(make_pair(-price, qty));
		} else if (cmd[0] == 's') {
			ll qty, price;
			cin >> qty >> price;
			auto it = wts.find(price);
			if (it != wts.end()) {
				qty += it->second;
				wts.erase(it);
			}
			wts.insert(make_pair(price, qty));
		} else {
			return 0;
		}

		ll a = 0, b = min(wts.get_kth((1LL<<62)+5).second.order, wtb.get_kth((1LL<<62)+5).second.order)+1;

		while (b-a>1) {
			ll m = (a+b)/2;
			auto bought = wts.get_kth(m);
			auto sold = wtb.get_kth(m);

			if (-sold.first->first > bought.first->first) { //-sold.cost > bought.cost) {
				a = m;
			} else {
				b = m;
			}
		}

		auto bought = wts.get_kth(a);
		auto sold = wtb.get_kth(a);
		cout << - bought.second.cost - sold.second.cost << endl;
		cout.flush();
	}
}
