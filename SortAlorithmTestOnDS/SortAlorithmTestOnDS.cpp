/************************
内排序算法的实验比较
使用C++语言分别实现插入排序、冒泡排序、选择排序、归并排序、快速排序、堆排序、基数排序算法，要求：
1)使用随机数生成方法，分别产生规模为100、1000、10000的三组自然数序列，作为各排序算法的输入；
2)算法的实现要求是稳定的（stable）；
3)分别以三组自然数序列作为输入，执行各排序算法。要求每组序列各执行三次，记录各算法每次执行时间（毫秒），取平均值作为结果记入实验报告的表1中；
4)根据表1中的结果数据，通过折线图（横坐标表示输入规模，纵坐标表示平均执行时间）来对各算法的时间效率进行比较分析，回答如下问题：
–各组输入中那个排序算法时间开销最小？
随着输入规模的增长，哪个排序算法的增长趋势最缓慢？
*************************/

#include"pch.h"
#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<iomanip>
#define random(x) (rand()%x)
using namespace std;

//1.插入排序
//平均时间复杂度:O(N^2)
//最坏情况复杂度:O(N^2)
//最好情况复杂度:O(N)
//空间复杂度:O(1)
//最多需要n(n−1)/2次比较
//最少需要n−1次比较
//稳定排序
void insertsort(vector<int>& a)
{
	int n = a.size();
	for (int i = 1; i < n; i++)
	{
		int insert_num = a[i], j;
		for (j = i - 1; j >= 0; j--)
		{
			if (a[j] > insert_num)
				a[j + 1] = a[j];
			else
				break;
		}
		a[j + 1] = insert_num;
	}
}

//2.冒泡排序
//平均时间复杂度:O(N^2)
//最坏情况复杂度:O(N^2)
//空间复杂度:O(1)
//稳定排序
void bubblesort(vector<int>& a)
{
	int n = a.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
		}
	}
}

//3.选择排序
//平均时间复杂度 O(n^2)
//最坏时间复杂度 O(n^2)
//最好时间复杂度 O(n^2)
//空间复杂度 O(1)
//我这个写法 是稳定排序
void select_sort(vector<int>& vt)
{
	for (int i = 0; i < vt.size() - 1; i++)
	{
		int swap_pos = i;
		for (int j = i + 1; j < vt.size(); j++)
		{
			if (vt[swap_pos] > vt[j])
			{
				swap_pos = j;
			}
		}

		if (swap_pos != i)
		{
			swap(vt[swap_pos], vt[i]);
		}
	}
}

//4.归并排序
//平均时间复杂度：O(NlogN)
//稳定排序
vector<int> mergeHelper(vector<int> &a, int left, int right)
{
	if (left == right) return vector<int>(1, a[left]);
	int mid = (right - left) / 2 + left;
	vector<int> l = mergeHelper(a, left, mid);
	vector<int> r = mergeHelper(a, mid + 1, right);
	//merge
	vector<int> ret;
	int ll = 0, rr = 0;
	while (ll < l.size() && rr < r.size())
	{
		if (l[ll] <= r[rr])     ret.push_back(l[ll++]);
		else                    ret.push_back(r[rr++]);
	}
	while (ll < l.size()) ret.push_back(l[ll++]);
	while (rr < r.size()) ret.push_back(r[rr++]);
	return ret;
}
void mergesort(vector<int>& a)
{
	a = mergeHelper(a, 0, a.size() - 1);
}

//5.快速排序
//平均时间复杂度：O(NlogN)
//最坏情况复杂度：O(N^2)
//不稳定排序
//快排的最差时间复杂度为O(n²)
//通常出现在选择的轴值(pivot)不能将数组划分为两个长度相等的子数组的时候
//一个较好的办法是“三数取中”，查看当前数组的第一个、中间一个和最后一个位置的数组，取其中位数，以此来降低轴值选择得不好的可能性。
int findmiddle(int a, int b, int c)
{
	if (a >= b && a <= c)
		return a;
	else if (b >= a && b <= c)
		return b;
	else
		return c;
}
void quicksortHelper(vector<int>& a, int start, int end)
{
	if (start >= end) return;
	int l = start, r = end;
	int pivot = findmiddle(a[start], a[end], a[(end - start) / 2 + start]);
	while (l <= r)
	{
		while (l <= r && a[r] > pivot)  r--;
		while (l <= r && a[l] < pivot)  l++;
		if (l <= r) swap(a[l++], a[r--]);
	}
	quicksortHelper(a, start, r);
	quicksortHelper(a, l, end);
}
void quicksort(vector<int>& a)
{
	quicksortHelper(a, 0, a.size() - 1);
}

