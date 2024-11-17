#include <stdio.h>
#include<utility>
#include<iostream>
#include<vector>


template <typename T>
class MyContVec {
    public:
        MyContVec () {};
        MyContVec (T v) {
            values [0] = v;
        };

        ~MyContVec () {delete [] values; };

        int size () {
           // length = sizeof(values) / sizeof(T);
            return length;
        };

        void push_back (T v) {
            //int new_size = length + 1;
            T* new_region = /*::operator*/ new T [length + 1/*new_size*/];
            for(size_t i = 0; i < length; ++i){
                new_region[i] = values[i];
            };

            new_region[length] = std::move(v);

            delete [] values;
            values = new_region;
            length += 1;
            // !!! delete[] new_region;
        };

        void erase (/*T v,*/ int del) {
            //int new_size = length + 1;            
            /*decltype(values)*/T* new_region = /*::operator*/ new /*decltype(values)*/ T [length - 1/*new_size*/];
            int k = 0;
            for(size_t i = 0; i < length; ++i){
                if(i == del-1) k = 1;                   
                new_region[i] = values[i + k];
            };

            //new_region[length] = std::move(v);

            delete [] values;
            values = new_region;
            length -= 1;
            // !!! delete[] new_region;
        };


        void insert (T v, int pos) {
            //int new_size = length + 1;
            T* new_region = /*::operator*/ new T [length + 1/*new_size*/];
            int k = 0;
            for(size_t i = 0; i < length; ++i){
                if(i == pos) k = 1;
                new_region[i+k] = values[i];
            };

            new_region[pos] = std::move(v);

            delete [] values;
            values = new_region;
            length += 1;
            // !!! delete[] new_region;
        };

        void printValue() {
            //auto a = sizeof(values);
            //auto b = sizeof(T);

            //length = a; /// b;
            for(size_t i = 0; i < length; ++i){
                std::cout << values[i] << std::endl;
            }
        };

        T operator[] (int i) {
            return values[i];
        }        

    private:
        int length = 0;
        int capacity = 0;
        T* values = nullptr;    

};

template <typename T>
struct Node{
    Node* next;
    Node* prev;
    T data;
}; 

template <typename T>
class MyContList {
    public:
        MyContList () {};
        MyContList (T v) {
            node->prev = nullptr;
            node->next = nullptr;
            node->data = v;
         };

        ~MyContList () {/*delete [] values;*/ 
            for(int i = m_size; i < 0; i--){
                Node<T> * tmp = node->prev;
                delete m_last;
                m_last = tmp;
            }
        };

        int size () {
           // length = sizeof(values) / sizeof(T);
            return m_size;
        };

        void push_back (T v) {
            Node<T>* new_node = new Node<T>{};

            m_last->next = new_node;

            new_node->prev = m_last;
            new_node->next = nullptr;
            new_node->data = v;            
            m_last = new_node;
            m_size += 1;

            // //int new_size = length + 1;
            // T* new_region = /*::operator*/ new T [length + 1/*new_size*/];
            // for(size_t i = 0; i < length; ++i){
            //     new_region[i] = values[i];
            // };

            // new_region[length] = std::move(v);

            // delete [] values;
            // values = new_region;
            // length += 1;
            // // !!! delete[] new_region;
        };

        void erase (/*T v,*/ int del) {
            Node<T> * tmp = m_last;
            for(int i = m_size; i > 0; i--){
                if(i == del){   
                    auto a = tmp->next->prev;
                    auto b = tmp->prev->next;
                    tmp->prev->next = a;
                    tmp->next->prev = b;
                    delete tmp;
                    //m_last = tmp;
                    continue;
                }
                else{
                    tmp = tmp->prev;
                }
            }
        };


        void insert (T v, int pos) {
            // //int new_size = length + 1;
            // T* new_region = /*::operator*/ new T [length + 1/*new_size*/];
            // int k = 0;
            // for(size_t i = 0; i < length; ++i){
            //     if(i == pos) k = 1;
            //     new_region[i+k] = values[i];
            // };

            // new_region[pos] = std::move(v);

            // delete [] values;
            // values = new_region;
            // length += 1;
            // // !!! delete[] new_region;
        };

        void printValue() {
            // //auto a = sizeof(values);
            // //auto b = sizeof(T);

            // //length = a; /// b;
            // for(size_t i = 0; i < length; ++i){
            //     std::cout << values[i] << std::endl;
            // }
        };

        T operator[] (int i) {
             return node->data;
        }        

    private:
        // struct Node{
        //     Node* next;
        //     Node* prev;
        //     T data;
        // }; 

        int m_size = 0;
        Node<T>* node = nullptr;   
        Node<T>* m_last = nullptr;
};


 int main(int argc, char* argv[]){

       { 
        MyContVec<int> values;
        for(int i = 0; i < 10; i++)
            values.push_back((float)i);
        //values.push_back(188);

        values.printValue();
        std::cout << "erase" << '\n';

        
        values.erase(7);
        values.erase(5);
        values.erase(3);
        values.printValue();
        std::cout << "insert" << '\n';

        values.insert(10,0);//values.insert(11,1);
        values.insert(20,values.size() / 2);
        values.insert(30,values.size());
        values.printValue();

        std::cout << "[]" << '\n';
        std::cout << values[4] << '\n';

        // std::vector<int> a;
        // a.push_back(1);
        // a.push_back(4);
        // a.push_back(8);
        // print_container(a);
        // a.erase(a.begin(), a.end()-1);
        // print_container(a);
        }

        {
        MyContList<int> values;
        for(int i = 1; i <= 10; i++)
            values.push_back((float)i);
        //values.push_back(188);

        values.printValue();
        std::cout << "erase" << '\n';

        
        values.erase(7);
        values.erase(5);
        values.erase(3);
        values.printValue();
        std::cout << "insert" << '\n';

        values.insert(10,0);//values.insert(11,1);
        values.insert(20,values.size() / 2);
        values.insert(30,values.size());
        values.printValue();

        std::cout << "[]" << '\n';
        std::cout << values[4] << '\n';
        }
    return 0;
}