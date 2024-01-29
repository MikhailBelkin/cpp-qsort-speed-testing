#include <vector>
#include <iostream>
#include "log_duration.h"
#include <cmath>


class Comp {
public:
	static bool  prior(int left, int right) {
		return (left < right);
	}

	static bool  prior(double left, double right) {
		return (left < right);
	}


	static bool  prior(float left, float right) {
		return (left < right);
	}

	static bool  prior(char left, char right) {
		return (left < right);
	}


};




template <typename E>
inline void swap(E A[], int i, int j) {
	E temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}


template <typename E>
inline int findpivot(E A[], int i, int j) {
	return (i + j) / 2;
}


// Функция для нахождения индекса медианы из трех чисел в массиве
inline int index_of_median(int arr[], int idx1, int idx2, int idx3) {
	int a = arr[idx1];
	int b = arr[idx2];
	int c = arr[idx3];

	// Находим минимум из a и b
	if (a <= b && b <= c)
		return idx2;  // b - медиана
	else if (c <= b && b <= a)
		return idx2;  // b - медиана
	else if (b <= a && a <= c)
		return idx1;  // a - медиана
	else if (c <= a && a <= b)
		return idx1;  // a - медиана
	else
		return idx3;  // c - медиана
}

template <typename E>
inline int findpivot2(E A[], int i, int j) {
	//return i;
	return index_of_median(A, i, j, (i + j) / 2);
}


template <typename E, typename Comp>
inline int partintion(E A[], int l, int r, E& pivot) {
	do {
		while (Comp::prior(A[++l], pivot));
		while ((l < r) && Comp::prior(pivot, A[--r]));
		swap(A, l, r);

	} while (l < r);
	return l;
}


template <typename E, class Comp>
void qsort1(E A[], int i/*start_pos*/, int j/*end_pos*/) {
	if (j <= i) {
		return;
	}
	int pivot_index = findpivot(A, i, j);
	swap(A, pivot_index, j);
	int k = partintion<E, Comp>(A, i - 1, j, A[j]);
	swap(A, k, j);
	qsort1<E, Comp>(A, i, k - 1); 
	qsort1<E, Comp>(A, k + 1, j);



}


template <typename E, class Comp>
void qsort2(E A[], int i/*start_pos*/, int j/*end_pos*/) {
	if (j <= i) {
		return;
	}
	int pivot_index = findpivot(A, i, j);
	
	swap(A, pivot_index, j);
	int k = partintion<E, Comp>(A, i - 1, j, A[j]);
	swap(A, k, j);
	qsort2<E, Comp>(A, i, k - 1);
	qsort2<E, Comp>(A, k + 1, j);



}

template <typename E, class Comp>
void qsort3(E A[], int i/*start_pos*/, int j/*end_pos*/) {
	if (j <= i) {
		return;
	}
	if (j - i <= 20) { //insertion sort
		for (int cur = i; cur < j; ++cur) {
			int key = A[cur];
			int elem = cur - 1;


			while (elem >= 0 && A[elem] > key) {
				A[elem + 1] = A[elem];
				elem--;
			}
			A[elem + 1] = key;
		}
		return;
	}
	int pivot_index = findpivot(A, i, j);

	swap(A, pivot_index, j);
	int k = partintion<E, Comp>(A, i - 1, j, A[j]);
	swap(A, k, j);
	qsort3<E, Comp>(A, i, k - 1);
	qsort3<E, Comp>(A, k + 1, j);



}




template <typename E, class Comp>
inline void qsort4(E A[], int i/*start_pos*/, int j/*end_pos*/) {
	if (j <= i) {
		return;
	}
	if (j - i <= 20) { //insertion sort
		for (int cur = i; cur < j; ++cur) {
			int key = A[cur];
			int elem = cur - 1;


			while (elem >= 0 && A[elem] > key) {
				A[elem + 1] = A[elem];
				elem--;
			}
			A[elem + 1] = key;
		}
		return;
	}
	int pivot_index = findpivot(A, i, j);

	swap(A, pivot_index, j);
	int k = partintion<E, Comp>(A, i - 1, j, A[j]);
	swap(A, k, j);
	qsort4<E, Comp>(A, i, k - 1);
	qsort4<E, Comp>(A, k + 1, j);



}




int main() {
	const int SIZE = 10000000;
	std::vector<int> src_data(SIZE);

	for (int i = 0; i < src_data.size(); i++) {
		src_data[i] = 1 + rand()%99;

	}


	std::vector<int> src_data_rand(SIZE);
	src_data_rand = src_data;


	
	/*std::cout << "Before sort" << std::endl;
	for (auto data : src_data) {
		std::cout << data << ",  ";

	}
	std::cout << std::endl;*/

	{
		LOG_DURATION("original");
		qsort1<int, Comp>(src_data_rand.data(), 0, src_data_rand.size() - 1);

	}

	src_data_rand = src_data;

	{
		LOG_DURATION("a");
		qsort2<int, Comp>(src_data_rand.data(), 0, src_data_rand.size() - 1);

	}

	src_data_rand = src_data;

	{
		LOG_DURATION("a+b");
		qsort3<int, Comp>(src_data_rand.data(), 0, src_data_rand.size() - 1);

	}


	src_data_rand = src_data;

	{
		LOG_DURATION("a+b+c");
		qsort4<int, Comp>(src_data_rand.data(), 0, src_data_rand.size() - 1);

	}


	/*std::cout << "After sort" << std::endl;
	for (auto data : src_data_rand) {
		std::cout << data << ",  ";

	}
	std::cout << std::endl;
	*/
	return 0;
}