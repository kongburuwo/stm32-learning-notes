#include <stdio.h>

// 编写一个程序，让用户输入一个数字，然后判断这个数字是否为回文数（正着读和倒着读都一样）。
// 例如，输入 121 时，程序会计算出反转数也是 121，因此判断它是回文数。
// 而输入 123 时，反转数是 321，两者不相等，因此不是回文数
int main()
{
	int num, originalNum, reversedNum = 0;
	printf("请输入一个数字：\n");
	scanf("%d", &num);

	
	originalNum = num;

	while (num > 0)
	{
		int digit = num % 10; // 获取最后一位数字
		reversedNum = reversedNum * 10 + digit; // 将原始数字反转
		num /= 10; // 去掉最后一位数字
	}

	if (reversedNum == originalNum)
	{
		printf("%d 是回文数\n", originalNum);
	}
	else
	{
		printf("%d 不是回文数\n", originalNum);
	}
	printf("原始数字：%d\n", originalNum);
	

	return 0;
}
 