#include "examples.h"

//int rand_int(int start, int end) {
//	random_device rd;
//	default_random_engine eng(rd());
//	uniform_int_distribution<int> dis(start, end);
//	return dis(eng);
//}

template <typename T>
T absolute(T a, T b)
{
	return a > b ? a - b : b - a;
}

// O(1)
bool suma_cuatro_t::no_intersections(pair_sum_t a, pair_sum_t b) {
	return !(a.first == b.first || a.first == b.second ||
		a.second == b.first || a.second == b.second);
}

// O(n) + O(n^2) + O(1) + O(nlog(n)) --> O(n^2)
suma_cuatro_t::suma_cuatro_t(size_t n) :functor_t<int>{ n, 1, 10 }, data_in_pairs_((n* (n - 1)) / 2) {

	// Combinaciones de 2 en 2 --> O(n^2)
	auto it = begin(data_in_pairs_);
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
			*it++ = pair_sum_t{ data_[i] + data_[j], i, j };

	// Ordenamiento  --> O(nlog(n))
	sort(begin(data_in_pairs_), end(data_in_pairs_), [](pair_sum_t a, pair_sum_t b) {
		return a.sum < b.sum;
		});
}

// O(n) + O(1) + O(nlog(n)) + O(1) --> O(nlog(n))
pair<vector<int>, set<vector<int>>> suma_cuatro_t::operator()(int value) {

	// Iterators	
	auto it_1 = begin(data_in_pairs_);
	auto it_2 = rbegin(data_in_pairs_);
	while (it_1 != end(data_in_pairs_) && it_2 != rend(data_in_pairs_)) // O(nlog(n))
	{
		if (it_1->sum + it_2->sum == value) // O(1)
		{
			if (no_intersections(*it_1, *it_2))
				result_.insert({	// log(n)
						data_[it_1->first],
						data_[it_1->second],
						data_[it_2->first],
						data_[it_2->second]
					});
			it_2++;
			it_1++;
		}
		else if (it_1->sum + it_2->sum > value)
			it_2++;
		else
			it_1++;
	}
	return { data_, result_ }; // O(1)
}

par_lejano_t::par_lejano_t(size_t n): functor_t<double>{ n, 1, 10 } {
}

pair<double, double> par_lejano_t::operator()()
{
	double max = data_.front();
	double min = data_.front();
	for (const auto& item: data_)
	{
		if (item > max)
			max = item;
		if (item < min)
			min = item;
	}
	return { min, max };
}

par_cercano_t::par_cercano_t(size_t n) : functor_t<double>{ n, 1, 10 } {
}

pair<double, double> par_cercano_t::operator()()
{
	sort(begin(data_), end(data_));	// O(n log(n))
	auto first = next(begin(data_), + 1);
	auto last = next(begin(data_), size(data_) - 1);
	tuple<double, double, double> min{ absolute(data_.front(), *first), 0, 0 };
	for (auto it = first; it != last; ++it)
	{
		auto distance = absolute(*it, *(it + 1));
		if (distance < get<0>(min))
			min = { distance, *it, *(it + 1) };
	}
	return { get<1>(min), get<2>(min) };
}

minimo_local_t::minimo_local_t(size_t n): functor_t<int>{n, 1, 10}
{
}

int minimo_local_t::operator()()
{
	auto first = 0;
	auto last = size(data_) - 1;
	while (true)
	{
		auto mid = (last - first) / 2;
		if (mid <= 0 || mid >= size(data_) - 1)
			break;

		if (data_[mid - 1] < data_[mid] && data_[mid] < data_[mid + 1])
			return data_[mid];
		else if (data_[mid - 1] < data_[mid + 1])
			last = mid - 1;
		else
			first = mid + 1;
	}
	return -1;
}
