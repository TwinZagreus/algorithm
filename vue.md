

### 讲讲VUE

​		-MVVM数据驱动

​				-Model：模型层，负责处理业务逻辑以及和服务器端进行交互

​				-View：视图层：负责将数据模型转化为UI展示出来，可以简单的理解为HTML页面

​				-ViewModel：视图模型层，用来连接Model和View，在Vue中就是我们的VueModel

​		-组件化

​				-高内聚、低耦合、可组合、可复用

​				-提高开发更新维护效率

​		-虚拟DOM

​				-直接操作DOM性能低，页面性能问题大部分是DOM操作引起的

​				-vue可以对这颗抽象树进行创建节点,删除节点以及修改节点的操作， 经过diff算法得出一些需要修改的最小单位,再更新视图，减少了dom操作，提高了性能

### SPA(单页面应用)理解

​		-单页应用SPA是一种网络应用程序或网站的模型

​

|                 | **单页面应用（SPA）**     | **多页面应用（MPA）**               |
| --------------- | ------------------------- | ----------------------------------- |
| 组成            | 一个主页面和多个页面片段  | 多个主页面                          |
| 刷新方式        | 局部刷新                  | 整页刷新                            |
| url模式         | 哈希模式                  | 历史模式                            |
| SEO搜索引擎优化 | 难实现，可使用SSR方式改善 | 容易实现                            |
| 数据传递        | 容易                      | 通过url、cookie、localStorage等传递 |
| 页面切换        | 速度快，用户体验良好      | 切换加载资源，速度慢，用户体验差    |
| 维护成本        | 低                        | 高                                  |

​		-优点：

​				-具有桌面应用的即时性、网站的可移植性和可访问性

​				-用户体验好、快，内容的改变不需要重新加载整个页面

​				-良好的前后端分离，分工更明确

​		-缺点：

​				-不利于搜索引擎的抓取

​				-首次渲染速度相对较慢

### VueComponent和VueModel

​		-VM是Vue构造函数new出来的实例化对象

​		-VC是VueComponent构造函数new出来的实例

​		-VC继承于VM，VM是VC的原型对象。VC可以通过.\_\_proto\_\_访问到VM

​		-题外：.vue文件是VC构造函数new出来的实例所以this指向他的调用他的实例

### v-show和v-if

​		-用法上也是相同的

​		-v-show隐藏则是为该元素添加css--display:none,不会触发组件的生命周期不能用于template标签

​		-v-if显示隐藏是将dom元素整个添加或删除；由false变为true的时候，触发组件的beforeCreate、create、beforeMount、mounted钩子，由true变			为false的时候触发组件的beforeDestory、destoryed方法

### created和mouted的区别

​		-created是在组件实例一旦创建完成的时候立刻调用，这时候页面dom节点并未生成；

​		-mounted是在页面dom节点渲染完毕之后就立刻执行的。

​		-建议对页面内容的改动放在created生命周期当中

### v-for优先级比v-if高

​		-如果放在一个元素上每次渲染都会先循环再进行条件判断

### Vue响应式

#### 实现原理

​		-Observe类将对象内部通过defineReactive方法，使用object.defineProperty将属性进行重写getter和setter劫持

​		-Observe类将数组是通过重写数组（pop、shift、splice）等方法实现的

#### 缺点

​		-新增和删除无法监控。要通过$set、$delete实现响应式

​		-对于复杂对象需要深度监听、递归到底、计算量大

​		-无法监听数组

#### ==依赖收集==

​		-vue接收一个模板和data参数。
1，首先将data中的数据进行递归遍历，对每个属性执行Object.defineProperty，定义get和set函数。并为每个属性添加一个dep数组。当get执行时，会为调用的dom节点创建一个watcher存放在该数组中。当set执行时，重新赋值，并调用dep数组的notify方法，通知所有使用了该属性watcher，并更新对应dom的内容。
2，将模板加载到内存中，递归模板中的元素，检测到元素有v-开头的命令或者双大括号的指令，就会从data中取对应的值去修改模板内容，这个时候就将该dom元素添加到了该属性的dep数组中。这就实现了数据驱动视图。在处理v-model指令的时候，为该dom添加input事件（或change），输入时就去修改对应的属性的值，实现了页面驱动数据。
3，将模板与数据进行绑定后，将模板添加到真实dom树中。


