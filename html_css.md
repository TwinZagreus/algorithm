## HTML
###预格式标签\<pre\>
​		-在网页中，那些需要保留原本格式的内容，需要使用pre标签，

​		-对于我们来说使用最多的场景就是在网页中编写代码

###图片标签\<img\>
​		-alt是对图片的描述帮助搜索引擎来识别图片
###超链接\<a\>
​		-内部跳转的超链接，通过修改href属性可以使超链接在页面内部进行跳转。

​    			-\# 表示跳转到页面的顶部

​    			-\#id 表示跳转到页面的指定位置

```html
<a href="#p3">去p3</a>
<p id="p3">我们过了江，进了车站。我买票，他忙着照看行李。行李太多，得向脚夫行些小费才可过去。他便又忙着和他们讲价钱。我那时真是聪明过分，总觉他说话不大漂亮，非自己插嘴不可，但他终于讲定了价钱；就送我上车。他给我拣定了靠车门的一张椅子；我将他给我做的紫毛大衣铺好座位。他嘱我路上小心，夜里要警醒些，不要受凉。又嘱托茶房好好照应我。我心里暗笑他的迂；他们只认得钱，托他们只是白托！而且我这样大年纪的人，难道还不能料理自己么？我现在想想，我那时真是太聪明了。
</p>
<a href="#">去顶部</a>
```

###元素的嵌套规则

​		-块元素中可以放置块元素，也可以放置行内元素

​		-行内元素中尽量不要放置块元素

​		-a元素中可以放置除它自身外的任何元素

​		-p元素中不能放置块元素

### H5新特性

#### Storage相关

​		-localStorage和sessionStorage都继承于Storage。所以他们的语法基本相同

​		-差异：存储在 localStorage 的数据可以长期保留；而当页面会话结束——也就是说，当页面被关闭时，存储在 sessionStorage 的数据会被清除 。

#### 语义化标签

article，footer，header，nav，section

####canvas元素绘画，audio，video


## CSS

###属性选择器

​		-用来根据元素的属性来选中元素

​		-语法：

​				[属性名] 选中具有该属性的元素

​    		    [属性名=属性值] 选中指定属性值的元素

​    		    [属性名^=属性值] 选中属性值以指定内容开头的元素

​    		    [属性名$=属性值] 选中属性值以指定内容结尾的元素

​	    		[属性名*=属性值] 选中属性值包含指定内容的元素

### 交集选择器
​		-作用：选中同时符合多个选择器元素

​		-语法：选择器1选择器2选择器3{}

### 分组（并集）选择器

​		-作用：同时选中多个选择器对应的元素

​		-语法：选择器1,选择器2,选择器3,...选择器n{}

###子元素选择器
​		-作用：选中指定元素的子元素

​		-语法：父元素 > 子元素{}

###后代元素选择器
​		-作用：选中指定元素的后代元素

​		-语法：祖先 后代{}

###兄弟元素选择器
​		-作用：选中指定的兄弟元素

​		-语法：

​				-   兄 + 弟 {}

​         		选中紧随其后的一个兄弟

​				-   兄 ~ 弟 {}

​         		选中后边的所有兄弟元素

### 样式继承

​		-设置给祖先元素的样式，也会同时应用到其后代元素上

​		-但并不是所有的样式都会发生继承！所有的布局、背景、边框等相关的样式		都不会发生继承

### 选择器权重

​		-继承的样式：没有优先级

​       -通配选择器: 0,0,0,0

​       -元素选择器：0,0,0,1

​       -类和伪类选择器：0,0,1,0

​       -id选择器：0,1,0,0

​       -内联样式：1,0,0,0

​		-**==注意==**：

​				优先级高的优先显示，优先级的累加无法跨域数量级,

​				如果优先级一样，则优先显示靠下的样式

​				如果为样式添加 !important，则该样式会获得最高的优先级，优先于其他				样式显示，慎用！

​        		分组选择器优先级都是单独计算的！

###box-sizing 用来指定盒子可见框的计算方式

