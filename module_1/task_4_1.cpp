

template<typename T>
struct DefaultComparator{
    bool operator()(const T& left, const T& right) const {
        return left < right;
    }
};

template<typename T, typename Comparator = DefaultComparator<T>>
class Heap{
private:

};

int main(){

}