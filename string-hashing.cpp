/* single-hash hashing */
struct Hashing{
	int n;
	int p,m;
	string s;
	vector<int> prefix_hash;
	vector<ll> p_inverse;

	Hashing(string s, int p=29, int m=1e9+7){
		this->s = s;
		this->p = p;
		this->m = m;
		this->n = s.size();

		prefix_hash.resize(n);
		p_inverse.resize(n);

		pre_compute();
	}

	void pre_compute(){
		ll p_pow = 1, prev_hash = 0;

		/* prefix hash calculation */
		for(int i = 0; i < n; i++){
			prefix_hash[i] = (prev_hash + ((s[i]-'a'+1) * p_pow) % m)%m;
			if(i < n-1) p_pow = (p_pow * p)%m;
			prev_hash = prefix_hash[i];
		}

		/* inverse power of p in O(n) time */
		p_inverse[n-1] = mod_inverse(p_pow, m);
		for(int i = n-2; i >= 0; i--){
			p_inverse[i] = (p_inverse[i+1] * p)%m;
		}

	}

	
	ll substr_hash(int l, int r){
		int val1 = prefix_hash[r];
		int val2 = l>0?prefix_hash[l-1]:0LL;


		return (val1-val2+m)%m * p_inverse[l] % m;
	}
};


/* multi-hash hashing */
struct Hashing{
	int n;
	string s;
	vector<int> p, m;
	vector<vector<ll>> prefix_hash, p_inverse;

	Hashing(string s){
		this->s = s;
		this->n = sz(s);

		p = {29, 31};
		m = {1000000007, 1000000009};
		prefix_hash.resize(sz(p), vector<ll> (n));
		p_inverse.resize(sz(p), vector<ll> (n));

		pre_compute();
	}

	void pre_compute(){

		for(int k = sz(p)-1; k >= 0; k--){
			ll p_pow = 1, prev_hash = 0;

			for(int i = 0; i < n; i++){
				prefix_hash[k][i] = (prev_hash + ((s[i]-'a'+1) * p_pow) % m[k])%m[k];
				if(i < n-1) p_pow = (p_pow * p[k])%m[k];
				prev_hash = prefix_hash[k][i];
			}

			p_inverse[k][n-1] = mod_inverse(p_pow, m[k]);
			for(int i = n-2; i >= 0; i--){
				p_inverse[k][i] = (p_inverse[k][i+1] * p[k])%m[k];
			}
		}

	}

	vector<ll> substr_hash(int l, int r){
		vector<ll> res(sz(p));

		for(int k = sz(p)-1; k >= 0; k--){
			ll val1 = prefix_hash[k][r];
			ll val2 = l>0?prefix_hash[k][l-1]:0LL;


			res[k] = mod_mul(mod_sub(val1,val2,m[k]), p_inverse[k][l], m[k]);
		}

		return res;
	}
};