# k近邻（k-NN）
k-NN with c++

## 定义
给定一个训练数据集，对新的输入实例，在训练数据集中找到与该实例最邻近的K个实例，这K个实例的多数属于某个类，就把该输入实例分类到这个类中

<div align=center>
<img src="https://pic3.zhimg.com/80/v2-c3f1d2553e7467d7da5f9cd538d2b49a_hd.png"/>
</div>

## 特征缩放
$$\bar{x}=\frac{1}{n}\sum_{j=1}^n(x_j)$$
$$\sigma=\sqrt{\frac{1}{n}\sum_{j=1}^n(x_j-\bar{x})^2}$$
### 调节比例 (Rescaling)

$$\hat x_i^{(j)}=\frac{x_i^{(j)}-min(x_i)}{max(x_i)-min(x_i)}$$
$$\hat x \in [0,1]$$

### 归一化(Mean normalization)
$$\hat x_i^{(j)}=\frac{x_i^{(j)}-\bar{x_i}}{max(x_i)-min(x_i)}$$
$$\hat x \in [-1,1]$$

### 标准化 (Standardization)
$$\hat x_i^{(j)}=\frac{x_i^{(j)}-\bar{x_i}}{\sigma}$$

## 距离度量[^book1]
![](https://pic1.zhimg.com/80/v2-60bb382b0d22ec0ce296ed0e024f31bc_hd.png)

## 参考
- https://zhuanlan.zhihu.com/p/25994179

[^book1]: 李航博士《统计学习方法》