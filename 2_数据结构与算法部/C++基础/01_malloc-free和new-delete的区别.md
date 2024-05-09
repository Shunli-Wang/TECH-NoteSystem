# 01_malloc-free和new-delete的区别

考察目的：很多工程都是C和C++混写，所以要了解分配内存的差异。

malloc()和free()是C中的`库函数`；
mew和delete是C++中的`操作符`；

共同特征：用来分配内存和释放内存；

不同特征：
    1. new是自动计算分配内存的大小，malloc需要手动计算；
    2. new返回对象类型的指针，malloc返回的是void *，若要使用还需要进行类型强制转换；
        Task *ptask = (Task *)malloc(sizeof(*ptask));
    3. new分配失败后会抛出异常，malloc分配失败返回的是NULL；
    4. new是在free store上分配内存，会通过构造函数进行初始化；malloc在堆上分配；
    5. delete需要对象类型的指针，因为要调用析构函数；free是void*类型的指针；

# 02_虚函数和虚函数表指针的创建时机


