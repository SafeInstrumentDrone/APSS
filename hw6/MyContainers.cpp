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

        ~MyContVec () {
            delete [] values; 
        };

        int size () {
            return length;
        };

        void push_back (T v) {
            T* new_region = new T [length + 1];
            for(size_t i = 0; i < length; ++i){
                new_region[i] = values[i];
            };
            new_region[length] = std::move(v);
            delete [] values;
            values = new_region;
            length += 1;
        };

        void erase (int del) {            
            T* new_region = new T [length - 1];
            int k = 0;
            for(size_t i = 0; i < length; ++i){
                if(i == del-1) k = 1;                   
                new_region[i] = values[i + k];
            };
            delete [] values;
            values = new_region;
            length -= 1;
        };

        void insert (T v, int pos) {
            T* new_region =  new T [length + 1];
            int k = 0;
            for(size_t i = 0; i < length; ++i){
                if(i == pos) k = 1;
                new_region[i+k] = values[i];
            };

            new_region[pos] = std::move(v);

            delete [] values;
            values = new_region;
            length += 1;
        };

        void printValue() {
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

// template <typename T>
// struct Node{
//     Node* next;
//     Node* prev;
//     T data;
// }; 

template <typename T>
class MyContList {
    public:
        MyContList () {};
        MyContList (T v) {
            m_first->prev = nullptr;
            m_first->next = nullptr;
            m_first->data = v;
         };

        ~MyContList () {
            while(m_first){
                delete std::exchange(m_first, m_first->next);
            }
        };

        int size () {
            return m_size;
        };

        void push_back (T v) {
            Node* new_node = new Node{};

            if(m_size > 0){
                m_last->next = new_node;
                new_node->prev = m_last;
                new_node->next = nullptr;
                new_node->data = v;            
                m_last = new_node;                
            }else{                 
                m_first = new_node;
                m_last = new_node;
                m_first->data = v;
                m_last->data = v;          
            }
            m_size += 1;    
        };

        void erase (int del) {
            Node* tmp = m_last;  //тут бы проверку - к концу или началу ближе индекс...
            for(int i = m_size; i > 0; i--){
                if(i == del){   
                    tmp->next->prev = tmp->prev;
                    tmp->prev->next = tmp->next;
                    delete tmp;
                    m_size--;
                    break;
                }
                else{
                    //tmp = tmp->prev;
                    std::exchange(tmp, tmp->prev);
                }
            }
        };

        void insert (T v, int pos) {
            if(pos>=m_size){//  багофича: здесь, если прилетела вставка больше наличия - просто пушбачим в конец
                push_back(v);
                return;
            };

            Node* new_node = new Node{};
            new_node->data = v;
            Node* tmp = m_first; //тут бы проверку - к началу или концу ближе индекс...
            for(int i=0; i < pos; ++i){                
                std::exchange(tmp, tmp->next);
            };
            if(!(tmp->prev == nullptr)){ //если вставка в начало
                new_node->prev = tmp->prev;
                tmp->prev->next = new_node;
            }else 
                m_first = new_node;
                
            new_node->next = tmp;                
            tmp->prev = new_node;
            
            m_size++;
        };

        void printValue() {
            Node* tmp = m_first;
            while (tmp){                
                std::cout << tmp->data << std::endl; 
                std::exchange(tmp, tmp->next);
            }
        };

        T operator[] (int pos) {
            Node* tmp = m_first; //тут бы проверку - к началу или концу ближе индекс...
            for(int i=0; i < pos; ++i){                
                std::exchange(tmp, tmp->next);
            };
            return tmp->data;
        }        

    private:
        struct Node{
            Node* next;
            Node* prev;
            T data;
        }; 

        int m_size = 0;
        Node* m_first = nullptr;   
        Node* m_last = nullptr;
};


 int main(int argc, char* argv[]){
        
        MyContVec<int> valuesV;
        for(int i = 0; i < 10; i++)
            valuesV.push_back(i);
        
        std::cout << "sizeVec=" << valuesV.size() << std::endl;
        valuesV.printValue();

        std::cout << "eraseVec" << std::endl;   
        valuesV.erase(7);
        valuesV.erase(5);
        valuesV.erase(3);                     
        valuesV.printValue();
        
        std::cout << "insertVec first" << std::endl;
        valuesV.insert(10,0);
        valuesV.printValue();

        std::cout << "insertVec middle" << std::endl;
        valuesV.insert(20,valuesV.size() / 2);
        valuesV.printValue();

        std::cout << "insertVec last" << std::endl; 
        valuesV.insert(30,valuesV.size());
        valuesV.printValue();

        std::cout << "Vec[4]=" << valuesV[4] << std::endl;

        MyContList<int> valuesL;
        for(int i = 0; i < 10; i++)
            valuesL.push_back(i);

        std::cout << "sizeList=" << valuesL.size() << std::endl;
        valuesL.printValue();

        std::cout << "eraseList" << std::endl;        
        valuesL.erase(7);
        valuesL.erase(5);
        valuesL.erase(3);
        valuesL.printValue();

        std::cout << "insertList first" << std::endl;
        valuesL.insert(10,0);
        valuesL.printValue(); 

        std::cout << "insertList middle"<< std::endl;
        valuesL.insert(20,valuesL.size() / 2);
        valuesL.printValue();

        std::cout << "insertList end"<< std::endl;
        valuesL.insert(30,valuesL.size());
        valuesL.printValue();

        std::cout << "List[4]=" <<valuesL[4] << std::endl;
        
    return 0;
}