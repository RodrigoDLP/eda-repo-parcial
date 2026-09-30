#include<bits/stdc++.h>
using namespace std;

//Persistent trie and reference main from implementation from mridul1809 on GitHub
//https://github.com/mridul1809/CompetitiveProgramming/blob/master/templates/Trie.cpp
const int BIT_LENGTH = 32;

class Trie {

public:

	//N is number of possible characters in a string
	const static int N = 2;

	//baseChar defines the base character for possible characters
	//like '0' for '0','1','2'... as possible characters in string
    const static char baseChar = '0';

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
    int checkString(const string &s)
    {
    	int p = 0;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return 0;

    		p = tree[p].next[s[i]-baseChar];
    	}

    	return tree[p].isEnd;
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

	//Not on original repository
	int persistentRemove(int head, const string& s) {
		//cout << "remove query starting\n";
		if (!persistentCheckString(head, s)) return head;
		int old = head;

		tree.push_back(tree[old]);
		int newHead = tree.size() - 1;
		int now = newHead;
		tree[now].freq--;
		for (char c : s) {
			int x = c - baseChar;
			int oldChild = tree[old].next[x];

			tree.push_back(tree[oldChild]);
			int newChild = tree.size() - 1;

			tree[now].next[x] = newChild;

			old = oldChild;
			now = newChild;
			tree[now].freq--;
		}
		tree[now].isEnd--;
		return newHead;
	}



    //persistent check prefix
    int persistentCheckPrefix(int head, const string &s)
    {
    	int p = head;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return 0;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return tree[p].freq;
    }

	/*int kth(int head, int k) {
		int p = head;
		for(int i=0;i<s.size();i++) {
			int cumulativebasechar =
			for (int j=0; j<N; ++j) {


				if(tree[p].next[s[i]-baseChar] == -1)
					return 0;

				p = tree[p].next[s[i]-baseChar];
			}
		}
		return tree[p].freq;
	}*/

	//used ai to speed this one up
	string kth(int head, int k) {
		//cout << "kth query starting\n";
		if (k <= 0 || k > tree[head].freq) return "";
		string result;
		int p = head;
		while (true) {
			if (k <= tree[p].isEnd) return result;
			k -= tree[p].isEnd;
			bool found = false;
			for (int c = 0; c < N; ++c) {
				int child = tree[p].next[c];
				if (child == -1)
					continue;
				if (k <= tree[child].freq) {
					result += char(baseChar + c);
					p = child;
					found = true;
					break;
				}
				k -= tree[child].freq;
			}
			//if (!found) return ""; // inconsistent trie / invalid k
			if (!found) throw std::runtime_error("Apparently trie is inconsistent");
		}
	}

	//same as before, used ai for speed
	string descend_bitwise(int headA, int headB, const string& s) {
		string result;
		int pA = headA;
		int pB = headB;
		for (int i = 0; i < s.size(); ++i) {
			int x = s[i] - baseChar;
			int preferred = x ^ 1;

			int childA = (pA == -1 ? -1 : tree[pA].next[preferred]);
			int childB = (pB == -1 ? -1 : tree[pB].next[preferred]);

			int freqA = (childA == -1 ? 0 : tree[childA].freq);
			int freqB = (childB == -1 ? 0 : tree[childB].freq);
			if (freqA - freqB > 0) {
				result += char(baseChar + preferred);
				pA = childA;
				pB = childB;
			}
			else {
				int other = x;
				childA = (pA == -1 ? -1 : tree[pA].next[other]);
				childB = (pB == -1 ? -1 : tree[pB].next[other]);
				result += char(baseChar + other);
				pA = childA;
				pB = childB;
			}
		}
		return result;
	}

	string kth_descend_bitwise(int headA, int headB, int k, const string& s) {
		int currentk = k;
		string result;
		int pA = headA;
		int pB = headB;
		for (int i = 0; i < s.size(); ++i) {
			int x = s[i] - baseChar;
			int maybepreferred = x; // 10/10 naming convention
			int childA = (pA == -1 ? -1 : tree[pA].next[maybepreferred]);
			int childB = (pB == -1 ? -1 : tree[pB].next[maybepreferred]);

			int freqA = (childA == -1 ? 0 : tree[childA].freq);
			int freqB = (childB == -1 ? 0 : tree[childB].freq);
			//if (freqA - freqB == 0 && currentk != 0) throw std::runtime_error("query to kth descend bitwise without there being k elements");

			if (currentk <= freqA-freqB) {
				result += char(baseChar + maybepreferred);
				pA = childA;
				pB = childB;
			}
			else {
				currentk -= (freqA - freqB);
				int other = maybepreferred ^ 1;
				childA = (pA == -1 ? -1 : tree[pA].next[other]);
				childB = (pB == -1 ? -1 : tree[pB].next[other]);
				result += char(baseChar + other);
				pA = childA;
				pB = childB;
			}
		}
		return result;
	}

