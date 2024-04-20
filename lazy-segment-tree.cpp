// range update and range query
// it delays the calculations until it is required
/*
			THINKING of LAZY problems

	i) what to store in lazy 
	ii) how to apply calculations to current node
	iii) what to push to cur node's children
	iV) rest is the standard segment tree


*/

struct Node{
	ll sum;
	int lazy;
	Node(){
		sum = 0;
		lazy = 0;
	}
};

class LazySGT{
	vector<Node> seg;

private:
	Node merge(Node &a, Node &b){
		Node t;
		t.sum = a.sum + b.sum;
		return t;
	}

	void apply(int l, int r, int node){
		// apply logic
		seg[node].sum += (r-l)*seg[node].lazy;
	}

	void push(int l, int r, int node){
		if(seg[node].lazy != 0){
			// apply logic
			apply(l, r, node);

			// push down
			if(r-l != 1){
				seg[node<<1].lazy += seg[node].lazy;
				lazy[node<<1 | 1] += seg[node].lazy;
			}

			seg[node].lazy = 0;
		}
	}
	
public:
	LazySGT(int n){
		seg.resize(4*n+1);
	}

	void build(vector<int> &arr, int l, int r, int node=1){
		if(r-l == 1){
			Node t;
			t.sum = arr[l];
			seg[node] = t;
			return;
		}

		int mid = (l+r) >> 1;

		build(arr, l, mid, 2*node);
		build(arr, mid, r, 2*node+1);

		seg[node] = merge(seg[2*node], seg[2*node+1]);
	}

	void update(int val, int x, int y, int l, int r, int node=1){
		push(l, r, node); // lazy update for any node

		if(l >= y || r <= x)
			return;

		if(l >= x && r <= y){
			seg[node].lazy += val;
			push(l, r, node);
			return;
		}


		int mid = (l+r)/2;

		update(val, x, y, l, mid, 2*node);
		update(val, x, y, mid, r, 2*node+1);

		seg[node] = merge(seg[2*node], seg[2*node+1]);
	}

	int query(int x, int y, int l, int r, int node=1){
		// lazy updates
		push(l, r, node);

		if(l >= y || r <= x)
			return 0;

		if(l >= x && r <= y)
			return seg[node].sum;

		int mid = (l+r) >> 1;

		ll left = query(x, y, l, mid, 2*node);
		ll right = query(x, y, mid, r, 2*node+1);

		return left + right;
	}
};