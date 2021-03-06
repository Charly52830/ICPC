/* Suffix automata
*
*  Source: https://cp-algorithms.com/string/suffix-automaton.html
*/

#include <map>
#include <iostream>
#include <vector>

using namespace std;

/* Max length of the string */
#define MAXLEN 100010

struct state {
	int len, link;
	map<char,int> transitions;
};

class SuffixAutomata {
	
	private:
	
	vector<state> states;
	int size, last;
	
	void init_automata(int N) {
		states = vector<state>(2 * N);
		last = 0;
		size = 1;
		states[0].link = -1;
		states[0].len = 0;
	}
	
	void add_char(char c) {
		int cur = size++;
		states[cur].len = states[last].len + 1;
		int p = last;
		while(p != -1 && !has_transition(p, c)) {
			states[p].transitions[c] = cur;
			p = states[p].link;
		}
		if(p == -1) {
			states[cur].link = 0;
		}
		else {
			int q = next_state(p, c);
			if(states[p].len + 1 == states[q].len) {
				states[cur].link = q;
			}
			else {
				int clone = size++;
				states[clone].len = states[p].len + 1;
				states[clone].transitions = states[q].transitions;
				states[clone].link = states[q].link;
				while(p != -1 && next_state(p, c) == q) {
					states[p].transitions[c] = clone;
					p = states[p].link;
				}
				states[q].link = states[cur].link = clone;
			}
		}
		last = cur;
	}
	
	public:
	
	SuffixAutomata(string str) {
		init_automata(str.size());
		for(int x = 0; x < str.size(); x++)
			add_char(str[x]);
	}
	
	bool has_transition(int i, char c) {
		return states[i].transitions.count(c);
	}
	
	int next_state(int i, char c) {
		return states[i].transitions[c];
	}
	
};

int main() {
	char s[]="acababa\0";
	char t[]="ababa\0";
	SuffixAutomata sa(s);
	int cur, x;
	for(x = cur = 0; sa.has_transition(cur, s[x]); cur = sa.next_state(cur,s[x]), x++) 
		cout<<cur<<" ";
	cout<<cur<<endl;
	for(x = cur = 0; sa.has_transition(cur, t[x]); cur = sa.next_state(cur,t[x]), x++) 
		cout<<cur<<" ";
	cout<<cur<<endl;	
	return 0;
}

/*
 *	Salida:
 *	0 1 2 3 4 5 6 8
 *	0 1 7 9 6 8
 */

