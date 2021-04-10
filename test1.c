#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//void* my_memmove(void* p2, void* p1, size_t n)
//{
//	void* ret = p2;
//	if (p1 < p2)
//	{
//		//从后往前复制
//		while (n--)
//		{
//			*((char*)p2 + n) = *((char*)p1 + n);
//		}
//	}
//	else
//	{
//		//从前往后复制
//		while (n--)
//		{
//			*(char*)p2 = *(char*)p1;
//			++(char*)p2;
//			++(char*)p1;
//		}
//
//	}
//	return ret;
//}
//int main()
//{
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	my_memmove(arr, arr + 2, 20);
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}
