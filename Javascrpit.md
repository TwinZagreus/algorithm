### JavaScript简介

#### 解释型

解释型编程语言指代码不需要手动编译,浏览器都已经自动集成了JS的解释器,Node.JS也是JS引擎，它使得JS可以直接在计算机中运行。无论是浏览器还是Node.js都需要遵循==**ECMAScript（ES）标准**==

#### 函数型

#### 单线程

JS同一时间只能做一件事，一件事完成才会继续做另一件事。单线程降低了JS代码的复杂度，也在某些场景下使得JS性能变差，所以JS又为我们提供了异步的编程方式

#### 面向对象

#### 扩展ES

### JS事件循环机制

#### 调用栈（call stack）

 栈是一种数据结构，后进先出

调用栈中，放的是要执行的代码

#### 任务队列（task queue）

队列是一种数据结构，先进先出

任务队列的是将要执行的代码

当调用栈中的代码执行完毕后，队列中的代码才会按照顺序依次进入到栈中执行

##### 实例

```js
for(var i = 0; i< 10 ; i++) {
   setTimeout(function() {
      console.log(i);
   }, 0);
}//答案全都是10
```

script部分入栈,for循环作为同步任务,率先执行,而setTimeout作为异步任务被webcore中的timer模块暂时挂起,异步任务在webcore中执行,完成后会通知调用栈(call stack),并将其同步部分(一般是回调)放入任务队列(task queue)里面去。等到主进程执行完,就会去执行任务队列(task queue)里面的内容。由于var出来的变量位于他自身的函数作用域当中,是会被for循环重复赋值.这就是**==事件循环==**

```js
for(let i = 0; i< 10 ; i++) {
   setTimeout(function() {
      console.log(i);
   }, 0);  // 答案是 0,1,2,3,4,5,6,7,8,9
}
```

es6提供的let声明方式,存储的变量会单独开辟出一个作用域,被我们称之为"块级作用域"。每个块级作用域依次入栈出栈(进去了执行完,立即出,不会出现堆栈的情况),每次执行完都会执行一次任务队列

#### 宏任务(macro task)（task） 和 微任务(micro task)（job）

任务队列分为宏任务和微任务，在最新标准中分为task和job

宏任务包括

```js
script(整体代码)
setTimeout//定时器的本质，就是在指定时间后将函数添加到消息队列中
setInterval//间隔一段时间就将函数添加到消息队列中是如果函数执行的速度比较慢，它是无法确保每次执行的间隔都是一样的
I/O
UI交互事件
postMessage
MessageChannel
setImmediate(Node.js 环境)
```

微任务包括

```js
Promise.then
Object.observe
MutationObserver
process.nextTick(Node.js 环境)
```

1. 执行一个宏任务（栈中没有就从事件队列中获取）
2. 执行过程中如果遇到微任务，就将它添加到微任务的任务队列中
3. 宏任务执行完毕后，立即执行当前微任务队列中的所有微任务（依次执行）
4. 当前宏任务执行完毕，开始检查渲染，然后GUI线程接管渲染
5. 渲染完毕后，JS线程继续接管，开始下一个宏任务（从事件队列中获取）

### null、NaN、undefined

#### 空值 （Null）

空值用来表示空对象

空值只有一个 null

使用typeof检查一个空值时会返回"object"

基础数学运算中视为0

```js
!null//true
typeof null//"object"
null+5//5数学运算中是为0
```



#### 未定义（Undefined）

当声明一个变量而没有赋值时，它的值就是Undefined

Undefined类型的值只有一个就是 undefined

使用typeof检查一个Undefined类型的值时，会返回 "undefined"

基础数学运算会返回NaN

```js
!undefined//true
typeof undefined//"undefined"
undefined+1//Nan
```

==**注意**==

```js
undefined == null//true
undefined === null//false
```

#### NaN（Not a Number）

当我们要得到的数字不是数字时，JavaScript会返回NaN

NaN实际上是一个数字

```js
typeof NaN//number
NaN==NaN//false

let a="a"-1
isNan(a)//true
```

### 所有表示空性的没有的错误的值都会转换为false

 0、NaN、空串、null、undefined、false

