---
layout: plain
generate: false
---
````C++
#include "ThorSerialize/JsonThor.h"
#include "ThorSerialize/SerUtil.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

int main()
{
    std::vector<int>    data = {1,2,3,4,5,6,7};
    std::cout << jsonExport(data) << "\n";
}
...
 [ 1, 2, 3, 4, 5, 6, 7]
````
The standard library container types are all supported. You simply need to include `#include "ThorSerialize/SerUtil.h"`.

* `std::array<T,N>`
* `std::list<T>`
* `std::vector<T, Allocator>`
* `std::deque<T, Allocator>`
* `std::pair<A,B>`
* `std::set<K>`
* `std::multiset<K>`
* `std::map<K,V>`
* `std::multimap<K,V>`
* `std::tuple<Args...>`
* `std::unordered_set<K,V>`
* `std::unordered_multiset<K>`
* `std::unordered_map<K,V>`
* `std::unordered_multimap<K,V>`
* `std::initializer_list<T>`
* `std::unique_ptr<T>`
