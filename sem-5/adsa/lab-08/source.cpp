#include <iostream>
#include <cstdio>
#include <limits>
#include <vector>

struct Edge {
	Edge() : m_From {}, m_To {}, m_Weight {}
	{}

	Edge(const unsigned long& f, const unsigned long& t, const long& wt) :
		m_From { f }, m_To { t }, m_Weight { wt }
	{}

	unsigned long m_From;
	unsigned long m_To;
	long m_Weight;
};

void BellmanFord(const std::vector<Edge>& edges, const unsigned long& v)
{
	std::vector<long> distance {};
	distance.resize(v, std::numeric_limits<long>::max());
	distance[0] = 0;

	for (unsigned long i = 0; i < v - 1; ++i) {
		for (const auto& ele : edges) {
			if (distance[ele.m_From] == std::numeric_limits<long>::max()) {
				continue;
			}

			if (auto temp = distance[ele.m_From] + ele.m_Weight;
				temp < distance[ele.m_To]) {
				distance[ele.m_To] = temp;
			}
		}
	}

	for (unsigned long i = 0; i < v; ++i) {
		std::cout << i << " - " << distance[i] << '\n';
	}
	std::cout << '\n';
}

int main()
{
	long testCases {};
	std::cin >> testCases;

	std::vector<Edge> edges {};

	while (testCases--) {
		std::cout << "TC: " << testCases << '\n';
		unsigned long v {};
		unsigned long e {};
		std::cin >> v >> e;

		for (unsigned long i = 0; i < e; ++i) {
			unsigned long from {};
			unsigned long to {};
			long wt {};
			std::cin >> from >> to >> wt;
			edges.emplace_back(from, to, wt);
		}

		BellmanFord(edges, v);

		edges.clear();
	}

	return EXIT_SUCCESS;
}
