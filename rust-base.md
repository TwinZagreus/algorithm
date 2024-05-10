# Rust-base

## 1.常见概念

### 1.1.变量与可变性

####1.1.1.在rust中，<u>变量</u>默认是==不可改变==的。

下面代码块（code1.1）是错误的

```rust
//code1.1
fn main() {
    let x = 5;
    println!("The value of x is: {x}");
    x = 6;
    println!("The value of x is: {x}");
}
```

错误信息指出错误的原因是 `不能对不可变变量 x 二次赋值`（`cannot assign twice to immutable variable  `），因为你尝试对不可变变量 `x` 赋第二个值。

#### 1.1.2.在变量名前添加mut使其可变

```rust
//code1.2
fn main() {
    let mut x = 5;
    println!("The value of x is: {x}");
    x = 6;
    println!("The value of x is: {x}");
}
```
将会成功运行如下

```
The value of x is: 5
The value of x is: 6
```


#### 1.1.3.<u>常量</u>是绑定到一个名称的不允许改变的值

不允许对常量使用 `mut`。常量不光默认不可变，它总是不可变。声明常量使用 `const` 关键字而不是 `let`，并且 *必须* 注明值的类型。
