#include "examples.h"

// Test minimo
// O(n^2)
void E9()
{
	// O(n^2)
	suma_cuatro_t sc(20);
	// O(nlog(n))
	auto [d, ds] = sc(8);
	// O(n)
	for (auto i : d)
		cout << i << " ";
	cout << endl;
	// O(n)
	for (auto i : ds)
	{
		for (int j : i)
			cout << j << " ";
		cout << endl;
	}
}

void E10()
{
	// O(n)
	par_lejano_t pl(20);
	// O(nlog(n))
	auto [a, b] = pl();
	cout << a << " " << b << endl;
	// O(n)
	for (auto i : pl.data())
		cout << i << " ";
	cout << endl;
}

void E11()
{
	// O(n)
	par_cercano_t pc(20);
	// O(nlog(n))
	auto [a, b] = pc();
	cout << a << " " << b << endl;
	// O(n)
	for (auto i : pc.data())
		cout << i << " ";
	cout << endl;
}

void E12()
{
	minimo_local_t ml(20);
	auto result = ml();
	cout << result << endl;
	for (auto i : ml.data())
		cout << i << " ";
	cout << endl;
}

int main() {
	// E9();
	// E10();
	// E11();
	// E12();
	return 0;
}