### ==页面之间通信==

​		-1、LocalStorage 作为前端最常用的本地存储，LocalStorage 变化时，会触发storage事件。利用这个特性，我们可以在发送消息时，把消息写入到某个 LocalStorage 中；然后在各个页面内，通过监听storage事件即可收到通知。

​		-2、通过URL传递，通过window.open或window.location打开。

### computed和watch区别

​		-computed每一个计算属性内部维护一个dirty:true;当为true时执行方法把值缓存起来并将值改为false;当第二次取值时为false,直接返回缓存的值

​		-watch

​				1.计算属性会创建一个计算属性watcher,这个watcher上有一个lazy为true不会立刻执行

​				2.通过object.defineProperty将计算属性定义到实例属性上

​				3.当用户取值出发getter时,会访问watcher的dirty,如果为true则求值

​				4.如果依赖的属性发生变化,触发计算属性更新dirty并出发页面更新

​				5.如果依赖的值没有变化,则采用缓存

### Cookie、localStorage和sessionStorage的区别

#### Cookie

​		-勾选HttpOnly：使用 Cookie 不能被 Javascript 脚本访问，只有服务端能控制，通常用于访问者身份信息、安全信息

​		-domain：主机地址，不区分协议和端口

​		-expires：在指定时间失效

​		-max-age：多少秒之后失效，负数则立即删除（优先级大于expires）

​		-secure：只能用https传输

#### localStorage和sessionStorage是本地存储，数据不是由服务器请求传递的

​	-localStorage:生命周期是永久性的

​	-sessionStorage:关闭浏览器或者页面，sessionStorage 就会失效,只有在当前页面打开的链接，才可以访sessionStorage的数据

### \<keep-alive>相关

#### 相关基本用法和原理

include和exclude来匹配路由的名字。在 created 函数调用时将需要缓存的 VNode 节点保存在 this.cache 中／在 render（页面渲染） 时，如果 VNode 的 name 符合缓存条件（可以用 include 以及 exclude 控制），则会从 this.cache 中取出之前缓存的 VNode 实例进行渲染。

#### 优化管理

```js
在定义路由时，额外添加路由【元信息】，来补充一些信息要素
const Goods = resolve => require(['@/components/home/goods'], resolve)
const Ratings = resolve => require(['@/components/home/ratings'], resolve)

{
    path:'/',
    component:() => import('../views/home/index.vue'),
    //是否缓存
    meta: {
        KeepAlive: true
    }
}
{
    path: 'goods',
    name: 'goods',
    component: Goods,
    meta: {
        keepAlive: false // 不需要缓存
    }
},
{
    path: 'ratings',
    name: 'ratings',
    component: Ratings,
    meta: {
        keepAlive: true  // 需要缓存
    }
},
```

```xml
在app.vue中根据meta元信息来决定是否缓存组件
<div>
    <keep-alive>
        <router-view v-if="$route.meta.isKeepAlive" />
    </keep-alive>
    <router-view v-if="!$route.meta.isKeepAlive" />
</div>
```

#### 特有声明周期

activated()、deactivated()

### 虚拟DOM和diff算法

虚拟DOM（Virtual Dom），也就是我们常说的虚拟节点，是用JS对象来模拟真实DOM中的节点，该对象包含了真实DOM的结构及其属性，用于对比虚拟DOM和真实DOM的差异，从而进行局部渲染来达到优化性能的目的，减少回流和重绘的引发的性能损耗

diff算法是通过调用patch函数，比较新老节点。patch函数首先会通过判断是否为同一根节点，其中有对key的判断。如果不是同一根节点，会直接用新节点替换老节点。如果是同一节点会执行patchVnode进行子节点比较，如果新老子节点一样，直接返回。如果新有旧无直接添加。如果旧有新无直接删除。如果子节点都有且不相同调用updateChildren方法









### 断点上传文件：
客户端将文件的二进制内容进行分片，每片数据按顺序进行序号标识，上传每片数据时同时附带其序号。服务器接收到每片数据时，将其保存成一个临时文件，并记录每个文件的 hash 和序号。
若上传中止，将来再次上传时，可以向服务器索要已上传的分片序号，客户端仅需上传剩余分片即可。
当全部分片上传完成后，服务器按照分片的顺序组装成完整的文件，并删除分片文件。

