#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>
using namespace std;

template <typename T>
class SequenceList {
private:
    T* data;
    allocator<T> alloc;
    int number;
    int MaxSize = 5;

private:
    // 重新分配空间
    void rellocate() {
        T* new_data = alloc.allocate(MaxSize * 2);
        MaxSize *= 2;
        uninitialized_copy(data, data + number, new_data);
        for(int i = 0; i < number; i++)
            alloc.destroy(data + i);
        alloc.deallocate(data, number);
        data = new_data;
    }

    void rellocate(int size) {
        T* new_data = alloc.allocate(size);
        uninitialized_copy(data, data + number, new_data);
        for(int i = 0; i < number; i++)
            alloc.destroy(data + i);
        alloc.deallocate(data, number);
        data = new_data;
    }
public:
    // 默认构造函数
    SequenceList() {
        data = alloc.allocate(MaxSize);
        number = 0;
    }

    SequenceList(string file) {
        data = alloc.allocate(MaxSize);
        number = 0;
        T i;
        fstream in(file);
        while(in>>i)
            push_back(std::move(i));
        in.close();
    }

    // 移动构造函数
    SequenceList(SequenceList<T>&& seq) noexcept{
        data = seq.data;
        number = seq.number;
        seq.data = nullptr;
        seq.number = 0;
    }

    // 拷贝构造函数
    SequenceList(const SequenceList<T>& seq) {
        data = alloc.allocate(MaxSize);
        number = 0;
        // 当MaxSize小于seq的number，重新分配空间
        if(seq.number > MaxSize)
            rellocate(seq.number + 1);
        uninitialized_copy(seq.data, seq.data + seq.number, data);
        number = seq.number;
    }

    // 实现列表初始化
    SequenceList(const initializer_list<T>& p) {
        data = alloc.allocate(MaxSize);
        number = 0;
        for(auto i:p)
            push_back(std::move(i));
    }
    
    bool operator<=(const SequenceList<T>& seq) {
        int num = number > seq.number?seq.number:number;
        for(int i = 0; i < num; i++) {
            if(data[i] > seq.data[i])
                return false;
        }
        // 当前面的数据都相等时，判断两个对象的number大小
        if(number > seq.number)
            return false;
        return true;
    }

    bool operator>(const SequenceList<T>& seq) {
        return !(*this <= seq);
    }

    bool operator<(const SequenceList<T>& seq) {
        int num = number > seq.number?seq.number:number;
        for(int i = 0; i < num; i++) {
            if(data[i] >= seq.data[i])
                return false;
        }
        // 当前面的数据都相等时，判断两个对象的number大小
        if(number >= seq.number)
            return false;
        return true;
    }

    bool operator>=(const SequenceList<T>& seq) {
        return !(*this < seq);
    }

    bool operator==(const SequenceList<T>& seq) {
        if(number != seq.number)
            return false;
        for(int i = 0; i < number; i++)
            if(data[i] != seq.data[i])
                return false;
        return true;
    }

    bool operator!=(const SequenceList<T>& seq) {
        return !(*this == seq);
    }

    // 拷贝赋值运算符
    SequenceList& operator=(const SequenceList<T>& seq) {
        // 先析构已经初始化的空间
        for(int i = 0; i < number; i++)
            alloc.destroy(data + i);
        uninitialized_copy(seq.data, seq.data + seq.number, data);
        number = seq.number;
        return *this;
    }

    SequenceList& operator+=(const SequenceList& seq) {
        if(MaxSize < number + seq.number)
            rellocate(number + seq.number);
        uninitialized_copy(seq.data, seq.data + seq.number, data + number);
        number = number + seq.number;    
    }

    // 移动赋值运算符
    SequenceList& operator=(SequenceList<T>&& seq) {
        for(int i = 0; i < number; i++)
            alloc.destroy(data + i);
        data = seq.data;
        number = seq.number;
        seq.data = nullptr;
        return *this;
    }
    //插入到末尾
    void push_back(T&& value) noexcept{
        if(number == MaxSize)
            rellocate();
        alloc.construct(data + number, value);
        ++number;
    }

    bool insert_before(const T& element, const T& insert_value){
        int index = locate(element);
        return insert_index(index, insert_value);
    }

    bool insert_after(const T& element, const T& insert_value) {
        int index = locate(element);
        return insert_index(index + 1, insert_value);
    }

    bool insert_index(int index, const T& value) {
        if(index < 0 || index > number)
            return false;
        if(number == MaxSize)
            rellocate();
        alloc.construct(data + number, value);
        for(int i = number; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        ++number;
        return true;
    };

    void erase_element(const T& element) {
        for(int i = 0; i < number; i++)
            if(data[i] == element){
                erase_index(i);
                --i;
            }
    }

    void erase_index(int index) {
        for(int i = index; i < number - 1; i++)
            data[i] = data[i + 1];
        alloc.destroy(data + number);
        --number;
    }

    vector<int>& search(bool (*function)(T&)) {
        vector<int> vec;
        for(int i = 0; i < number; i++)
            if(function(data[i]))
                vec.push_back(i);
        return vec;
    }

    void revise(const T& value, const T& new_value) {
        for(int i = 0; i < number; i++)
            if(data[i] == value)
                data[i] = new_value;
    }

    void revise(bool (*function)(T&), const T& new_value) {
        for(int i = 0; i < number; i++)
            if(function(data[i]))
                data[i] = new_value;
    }

    void show_data() const {
        ostream_iterator<T> out(cout, " ");
        for(int i = 0; i < number; i++)
            out = data[i];
        cout<<endl;
    }

    ~SequenceList() {
        if(data != nullptr){
            for(int i = 0; i < number; i++)
                alloc.destroy(data + i);
            alloc.deallocate(data, number);
        }
    }

    int locate(const T& value) {
        for(int i = 0; i < number; i++)
            if(data[i] == value)
                return i;
        return -1;
    }

    void show_data_in_file(string file) {
        fstream out(file);
        ostream_iterator<T> ou(out, " ");
        for(int i = 0; i < number; i++)
            ou = data[i];
        out<<endl;
        out.close();
    }
};
int main()
{
    SequenceList<int> seq;
    for(int i = 0; i < 12; i++)
        seq.push_back(std::move(i));
    seq.insert_before(0, -1);
    seq.insert_after(11, 12);
    seq.show_data();
    SequenceList<int> seq1("in.txt");
    seq1.show_data();
    SequenceList<double> seq2 = {1.5, 2, 3, 4, 5};
    seq2.show_data();
    SequenceList<int> seq3(std::move(seq));
    seq3.show_data();
    seq1.show_data();
    cout << boolalpha << (seq3 <= seq) << noboolalpha << endl;
    SequenceList<int> seq4 = {1, 2, 3, 4};
    seq += seq4;
    seq.show_data();
    return 0;
}