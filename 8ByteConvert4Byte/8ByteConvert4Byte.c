#include <stdio.h>

int main(void)
{
		int a = 5;
		void* arg = &a;
		int var = arg;
		long* b = &a;
		int c = b;
		printf("%p\n", var);
		printf("%p\n", b);
		return 0;
}

