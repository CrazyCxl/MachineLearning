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
### 前置定义
节点：
$$P=[x_1,x_2,...,x_n]^T$$
K个最近节点所在集合：
$$J=[P_1,P_2,...,P_k]$$
目标点$P$ 到$P_{anchor}$所在的切分超平面的距离的绝对值为：
$$l_{t-ah}=|P^n-P_{anchor}^n|,n为维度$$

### 步骤
步骤1：
根据$P$ 的坐标值和每个节点的切分向下搜索（也就是说，如果$P_{anchor}$是按照 $x_r=a$ 进行切分，并且 $P_r<a$，则向左枝进行搜索，反之则走右枝）。

步骤2：
当达到一个底部节点时，将其标记为访问过。如果 $J$ 里不足k 个点，则将当前节点的特征坐标加入$J$。
如果 $J$ 已经有k个点并且当前节点的特征与 $P$ 的距离小于 $J$ 里最长的距离，则用当前特征替换掉 $J$ 中离 $P$ 最远的点。

步骤3：
如果当前节点不是整棵树最顶端节点，执行 (a)；反之，输出 $J$，算法完成。

**(a)**：向上爬一个节点。如果当前（向上爬之后的）节点未曾被访问过，将其标记为被访问过，然后执行 (1) 和 (2)，如果当前节点被访问过，再次执行 (a)。
- (1)：如果此时 $J$ 里不足 k 个点，则将节点特征加入 $J$，如果 $J$ 中已满 k 个点，且当前节点与 $P$ 的距离小于 $J$ 里最长的距离，则用节点特征替换掉 $J$ 中离最远的点。
- (2)：计算 $P$ 和当前节点切分线的距离。如果该距离大于等于  $J$ 中距离 $P$ 最远的距离并且 $J$ 中已有 k 个点，则在切分线另一边不会有更近的点，执行步骤3，如果该距离小于 $J$ 中最远的距离或者 $J$ 中不足 k 个点，则切分线另一边可能有更近的点，如果当前节点有另一个分支，则在当前节点的另一个枝从步骤1开始执行。

# graphviz
show dot in windows
>dot -Tpng .\kdtree.dot -o kdtree.png

## 参考
- https://zhuanlan.zhihu.com/p/25994179
- 李航博士《统计学习方法》
- https://www.joinquant.com/view/community/detail/2843
- https://graphviz.gitlab.io/documentation/