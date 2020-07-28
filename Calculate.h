#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

//菜单函数
void menu()
{
	cout << "          选择菜单" << endl;
	cout << "______________________________" << endl << endl;
	cout << "1.利用克莱姆法则求解线性方程组." << endl << endl;
	cout << "2.矩阵乘法." << endl << endl;
	cout << "3.矩阵求逆." << endl << endl;
	cout << "4.行列式求值." << endl;
	cout << "______________________________" << endl << endl;
	cout << "请输入您的选择：" << endl;
}

//行列式计算函数
double det(double** a, int n)
{
	if (n == 1)
		return a[0][0];

	double** b = new double* [n - 1];
	for (int i = 0; i < n - 1; i++)
		b[i] = new double[n - 1];
	int mov = 0;//判断余子式行是否移动   
	double sum = 0.0;//sum为行列式的值  
	for (int arow = 0; arow < n; arow++) // a的行数把矩阵a[n][n]赋值到b[n-1][n-1]  
	{
		for (int brow = 0; brow < n - 1; brow++)//把a阵第一列各元素的代数余子式存到b  
		{
			mov = arow > brow ? 0 : 1; //b中小于arow的行，直接赋值，等于和大于的加一  
			  //把a的第（brow + mov）行第(j+1)的元素赋值到b 的第brow行第j列的元素
			for (int j = 0; j < n - 1; j++)
			{
				b[brow][j] = a[brow + mov][j + 1];
			}
		}
		int flag = (arow % 2 == 0 ? 1 : -1);//因为列数为0，所以行数是偶数时候，代数余子式系数为1.  
		sum += flag * a[arow][0] * det(b, n - 1);//a第一列各元素与其代数余子式积的和即为行列式
	}
	delete[]b;
	return sum;
}



//将常数项代入到第k列的行列式
double calcud(double** m, double* c, int k, int n)
{
	double d = 0;
	double** temp = NULL;

	temp = new double* [n];
	for (int i = 0; i < n; i++)
		temp[i] = new double[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i][j] = m[i][j];
		}
	}

	for (int j = 0; j < n; j++)
	{
		temp[j][k] = c[j];
	}

	d = det(temp, n);
	delete[] temp;
	return d;
}

//克拉默法则求解
void cramer()
{
	int n;
	system("cls");
	cout << "请输入未知数个数：" << endl;
	cin >> n;
	double** m;
	double* c;
	c = new double[n];
	m = new double* [n];

	for (int i = 0; i < n; i++)
		m[i] = new double[n];

	cout << "请输入系数矩阵：" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> m[i][j];
		}
	}

	if (det(m, n) == 0)
	{
		cout << "系数行列式为零，不能用克拉默法则计算！" << endl;
	}

	else
	{
		cout << "请输入右端常数项：" << endl;
		for (int i = 0; i < n; i++)
		{
			cin >> c[i];
		}
		for (int i = 0; i < n; i++)
		{

			cout << "X" << i + 1 << " = " << calcud(m, c, i, n) / det(m, n) << endl;

		}
	}
	delete[]m;
	system("pause");
	system("cls");
}




//矩阵类
class Matrix
{
public:
	double** matrix;
	int row, col;
};

//输入矩阵
Matrix input()
{
	
	Matrix m;
	cout << "请输入矩阵行数：";
	cin >> m.row;
	cout << "请输入矩阵列数：";
	cin >> m.col;
	m.matrix = (double**)malloc(m.row * sizeof(double*));
	for (int i = 0; i < m.row; i++)
		m.matrix[i] = (double*)malloc(m.col * sizeof(double));
	cout << "输入你的矩阵：" << endl;
	for (int i = 0; i < m.row; i++)
	{
		for (int j = 0; j < m.col; j++)
		{
			cin >> m.matrix[i][j];
		}
	}
	return m;
}

//输出矩阵
void output(Matrix m)
{
	cout << "矩阵输出为：" << endl;
	for (int i = 0; i < m.row; i++)
	{
		for (int j = 0; j < m.col; j++)
		{
			cout << m.matrix[i][j] << ' ';
		}
		cout << endl;
	}
}

//矩阵行列相乘相加
double M(Matrix m1, Matrix m2, int i, int j)
{
	double m = 0;
	for (int k = 0; k < m1.col; k++)
		m = m + m1.matrix[i][k] * m2.matrix[k][j];
	return m;
}

//矩阵乘法
void mul(Matrix m1, Matrix m2)
{
	if (m1.col == m2.row)
	{
		Matrix z;
		z.row = m1.row;
		z.col = m2.col;
		z.matrix = (double**)malloc(z.row * sizeof(double*));
		for (int i = 0; i < z.row; i++)
			z.matrix[i] = (double*)malloc(z.col * sizeof(double));
		for (int i = 0; i < m1.row; i++)
			for (int j = 0; j < m2.col; j++)
				z.matrix[i][j] = M(m1, m2, i, j);
		cout << "相乘后";
		output(z);
	}
	else
		cout << "行列不符，不能相乘！" << endl;
}


void cal()
{
	system("cls");
	Matrix x, y;
	cout << "请输入矩阵A：" << endl;
	x = input();
	cout << "请输入矩阵B：" << endl;
	y = input();
	
	mul(x, y);
	system("pause");
	system("cls");
}

//求余子式
double cofactor(double** m, int k, int h, int n)
{
	double d = 0;
	double** temp = NULL;

	temp = new double* [n-1];
	for (int i = 0; i < n-1; i++)
		temp[i] = new double[n-1];
	int movr = 0;//行的移动
	int movc = 0;//列的移动

	for (int i = 0; i < n-1; i++)
	{
		movr = k > i ? 0 : 1;
		for (int j = 0; j < n-1; j++)
		{
			movc = h > j ? 0 : 1;
			temp[i][j] = m[i + movr][j+movc];
		}

	}


	d = det(temp, n-1);
	delete[] temp;
	return d;
}

void Inverse()
{
	int n;
	system("cls");
	cout << "请输入矩阵阶数：" << endl;
	cin >> n;
	double** m;
	double** b;
	m = new double* [n];

	for (int i = 0; i < n; i++)
		m[i] = new double[n];

	b = new double* [n];
	for (int i = 0; i < n; i++)
		b[i] = new double[n];
	cout << "请输入矩阵：" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> m[i][j];
		}
	}
	if (det(m, n) == 0)
	{
		cout << "行列式为0，不能求逆！" << endl;
	}
	else if (n == 1)
	{
		cout << "矩阵逆为：" << endl;
		cout << m[0][0];
	}
	else
	{
		double x = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				x = (i + j + 2) % 2 == 0 ? 1 : -1;
				b[j][i] = x * cofactor(m, i, j, n) / det(m, n);
				if (x * cofactor(m, i, j, n) / det(m, n) == 0)
					b[j][i] = 0;
			}
		}
		cout << "矩阵的逆为：" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << b[i][j] << " ";
			}
			cout << endl;
		}
	}
	delete[]m;
	delete[]b;
	system("pause");
	system("cls");
}
void Det()
{
	int n;
	system("cls");
	cout << "请输入行列式阶数：" << endl;
	cin >> n;

	double** m;
	m = new double* [n];

	for (int i = 0; i < n; i++)
		m[i] = new double[n];

	cout << "请输入行列式：" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> m[i][j];
		}
	}

	cout << "\n\nA = " << det(m, n) << endl;
	system("pause");
	system("cls");
}
