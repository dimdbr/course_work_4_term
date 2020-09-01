
// ChMlab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;
double fuction(double x, double y)
{ 
	return 1 + 0.4*y*sin(x) - 1.5*pow(y, 2);
}

double y_funct(double x)
{
	return x / (1 + x * pow(log(x), 2));
}
void ADAMS(double h, double x_0, double y_0)
{
	vector<double> X;
	vector<double> Y;
	vector<double> Y_p;
	X.push_back(x_0);
	Y.push_back(y_0);
	Y_p.push_back(y_funct(x_0));
	double x_1 = x_0 + h;
	double y_1 = y_0 + h * fuction(x_0, y_0);
	X.push_back(x_1);
	Y.push_back(y_1);
	Y_p.push_back(y_funct(x_1));
	double x_2 = x_1 + h;
	double y_2 = y_1 + h * (3 / 2 * fuction(x_1, y_1)-1/2*fuction(x_0,y_0));
	X.push_back(x_2);
	Y.push_back(y_2);
	Y_p.push_back(y_funct(x_2));
	double x_3 = x_2 + h;
	double y_3 = y_2 + h * (23 / 12 * fuction(x_2, y_2) - 4 / 3 * fuction(x_1, y_1) + 5 / 12 * fuction(x_0, y_0));
	X.push_back(x_3);
	Y.push_back(y_3);
	Y_p.push_back(y_funct(x_3));
	int k;
	do
	{
		k = Y.size() - 1;
		double temp = Y[k] + h * (55 / 24 * fuction(X[k], Y[k]) - 59 / 24 * fuction(X[k - 1], Y[k - 1]) +
			37 / 24 * fuction(X[k - 2], Y[k - 2]) - 3 / 8 * fuction(X[k - 3], Y[k - 3]));
		Y.push_back(temp);
		X.push_back(X[k] + h);
		Y_p.push_back(y_funct(X[k] + h));
	} while (X[k+1] < x_0 + 1);
	cout << setw(10) << "X" << setw(10) << "Y" << setw(10) << "YPrecise" << setw(15) << "|Y-Yprecise|" << endl;
	for (int i = 0; i < Y.size(); i++)
	{
		cout << setw(10) << X[i] << setw(10) << Y[i] << setw(10) << Y_p[i] << setw(15) << fabs(Y[i] - Y_p[i]) << endl;
	}
}
void RKM(double h, double x_0, double y_0)
{
	vector<double> X;
	vector<double> Y;
	vector<double> Y_p;
	X.push_back(x_0);
	Y.push_back(y_0);
	Y_p.push_back(y_0);
	double x_next, y_next, k1, k2, k3, k4;
	do
	{
		int p = Y.size()- 1;
		k1 = fuction(X[p], Y[p]);
		k2 = fuction(X[p] + 0.5*h, Y[p] + 0.5*h*k1);
		k3 = fuction(X[p] + 0.5*h, Y[p] + 0.5*h*k2);
		k4 = fuction(X[p] + h, Y[p] + h * k3);
		y_next = Y[p] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
		Y.push_back(y_next);
		x_next = X[p] + h;
		X.push_back(x_next);
		Y_p.push_back(y_funct(x_next));
	} while (x_next < x_0 + 1);
	cout << setw(10) << "X" << setw(10) << "Y" << setw(10) << "YPrecise" << setw(15) << "|Y-Yprecise|" << endl;
	for (int i = 0; i < Y.size(); i++)
	{
		cout << setw(10) << X[i] << setw(10) << Y[i] << setw(10) << Y_p[i] << setw(15) << fabs(Y[i] - Y_p[i]) << endl;
	}
}
int main()
{
    std::cout << "Hello World!\n"; 
	double x_0 = 0;
	double y_0 = 0;
	cout << "R-K method" << endl;
	RKM(0.1, x_0, y_0);
	cout << "Adams method" << endl;
	ADAMS(0.1, x_0, y_0);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
