#include <iostream>
using namespace std;
#define password "12345678"
bool verifyPwd(char* pwd)
{
	int flag;
	flag = strcmp(password, pwd);
	return flag == 0;
}
void main()
{
	bool bFlag;
	char pwd[1024];
	printf("please input your password:\n");
	while (1)
	{
		scanf("%s", pwd);
		bFlag = verifyPwd(pwd);
		if (bFlag)
		{
			printf("passed\n");
			break;
		}
		else {
			printf("wrong password, please input again:\n");
		}
	}
}