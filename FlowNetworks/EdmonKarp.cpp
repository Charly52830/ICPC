/**
*	Edmond-Karp for max flow.
*	O(|V| * |E|^2)
*/

#include<tuple>
#include<string.h>
#include<iostream>
#include<queue>
#include<vector>
#define MAXNODES 101
#define oo 1e9
#define g0(a) get<0>(a)
#define g1(a) get<1>(a)
#define g2(a) get<2>(a)

using namespace std;

typedef tuple<int,int,int> ti;
typedef long long ll;

ti mt(int a,int b,int c) {
	ti t;
	g0(t)=a;
	g1(t)=b;
	g2(t)=c;
	return t;
}

/** Adyacency matriz for storing the weight of the graph. */
int adyacencyMatrix[MAXNODES][MAXNODES];
/** Adyacency list for storing the list of edges of each vertex. */
vector<vector<int> > adyacencyList;
int parents[MAXNODES];

void reduceWeight(int source, int sink,int weight) {
	int node=sink;
	while(parents[node] != source) {
		adyacencyMatrix[node][parents[node]]+=weight;
		adyacencyMatrix[parents[node]][node]-=weight;
		node=parents[node];
	}
	adyacencyMatrix[node][source]+=weight;
	adyacencyMatrix[source][node]-=weight;
}

int main() {
	int numNodes,numEdges;
	scanf("%d %d",&numNodes,&numEdges);
	adyacencyList.resize(numNodes+1);
	for(int x=0;x<numEdges;x++) {
		int outputVertex,inputVertex,weight;
		scanf("%d %d %d",&outputVertex,&inputVertex,&weight);
		adyacencyMatrix[outputVertex][inputVertex]=weight;
		adyacencyList[outputVertex].push_back(inputVertex);
		adyacencyList[inputVertex].push_back(outputVertex);
	}
	/** By defect, source equals 1, sink equals last number. */
	int source=1,sink=numNodes,antiqueFlow=-1;
	ll maxFlow=0;
	while(antiqueFlow != maxFlow) {
		int flowGained=0;
		antiqueFlow=maxFlow;
		memset(parents,-1,sizeof parents);
		queue<ti> q;	//Node, parent, current flow through shortest path
		q.push(mt(source,source,oo));
		while(!q.empty()) {
			int currentNode=g0(q.front());
			int parent=g1(q.front());
			int currentFlow=g2(q.front());
			q.pop();
			if(parents[currentNode] == -1) {
				parents[currentNode]=parent;
				for(auto i:adyacencyList[currentNode]) if(adyacencyMatrix[currentNode][i] > 0)
					q.push(mt(i,currentNode,min(currentFlow,adyacencyMatrix[currentNode][i])));
				if(currentNode == sink)
					flowGained=currentFlow;
			}
		}
		if(flowGained > 0) {
			maxFlow+=flowGained;
			reduceWeight(source,sink,flowGained);
		}
	}
	printf("%d\n",maxFlow);
	return 0;
}

/**
*	Entrada:
*	6 8
*	1 2 5
*	1 4 4
*	4 2 3
*	4 5 1
*	2 3 6
*	3 5 8
*	3 6 5
*	5 6 2
*
*	Salida:
*	7
*/
