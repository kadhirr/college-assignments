#include <iostream>
#include <cstdio>
#include <vector>

using Size_Type  = std::size_t;
using Graph_Type = std::vector<std::vector<Size_Type>>;

struct Graph {

	Graph() : m_Vertex {}, m_Edge {}, m_Index { 1 }, m_Graph {}
	{}

	Graph(Size_Type v, Size_Type e, bool d = false, Size_Type i = 1) :
		m_Vertex { v },
		m_Edge { e },
		m_Directed { d },
		m_Index { i },
		m_Graph {}
	{}

	void Input()
	{
		m_Graph.resize(m_Vertex + m_Index);

		Size_Type from {};
		Size_Type to {};
		for (Size_Type i = 0; i < m_Edge; ++i) {
			std::cin >> from >> to;

			m_Graph[from].emplace_back(to);

			if (!m_Directed) {
				m_Graph[to].emplace_back(from);
			}
		}
	}

	Size_Type  m_Vertex;
	Size_Type  m_Edge;
	bool       m_Directed;
	Size_Type  m_Index;
	Graph_Type m_Graph;
};

void TopologicalSort_impl(const auto& n, const auto& g, auto& v, auto& o)
{
	for (const auto& ele : g[n]) {
		if (!v[ele]) {
			v[ele] = true;
			TopologicalSort_impl(ele, g, v, o);
			o.emplace_back(ele);
		}
	}
}

void TopologicalSort(const Graph& graph)
{
	std::vector<bool> visited {};
	visited.resize(graph.m_Vertex, false);

	auto raw = graph.m_Graph;
	auto aux = graph.m_Vertex + graph.m_Index;

	std::vector<unsigned long> ordering {};

	for (auto i = graph.m_Index; i < aux; ++i) {
		if (!visited[i]) {
			visited[i] = true;
			TopologicalSort_impl(i, raw, visited, ordering);
			ordering.emplace_back(i);
		}
	}

	for (auto it = ordering.crbegin(); it != ordering.crend() - 1; ++it) {
		std::cout << *it << ' ';
	}
	std::cout << ordering.front() << '\n';
}

int main()
{
	long testCases {};
	std::cin >> testCases;

	while (testCases--) {
		std::cout << "Testcase: " << testCases << '\n';
		unsigned long vertex {};
		unsigned long edges {};
		std::cin >> vertex >> edges;

		// vertices, edges, directed.
		Graph graph { vertex, edges, true };
		graph.Input();

		TopologicalSort(graph);
		std::cout << '\n';
	}

	return EXIT_SUCCESS;
}
