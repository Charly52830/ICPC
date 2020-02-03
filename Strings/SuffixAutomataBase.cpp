/* Suffix automata
*
*  Source: https://cp-algorithms.com/string/suffix-automaton.html
*/

#include<map>
#include<iostream>

/* Max length of the string */
#define MAXLEN 3000

/* Macro for querying existence of transitions on state i */
#define has_transition(i, c)	states[i].transitions.count(c)

/* Macro for getting next state through transition c from state i */
#define next_state(i, c)	states[i].transitions[c]

using namespace std;

struct state {
	int len, link;
	map<char,int> transitions;
};

state states[MAXLEN * 2];
int size, last;

void init_automata() {
	states[0].len = 0;
	states[0].link = -1;
	size = 1;
	last = 0;
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
			while(p != -1 && next_state(p,c) == q) {
				states[p].transitions[c] = clone;
				p = states[p].link;
			}
			states[q].link = states[cur].link = clone;
		}
	}
	last = cur;
}

void build_machine(const char *str) {
	init_automata();
	for(int i = 0; str[i] != '\0';i++) 
		add_char(str[i]);
}

int main() {
	char s[]="acababa\0";
	char t[]="ababa\0";
	build_machine(s);
	int cur, x;
	for(x = cur = 0; has_transition(cur, s[x]); cur = next_state(cur,s[x]), x++) 
		cout<<cur<<" ";
	cout<<cur<<endl;
	for(x = cur = 0; has_transition(cur, t[x]); cur = next_state(cur,t[x]), x++) 
		cout<<cur<<" ";
	cout<<cur<<endl;	
	return 0;
}

/*
 *	Salida:
 *	0 1 2 3 4 5 6 8
 *	0 1 7 9 6 8
 */