	//hecho con IA
	// Devuelve el MEX de una versión persistente del trie.
	//
	// - Todas las cadenas tienen exactamente BIT_LENGTH bits.
	// - Puede haber cadenas repetidas.
	// - No utiliza freq para determinar si un subárbol está completo.
	// - Funciona con BIT_LENGTH = 32.
	string persistentMEX(int head) {

	    // Cuenta cuántas hojas (strings completos) distintas
	    // existen dentro del subárbol 'p'.
	    //
	    // Los duplicados no importan porque un mismo string
	    // corresponde siempre al mismo nodo hoja.
	    auto countLeaves = [&](auto&& self, int p, int depth) -> uint64_t {

	        if (p == -1)
	            return 0;

	        // Hemos llegado al final de la cadena.
	        if (depth == BIT_LENGTH)
	            return (tree[p].isEnd > 0 ? 1ULL : 0ULL);

	        uint64_t left  = self(self, tree[p].next[0], depth + 1);
	        uint64_t right = self(self, tree[p].next[1], depth + 1);

	        return left + right;
	    };

	    string result;
	    int p = head;

	    for (int depth = 0; depth < BIT_LENGTH; ++depth) {

	        int remaining = BIT_LENGTH - depth - 1;

	        int child0 = tree[p].next[0];

	        // Cantidad de valores DISTINTOS que existen
	        // en el subárbol que empieza por 0.
	        uint64_t leaves0 = countLeaves(
	            countLeaves,
	            child0,
	            depth + 1
	        );

	        // Cantidad máxima de números distintos que pueden existir
	        // en este subárbol.
	        //
	        // Usamos uint64_t porque BIT_LENGTH puede ser 32.
	        uint64_t possible = (1ULL << remaining);

	        if (leaves0 < possible) {

	            // Falta algún número en el subárbol 0.
	            result += '0';

	            if (child0 == -1) {
	                // No existe absolutamente ningún número con
	                // este prefijo. El menor posible completa con ceros.
	                result += string(remaining, '0');
	                break;
	            }

	            p = child0;
	        }
	        else {

	            // Todos los números posibles con prefijo 0 existen.
	            // Por tanto, el MEX está necesariamente en el subárbol 1.
	            result += '1';

	            int child1 = tree[p].next[1];

	            if (child1 == -1) {
	                // No existe ningún número con este prefijo.
	                result += string(remaining, '0');
	                break;
	            }

	            p = child1;
	        }
	    }

	    return result;
	}



    //persistent check string
    int persistentCheckString(int head, const string &s)
    {
    	int p = head;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return 0;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return tree[p].isEnd;
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
	void remove(const string& s) {
		if (heads.back() == 0) throw std::runtime_error("trying to remove from empty trie");
		heads.push_back(persistentTrie.persistentRemove(heads.back(), s));
	}
	void insert_version(int version, const string& s) {
		if (heads.size() == 1 && persistentTrie.tree.size() == 1) {insert(s); return;}
		heads.push_back(persistentTrie.persistentInsert(heads[version], s));
	}
	void remove_version(int version, const string& s) {
		if (heads.size() == 1 || persistentTrie.tree.size() == 1) throw std::runtime_error("trying to remove from empty trie");
		heads.push_back(persistentTrie.persistentRemove(heads[version], s));
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
		return persistentTrie.persistentCheckString(heads.back(), s) > 0;
	}
	bool exists_version(int version, const string& s, bool register_version) {
		if (register_version) heads.push_back(heads[version]);
		return persistentTrie.persistentCheckString(heads[version], s) > 0;
	}
	int get_amount_full(const string& s, bool register_version) {
		if (register_version) heads.push_back(heads.back());
		return persistentTrie.persistentCheckString(heads.back(), s);
	}
	int get_amount_full_version(int version, const string& s, bool register_version) {
		if (register_version) heads.push_back(heads[version]);
		return persistentTrie.persistentCheckString(heads[version], s);
	}
	string kth(int k, bool register_version) {
		if (register_version) heads.push_back(heads.back());
		return persistentTrie.kth(heads.back(), k);
	}
	string kth_version(int version, int k, bool register_version) {
		if (register_version) heads.push_back(heads[version]);
		return persistentTrie.kth(heads[version], k);
	}
	string max_xor_in_range(int vleftminusone, int vright, const string& s) {
		return persistentTrie.descend_bitwise(heads[vright], heads[vleftminusone], s);
	}
	string kth_xor_in_range(int vleftminusone, int vright, int k, const string& s) {
		return persistentTrie.kth_descend_bitwise(heads[vright], heads[vleftminusone], k, s);
	}
};


//1-indexed versions, no remove method, do not forget persistentInsert, not insert
//NOT ALL OPERATIONS TESTED

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q; cin >> n >> q;
	PersistentTrieWrapper trie;
	for (int i=0; i<n; ++i) {
		int a; cin >> a;
		bitset<32> btemp(a);
		trie.insert(btemp.to_string());
	}
	for (int qi = 0; qi < q; ++qi) {
		int ti; cin >> ti;
		if (ti == 1) {

		} else {

		}
	}




	for (int q=0; q<Q; ++q) {
		cin >> t >> v;
		if (t == 1) {
			cin >> y;
			bitset<32> btemp(y);
			trie.insert_version(v, btemp.to_string());
		} else if (t == 2) {
			cin >> y;
			bitset<32> btemp(y);
			trie.remove_version(v, btemp.to_string());
		} else if (t == 3) {
			cin >> y;
			string output = trie.kth_version(v, y, true);
			int outputint = bitset<32>(output).to_ulong();
			cout << outputint << "\n";
		} else throw std::runtime_error("input read wrong");
	}


	return 0;
}