### 相等运算符

==它会将其转换为相同的类型（通常转换为数值）然后再比较类型转换后值相同也会返回true

===不会进行类型转换

```js
1==“1”//true
true == "1"//true
null==undefined//true

1 === "1"//false
null === undefined//false
```

!=会自动的进行类型转换

!==不会自动的类型转换

```js
1 != 1//false
1 != "1“//false
1 !== "1"//true
```

### 作用域

#### 全局作用域

全局作用域在网页运行时创建，在网页关闭时消耗

所有直接编写到script标签中的代码都位于全局作用域中

全局作用域中的变量是全局变量，可以在任意位置访问

#### 局部作用域

##### 块作用域

块作用域是一种局部作用域

块作用域在代码块执行时创建，代码块执行完毕它就销毁

在块作用域中声明的变量是局部变量，只能在块内部访问，外部无法访问

##### 函数作用域

函数作用域也是一种局部作用域

函数作用域在函数调用时产生，调用结束后销毁

函数每次调用都会产生一个全新的函数作用域

在函数中定义的变量是局部变量，只能在函数内部访问，外部无法访问

#### 作用域链

当我们使用一个变量时，JS解释器会优先在当前作用域中寻找变量，

如果找到了则直接使用

如果没找到，则去上一层作用域中寻找，找到了则使用

如果没找到，则继续去上一层寻找，以此类推

如果一直到全局作用域都没找到，则报错 xxx is not defined

#### 块级作用域和全局作用域的声明与赋值时间

在块级作用域内的函数声明会同时在块作用域和全局作用域的变量对象上创建声明，但它只会将自身的值提升到块作用域的顶部，而此时全局作用域下的 a 为 undefined。当代码运行到函数声明这一步时才会对外层作用域进行赋值。

```js
console.log(a, window.a);
{
  console.log(a, window.a);
  a = 1;
  console.log(a, window.a);
  function a(){}
  console.log(a, window.a);
  a = 5;
  console.log(a, window.a);
}
console.log(a, window.a);


undefined    undefined
ƒ a(){}    undefined
1    undefined
1    1
5    1
1    1
```



### let和var区别

let声明的变量具有块作用域在代码块中声明的变量无法在代码块的外部访问

```js
{
	let a = 10
}
console.log(a)//无法访问到let
```

var声明的变量，不具有块作用域，但有函数作用域。'

在全局中使用var声明的变量，都会作为window对象的属性保存'

使用function声明的函数，都会作为window的方法保存

```js
var b = 20
window.b = 20//直接在script中声明两者等价
```

==注意==在局部作用域中，如果没有使用var或let声明变量，则变量会自动成为window对象的属性 也就是全局变量

```js
function fn2(){
	d = 10 // 在局部作用域中，如果没有使用var或let声明变量，则变量会自动成为window对象的属性 也就是全局变量
    //等价于window.d=10
    //var d=10因为var有函数作用域也属于局部作用域所以外部无法访问到
}
fn2()
console.log(d)
```

### 变量提升

```js
console.log(b);
var b = 10;
//var b声明变量这一操作会提升到代码最前但b=10这一赋值过程不会
//所以打印输出undefined

fn();
function fn(){//直接定义的函数会变量提升且赋值
	alert("我是fn函数~");
}
var fn2 =function(){
    //var定义的函数不会变量提升
    alert("我是fn2函数~");
}
```

### this相关

  1. 以函数形式调用，this是window

  2. 以方法形式调用，this是调用方法的对象

  3. 构造函数中，this是新建的对象

  4. 箭头函数没有自己的this，由外层作用域决定

  5. 通过call和apply调用的函数，它们的第一个参数就是函数的this

  6. 通过bind返回的函数，this由bind第一个参数决定（无法修改）

        ==**箭头函数没有自身的this，它的this由外层作用域决定，也无法通过call apply 和 bind修改它的this 箭头函数中没有arguments**==

