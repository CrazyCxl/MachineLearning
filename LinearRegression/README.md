# LinearRegression
LinearRegression with c++

# 函数
## 假设函数
$$h_\theta(x)=\theta_0+\theta_1x_1+...+\theta_nx_n$$

## 代价函数
$$J(\theta)=\frac{1}{2m}\sum_{i=1}^m(h_\theta(x_i)-y_i)^2$$

## 梯度下降
$$
\theta_j=\theta_j-\alpha(\frac{\partial}{\partial\theta_j})J(\theta)
$$
$$
\frac{\partial{J}}{\partial\theta_j}=
\begin{cases}
\frac{1}{m}\sum_{i=1}^m(h_\theta(x^{(i)})-y^{(i)})，j=0\\\\
\frac{1}{m}\sum_{i=1}^m(h_\theta(x^{(i)})-y^{(i)})x_j^{(i)}，j>0
\end{cases}
$$


# Note
- Dynamic change learning rate
- Do not use feature scaling

# Reference
https://www.jianshu.com/p/c7e642877b0e