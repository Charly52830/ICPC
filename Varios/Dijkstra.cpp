/*
*	Compilar con c++17
*	g++ -std=c++1z Programa.cpp
*
*	g: lista de adyacencia
*	d: arreglo con la distancia final
*/

void dijkstra(int start, vector<int> & d) {
	d = vector<int>(n, oo);
	d[start] = 0;
	set<pair<int, int>> _set;
	_set.insert({0, start});
	while(!_set.empty()) {
		int v = _set.begin() -> second;
		_set.erase(_set.begin());
		for(auto [to, w] : g[v]) {
			if(d[to] > d[v] + w) {
				auto it = _set.find({d[to], to});
				if(it != _set.end())
					_set.erase(it);
				d[to] = d[v] + w;
				_set.insert({d[to], to});
			}
		}
	}
}
