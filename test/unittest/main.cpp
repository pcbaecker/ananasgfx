#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"

template <class T> class LazyInit {
public:
    LazyInit(T* p) noexcept : pointer(p) {}

    virtual ~LazyInit() noexcept {
        if (pointer) {
            std::cout << "Length = " << pointer->length() << std::endl;
        }
    }

    T* get() const noexcept {
        return this->pointer;
    }

private:
    T* pointer = nullptr;
};

TEST_CASE("test") {

    std::string s = "peter";
    std::string* my = nullptr;

    {
        LazyInit<std::string> l(&s);
        my = l.get();
    }

    REQUIRE(my == nullptr);

    std::cout << "yo" << std::endl;
}