#include <stdio.h>


template <typename T>
class MyContVec {
    public:
        MyContVec () {};
        MyContVec (T v) {
            values [0] = v;
        };

        ~MyContVec () {delete [] values; };

        int size () {
            length = sizeof(values) / sizeof(T);
            return length;
        };

        void push_back (T v) {
            int new_size = length + 1;
            T* new_region = ::operator new T [new_size];
            for(size_t i = 0; i < length; ++i){
                new_region[i] = values[i];
            };

            new_region[length] = std::move(v);

            delete [] values;
            values = new_region;
            length += 1;
            // !!! delete[] new_region;
        };

        void printValue() {
            length = sizeof(values) / sizeof(T);
            for(size_t i = 0; i < length; ++i){
                std::cout << values[i] << std::endl;
            }
        };

    private:
        int length = 0;
        int capacity = 0;
        T* values = nullptr;    

};



 int main(int argc, char* argv[]){
        //49:00 / 1:25:15

    return 0;
}