//6.堆排序
//建堆的平均时间是：O(N)
//建堆的最坏情况是：O(NlogN)
//删除元素的时间是：O(logN)
//整个排序平均时间复杂度：O(N+NlogN)=O(NlogN)
//最坏情况复杂度：O(NlogN)
//不稳定排序
//建立一个大顶堆O(n),要求就是 把最大的元素 移动到堆顶 也就是a[0]
void make_heap(vector<int>& a, int size) //size的当前堆的大小，也就是数组的前size个数
{
	for (int i = size - 1; i > 0; i--)
	{
		if (i % 2 && a[i] > a[(i - 1) / 2])//奇数
			swap(a[i], a[(i - 1) / 2]);
		else if (i % 2 == 0 && a[i] > a[(i - 2) / 2])//偶数
			swap(a[i], a[(i - 2) / 2]);
	}
}
void heapsort(vector<int>& a)
{
	int n = a.size();
	while (n)
	{
		make_heap(a, n); //每次把新的最大元素移到堆顶，也就是a[0]
		n--;
		swap(a[0], a[n]); //然后把当前最大移动到后面来作为排好序的元素
	}
}

//7.基数排序
//时间复杂度最坏情况、平均情况、最差情况均为O(d(n+r))
//其中，r代表关键码的基数，d代表长度，n代表关键码的个数
int maxbit(vector<int>& data)
{
	int n = data.size();
	int d = 1; //保存最大的位数
	int p = 10;
	for (int i = 0; i < n; ++i)
	{
		while (data[i] >= p)
		{
			p *= 10;
			++d;
		}
	}
	return d;
}
void radixsort(vector <int>& data) //基数排序
{
	int n = data.size();
	int d = maxbit(data);
	int tmp[10000] = {};
	int count[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];
		radix = radix * 10;
	}
}


void test()
{
	vector<int> A;
	srand((int)(time(0)));
	for (int i = 0; i < 100; i++)
		A.push_back(random(50000));
	cout << "100个数据为：\t";

	vector<int> A2;
	vector<int> A3;
	vector<int> A4;
	vector<int> A5;
	vector<int> A6;
	vector<int> A7;
	for (int i = 0; i < 100; i++)
	{
		A2.push_back(A[i]);
		A3.push_back(A[i]);
		A4.push_back(A[i]);
		A5.push_back(A[i]);
		A6.push_back(A[i]);
		A7.push_back(A[i]);
	}

	clock_t start = clock();
	insertsort(A);
	clock_t end = clock();
	cout << "1.插入：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	bubblesort(A2);
	end = clock();
	cout << "2.冒泡：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	select_sort(A3);
	end = clock();
	cout << "3.选择：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	mergesort(A4);
	end = clock();
	cout << "4.归并：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	quicksort(A5);
	end = clock();
	cout << "5.快速：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	heapsort(A6);
	end = clock();
	cout << "6.堆的：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	radixsort(A7);
	end = clock();
	cout << "7.基数：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";
			
	cout << "\n1000个数据为：\t";
	vector<int> AA;
	srand((int)(time(0)));
	for (int i = 0; i < 1000; i++)
		AA.push_back(random(50000));

	vector<int> AA2;
	vector<int> AA3;
	vector<int> AA4;
	vector<int> AA5;
	vector<int> AA6;
	vector<int> AA7;
	for (int i = 0; i < 1000; i++)
	{
		AA2.push_back(AA[i]);
		AA3.push_back(AA[i]);
		AA4.push_back(AA[i]);
		AA5.push_back(AA[i]);
		AA6.push_back(AA[i]);
		AA7.push_back(AA[i]);
	}

	start = clock();
	insertsort(AA);
	end = clock();
	cout << "1.插入：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	bubblesort(AA2);
	end = clock();
	cout << "2.冒泡：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	select_sort(AA3);
	end = clock();
	cout << "3.选择：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	mergesort(AA4);
	end = clock();
	cout << "4.归并：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	quicksort(AA5);
	end = clock();
	cout << "5.快速：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	heapsort(AA6);
	end = clock();
	cout << "6.堆的：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	radixsort(AA7);
	end = clock();
	cout << "7.基数：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";
	


	vector<int> AAA;
	srand((int)(time(0)));
	for (int i = 0; i < 10000; i++)
		AAA.push_back(random(50000));

	vector<int> AAA2;
	vector<int> AAA3;
	vector<int> AAA4;
	vector<int> AAA5;
	vector<int> AAA6;
	vector<int> AAA7;
	for (int i = 0; i < 10000; i++)
	{
		AAA2.push_back(AAA[i]);
		AAA3.push_back(AAA[i]);
		AAA4.push_back(AAA[i]);
		AAA5.push_back(AAA[i]);
		AAA6.push_back(AAA[i]);
		AAA7.push_back(AAA[i]);
	}
	cout << "\n10000个数据为：\t";
	start = clock();
	insertsort(AAA);
	end = clock();
	cout << "1.插入：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	bubblesort(AAA2);
	end = clock();
	cout << "2.冒泡：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	select_sort(AAA3);
	end = clock();
	cout << "3.选择：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	mergesort(AAA4);
	end = clock();
	cout << "4.归并：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	quicksort(AAA5);
	end = clock();
	cout << "5.快速：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	heapsort(AAA6);
	end = clock();
	cout << "6.堆的：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t";

	start = clock();
	radixsort(AAA7);
	end = clock();
	cout << "7.基数：" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms\t\n";

}

int main() {
	for (int i = 0; i < 5; i++)
	{
		cout << "第" << i + 1 << "次实验 : \n";
		test();
	}
	return 0;
}