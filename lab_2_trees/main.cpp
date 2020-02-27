#include <iostream>
#include <chrono>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <map>

/*!
 *  Narzedzie do zliczania czasu
 *
 *  Sposob uzycia:
 *
 *  {
 *    Benchmark<std::chrono::nanoseconds> b;
 *    // kod do zbadania
 *    size_t elapsed = b.elapsed();
 *  }
 *
 *  lub
 *
 *  {
 *    Benchmark<std::chrono::milliseconds> b(true);
 *    // kod do zbadania
 *  } // obiekt wypisze wartosc czasu w podanych jednostkach na stderr
 */
template<typename D = std::chrono::microseconds>
class Benchmark {
public:

    explicit Benchmark(bool printOnExit = false) : m_print(printOnExit) {
        start = std::chrono::high_resolution_clock::now();
    }
    typename D::rep elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        auto result = std::chrono::duration_cast<D>(end-start);
        return result.count();
    }
    ~Benchmark() {
        auto result = elapsed();
        if (m_print)
        {
            std::cerr << "Czas: " << result << "\n";
        }
    }
private:
    std::chrono::high_resolution_clock::time_point start;
    bool m_print = true;
};

/*
 * Slownik
 *
 */
template<typename KeyType, typename ValueType>
class TreeMap
{
  public:
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<key_type, mapped_type>;

    struct Node
    {
        value_type data;
        Node *parent;
        Node *lch;
        Node *rch;

        Node(value_type val){
            parent = lch = rch = nullptr;
            data = val;
        }
    };
    Node *root;

    TreeMap(){
        root = nullptr;
    }    // konstruktor trywialny
    ~TreeMap() = default;   // destruktor trywialny

    /*!
     * true jezeli slownik jest pusty
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /*!
     * dodaje wpis do slownika
     */
    void insert(const key_type& key, const mapped_type &value)
    {
        if(isEmpty()){
            root = new Node({key, value});
            return;
        }

        Splay(key);
        if (key < root->data.first){
            Node *new_node = new Node({key, value});
            new_node->lch = root->lch;
            if(new_node->lch != nullptr)
                new_node->lch->parent = new_node;
            new_node->parent = root;
            root->lch = new_node;

        }
        else if(key > root->data.first ){
            Node *new_node = new Node({key, value});
            new_node->rch = root->rch;
            if(new_node->rch != nullptr)
                new_node->rch->parent = new_node;
            new_node->parent = root;
            root->rch = new_node;
        }
        else{
            root->data = value_type({key, value});
        }
        Splay(key);
    }

    /*!
     * dodaje wpis do slownika przez podanie pary klucz-wartosc
     */
    void insert(const value_type &key)
    {
        insert(key.first, key.second);
    }

    /*!
     * zwraca referencje na wartosc dla podanego klucza
     *
     * jezeli elementu nie ma w slowniku, dodaje go
     */
    mapped_type &operator[](const key_type& key)
    {
        if(!contains(key))
            insert(key, 0);
        return value(key);
    }

    /*!
     * zwraca wartosc dla podanego klucza
     */
    mapped_type &value(const key_type& key)
    {
        Splay(key);
        if(isEmpty() || root->data.first != key)
            throw std::runtime_error("There's no such element in the tree!");
        else
            return root->data.second;
    }

    void Search(const key_type &key)//searching
    {
        root = Splay(key);
    }

    /*!
     * zwraca informacje, czy istnieje w slowniku podany klucz
     */
    bool contains(const key_type& key) {
        Splay(key);
        return root != nullptr && root->data.first == key;
    }

    /*!
     * zwraca liczbe wpisow w slowniku
     */
    size_t size() {
        return size(root);
    }

    size_t size(Node *curr){
        if(curr == nullptr) return 0;
        return 1 + size(curr->lch) + size(curr->rch);
    }
private:
    Node *findNode(const key_type &key){
        return findNode(root, key);
    }

    Node *findNode(Node *curr, const key_type &key){
        if(curr == nullptr)
            return nullptr;
        if(curr->data.first == key)
            return curr;

        if(curr->data.first < key){
            if(curr->rch != nullptr){
                return findNode(curr->rch, key);
            } else
                return curr;
        } else{
            if(curr->lch != nullptr){
                return findNode(curr->lch, key);
            } else
                return curr;
        }
    }

    void rightRotate(Node *curr)
    {
        Node *p = curr->parent, *left = curr->lch;
        curr->lch = p;
        curr->parent = p->parent;
        if(p->parent != nullptr){
            if(p->parent->lch == p)
                p->parent->lch = curr;
            if(p->parent->rch == p)
                p->parent->rch = curr;
        }
        p->rch = left;
        if(left != nullptr)
            left->parent = p;
        p->parent = curr;
        if(curr->parent == nullptr)
            root = curr;
    }

    void leftRotate(Node *curr)
    {
        Node *p = curr->parent, *right = curr->rch;
        curr->rch = p;
        curr->parent = p->parent;
        if(p->parent != nullptr){
            if(p->parent->lch == p)
                p->parent->lch = curr;
            if(p->parent->rch == p)
                p->parent->rch = curr;
        }
        p->lch = right;
        if(right != nullptr)
            right->parent = p;
        p->parent = curr;
        if(curr->parent == nullptr)
            root = curr;
    }

    // splay -> przek drzewo
    Node *Splay(const key_type &key)
    {
        if(isEmpty())
            return nullptr;

        Node *n = findNode(key);
        while(true){
            if(n == root)
                return n;

            Node *p = n->parent;
            Node *gp = p->parent;
            bool p_lch = (root == n->parent) ? false : gp->lch == p;
            bool p_rch = (root == n->parent) ? false : gp->rch == p;

            if(root == n->parent){
                if(p->lch == n)
                    leftRotate(n);
                else if(p->rch == n)
                    rightRotate(n);
            } else if((p_lch && p->lch == n) || (p_rch && p->rch == n)){
                if(p_lch && p->lch == n){
                    leftRotate(p);
                    leftRotate(n);
                } else{
                    rightRotate(p);
                    rightRotate(n);
                }
            } else{
                if(p->rch == n && p_lch){
                    rightRotate(n);
                    leftRotate(n);
                } else if(p->lch == n && p_rch){
                    leftRotate(n);
                    rightRotate(n);
                }
            }

        }
    }
};

#include "tests.h"

int main()
{
    unit_test();

    std::ifstream file;
    file.open("pan-tadeusz.txt");

    std::vector<std::string> words;
    std::string s;
    int licz = 0;
    while(file >> s && licz < 11000){
        words.push_back(s);
        licz++;
    }
    file.close();

    std::ofstream results;
    results.open( "results.txt" );
    for(int i = 1000; i < 10001; i += 1000){
        TreeMap<std::string, std::string> dict_tree;
        std::map<std::string, std::string> dict_def;
        results << "Liczba elementów: " << i << '\n';
        Benchmark<> treeop;
        for(int j = 0; j < i; j++){
            dict_tree.insert({words[j], words[j+1]});
        }
        size_t elapsed = treeop.elapsed();
        results << "TreeMap: " << elapsed << '\n';
        Benchmark<> defop;
        for(int j = 0; j < i; j++){
            dict_def.insert({words[j], words[j+1]});
        }
        elapsed = defop.elapsed();
        results << "DefMap: " << elapsed << '\n';
    }

    return 0;
}
