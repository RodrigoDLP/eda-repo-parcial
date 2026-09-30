//Persistent trie and reference main from implementation from mridul1809 on GitHub
//https://github.com/mridul1809/CompetitiveProgramming/blob/master/templates/Trie.cpp
#include<bits/stdc++.h>
using namespace std;

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
	int Q; cin >> Q;
	int operationtype, itemp; string stemp;
	PersistentTrieWrapper persistentTrie;
	for (int i=0; i<Q; ++i) {
		cin >> operationtype;

		if (operationtype == 1) {
			cin >> stemp;
			persistentTrie.insert(stemp);
		} else if (operationtype == 2) {
			cin >> itemp;
			persistentTrie.copy_ith(itemp);
		} else if (operationtype == 3) {
			cin >> stemp;
			cout << persistentTrie.get_amount_prefix(stemp, true) << "\n";
		}
	}
	return 0;
}