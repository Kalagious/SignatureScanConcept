#include "general.h"



int main()
{
	LoadLibraryA("C:\\Users\\jhiggins\\source\\repos\\Testing\\x64\\Debug\\InternalDLL.dll");
	helloWorld(10);
	while (true)
		if (GetAsyncKeyState(VK_END) & 0x01)
			break;
}


uint32_t Garbagefunction2()
{
	int tmp = 1 + 23;
	std::cout << tmp;
	return 1;
}

uint32_t helloWorld(uint32_t test)
{
	uint32_t tmp = test + 5;
	tmp += 7;
	tmp -= 2;
	printf("Hello  -  %i\n", tmp);
	return test - 3;
}
