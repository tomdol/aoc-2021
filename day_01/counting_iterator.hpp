#pragma once

#include <iterator>

template<typename Predicate, typename T = int32_t>
struct CountingIterator : std::iterator<std::output_iterator_tag, T> {
    struct CountingProxy {
        CountingProxy(Predicate&& pred, T& counter) : _pred{std::forward<Predicate>(pred)}, _counter{counter} {}
        CountingProxy& operator=(const T& value) {
            if(_pred(value))
                ++_counter;
            return *this;
        }
    private:
        Predicate _pred;
        T& _counter;
    };

    CountingIterator(Predicate&& pred, T init = 0)
        : _counter{init}, _proxy{CountingProxy{std::forward<Predicate>(pred), _counter}} {}

    using reference = CountingProxy&;
    reference operator*() { return _proxy; }
    CountingIterator& operator++() { return *this; }
    T count() const { return _counter; }

private:
    T _counter;
    CountingProxy _proxy;
};
