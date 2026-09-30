#include<bits/stdc++.h>
using namespace std;

template<typename data_type>
struct PersistentFrequencySegmentTree {
    struct SegmentTreeNode {
        data_type data;
        int l, r;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(data_type data, int l, int r, SegmentTreeNode* left, SegmentTreeNode* right): data(data), l(l), r(r), left(left), right(right) {}
    };
    vector<SegmentTreeNode*> version_roots;
    PersistentFrequencySegmentTree(int n) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), 0, n - 1, nullptr, nullptr));
        build(version_roots[0]);
    }
    PersistentFrequencySegmentTree(int l, int r, vector<data_type> &a) {
        version_roots.emplace_back(new SegmentTreeNode(data_type(), l, r, nullptr, nullptr));
        build(version_roots[0], a);
    }
    void build(SegmentTreeNode *root) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = data_type();
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr,nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left);
        build(root -> right);
        }
    void build(SegmentTreeNode *root, vector<data_type> &a) {
        if (root -> l == root -> r) {
            // -1 porque indexamos en 1
            root -> data = a[root -> l - 1];
            return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new SegmentTreeNode(data_type(), root -> l, mi, nullptr, nullptr);
        root -> right = new SegmentTreeNode(data_type(), mi + 1, root -> r,nullptr, nullptr);
        build(root -> left, a);
        build(root -> right, a);
    }
    void update(int pos, data_type value, SegmentTreeNode *last, SegmentTreeNode *curr) {
        if (curr -> l == curr -> r) {
            curr -> data += value; //cambio está aquí
            return;
        }
        int mi = (curr -> l + curr -> r) / 2;
        if (pos <= mi) {
            curr -> right = last -> right;
            curr -> left = new SegmentTreeNode(last -> left -> data, curr -> l, mi,
            nullptr, nullptr);
            update(pos, value, last -> left, curr -> left);
        }
        else {
            curr -> left = last -> left;
            curr -> right = new SegmentTreeNode(last -> right -> data, mi + 1, curr
            -> r, nullptr, nullptr);
            update(pos, value, last -> right, curr -> right);
        }
        curr -> data = curr -> left -> data + curr -> right -> data;
    }
    int update(int version, int pos, data_type value) {
        SegmentTreeNode *root = new SegmentTreeNode(data_type(), version_roots[0]-> l, version_roots[0] -> r, nullptr, nullptr);
        version_roots.emplace_back(root);
        update(pos, value, version_roots[version], root);
        return (int)version_roots.size() - 1;
    }
    data_type query(int x, int y, SegmentTreeNode *root) {
        if (y < root -> l or root -> r < x or x > y) return data_type(0);
        if (x <= root -> l and root -> r <= y) return root -> data;
        return query(x, y, root -> left) + query(x, y, root -> right);
    }
    data_type query(int version, int x, int y) {
        return query(x, y, version_roots[version]);
    }

    int kth(int k, SegmentTreeNode* lastver, SegmentTreeNode* currver) {
        if (lastver->l == lastver->r) return lastver->l;
        if (k <= currver->left->data - lastver->left->data) return kth(k, lastver->left, currver->left);
        return kth(k - (currver->left->data - lastver->left->data), lastver->right, currver->right);
    }

    int kth(int k, int lastver, int currver) {
        return kth(k, version_roots[lastver], version_roots[currver]);
    }



    int get_current_version() {
        return (int)version_roots.size() - 1;
    }
};

//Persistent trie and reference main from implementation from mridul1809 on GitHub
//https://github.com/mridul1809/CompetitiveProgramming/blob/master/templates/Trie.cpp


class Trie {

public:

	//N is number of possible characters in a string
	const static int N = 26;

	//baseChar defines the base character for possible characters
	//like '0' for '0','1','2'... as possible characters in string
    const static char baseChar = 'a';

	struct TrieNode
	{
		int next[N];
		//if isEnd is set to true , a string ended here
		int isEnd;
		//freq is how many times this prefix occurs
    	int freq;

		TrieNode()
		{
			for(int i=0;i<N;i++)
				next[i] = -1;
			isEnd = 0;
			freq = 0;
		}
	};

	//the implementation is via vector and each position in this vector
	//is similar as new pointer in pointer type implementation
	vector <TrieNode> tree;

	//Base Constructor
	Trie ()
	{
		tree.push_back(TrieNode());
	}

	//inserting a string in trie
	void insert(const string &s)
    {
        int p = 0;
        tree[p].freq++;
        for(int i=0;i<s.size();i++)
        {
        	// tree[]
            if(tree[p].next[s[i]-baseChar] == -1)
            {
                tree.push_back(TrieNode());
                tree[p].next[s[i]-baseChar] = tree.size()-1;
            }

            p = tree[p].next[s[i]-baseChar];
            tree[p].freq++;
        }
        tree[p].isEnd += 1;
    }

    //check if a string exists as prefix
    int checkPrefix(const string &s)
    {
    	int p = 0;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return 0;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return tree[p].freq;
    }

