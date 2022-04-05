## pair 和 tuple
1. 可用 tuple_size<>::value 查看有几个元素  
2. 不包含const拷贝构造函数, 不能被当成 pair 的值   
3. 如果pair类型含有 tuple, 构造函数必须指明 piecewise_construct 
4. 可使用 reference_wrap 和 ref 函数包裹值 


# ratio 分数


# STL组件
1. 容器: 某类对象的集合
2. 迭代器: 遍历集合内元素
3. 算法: 处理集合内元素

## 容器
放入和返回的元素是拷贝的(可使用 指针  智能指针 reference_wrap),  
容器内元素的要求:  
1. 必须是可复制 copy 或者可移动的 move 
2. 必须可通过 assign 操作符  
3. 析构函数必须合法 
4. 对于序列式容器, 默认构造函数必须存在, 是为了 .resize 时, 创建默认元素 
5. 关联式容器必须指明排序准则, 默认是 less<> 
6. 无序容器必须指明 hash 函数  

### 容器分类
1. 序列式容器   (顺序取决于插入的时间和地点)    
array  vector  dequeue list  forward_list


2. 关联式容器   (已排序的容器，顺序取决于value和排序的规则)   
set   multiset   map    multimap


3. 无序容器    (位置无关紧要, 位置可能在其生命周期中发生改变)   
unorder_set   unorder_multiset   unorder_map    unorder_multimap

### 关联式数组
含有 key-value 类型的集合   
可使用 at() 访问元素, 不存在则抛出 out of range 异常   
除非需要排序, 否则倾向于使用 unorder_map    
因为unorder_map复杂度是 摊提式常量   
而 map 是对数复杂度  

### 其他容器
1. string 
2. C-style array 
3. 自定义容器 

### 容器适配器
非标准容器类型, 属于预定义容器  
stack   queue   priority_queue 

### 容器初始化
1. initializer list 初始化 
2. 以其他容器 来初始化 
3. 以c-ctyle array 初始化，配合 std::begin std::end
4. 以输入 istream_iterator 初始化

## 迭代器  (以一个对象表示元素在容器中的位置)
1. 定义于每个容器内部   
template <typename T>  
class Container {  
public:   
    typedef ... iterator;   
    typedef ... const_iterator;  

};

2. 迭代器递增时, 尽量使用 ++pos 替换 pos++ 

### 迭代器种类 
1. 前向迭代器   
只能累加, forward_list 的迭代器  
2. 双向迭代器  
可以前进或者后退   
(multi)list  (multi)set  multi(map)  
3. 随机访问迭代器     
同时具备双向迭代器和随机访问的能力, 可以增加或者减少一个偏移量   
vector  dequeue array string
4. 输入型迭代器  
向前迭代时, 能读取迭代器的值  Input stream 属于此类
5. 输出型迭代器   
向前迭代时, 能写迭代器的值   Insert 和 Output stream 属于此类 

### 迭代器适配器 
具有迭代器接口, 但是实现方式不同   
1. 安插型迭代器 (使用安插替换覆写, 解决空间不足的问题)    
back-inserter   front-inserter  general-inserter 
2. 串流迭代器 
istream_iterator  ostream_iterator
3. 反向迭代器   
所有提供双向迭代器和随机迭代器的容器, 可使用 rbegin 和 rend 获取反向迭代器   
rbegin是最后一个元素, rend 指向第一个元素的前方, 超尾
4. 搬移迭代器  



## 算法 
### 区间 
1. 所有算法都是半开区间的   
2. 超尾

### 多区间
1. 必须确保第二个区间个数 >= 第一个区间 


