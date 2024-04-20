struct Node{
	bool isEnd; // count of strings, etc.
	Node *child[26];

	Node(){
		this->isEnd = false;
		for(int i = 0; i < 26; i++) this->child[i] = NULL;
	}

	bool hasChild(char ch){
		return this->child[ch-'a'] != NULL;
	}

	void createChild(char ch){
		this->child[ch-'a'] = new Node();
	}

	Node *goToChild(char ch){
		return this->child[ch-'a'];
	}
};

struct Trie{
	Node *root;

	Trie(){
		root = new Node();
	}

	void insert(string word){
		Node *temp = root;

		for(auto &ch: word){
			if(!temp->hasChild(ch))
				temp->createChild(ch);
			temp = temp->goToChild(ch);
		}

		temp->isEnd = true;
	}

	bool search(string word){
		Node *temp = root;

		for(auto &ch: word){
			if(!temp->hasChild(ch)) return false;

			temp = temp->goToChild(ch);
		}

		return temp->isEnd;
	}
};