    //check is string exists
    bool checkString(const string &s)
    {
    	int p = 0;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return false;

    		p = tree[p].next[s[i]-baseChar];
    	}

    	return tree[p].isEnd > 0;
    }



	int persistentStall(int version) {
		if (version == 0) tree.push_back(TrieNode());
		else tree.push_back(tree[version]);
		int newHead = tree.size()-1;
		return newHead;
	}

    //persistent insert
    //returns location of new head
    int persistentInsert(int head , const string &s)
    {
    	int old = head;

    	tree.push_back(TrieNode());
    	int now = tree.size()-1;
    	int newHead = now;

    	int i,j;

    	for(i=0;i<s.size();i++)
    	{
    		if(old == -1)
    		{
    			tree.push_back(TrieNode());
    			tree[now].next[s[i]-baseChar] = tree.size() - 1;
    			tree[now].freq++;
    			now = tree[now].next[s[i]-baseChar];
    			continue;
    		}
    		for(j=0;j<N;j++)
    			tree[now].next[j] = tree[old].next[j];
    		tree[now].freq = tree[old].freq;
    		tree[now].isEnd = tree[old].isEnd;

    		tree[now].freq++;

    		/*tree.push_back(TrieNode());
    		tree[now].next[s[i]-baseChar] = tree.size()-1;

    		old = tree[old].next[s[i]-baseChar];
    		now = tree[now].next[s[i]-baseChar];*/
    		int x = s[i] - baseChar;

    		int oldChild = tree[old].next[x];

    		if (oldChild == -1)
    			tree.push_back(TrieNode());
    		else
    			tree.push_back(tree[oldChild]);

    		int newChild = tree.size() - 1;

    		tree[now].next[x] = newChild;

    		old = oldChild;
    		now = newChild;
    	}

    	tree[now].freq++;
    	tree[now].isEnd += 1;

    	return newHead;
    }

    //persistent check prefix
    int persistentCheckPrefix(int head, const string &s)
    {
    	int p = head;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return false;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return tree[p].freq;
    }

    //persistent check string
    bool persistentCheckString(int head, const string &s)
    {
    	int p = head;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return false;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return tree[p].isEnd > 0;
    }
};

string s,temp;
int main2()
{
    Trie trie = Trie();

    cout << trie.checkString("hello") << endl;	//output : 0

    trie.insert("hello");

    cout << trie.checkPrefix("hell") << endl;	//output : 1

    cout << trie.checkString("hell") << endl;	//output : 0

    cout << trie.checkString("hello") << endl;	//output : 1


    //Example for persistent trie
    Trie persistentTrie = Trie();
    vector <int> heads;

    //insert words
    heads.push_back(0);
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "hello"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "world"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "persistent"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "trie"));

    cout << persistentTrie.persistentCheckString(heads[0] , "hello") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[1] , "hello") << endl;	//output : 1

    cout << persistentTrie.persistentCheckString(heads[1] , "world") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[2] , "world") << endl;	//output : 1

    cout << persistentTrie.persistentCheckString(heads[2] , "persistent") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[3] , "persistent") << endl;	//output : 1

    cout << persistentTrie.persistentCheckString(heads[3] , "trie") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[4] , "trie") << endl;	//output : 1


    return 0;
}

struct PersistentTrieWrapper {
	Trie persistentTrie = Trie();
	vector<int> heads = {0};
	void insert(const string& s) {
		heads.push_back(persistentTrie.persistentInsert(heads.back(), s));
	}
	void copy_ith(int version) {
		heads.push_back(heads[version]);
	}
	int get_amount_prefix(const string& s, bool register_version) {
		if (register_version) heads.push_back(heads.back());
		return persistentTrie.persistentCheckPrefix(heads.back(), s);
	}
	int get_amount_prefix_version(int version, const string& s, bool register_version) {
		if (register_version) heads.push_back(heads[version]);
		return persistentTrie.persistentCheckPrefix(heads[version], s);
	}
	bool exists(const string& s, bool register_version) {
		if (register_version) heads.push_back(heads.back());
		return persistentTrie.persistentCheckString(heads.back(), s);
	}
	bool exists_version(int version, const string& s, bool register_version) {
		if (register_version) heads.push_back(heads[version]);
		return persistentTrie.persistentCheckString(heads[version], s);
	}
};


//1-indexed versions, no remove method, do not forget persistentInsert, not insert
//EXISTS OPERATIONS UNTESTED

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, Q; cin >> n >> Q;
	PersistentTrieWrapper trie;
	for (int i=0; i<n; ++i) {
		string stemp; cin >> stemp;
		trie.insert(stemp);
	}
	for (int q=0; q<Q; ++q) {
		int l, r; string stemp; cin >> l >> r >> stemp;
		cout << trie.get_amount_prefix_version(r, stemp, false) - trie.get_amount_prefix_version(l-1, stemp, false) << "\n";
	}



}