​		-content-box 默认值，width和height用来设置内容区的大小

​		-border-box 设置该值后，width和height用来设置盒子可见框的大小

###相邻外边距的折叠

​		-兄弟元素间外边距会取较大值

​		-父子元素间子元素垂直外边距会传递给父元素

​				-使用clear解决问题==**注意：**==display设置为table

```css
.clearfix::before{
	content: "";
	display: table;
	clear: both;
}
.box3{
	width: 200px;
	height: 200px;
	background-color: greenyellow;
}
.box4{
	width: 100px;
	height: 100px;
	background-color: orange;
	margin-top: 100px;
}
```

```html
<div class="box3 clearfix">
    <div class="box4"></div>
</div>
```



### 行内元素

​		-width height无效行内元素的大小被内容撑开，

​		-padding、border可以设置、但不会影响垂直方向的页面布局

​		-margin只有水平方向有效果

### display和visibility

#### display可选值

​		-inline 将元素设置为行内元素

​		-block 将元素设置为块元素

​		-inline-block 行内块元素

​				-行内块兼具行内元素和块元素的特点，不独占一行，又可以设置宽高

​		-none 隐藏元素

####display：none与visibility: hidden与**opacity：0**

​		-display直接隐藏元素

​		-visibility不可见，但是占据页面位置

​		-opacity：0占据空间可以设置透明度（可以进行DOM事件监听)

###文字居中

```css
//水平居中
text-align: center;
/*将行高设置为和元素高度一样的值即可让元素垂直居中*/
line-height: 50px; 
height: 50px;
```

####text-align可选项(图片、行内块、wen'zi都可以使用文本对齐的方式)

​		-left 默认值 左对齐

​		-center 居中对齐

​		-right 右对齐

​		-justify 两端对齐

### 解决浮动后的父元素高度塌陷

####将父元素高度写死

####开启BFC

​		-开启BFC的特性

​				1.父元素开启BFC后，子元素的垂直外边距不会传递给父元素

​				2.开启BFC后，元素不会被浮动元素所覆盖

​				3.开启BFC后，元素可以包含浮动的子元素

​		-开启BFC的常用方法

​				1.display: flow-root

​				2.将overflow设置为一个非visible的值

####clear清除浮动元素对当前元素所产生的影响

```html
<body>
	<div class="box1 clearfix">
		<div class="box2"></div>
	</div>
</body>
```

```css
<style>
	.box1{
		border: 10px red solid;
	}
	.box2{
		float: left;
		width: 200px;
		height: 200px;
		background-color: #bfa;            
	}
	.clearfix::after{
		content: "";
		display: block;
		clear: both;
	}
</style>
```

###绝对定位

​		-开启绝对定位后，如果不设置偏移量，默认偏移量为auto会使元素的位置不会发生变化。

​		-开启绝对定位后，参照于它的包含块进行定位的！

​				-绝对定位元素的包含块是离它最近的开启了定位的祖先元素

​				-如果所有的祖先都没有开启定位，则它的包含块是初始包含块

​				-初始包含块的大小和视口是相同

###元素居中的方式

​		-利用margin:0 auto来实现水平居中

​		-利用定位来实现水平和垂直居中

```css
position: absolute;
top: 0;
bottom: 0;
left: 0;
right: 0;
margin: auto;
原理：利用定位后新的等式来实现居中
左右偏移量 + 左右外边距 + 可见框的宽度 = 包含块的宽度
上下偏移量 + 上下外边距 + 可见框的高度 = 包含块的高度
```

​		-利用弹性盒来实现水平和垂直居中

​		-利用display：table-cell和vertical-align: middle垂直居中

### 设置超出显示省略号

#### 单行文本溢出显示省略号

```css
overflow:hidden;
white-space: nowrap;
text-overflow: ellipsis;
-o-text-overflow:ellipsis;
```

#### 多行文本溢出显示省略号

```css
overflow:hidden;
text-overflow: ellipsis;
-webkit-line-clamp: 3;
display: -webkit-box;
-webkit-box-orient: vertical;
```

