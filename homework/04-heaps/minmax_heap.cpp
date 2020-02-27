/**
 * @file minmax_heap.cpp
 *
 * 2019Z-AISDI-TUT-4
 *
 * Homework #4.
 */


#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>


namespace {

    template <typename T>
    class ReversibleHeap {
        std::vector<T> v{}; /**< Container for the elements. */
        bool min_heap_mode = true; /**< Heap direction (min-heap vs max-heap). */

      public:
        using size_type = std::size_t;

        ReversibleHeap() = default;

        /**
         * Gets the top value in O(1) time.
         */
        const T& top() const {
            if (this->v.empty()) throw std::out_of_range("calling top() for an empty heap");
            return this->v.front();
        }

        /**
         * Adds a new value to the heap.
         */
        void push(const T& value) {
            this->v.push_back(value);
            this->sift_up(this->v.size() - 1);
        }

        /**
         * Removes the top value from the heap.
         */
        void pop() {
            if (!this->v.empty()) {
                if (this->v.size() > 1) { std::swap(this->v.front(), this->v.back()); }
                this->v.pop_back();

                if (!this->v.empty()) { this->sift_down(0); }
            }
        }

        /**
         * Prints the elements of the heap horizontally.
         */
        void print() {
            std::cout << (this->min_heap_mode ? "min-heap " : "max-heap ");
            std::cout << "of size " << this->v.size() << ": " << std::endl;
            this->print_(0, 2);
        }

        /**
         * Changes the direction of the heap (min <-> max).
         */
        void reverse() {
            this->min_heap_mode = !this->min_heap_mode;
            auto size = this->v.size();
            for(int i = (int)(size-2)/2; i >= 0; --i)
            {
                sift_down(i);
            }
        }

      private:
        /**
         * Compares nodes according to current heap direction (min/max).
         */
        bool compare(const T& lhs, const T& rhs) {
            return this->min_heap_mode ? lhs < rhs : lhs > rhs;
        }

        /**
         * Computes parent's position for a node at `pos`.
         */
        size_type parent(size_type pos) const {
            return pos > 0 ? (pos - 1) / 2 : throw std::out_of_range("parent(pos <= 0)");
        }

        /**
         * Computes position of the `rank`-th child for a node at `pos`.
         */
        size_type child(size_type pos, size_type rank) const {
            assert(0 <= rank && rank < 2);
            return 2 * pos + rank + 1;
        }

        /**
         * Moves the element at `pos` upwards until heap property is restored.
         */
        void sift_up(size_type pos) {
            while (pos) {
                size_type parent = this->parent(pos);

                if (this->compare(this->v[pos], this->v[parent])) {
                    std::swap(this->v[pos], this->v[parent]);
                    pos = parent;
                } else {
                    break;
                }
            }
        }

        /**
         * Moves the element at `pos` downwards until heap property is restored.
         */
        void sift_down(size_type pos) {
            size_type best_pos = pos;

            for (size_type i = 0; i < 2; ++i) {
                size_type child_pos = this->child(pos, i);

                if (child_pos < this->v.size()) {
                    if (this->compare(this->v[child_pos], this->v[best_pos])) {
                        best_pos = child_pos;
                    }
                }
            }

            if (best_pos != pos) {
                std::swap(this->v[pos], this->v[best_pos]);
                this->sift_down(best_pos);
            }
        }

        /**
         * Prints heap from node `pos`.
         */
        void print_(std::size_t pos, int indent = 0) {
            if (pos < this->v.size()) {
                this->print_(this->child(pos, 1), indent + 4);

                if (indent) { std::cout << std::setw(indent) << " "; }
                std::cout << this->v[pos] << "\n";

                this->print_(this->child(pos, 0), indent + 4);
            }
        }
    };


    namespace test {

        void fill_heap(ReversibleHeap<int>& heap, std::vector<int> values) {
            for (const auto& x : values) {
                heap.push(x);
            }
        }


        void verify_heap(ReversibleHeap<int>& heap, std::vector<int> values) {
            for (const auto& x : values) {
                assert(heap.top() == x);
                heap.pop();
            }
        }


        void test_min_heap(std::vector<int> v, bool print = false) {
            auto heap = ReversibleHeap<int>();
            fill_heap(heap, v);
            if (print) { heap.print(); }

            std::sort(v.begin(), v.end());
            verify_heap(heap, v);
        }


        void test_min_heap_to_max(std::vector<int> v, bool print = false) {
            auto heap = ReversibleHeap<int>();
            fill_heap(heap, v);
            if (print) { heap.print(); }

            heap.reverse();  // switching to max-heap mode
            if (print) { heap.print(); }

            std::sort(v.begin(), v.end(), std::greater<int>());
            verify_heap(heap, v);
        }


        void test_max_heap_to_min(std::vector<int> v, bool print = false) {
            auto heap = ReversibleHeap<int>();
            heap.reverse();  // starting from max-heap mode

            fill_heap(heap, v);
            if (print) { heap.print(); }

            heap.reverse();  // back to min-heap
            if (print) { heap.print(); }

            std::sort(v.begin(), v.end());
            verify_heap(heap, v);
        }

    }  // namespace test

}  // namespace


int main() {
    // Example vector
    std::vector<int> v{10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};

    std::cout << "[test] Basic case, works as a min-heap\n";
    test::test_min_heap(v, false);

    std::cout << "[test] Basic case, converts to max-heap\n";
    test::test_min_heap_to_max(v, false);

    std::cout << "[test] Basic case, pushing to max-heap, converts back to min-heap\n";
    test::test_max_heap_to_min(v, false);

    // Single element
    v = {10};

    std::cout << "[test] Single element, works as a min-heap\n";
    test::test_min_heap(v, false);

    std::cout << "[test] Single element, converts to max-heap\n";
    test::test_min_heap_to_max(v, false);

    std::cout << "[test] Single element, pushing to max-heap, converts back to min-heap\n";
    test::test_max_heap_to_min(v, false);

    // Random case
    std::vector<int> v_rand(1000);

    std::mt19937 mersenne(20191126);
    std::uniform_int_distribution<> dist{0, 100};

    auto generator = [&dist, &mersenne]() { return dist(mersenne); };

    std::generate(v_rand.begin(), v_rand.end(), generator);

    std::cout << "[test] Random case, works as a min-heap\n";
    test::test_min_heap(v_rand, false);

    std::cout << "[test] Random case, converts to max-heap\n";
    test::test_min_heap_to_max(v_rand, false);

    std::cout << "[test] Random case, pushing to max-heap, converts back to min-heap\n";
    test::test_max_heap_to_min(v_rand, false);
}
