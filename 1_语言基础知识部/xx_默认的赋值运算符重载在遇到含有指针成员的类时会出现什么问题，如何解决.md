# 问题：默认的赋值运算符重载在遇到含有指针成员的类时会出现什么问题，如何解决？

https://www.bilibili.com/video/BV1et411b73Z?p=124&vd_source=d53ef1e7fb36d2471125f5e1d4d681df

**分析**：这个问题其实是在考察深浅拷贝。最好结合例子进行分析。下面的例子用了编译器自己提供的赋值运算符函数，发生了浅拷贝，最终导致堆上的内存被析构了两次，造成内存泄漏。

```c++
class Person {
public:
    int* m_age;

public:
    Person(int n) {
        m_age = new int(n); // 堆区创建，指针赋值
    }
    Person(const Person& p) { // 拷贝构造函数-深拷贝
        // m_age = p.m_age; 默认的拷贝构造，只拷贝指针的数值
        m_age = new int(*p.m_age);
    }
    ~Person() {
        if (m_age != NULL) { // 创建在堆区的数据，需要程序员手动释放
            delete m_age;
            m_age = NULL;
        }
    }
};

int main()
{
    Person p1(10);
    Person p2(20);
    Person p3(30);
    p2 = p1; // 赋值运算操作，默认的是浅拷贝，两个指针指向了同一块内存。最终导致内存被析构两次。
    cout << "p1的年龄是：" << *p1.m_age << endl; // 10
    cout << "p2的年龄是：" << *p2.m_age << endl; // 10
    // 虽然能够正确输出，但是在结束时析构对象会发生问题
    // 本质上是因为默认的operator=函数会执行浅拷贝

    return 0;
}
```

**改进**：解决办法是自己实现operator=函数，手动释放旧内存，再创建新内存进行复制。这样就不会发生泄漏问题了。

```c++
class Person {
public:
    int* m_age;

public:
    Person(int n) {
        m_age = new int(n); // 堆区创建，指针赋值
    }
    Person(const Person& p) { // 拷贝构造函数-深拷贝
        // m_age = p.m_age; 默认的拷贝构造，只拷贝指针的数值
        m_age = new int(*p.m_age);
    }
    ~Person() {
        if (m_age != NULL) { // 创建在堆区的数据，需要程序员手动释放
            delete m_age;
            m_age = NULL;
        }
    }
    void operator=(Person & p) {
        if (m_age != NULL) { // 先把旧的内存释放干净
            delete m_age;
            m_age = NULL;
        }
        m_age = new int(*p.m_age); // 再进行深拷贝
    }
};

int main()
{
    Person p1(10);
    Person p2(20);
    Person p3(30);
    p2 = p1; // 赋值运算操作，执行深拷贝。
    cout << "p1的年龄是：" << *p1.m_age << endl; // 10
    cout << "p2的年龄是：" << *p2.m_age << endl; // 10
    // 正常退出，不会发生任何问题。

    return 0;
}
```

**连续赋值实现**：之前的版本已经能够实现`p1 = p2;`，但是无法实现`p1 = p2 = p3;`。需要修改operator=函数的返回值和类型。常规写法：

```c++
Person& operator=(Person & p) { // 返回值类型应为引用，
        if (m_age != NULL) {
            delete m_age;
            m_age = NULL;
        }
        m_age = new int(*p.m_age);

        return *this; // this是指向此对象的指针，返回自身需要解引用。
    }
```









