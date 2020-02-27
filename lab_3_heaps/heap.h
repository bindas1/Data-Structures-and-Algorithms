//
// Created by Bartłomiej Binda on 23/11/2019.
//

#ifndef LAB3_KOPCE_HEAP_H
#define LAB3_KOPCE_HEAP_H

#include <utility>
#include <climits>
#include <vector>

template<typename KeyType, typename ValueType>
class Heap4
{
public:
    using KeyValueType = std::pair<KeyType, ValueType>;
    std::vector<KeyValueType> heap;

    bool empty() const noexcept
    {
        return heap.size() == 0;
    }

    void insert(KeyType const & key, ValueType const & value)
    {
        heap.push_back({key, value});
        int i = heap.size()-1, j = parent(i); //zapisujemy numer wÄ™zÅ‚a z nowym elementem i szukamy numeru wÄ™zÅ‚a rodzica

        while(i >= 0 && heap[j].first > key){
            swap(i, j);
            i = j;
            j = parent(i);    //znajdujemy numer wÄ™zÅ‚a rodzica
        }
    }

    void insert(KeyValueType const & key_value)
    {
        insert(key_value.first, key_value.second);
    }

    KeyValueType const & peek() const noexcept
    {
        if(!heap.empty())
            return heap.front();
        else
            throw std::runtime_error("Heap is empty");
    }

    KeyValueType pop() noexcept
    {
        KeyValueType r = heap[0];
        swap(0, heap.size()-1);
        heap.pop_back();

        int i = 0;
        int j = child(i); // index of the first child
        int min = child(i);
        while(j < heap.size() && j) {
            int counter = 0;
            while(counter < 4 && j+counter < heap.size()) {
                if(heap[min].first > heap[j+counter].first)
                    min = j + counter;
                counter++;
            }
            if(heap[min].first < heap[i].first){
                swap(i, min);
            }
            i = min;
            j = child(i);
            min = child(i);
        }
        return r;
    }

    size_t size() const noexcept
    {
        return heap.size();
    }

    int parent(int index) const{
        if(index >= 0)
        {
            return (index - 1) / 4;
        }
        else
        {
            throw std::runtime_error("wrong index dude!");
        }
    }

    int child(int index) const{
        int ch = 4 * index + 1;
        if(ch > heap.size()-1)
        {
            return INT_MAX;
        }
        else
        {
            return ch;
        }
    }

    void swap(int x, int y){
        KeyValueType temp = heap[x];
        heap[x] = heap[y];
        heap[y] = temp;
    }

    template<typename StreamType>
    void print(StreamType& stream) const
    {
        print(stream, 0, 0);
        stream << std::endl;
    }

    template<typename StreamType>
    void print(StreamType& stream, int index, int tab) const
    {
        if(index < heap.size()){
            for(int i = 0; i < tab; i++) {
                stream << "\t";
            }
            stream << heap[index].first << std::endl;
            for(int i = 0; i < 4; i++) {
                print(stream, child(index)+i, tab+1);
            }
        }
    }
};

#endif //LAB3_KOPCE_HEAP_H
