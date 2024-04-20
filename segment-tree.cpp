// https://cp-algorithms.com/data_structures/segment_tree.html


struct Node{
	int sum;
	Node(int sum=0){
		this->sum = sum;
	}
};

class SGT{
	vector<Node> seg;
private:
	Node merge(Node &a, Node &b){
		return Node(a.sum+b.sum);
	}
public:
	SGT(int n){
		seg.resize(4*n+1);
	}

	// interval [l, r)
	void build(vector<int> &arr, int l, int r, int node=1){
		if(r-l == 1){
			seg[node] = arr[l];
			return;
		}
		
		int mid = (l+r)/2;

		build(arr, l, mid, 2*node);
		build(arr, mid, r, 2*node+1);


		// data processing step (depends on question)
		seg[node] = merge(seg[2*node], seg[2*node+1]);
	}

	/* query range [x, y) &&&&  interval [l, r)  */
	long long query(int x, int y, int l, int r, int node = 1){
		// outside range
		if(x >= r || y <= l)
			return 0;

		// entirely inside the desired range
		if(x <= l && y >= r)
			return seg[node];


		// partially overlapping case -> explore its childrens
		int mid = (l+r)/2;

		long long left  = query(x, y, l, mid, 2*node);
		long long right = query(x, y, mid, r, 2*node+1);

		return left+right;
	}

	void update(int idx, int val, int l, int r, int node=1){
		if(r-l == 1){
			seg[node] += val;
			return;
		}

		int mid = (l+r)/2;

		if(idx < mid)
			update(idx, val, l, mid, node*2);
		else
			update(idx, val, mid, r, node*2+1);


		// then recalculate the values for parent node
		seg[node] = merge(seg[node*2], seg[node*2+1]);
	}
};




/* 
	Saving entire subarray at each vertex.
	Queries with NO updation.
 */


class MergeSortTree{
	// SC = O(NlogN)
	vector<vector<int>> seg;
public:
	MergeSortTree(int n){
		seg.resize(4*n+1);
	}

	// TC = O(N) for recursion + O(NlogN) for merge operation
	void build(vector<int> &arr, int l, int r, int node=1){
		if(r-l == 1){
			seg[node].push_back(arr[l]);
			return;
		}

		int mid = (l+r)/2;

		build(arr, l, mid, 2*node);
		build(arr, mid, r, 2*node+1);

		// merge list
		merge(seg[2*node].begin(), seg[2*node].end(), 
			seg[2*node+1].begin(), seg[2*node+1].end(), 
			seg[node].begin()
		);
	}

	// smallest number >= key
	int query(int x, int y, int key, int l, int r, int node=1){
		if(r <= x || l >= y)
			return INT_MAX;

		if(l >= x && r <= y){
			auto it = lower_bound(begin(seg[node]), end(seg[node]), key);

			if(it == seg[node].end()) return INT_MAX;

			return *it;
		}

		int mid = (l+r)/2;

		int left = query(x, y, key, l, mid, 2*node);
		int right = query(x, y, key, mid, r, 2*node+1);

		return min(left, right);
	}

	// updation will take O(NlogN*NlogN) time for updation
};


/* QUERIES WITH MODIFICATION  */
class MergeSortTree{
	// SC = O(NlogN)
	vector<multiset<int>> seg;
public:
	MergeSortTree(int n){
		seg.resize(4*n+1);
	}

	// TC = O(N) for recursion + O(N*logN*logN) for merge operation
	void build(vector<int> &arr, int l, int r, int node=1){
		if(r-l == 1){
			seg[node].insert(arr[l]);
			return;
		}

		int mid = (l+r)/2;

		build(arr, l, mid, 2*node);
		build(arr, mid, r, 2*node+1);

		// merge list
		merge(seg[2*node].begin(), seg[2*node].end(), 
			seg[2*node+1].begin(), seg[2*node+1].end(), 
			back_inserter(seg[node])
		);
	}

	// smallest number >= key
	int query(int x, int y, int key, int l, int r, int node=1){
		if(r <= x || l >= y)
			return INT_MAX;

		if(l >= x && r <= y){
			auto it = lower_bound(begin(seg[node]), end(seg[node]), key);

			if(it == seg[node].end()) return INT_MAX;

			return *it;
		}

		int mid = (l+r)/2;

		int left = query(x, y, key, l, mid, 2*node);
		int right = query(x, y, key, mid, r, 2*node+1);

		return min(left, right);
	}

	// updation will take O(N*logN*logN) time for updation
	void update(int idx, int val, int prvVal, int l, int r, int node=1){
		// [l, r) contains prvVal
		seg[node].erase(seg[node].find(prvVal));
		seg[node].insert(val);

		if(l-r == 1)
			return;


		int mid = (l+r)/2;

		if(idx < mid)
			update(idx, val, prvVal, l, mid, 2*node);
		else
			update(idx, val, prvVal, mid, r, 2*node+1);
	}
};