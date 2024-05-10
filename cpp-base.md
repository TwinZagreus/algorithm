# C++ Primer Plus

### 第2章 开始学习c++

- c++程序应当为程序中使用的每一个函数提供原型。

### 第3章 处理数据
#### 3.1 简单变量

- 信息将要存储在哪里

- 要存储什么值

- 存储何种类型的信息

  ```c++
  #include <iostream>
  int main()
  {
      using namespace std;
      char ch = 'M';       // assign ASCII code for M to ch
      int i = ch;          // store same code in an int
      cout << "The ASCII code for " << ch << " is " << i << endl;
      return 0;
  }
  
  ```

  上述代码运行结果是

  ```
  The ASCII code for M is 77
  ```

​	注意：在ch（char）和i（int）中储存都为77，是cout工具帮我们完成了转化工作，cout将会根据你的数据类型如何显示值

#### 3.2 const限定符

​	注意：尽量不要使用#define来定义符号常量，而应使用const

#### 3.3 浮点数

##### 3.3.1 浮点数的有效位数


```c++
#include <iostream>
int main()
{
    using namespace std;
    cout.setf(ios_base::fixed, ios_base::floatfield); // 小数顶点模式输出，保留6位
    float tub = 10.0 / 3.0;     // float表示6位有效数字
    double mint = 10.0 / 3.0;   // double表示15位有效数字
    const float million = 1.0e6;

    cout << "tub = " << tub;
    cout << ", a million tubs = " << million * tub;
    cout << ",\nand ten million tubs = ";
    cout << 10 * million * tub << endl;

    cout << "mint = " << mint << " and a million mints = ";
    cout << million * mint << endl;
    return 0;
}

```

上述代码运行结果是

```c++
tub = 3.333333, a million tubs = 3333333.250000,
and ten million tubs = 33333332.000000
mint = 3.333333 and a million mints = 3333333.333333
```

​	注意：float只能表示6位有效数字，6位以后都不准确。double能精确表示15位有效数字

##### 3.3.2 浮点数的默认值转为double
​	

