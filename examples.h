#ifndef EXAMPLES_H
#define EXAMPLES_H

#include <iostream>
#include <set>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <tuple>

using namespace std;

template <typename T>
auto get_random(T first, T last) {
	random_device rd;
	default_random_engine eng(rd());

	if constexpr (is_integral_v<T>)
	{
		uniform_int_distribution<T> dis(first, last);
		return dis(eng);
	}
	else
	{
		uniform_real_distribution<T> dis(first, last);
		return dis(eng);
	}
}

// O(n)
template <typename T, template <typename...> class Container, typename RandomOperator>
void generate_data(Container<T>& data, T start, T end, RandomOperator random_operator) {
	for (auto& item : data)
		item = random_operator(start, end);
}

struct pair_sum_t {
	int sum = 0;
	int first = 0;
	int second = 0;
	pair_sum_t() = default;
	pair_sum_t(int sum, int first, int second) :sum{ sum }, first{ first }, second{ second } {}
};

template <typename T>
class functor_t {

protected:
	vector<T> data_;

public:
	functor_t(size_t n, T first, T last) :data_(n)
	{
		generate_data(data_, first, last, get_random<T>);
	}

	vector<T> data() const
	{
		return data_;
	}
};

class suma_cuatro_t : public functor_t<int> {

private:

	vector<pair_sum_t> data_in_pairs_;
	set<vector<int>> result_;

	// O(1)
	static bool no_intersections(pair_sum_t a, pair_sum_t b);

public:

	// O(n^2)
	explicit suma_cuatro_t(size_t n);

	// O(nlog(n))
	pair<vector<int>, set<vector<int>>> operator()(int value);
};

class par_lejano_t : public functor_t<double> {

public:
	par_lejano_t(size_t n);
	pair<double, double> operator()();
};

class par_cercano_t : public functor_t<double> {

public:
	par_cercano_t(size_t n);
	pair<double, double> operator()();
};

class minimo_local_t : public functor_t<int> {
	
public:
	minimo_local_t(size_t n);
	int operator()();
};
#endif
