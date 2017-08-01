#include <iostream>
#include <stdio.h>
#include <stack>

//# define N 5
# define N 8	//有重复值情况 

using namespace std;

typedef struct pair{
	int val;
	int num;
	pair(int v=0):val(v), num(1){}
}Pair;

int nextIndex(int maxIndex, int len)	//计算循环数组中元素的下一个元素的下标 
{
	return (maxIndex+1)%len;
}

int getInternaLSum(int times)			//计算C(n, 2)	=  n*(n-1)/2 
{
	printf("times: %d\n", times);
	if(times == 1)
		return 0;
	return times*(times-1)/2;
}

int f(int array[], int len)
{
	if(array==NULL || len<2)
		return 0;
	int maxIndex = 0;
	for(int i=0; i<len; i++)
	maxIndex = array[maxIndex]<array[i] ? i : maxIndex;
	int value = array[maxIndex];
	stack<Pair> s;
	s.push(Pair(value));
	int index = nextIndex(maxIndex, len);
	int result = 0;
	while(index != maxIndex){					//遍历循环数组 
		value = array[index];
	printf("value:%d\n", value);
		if(!s.empty() && s.top().val<value){	//第一种情况：需要入栈的值大于栈顶元素，则弹出栈顶元素并且计算出栈顶元素的山峰对数C(n,2)+2n 
			int times = s.top().num;	s.pop();
		//	result += getInternaLSum(times) + times;
		//	result += s.empty() ? 0 : times;
			result += (getInternaLSum(times) + times*2);
			printf("getInternaLSum(times), times, result: %d, %d, %d\n",getInternaLSum(times), times, result);
		}
		if(!s.empty() && s.top().val==value){ 	//第二种情况：需要入栈的值等于此时栈顶元素的值，则栈顶元素的重复次数加1就行 
			s.top().num++;
		}
		else{									//第三种情况：需要入栈的值小于栈顶元素的值，则正常压栈 
			s.push(Pair(value));
		} 
		index = nextIndex(index, len);			//计算循环数组中遍历的下一个元素的下标 
	}
	while(!s.empty())							//计算单调栈中剩余元素的山峰对数 
	{
		int times = s.top().num;	s.pop();	//先一个一个出栈 
		result += getInternaLSum(times);		//计算出栈元素自身内部重复的山峰对数 
		if(!s.empty()){							//栈不空，加times 
			result += times;
			if(s.size() > 1)					//剩余至少三个元素，加times 
				result += times;
			else{								//剩余自身和栈底元素 
				result += s.top().num > 1 ? times : 0;		//栈底元素个数大于1，加times;否则不加 
				s.pop();
			}
		}
	}
	return result;
}

int main(void)
{
//	int array[N] = {1, 2, 4, 5, 3};
	int array[N] = {5, 2, 2, 2, 3, 3, 4, 4};
	
	int sum = f(array, N);
	
	printf("可以相互观察到的山峰对数：%d\n", sum);
	
	return 0;
}
