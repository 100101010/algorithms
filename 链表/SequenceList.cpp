#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <cstring>
#include <numeric>
#include <cmath>
#include <stack>
#include <memory>
using namespace std;
constexpr int MaxSize = 100;
template <typename __T>
class LinkList{
private:
	allocator<__T> alloc;
	__T* data;
	int count;

public:
	LinkList();
	LinkList(const initializer_list<__T>& p);
	~LinkList();

	constexpr const int size() const {return count;};
	bool insert(__T&& value) noexcept;
	bool insert(const __T& value);
	constexpr int search(const __T& value) const;
	constexpr int search(__T&& value) const noexcept;
	bool del(int&& index);
	bool del(const int& index);
	bool revise(int&& index, __T&& value);
	void print();
};
template <typename __T>
LinkList<__T>::LinkList() {
	data = alloc.allocate(MaxSize);
	count = 0;
}

template <typename __T>
LinkList<__T>::LinkList(const initializer_list<__T>& p) {
	data = alloc.allocate(MaxSize);
	count = 0;
	for(auto i:p)
		insert(i);
}

template <typename __T>
LinkList<__T>::~LinkList() {
	for(int i = 0; i < count; i++)
		alloc.destroy(data+i);
	alloc.deallocate(data, MaxSize);
}

template <typename __T>
bool LinkList<__T>::insert(__T&& value) noexcept {
	if(count >= MaxSize)
		return false;
	alloc.construct(data + count, value);
	++count;
}

template <typename __T>
bool LinkList<__T>::insert(const __T& value) {
	if(count >= MaxSize)
		return false;
	alloc.construct(data + count, value);
	++count;
}

template <typename __T>
constexpr int LinkList<__T>::search(__T&& value) const noexcept {
	int i;
	for(i = 0; i < count; i++)
		if(data[i] == value)
			break;
	return (i == count?-1:i);
}

template <typename __T>
constexpr int LinkList<__T>::search(const __T& value) const {
	int i;
	for(i = 0; i < count; i++)
		if(data[i] == value)
			break;
	return (i == count?-1:i);
}

template <typename __T>
bool LinkList<__T>::del(int&& index) {
	if(index > count || index <= 0)
		return false;
	for(int i = index - 1; i < count - 1; i++)
		data[i] = data[i + 1];
	--count;
	alloc.destroy(data + count);
	return true;
}

template <typename __T>
bool LinkList<__T>::del(const int& index) {
	if(index > count || index <= 0)
		return false;
	for(int i = index - 1; i < count - 1; i++)
		data[i] = data[i + 1];
	--count;
	alloc.destroy(data + count);
	return true;
}

template <typename __T>
bool LinkList<__T>::revise(int&& index, __T&& value) {
	if(index > count || index <= 0)
		return false;
	data[index - 1] = value;
	return true;
}

template <typename __T>
void LinkList<__T>::print() {
	for(int i = 0; i < count; i++)
		cout<<data[i]<<" ";
	cout<<endl;
}

int main()
{
	LinkList<int> link = {1, 2, 3, 4, 5};
	link.insert(1);
	link.print();
	return 0;
}