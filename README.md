# [Amirkabir University of Technology 1400-2: Advanced Programming Course](https://github.com/courseworks/)

## C++ Route Map

- [x] [Stanford CS106B Programming Abstractions In C++](https://github.com/Andy-xiaokang/CS106B)
- [x] [Stanford CS106L Standard C++ programming](https://github.com/Andy-xiaokang/CS106L)
- [x] [Amirkabir University of Technology 1400-2: Advanced Programming Course](https://github.com/Andy-xiaokang/AP1400-2)

## AP1400-2 setup

1. `git clone git@github.com:courseworks/AP1401-1-HW1.git`
2. install [google test](https://github.com/google/googletest/blob/main/googletest/README.md)

    ```shell
    git clone https://github.com/google/googletest.git -b release-1.12.1
    cd googletest # Main directory of the cloned repository.
    mkdir build # Create a directory to hold the build output.
    cd build
    cmake .. # Generate native build scripts for GoogleTest.
    make
    sudo make install
    ```

3. under `/src` directory, turn the ` if (true) ` to `if (false)` to run the unit test
4. build and run (under the project directory) || or directly run in clion

    ```shell
    mkdir build
    cd build
    cmake ..
    make
    ```

5. use Clion for code editor(optional), it's more convenient for C++ programming

## 主要内容

- hw4 Shared_Ptr Unique_Ptr 使用模板类，面向对象的思维模拟 dynamic memory management 的过程，同时遵从 RAII(constructor acquire, destructor
  free) 的准则，对象生命周期结束时自动回收内存。涉及到的主要内容有 template class, operator overload, special member function;
- hw5 inheritance and polymorphism; 
    1. 在 C++ 中，不需要在子类的析构函数中显式调用父类的析构函数。父类的析构函数会自动在子类的析构函数执行完成后被调用。
    2. 在 C++ 中，当创建子类对象时，父类的构造函数会自动被调用，但你需要在子类的构造函数初始化列表中显式指定要调用的父类构造函数。如果不指定，则默认调用父类的默认构造函数（如果存在）
    3. pure virtual function 声明的 abstract class 不可实例化。子类必须实现 pure virtual function
    4. virtual 声明，在父类和子类由继承所引起的多态性中，由指针所调用的虚函数根据指针在内存中所指向的对象的类型来调用对应的虚函数，而不是根据指针类型来调用虚函数（基类的指针可以指向子类的对象，如何使用基类的指针调用正确的子类成员函数？**virtual**）
- hw6 template class, `fstream` and `sstream`, `regex expression` and `priority queue`, `std::accumulate`. 
    1. 注意 q3 中 regex 的一个非常微妙的问题。如果捕获组的正则表达式可以不匹配任何字符串，则在字符串结尾会匹配`\0`空字符串，关键是此时`match[2].matched == true`，`match[2] == "\0"`, 如果后续对 match[2] 进行 std::stoi 转换，自然会抛出错误。 所以要写好正则表达式，在不该匹配的地方返回false. 例如，考虑正则表达式 (a*) 应用在字符串 "bbb" 上。这里，(a*) 是一个捕获组，用来匹配零个或多个字符 a。由于字符串 "bbb" 中没有字符 a，所以捕获组的结果是一个空字符串 
    2. `std::priority_queue` 是基于 `std::vector` 实现的，所以 priority queue 的队首实际上在 vector 的尾端， push, pop 都是基于 vector 的尾端实现的，所以传入 priority queue 的比较函数第一个数值比第二个大，则尾端最小，即按照权值最小的优先队列
  