# Logistic Regression
Logistic Regression with c++

## 函数
### 逻辑函数 （Logistic function）
$$g(z)=\frac{1}{1+e^{-z}}$$

<div align=center>
<img src="https://pic2.zhimg.com/80/v2-1562a80cf766ecfe77155fa84931e745_hd.png"/>
</div>

###  假设函数（Hypothesis function）
$$
\begin{align}
h_{\theta}(x)&=g({\theta}^Tx)\\\\
&=\frac{1}{1+e^{-{\theta}^Tx}}
\end{align}
$$

### 决策边界（Decision Boundary）
$${\theta}^Tx=0$$

### 代价函数 (Cost Function)
$$
J(\theta)=-\frac{1}{m}[\sum_{i=1}^m(y^{(i)}log\ h_\theta(x^{(i)})+(1-y^{(i)})log(1-h_\theta(x^{(i)})))]
$$
单个代价函数
\begin{cases}
-log(h_\theta(x)),y=1\\\\
-log(1-h_\theta(x)),y=0
\end{cases}


<div align=center>
<img src="https://pic2.zhimg.com/80/v2-a609f9d5da05c8fc3d349ba606e0868d_hd.png"/>
</div>
<div align=center>
<img src="https://pic1.zhimg.com/80/v2-b771e7ec34f3782b1ff6bd3c2a732160_hd.png"/>
</div>

### 梯度下降（Gradient Descent）
$$
\begin{align}
\theta_j&=\theta_j-\alpha(\frac{\partial}{\partial\theta_j})J(\theta)\\\\
&=\theta_j-\alpha(\frac{1}{m})\sum_{i=1}^m(h_\theta(x^{(i)})-y^{(i)})x_j^{(i)}
\end{align}
$$

# 注意
- x数组中可以在每一个的第一位插入1来替代常数项$\theta$

# Reference
- https://zhuanlan.zhihu.com/p/28408516
- https://zhuanlan.zhihu.com/p/28415991
- https://www.zhihu.com/question/41252833/answer/608587719