```js
const obj = {
    name:"孙悟空",
    sayHello(){
        console.log(this);//以方法的形式，this指向调用方法的对象
        function t(){
			console.log("t -->", this)
        }
        t()//以函数形式调用this肯定是window
        const t2 = function(){
            console.log("t2 -->", this)
        };
        t2()//以函数形式调用this肯定是window
        const t3 = () => {
            console.log("t3 -->", this)
        };
        t3();//箭头函数没有this，所以他的this与sayHello()相同
    }
}
const obj2={name:"对象2"}
obj.sayHello();
obj.sayHello.apply(obj2);//第一个this和箭头函数的this将变为obj2
```

### 对象中存储属性区域有两个：

#### 1、对象自身

#### 2、原型对象(prototype)

在对象中会有一个属性用来存储原型对象，这个属性叫做____proto____

会添加到原型对象中的情况：

1. 在类中通过xxx(){}方式添加的方法，位于原型中

2. 主动向原型中添加的属性或方法

原型对象也负责为对象存储属性，

1. 当我们访问对象中的属性时，会优先访问对象自身的属性，
2. 对象自身不包含该属性时，才会去原型对象中寻找

所有的同类型对象它们的原型对象都是同一个，也就意味着，同类型对象的原型链是一样的见代码

```js
class Dog {};
const d = new Dog();
const d2 = new Dog();
console.log(d.__proto__ === d2.__proto__);//true
```

 原型的作用：

​	1、原型就相当于是一个公共的区域，可以被所有该类实例访问，

​	2、可以将该类实例中，所有的公共属性（方法）统一存储到原型中

​	3、  这样我们只需要创建一个属性，即可被所有实例访问

​	4、 JS中继承就是通过原型来实现的,当继承时，子类的原型就是一个父类的实例

**==__proto__是当前对象的原型对象（隐式原型），而prototype是当前构造函数的原型对象（显式原型），见代码==**

```js
class Person{};
const p=new Person();
console.log(Person.prototype);
console.log(p.__proto__);//两者相同
Person.prototype===p.__proto__//true
```

#### 修改原型的原则原则：

               1. 原型尽量不要手动改
               2. 要改也不要通过实例对象去改
               3. 通过 类.prototype 属性去修改
               4. 最好不要直接给prototype去赋值

### 浅拷贝与深拷贝

```js
const arr2 = structuredClone(arr) // 专门用来深拷贝的方法
```

### 闭包

当我们需要隐藏一些不希望被别人访问的内容时就可以使用闭包

#### 闭包要件构成：

1. 函数的嵌套

2. 内部函数要引用外部函数中的变量

3. 内部函数要作为返回值返回

```js
function outer(){
    let num = 0 // 位于函数作用域中
    return () => {
        num++
        console.log(num)
    }
}
```

#### 闭包的生命周期：

1. 闭包在外部函数调用时产生，外部函数每次调用都会产生一个全新的闭包

2. 在内部函数丢失时销毁（内部函数被垃圾回收了，闭包才会消失）

#### 闭包的产生的内存泄露原因和解决方案

原因：闭包会造成内存泄漏，就是因为它把外部的包含它的函数的活动对象也包含在自己的作用域链中了，会比一般的函数占用更多内存

解决方法：创建一个变量给闭包函数，手动使用后，手动设置为null。

### Map和Object的主要区别：

Object中的属性名只能是字符串或符号，如果传递了一个其他类型的属性名，JS解释器会自动将其转换为字符串

Map中任何类型的值都可以称为数据的key

### 事件冒泡

事件的冒泡就是指事件的向上传到

当元素上的某个事件被触发后，其祖先元素上的相同事件也会同时被触发

冒泡的存在大大的简化了代码的编写，但是在一些场景下我们并不希望冒泡存在

不希望事件冒泡时，可以通过事件对象来取消冒泡

### 事件委派

就是将本该绑定给多个元素的事件，统一绑定给document或者父元素，这样可以降低代码复杂度方便维护

### JS的垃圾回收机制

标记清除

首先它会遍历堆内存上所有的对象，分别给它们打上标记，然后在代码执行过程结束之后，对所使用过的变量取消标记。在清除阶段再把具有标记的内存对象进行整体清除，从而释放内存空间

引用计数

只要没有任何变量或数据指向它，那么它就会被回收
