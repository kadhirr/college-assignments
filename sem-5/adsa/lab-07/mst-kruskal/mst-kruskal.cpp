#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using Size_Type = std::size_t;

struct DisjointSet {

	DisjointSet() : m_Parent {}, m_Rank {}
	{}

	DisjointSet(const Size_Type& n) : m_Parent {}, m_Rank {}
	{
		Resize(n);
	}

	void Resize(const Size_Type& n)
	{
		for (Size_Type i = 0; i < n; ++i) {
			m_Parent.emplace_back(i);
			m_Rank.emplace_back(0);
		}
	}

	Size_Type FindParent(const Size_Type& node)
	{
		if (m_Parent[node] == node) {
			return node;
		}

		return m_Parent[node] = FindParent(m_Parent[node]);
	}

	void Union(Size_Type first, Size_Type second)
	{
		if (m_Rank[first] > m_Rank[second]) {
			m_Parent[second] = FindParent(first);
		}
		else if (m_Rank[first] < m_Rank[second]) {
			m_Parent[first] = FindParent(second);
		}
		else {
			if (first > second) {
				std::swap(first, second);
			}

			m_Parent[second] = FindParent(first);
			++m_Rank[first];
		}
	}

	std::vector<Size_Type> m_Parent;
	std::vector<Size_Type> m_Rank;
};


struct Edge {
	Edge() : m_From {}, m_To {}, m_Weight {}
	{}

	Edge(const unsigned long& f, const unsigned long& t, const unsigned long& wt) :
		m_From { f }, m_To { t }, m_Weight { wt }
	{}

	unsigned long m_From;
	unsigned long m_To;
	unsigned long m_Weight;
};

void MST_Kruskal(std::vector<Edge>& edges, const unsigned long& v)
{
	std::sort(
		edges.begin(), edges.end(), [](const Edge& first, const Edge& second) {
			return first.m_Weight < second.m_Weight;
		});

	DisjointSet djSet { v };

	std::vector<unsigned long> parent {};
	parent.resize(v, 0);
	unsigned long totalCost {};

	for (const auto& ele : edges) {
		if (djSet.FindParent(ele.m_From) != djSet.FindParent(ele.m_To)) {
			djSet.Union(ele.m_From, ele.m_To);
			parent[ele.m_To] = ele.m_From;

			totalCost += ele.m_Weight;
		}
	}
	for (unsigned long i = 1; i < v; ++i) {
		std::cout << parent[i] << " - " << i << '\n';
	}
	std::cout << "Cost: " << totalCost << "\n\n";
}

int main()
{
	unsigned long testCases {};
	std::cin >> testCases;

	std::vector<Edge> edges {};

	while (testCases--) {
		std::cout << "TC: " << testCases << '\n';
		unsigned long vertex {};
		unsigned long edge {};
		std::cin >> vertex >> edge;

		for (unsigned long i = 0; i < edge; ++i) {
			unsigned long from {};
			unsigned long to {};
			unsigned long wt {};
			std::cin >> from >> to >> wt;

			edges.emplace_back(from, to, wt);
		}

		MST_Kruskal(edges, vertex);

		edges.clear();
	}
}
