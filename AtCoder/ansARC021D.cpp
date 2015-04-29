#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	for (int N; std::cin >> N;)
	{
		std::vector<int> c(N);
		for (auto&v : c) std::cin >> v;
		std::vector<int> a(N, N + 1);
		std::vector<int> id(N);
		for (int i = 0; i<N; ++i)
			id[i] = std::lower_bound(a.begin(), a.end(), c[i]) - a.begin(),
			a[id[i]] = c[i];
		std::cout << N - *std::max_element(id.begin(), id.end()) - 1 << std::endl;
	}
}