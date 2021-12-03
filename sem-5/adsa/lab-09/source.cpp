#include <iostream>
#include <cstdio>
#include <limits>
#include <vector>

void FloydWarshall()
{
	unsigned long v {};
	unsigned long e {};
	std::cin >> v >> e;

	std::vector<std::vector<unsigned long>> matrix {};
	matrix.resize(v);
	for (unsigned long i = 0; i < v; ++i) {
		for (unsigned long j = 0; j < v; ++j) {
			if (i == j) {
				matrix[i].push_back(0);
				continue;
			}
			matrix[i].push_back(std::numeric_limits<unsigned long>::max());
		}
	}

	for (unsigned long i = 0; i < e; ++i) {
		unsigned long from {};
		unsigned long to {};
		unsigned long wt {};
		std::cin >> from >> to >> wt;
		matrix[from][to] = wt;
	}

	for (unsigned long count = 0; count < v; ++count) {
		auto temp = matrix;

		for (unsigned long i = 0; i < v; ++i) {
			if (i == count) {
				continue;
			}

			for (unsigned long j = 0; j < v; ++j) {
				if (j == count or i == j) {
					continue;
				}

				if (matrix[i][count] == std::numeric_limits<unsigned long>::max() or
					matrix[count][j] == std::numeric_limits<unsigned long>::max()) {
					temp[i][j] = matrix[i][j];
				}
				else {
					temp[i][j] = std::min(
						matrix[i][j], matrix[i][count] + matrix[count][j]);
				}
			}
		}

		matrix = temp;
	}

	for (const auto& ele : matrix) {
		for (const auto& it : ele) {
			std::cout << it << ' ';
		}
		std::cout << '\n';
	}
}

int main()
{
	long testCases {};
	std::cin >> testCases;

	while (testCases--) {
		std::cout << "TC: " << testCases << '\n';
		FloydWarshall();
	}

	return EXIT_SUCCESS;
}