### 更易型算法
1. 移除 重放 或者修改元素的算法   只能用于序列式容器, 用于关联容器和无序容器会破坏排序规则  
2. remove 算法不删除算法的元素, 只是将移除的元素放在末尾, 并返回最后的元素位置(逻辑终点), 若想删除则应该使用成员函数 erase 删除
3. 迭代器对其所在的容器一无所知, 这样算法可以操作区间 
4. 序列式容器提供的 erase 成员是迭代器, 由于关联式容器和无序容器无法使用更易算法, 提供的 erase 参数为元素值 
5. 基于效能的考虑, 针对使用算法或成员函数, 应该优先考虑使用成员函数, 例如 list 的 remove 成员函数 比 remove 算法 + erase 成员函数更好

### 以函数作为算法的实参
#### 转化式
std::transform

#### 判断式 
1. 相同的值, 必须返回相同的结果 
单参判断式 std::find_if   双参判断式 std::sort  
2. 使用 lambda 函数作为参数有局限性  
例如 std::set<int, rule> 其中需要指明 rule 的类型, 匿名函数没有类型    
typedef bool(*rule)(int a, int b);    
rule func= [](int a, int b) { return true; }  
std::set<int, rule> set(func);   
另外没有 函数对象保存的内部成员变量的 值 的传递性 

### 函数对象   
1. 是一种带状态的函数  
2. 有自己的类型, 不同于普通函数的签名相同, 每个函数对象签名不同
3, 比普通函数运行更快 

### 函数适配器 binder


### 具体容器 

#### Array  
1. 是唯一一个无指定初始值时, 会预初始化的容器, 初始化值可能不为0   
std::array<int, 5> arr;   元素值不一定都为 0 
std::array<int, 5> arr = {} 元素值都为 0 
2. 当需要使用 array 数组时, 一定可以使用 array 容器, 并可以通过 data() 方法获取数据 
3. 提供了 tuple 接口， 可使用 std::get 方法获取值


#### vector 
1. 可以使用 reserve 保存适当的内存, 或者 std::vector vec(size) 初始化分配,  
但是必须保证 元素含有默认构造函数  reserve 不会缩减容量  
2. shrink_to_fit 可缩减容量 
3. std::vector vec(size) 指明了size, 则会调用元素默认构造函数 
4. 无元素时, 不能使用 pop_back, 会引发错误 
5. 可以与 std::array 一样使用 data() 
6. std::vector<bool> 是个特化版本, 提供 flip 取反, 一般是使用 1 byte, 特化版本使用 1 bit 
7. 重新分配内存， 会导致原先的迭代器 引用和指针失效。 删除元素不会。

#### deque 
1. 两端都能删除和插入元素， 是操作可在摊提时间内完成 
2. 访问元素有个间接的过程， 因此速度慢 
3. 除了头尾两端， 在其他位置插入元素， 会导致迭代器等失效 
4. 和 vector 相比, 不提供容量操作, 直接提供函数在头部插入和移除元素 

#### list 
1. 不支持随机访问, 但是插入元素很快
2. 安插和删除元素  迭代器等不会失效 
3. 可以 splice 和 merge sort 成员 

#### forward_list 
1. 只提供前向迭代器, 不提供 size 方法获取
2. 特殊的插入成员函数, _after, 在某个地方的后面插入
3. before_begin 返回锚点后面的位置 
4. 提供和  list 一样的方法 splice 和 merge 

#### set
1. 自动排序, 四个原则: 非对称  非子反  可传递  等效传递 
2. 不能直接改变元素的值, 会造成排序不准确, 必须先删除元素, 再添加元素
3. 不提供任何方法直接访问元素。
4. 可以在运行时，指定排序规则

#### map
1. 内部结构都采用了平衡二叉树的方法, 与 set 类似
2. 不能修改元素的key值, key为const, 但可以修改value
3. 不能在 for 循环中直接删除 pos, 因为for循环中, 一旦被移除了, 此时迭代器无效了, ++pos导致异常, 可重置pos
4. 即使使用 auto value = map["key"], 当key不存在时, 也会默认创建key值
5. 使用 map["key"] = value 速度慢, 因为 map["key"] 在构造 value时, 会先调用默认构造函数, 再用真实 value 替换,  
对于构造函数中含有静态变量的, 会造成静态变量不准确 


#### 

