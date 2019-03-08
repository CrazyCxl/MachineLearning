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

## 距离度量
![](https://pic1.zhimg.com/80/v2-60bb382b0d22ec0ce296ed0e024f31bc_hd.png)

# KD树(K-Dimensional)
kd树是一个二叉树结构，它的每一个节点记载了【特征坐标，切分超平面，指向左枝的指针，指向右枝的指针】。

## 构造
- 寻找所有特征坐标第n维的中位数，切分为左枝和右枝
- $n=(n+1)$%$n_{max}$ ，分别对左枝和右枝的特征坐标集合重复上一步骤

## KD树上的KNN实现
### 寻找锚节点
- 从最顶层的节点开始，选择目标点当前维度所在的分支
- 重复上一步骤直到下一分支为0

## 从锚节点开始寻找最近的K个节点
### 前置公式
#### [余弦定理](https://baike.baidu.com/item/余弦定理/957460?fr=aladdin)：
$$c^2=a^2+b^2-2ab\ cos{\alpha}$$
#### 向量的数量积（[内积，点积](https://baike.baidu.com/item/%E7%82%B9%E7%A7%AF/9648528?fromtitle=%E5%86%85%E7%A7%AF&fromid=422863)）：
$$
\begin{align}
\overrightarrow{a}\cdot\overrightarrow{b}&=\sum_{i=1}^na_ib_i\\\\
&=|\overrightarrow{a}||\overrightarrow{b}|cos\alpha
\end{align}
$$
$$
\overrightarrow{a}\perp\overrightarrow{b},\overrightarrow{a}\cdot\overrightarrow{b}=0
$$
#### 超平面：
$$\overrightarrow{w}\cdot\overrightarrow{x}+b=0$$
$$
\begin{align}
\overrightarrow{w}&=[w_1,w_2,...,w_n]^T\\\\
\overrightarrow{x}&=[x_1,x_2,...,x_n]^T\\\\
\end{align}
$$
其中$\overrightarrow{w}$为法向量

#### 点到超平面的距离
$$
l=\frac{\overrightarrow{w}\cdot{x_0}+b}{|\overrightarrow{w}|}
$$
[推导过程]((https://www.cnblogs.com/yanganling/p/8007050.html))：
>取点空间中一点$x0$，超平面$S$：$\overrightarrow{w}\cdot\overrightarrow{x}+b=0$
设点$x0$到平面$S$ 的距离为$l$，点$x0$在平面$S$上的投影点为$x1$，则$x1$满足
$$\overrightarrow{w}\cdot\overrightarrow{x1}+b=0$$
$\because\overrightarrow{x0x1}//\overrightarrow{w}$
$\therefore$
$$
\begin{align}
\overrightarrow{w}\cdot\overrightarrow{x0x1}&=|\overrightarrow{w}|\times|\overrightarrow{x0x1}|\\\\
&=|\overrightarrow{w}|l
\end{align}
$$
$\because$
$$
\begin{align}
\overrightarrow{w}\cdot\overrightarrow{x0x1}&=\sum_{i=1}^nw_i(x0_i-x1_i)\\\\
&=\sum_{i=1}^nw_ix0_i-(\sum_{i=1}^nw_ix1_i)\\\\
&=\overrightarrow{w}\cdot\overrightarrow{x0}-（\overrightarrow{w}\cdot\overrightarrow{x1}+b-b)\\\\
&=\overrightarrow{w}\cdot\overrightarrow{x0}+b
\end{align}
$$
$\therefore$
$$l=\frac{\overrightarrow{w}\cdot{x_0}+b}{|\overrightarrow{w}|}$$

### 前置定义
节点：
$$P=[x_1,x_2,...,x_n]^T$$
K个最近节点所在集合：
$$J=[P_1,P_2,...,P_k]$$
目标点$P_{target}$到$P_{anchor}$所在的切分超平面的距离的绝对值为：
$$l_{t-ah}=|P_{target}^n-P_{anchor}^n|,n为维度$$

### 步骤
- 先将$P_{anchor}$插入$J$

步骤1：
- $P_{anchor}$=$J$ 顶点的父节点，如果$P_{anchor}$不为空则将$P_{anchor}$插入$J$，否则结束

步骤2：
- 如果$P_{anchor}$另一个分支为空，重复步骤1
- 如果$P_{anchor}$另一个分支不为空，进入步骤3

步骤3：
- 如果$J$集合未填满，$P_{anchor}$为$P_{anchor}$的$P_{target}$所在的子分支，如果$P_{anchor}$为空则跳到步骤1，否则将$P_{anchor}$插入$J$
- 如果$J$集合已填满，计算$J$里的最大距离是否大于$l_{t-ah}$，如果是就进入步骤4，否则结束

步骤4：

## 参考
- https://zhuanlan.zhihu.com/p/25994179
- 李航博士《统计学习方法》
- https://www.joinquant.com/view/community/detail/2843