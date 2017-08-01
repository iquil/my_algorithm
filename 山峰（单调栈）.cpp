#include <iostream>
#include <stdio.h>
#include <stack>

//# define N 5
# define N 8	//���ظ�ֵ��� 

using namespace std;

typedef struct pair{
	int val;
	int num;
	pair(int v=0):val(v), num(1){}
}Pair;

int nextIndex(int maxIndex, int len)	//����ѭ��������Ԫ�ص���һ��Ԫ�ص��±� 
{
	return (maxIndex+1)%len;
}

int getInternaLSum(int times)			//����C(n, 2)	=  n*(n-1)/2 
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
	while(index != maxIndex){					//����ѭ������ 
		value = array[index];
	printf("value:%d\n", value);
		if(!s.empty() && s.top().val<value){	//��һ���������Ҫ��ջ��ֵ����ջ��Ԫ�أ��򵯳�ջ��Ԫ�ز��Ҽ����ջ��Ԫ�ص�ɽ�����C(n,2)+2n 
			int times = s.top().num;	s.pop();
		//	result += getInternaLSum(times) + times;
		//	result += s.empty() ? 0 : times;
			result += (getInternaLSum(times) + times*2);
			printf("getInternaLSum(times), times, result: %d, %d, %d\n",getInternaLSum(times), times, result);
		}
		if(!s.empty() && s.top().val==value){ 	//�ڶ����������Ҫ��ջ��ֵ���ڴ�ʱջ��Ԫ�ص�ֵ����ջ��Ԫ�ص��ظ�������1���� 
			s.top().num++;
		}
		else{									//�������������Ҫ��ջ��ֵС��ջ��Ԫ�ص�ֵ��������ѹջ 
			s.push(Pair(value));
		} 
		index = nextIndex(index, len);			//����ѭ�������б�������һ��Ԫ�ص��±� 
	}
	while(!s.empty())							//���㵥��ջ��ʣ��Ԫ�ص�ɽ����� 
	{
		int times = s.top().num;	s.pop();	//��һ��һ����ջ 
		result += getInternaLSum(times);		//�����ջԪ�������ڲ��ظ���ɽ����� 
		if(!s.empty()){							//ջ���գ���times 
			result += times;
			if(s.size() > 1)					//ʣ����������Ԫ�أ���times 
				result += times;
			else{								//ʣ�������ջ��Ԫ�� 
				result += s.top().num > 1 ? times : 0;		//ջ��Ԫ�ظ�������1����times;���򲻼� 
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
	
	printf("�����໥�۲쵽��ɽ�������%d\n", sum);
	
	return 0;
}
