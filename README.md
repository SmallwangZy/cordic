# 核心目标

本质是**坐标变换**，Cordic算法的目标如下：

- 嵌入式设备和硬件算力有限，使用如*查表*或*泰勒展开*实现消耗时间和资源。
- 尽可能<mark>避免乘法运算</mark>，转而使用<mark>移位或者加法</mark>。

一种仅需要加法和移位的**计算三角函数**的方法。

**伪旋转**是指去除掉`cos()`系数的旋转，向量在旋转之后拉伸不在考虑，只考虑角度。

# 数学推导

略

# 算法思想

迭代是Cordic算法的重要思想，一般都是迭代0-15次，一共16次，当然也可以是任意次，和大多数算法一样：

> 迭代次数越多，精度越高。

每次迭代的过程都是一次**旋转的过程**，可以是**顺时针**亦可以是**逆时针**旋转。

- 若当前旋转角度 > 目标求解角度:逆时针
- 若当前旋转角度 < 目标求解角度:顺时针

就是在不断逼近目标角度$\theta$。

那么不用乘法的思想在哪里体现呢？

首先已知从向量$\vec{a}=(x_a,y_a)$旋转$\theta$角度到向量$\vec{b}=(x_b,y_b)$，有旋转矩阵（这是伪旋转，忽略了提出的$\cos\theta$）：
$$
\left\{\begin{array}{l}
x_{\mathrm{b}}=x_{\mathrm{a}}-y_{\mathrm{a}} \tan \theta \\
y_{\mathrm{b}}=y_{\mathrm{a}}+x_{\mathrm{a}} \tan \theta
\end{array}\right.
$$
这里直接认为<mark>$\tan\theta$是$2^{-n}$，将原本需要求解的$\tan\theta$​直接变成移位</mark>$x_a$和$y_a$​两个数值。

这样一来，Cordic算法每次旋转向量的角度就不能是任意的了,而必须满足$\tan\theta^i=2^{-i}$的关系，为离散取值。（见下表）

一般来说，Cordic算法的旋转角度表都是**定好的**：
$$
\begin{array}{|c|c|c|c|c|}
\hline i & 2^{-i} \text { (小数形式) } & 2^{-i} \text { (指数形式) } & \tan \left(2^{-i}\right) / \text { / } & \tan \left(2^{-i}\right) / \text { 瓜度 } \\
\hline 0 & 1 & 2^{-0} & 45.0 & 0.785398163 \\
\hline 1 & 0.5 & 2^{-1} & 26.6 & 0.463647609 \\
\hline 2 & 0.25 & 2^{-2} & 14.0 & 0.244978663 \\
\hline 3 & 0.125 & 2^{-3} & 7.1 & 0.124354995 \\
\hline 4 & 0.0625 & 2^{-4} & 3.6 & 0.062418810 \\
\hline 5 & 0.03125 & 2^{-5} & 1.8 & 0.031239833 \\
\hline 6 & 0.015625 & 2^{-6} & 0.9 & 0.015623729 \\
\hline 7 & 0.0078125 & 2^{-7} & 0.4 & 0.007812341 \\
\hline 8 & 0.00390625 & 2^{-8} & 0.2 & 0.003906230 \\
\hline 9 & 0.001953125 & 2^{-9} & 0.1 & 0.001953123 \\
\hline
\end{array}
$$
我们观察这个表，虽然不可旋转任意角度了，但是随着$i$的增大，可旋转的角度越小，这意味着：

> 迭代次数的增加，可以让向量一直逼近目标量。误差会越来越小。

还有一个问题是算法的初始化问题，前面提到$\cos$会带来误差，伪旋转忽略了这个，已知：
$$
\cos\theta=\frac{1}{\sqrt{1+\tan^2\theta}}\approx\frac{1}{\sqrt{1+2^{-2i}}}
$$
假设遍历了$n$次，那么在$n\rightarrow\infty$d的时候，上式约为$0.607253$，我们可以令初始向量横坐标$x_0=0.607253$。

# 算法分类
Cordic算法有两种应用:

- 已知角度求出sin,cos值.
- 已知x,y的坐标,求出相位角.

两者本质上是互逆的.

对于第一种，我们将可以得到原向量的位置，然后不断向
# Reference

1. [CORDIC算法详解(一)-CORDIC 算法之圆周系统之旋转模式](https://cloud.tencent.com/developer/article/1651716)
2. [CORDIC算法详解(一)-CORDIC 算法之圆周系统之旋转模式_cordic碎碎思-CSDN博客](https://blog.csdn.net/Pieces_thinking/article/details/83512820)
3. [CORDIC算法原理详解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/384524393)
4. [CORDIC算法原理详解及其Verilog实现_verilog cordic算法-CSDN博客](https://blog.csdn.net/gemengxia/article/details/112475073)

