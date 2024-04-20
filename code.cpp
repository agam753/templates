#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;


#define agam_gupta

#define endl '\n'
#define ll long long
#define MP make_pair
#define fs first
#define sc second
#define pb push_back
#define ppb pop_back
#define FOR(i, a, n) for(ll i = (a); i <= (n); i++)
#define FORD(i, a, n) for(ll i = (a); i >= (n); i--)
#define all(v) (v).begin(), (v).end()
#define sz(v) (int)(v).size()
#define MOD 1000000007
#define INF (ll)1e18

#ifdef agam_gupta
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif


typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key


void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(float t) {cerr << t;}
void _print(long double t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(unsigned ll t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
void _print(pbds v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}


/******************************INTERACTOR************************************/
/*struct Interactor{
	ll n;
	vector<ll> v;
	Interactor(ll n, vector<ll> &v){
		this->n = n;
		this->v = v;
	}

	ll make_query(int l, int h){
		return v[l]+v[h];
	}
};
ll make_query(int l, int h){
	cout << "? " << l << " " << h << endl;

	int idx;
	cin>>idx;

	return idx;
}*/
/******************************INTERACTOR************************************/


/******************************UTILITY***************************************/
ll mod_mul(ll a, ll b, ll m){ a = a%m; b = b%m; return (a*b)%m; }
ll mod_add(ll a, ll b, ll m){ a = a%m; b = b%m; return (a+b)%m; }
ll mod_sub(ll a, ll b, ll m){ a = a%m; b = b%m; return (((a-b)%m)+m)%m; }
ll mod_expo(ll a, ll b, ll m) { a = a%m; b = b%m; ll ans = 1; while(b){ if(b&1) ans = (ans*a)%m; a = (a*a)%m; b >>= 1; } return ans%m; }
ll mod_inverse(ll a, ll b){ return mod_expo(a, b-2, b); }
ll expo(ll a, ll b){ ll ans = 1; while(b){ if(b&1) ans *= a; a *= a; b >>= 1; } return ans; }
ll combination(ll n, ll r, ll m, vector<ll> &fact, vector<ll> &ifact) {return mod_mul(fact[n], mod_mul(ifact[r], ifact[n-r], m), m);}
ll gcd(ll a, ll b) { if(b == 0) return a; return gcd(b, a % b); } 
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

vector<bool> Prime;
void sieve(ll n){
	Prime.resize(n+1, 1);

	Prime[0] = Prime[1] = 0;
	// NLog(LogN)
	FOR(i, 2, n){
		if(Prime[i] == 1){
			// start from i*i not from 2*i
			for(ll j = i*i; j <= n; j += i){
				Prime[j] = 0;
			}
		}
	}
}
/******************************UTILITY***************************************/



void run(){
	int n;
	cin>>n;

	vector<int> arr(n);
	FOR(i, 0, n-1) cin>>arr[i];

	if(arr[0] != arr[n-1]){
		cout << "NO" << endl;
		return;
	}

	FOR(i, 1, n-2){
		if(arr[i] < arr[0]){
			cout << "NO" << endl;
			return;
		}
	}

	cout << "YES" << endl;
}

int main(){
#ifdef agam_gupta
    freopen("debug.txt", "w", stderr);
#endif
	ios::sync_with_stdio(false); cin.tie(NULL);

	int t=1;
	cin>>t;

	while(t--){
		run();
	}
	return 0;
}