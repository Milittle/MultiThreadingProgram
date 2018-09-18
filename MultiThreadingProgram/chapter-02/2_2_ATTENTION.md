### 向线程函数传递参数
1. 在创建线程的时候,提供的默认参数一定会拷贝在线程内存里面
2. 需要注意的是,在将动态指针作为参数的时候,可能会出现错误
3. 一切传过去的变量都是对当前值的拷贝
4. 本来的想法是通过引用影响局部变量的值,然后在后续的处理中利用这个特性(但是一般函数的参数组合原则是:输入变量都是常量引用, 输出变量都是指针类型)
5. 也就是函数参数引用类型一般是要使用const类型的.
6. 那么为了实现引用的传递,需要通过std::ref()包含变量来实现引用传参
std::thread t(update_data_for_widget,w,std::ref(data));
以上的代码,update_data_for_widget函数收到的data就是本身data对象的引用,而不是data对象的拷贝的引用
7. 如果你熟悉std::bind那么你应该会使用thread来构建一个新的线程

### 构建一个线程可以传入什么对象来实现执行:
1. 全局普通函数std::thread t(func) 后面的参数是func的参数
2. 类成员变量函数(这个需要一个类的实体) std::thread t(&ThreadFunc::func, &threadFunc) 后面的参数是func的参数
3. 可调用对象(重载了运算符()的类或者结构体) std::thread t(threadFunc) 后面的参数是func的参数 (threadFunc是一个可调用实体)
4. 类的静态方法std::thread t(ThreadFunc::StaticFunc) 后面的参数是func的参数 (StaticFunc是ThreadFunc类的一个实体)
