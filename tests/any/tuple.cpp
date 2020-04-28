//
// Created by kekor on 26.04.2020.
//

template<typename... Args>
struct tuple;

template<>
struct tuple<> {};


template<typename Head, typename... Tail>
struct tuple<Head, Tail...> : tuple<Tail...> {
    tuple(Head h, Tail... tail): tuple<Tail...>(tail...), head_(h) {}
    ~tuple() {
        std::cout << "fuck" << std::endl;
    }
    typedef void* value_type;

    tuple<Tail...>& base = static_cast<tuple<Tail...>&>(*this);
    Head       head_;
};

template<int I, typename Head, typename... Args>
struct getter {
    typedef typename getter<I - 1, Args...>::return_type return_type;
    static return_type get(tuple<Head, Args...> &t) {
        auto addr = getter<I - 1, Args...>::get(t);
        return addr;
    }
};

template<typename Head, typename... Args>
struct getter<0, Head, Args...> {
    typedef typename tuple<Head, Args...>::value_type return_type;
    static return_type get(tuple<Head, Args...> &t) {
        auto addr = &t.head_;
        return addr;
    }
};

template<int I, typename Head, typename... Args>
typename getter<I, Head, Args...>::return_type
get(tuple<Head, Args...> &t) {
    auto addr = getter<I, Head, Args...>::get(t);
    return addr;
}

template <typename T>
void some_func(T val) {
    std::cout << val << std::endl;
}



template <class Tuple, size_t... Args>
class Helper {};


template <class Tuple>
class Helper<Tuple> {
public:
    Helper(std::vector<void*> &vectRef, Tuple &tp) {};
    ~Helper() {};
};


template <class Tuple, size_t Head, size_t... Tail>
class Helper<Tuple, Head, Tail...> {
public:
    Helper(std::vector<void*> &vectRef, Tuple &tp) {
        void *ptr = get<Head>(tp);
        vectRef.push_back(ptr);
        Helper<Tuple, Tail...>(vectRef, tp);
    }
};






template <class Tuple, size_t Head, size_t... Tail>
class GetContainer {
public:
    GetContainer(Tuple &tp) {
        void* put = get<Head>(tp);
        _pointers.push_back(put);
        Helper<Tuple, Tail...> helper(_pointers, tp);
    };

    void *runtimeGet(size_t i) {
        return _pointers[i];
    }
private:
    std::vector<void*> _pointers;
};

int main() {
    tuple<int, double, int> t(12, 2.34, 89);

    std::cout << typeid( t ).name() << std::endl;

    GetContainer<tuple<int, double, int>, 0, 1, 2> container(t);

    for (int i = 0; i < 3; ++i) {
        if (i == 0) {
            std::cout << *(int*)container.runtimeGet(i) << std::endl;
        } else if (i == 1) {
            std::cout << *(double*)container.runtimeGet(i) << std::endl;
        } else if (i == 2) {
            std::cout << *(int*)container.runtimeGet(i) << std::endl;
        }
    }
}