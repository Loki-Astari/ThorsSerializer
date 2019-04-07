---
layout: plain
generate: false
---
````C++
template<typename T>
class Traits<T*>
{
    public:
        static constexpr TraitType type = TraitType::Pointer;
        static T*   alloc();
        static void release(T* p);
};
````

In this case ThorsSerializer expects the `Traits<T>` class to have two extra static methods: `alloc()` and `release()`.

* `alloc()`  
Is used to allocate an object of type T
* `release()`  
Is used to release an onbject of type T that was allocated via the `alloc()` function.

If you simply want to use `new` and `delete` then the default partial specialization of thie object works out of the box with no extra configuration needed.

##### ThorsAnvil_PointerAllocator
````C++
strict MyDataMemoryPool
{
    MyData* alloc();
    void release(MyData*);
};
ThorsAnvil_PointerAllocator(MyData, MyDataMemoryPool);
````
The easy way to generate the `Traits<>` specialization for a pointer that has its own allocators is via the macro `ThorsAnvil_PointerAllocator()`.
