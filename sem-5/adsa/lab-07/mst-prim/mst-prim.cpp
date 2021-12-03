#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using Size_Type  = std::size_t;
using Node_Type  = std::pair<Size_Type, Size_Type>;
using Graph_Type = std::vector<std::vector<Node_Type>>;

struct Graph {

	Graph() :
		m_Vertex {},
		m_Edge {},
		m_Directed {},
		m_Weighted {},
		m_Index { 1 },
		m_Graph {}
	{}

	Graph(
		Size_Type v,
		Size_Type e,
		bool      d = false,
		bool      w = false,
		Size_Type i = 1) :
		m_Vertex { v },
		m_Edge { e },
		m_Directed { d },
		m_Weighted { w },
		m_Index { i },
		m_Graph {}
	{}

	void Input()
	{
		m_Graph.resize(m_Vertex + m_Index);

		Size_Type from {};
		Size_Type to {};
		Size_Type wt { 1 };
		for (Size_Type i = 0; i < m_Edge; ++i) {
			std::cin >> from >> to;

			if (m_Weighted) {
				std::cin >> wt;
			}

			m_Graph[from].emplace_back(to, wt);

			if (!m_Directed) {
				m_Graph[to].emplace_back(from, wt);
			}
		}
	}

	Size_Type  m_Vertex;
	Size_Type  m_Edge;
	const bool m_Directed;
	const bool m_Weighted;
	Size_Type  m_Index;
	Graph_Type m_Graph;
};

void MST_Prim(const Graph& graph)
{
	const auto&       raw = graph.m_Graph;
	std::vector<long>  parent {};
	std::vector<unsigned long>  minWeight {};
	std::vector<bool> inMST {};

	for (unsigned long i = 0; i < raw.size(); ++i) {
		parent.push_back(0);
		minWeight.push_back(std::numeric_limits<unsigned long>::max());
		inMST.push_back(false);
	}
	minWeight[0] = 0;
	parent[0]    = -1;

	std::priority_queue<
		Node_Type,
		std::vector<Node_Type>,
		std::greater<Node_Type>>
		pq {};
	pq.emplace(0, 0);

	while (!pq.empty()) {
		const auto node = pq.top().second;
		pq.pop();

		inMST[node] = true;

		for (const auto& it : raw[node]) {
			const auto& vertex = it.first;
			const auto& weight = it.second;

			if (inMST[vertex] == false && weight < minWeight[vertex]) {
				parent[vertex]    = node;
				minWeight[vertex] = weight;
				pq.emplace(weight, vertex);
			}
		}
	}

	for (unsigned long i = 1; i < parent.size(); ++i) {
		std::cout << parent[i] << " - " << i << '\n';
	}
}

int main()
{
	long testCases {};
	std::cin >> testCases;

	while (testCases--) {
		std::cout << "TC: " << testCases << '\n';
		unsigned long vertex {};
		unsigned long edges {};
		std::cin >> vertex >> edges;

		Graph graph { vertex, edges, false, true, 0 };
		graph.Input();

		const auto& temp = graph.m_Graph;
		for (const auto& ele : temp) {
			for (const auto& it : ele) {
				std::cout << '[' << it.first << ", " << it.second << ']';
			}
			std::cout << '\n';
		}
		std::cout << '\n';

		std::cout << "Prim's MST\n";
		MST_Prim(graph);
	}

	return EXIT_SUCCESS;
}

/*
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int N,m;
	cin >> N >> m;
	vector<pair<int,int> > adj[N]; 

	int a,b,wt;
	for(int i = 0; i<m ; i++){
		cin >> a >> b >> wt;
		adj[a].push_back(make_pair(b,wt));
		adj[b].push_back(make_pair(a,wt));
	}	
	
	std::vector<int> parent(N); 
	std::vector<int> key(N);
	std::vector<bool> mstSet(N);
  
    for (int i = 0; i < N; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    key[0] = 0; 
    parent[0] = -1; 
    pq.push({0, 0});

    while(!pq.empty())
    { 
        int u = pq.top().second; 
        pq.pop(); 
        
        mstSet[u] = true; 
        
        for (auto it : adj[u]) {
            int v = it.first;
            int weight = it.second;
            if (mstSet[v] == false && weight < key[v]) {
                parent[v] = u;
				key[v] = weight; 
                pq.push({key[v], v});    
            }
        }
    } 
    
    for (int i = 1; i < N; i++) 
        cout << parent[i] << " - " << i <<" \n"; 
	return 0;
}
*/