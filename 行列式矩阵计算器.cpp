//行列式计算器
//矩阵乘法
//矩阵求逆
//克拉默法则求解方程组
//


#include"Calculate.h"


int main()
{
	system("color f0");
	system("title 矩阵行列式计算器");
	int select;//控制选择

	while (true)
	{
		menu();
		cin >> select;
		if (select == 1)

			cramer();

		else if (select == 2)

			cal();

		else if (select == 3)

			Inverse();

		else if (select == 4)

			Det();

		else if (select == 0)

			exit(0);

		else
		{
			cout << "无此选项！" << endl;
			system("pause");
			system("cls");
		}
	}
	return 0;
}
