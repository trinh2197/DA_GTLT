#include<iostream>
#include <time.h>
#include <stdlib.h>
#include<stdio.h>
#include<iomanip>
#include <fstream>
#include <conio.h>
#include <string>
#include<Windows.h>
using namespace std;
string inputPassword()
{
	string pass = "";
	//ma hoa password nhap vao
	char c;
	while (true)
	{
		c = _getch();//ki tu khong hien ra man hinh
		if (c == 13)// enter
		{
			cout << "\n";
			break;
		}
		else if (c == '\b')//backspace=8
		{
			if (pass != "")
				cout << "\b \b";
			pass.erase(pass.size() - 1);//xoa tu vi tri pass.size()-1 den cuoi chuoi
		}
		else if (isprint(c)) // ki tu co the in ra dc
		{
			cout << "*";
			pass += c;
		}
	}

	return pass;
}

void requestLogin()
{
	string username, password;
	int kt = 1;
	while (kt)
	{
		system("cls");
		cout << endl << "                 *****************************************";
		cout<<endl <<   "                 *  DO AN GIAI THUAT VA LAP TRINH        *" << endl;
		cout <<         "                 *  GVHD: Nguyen Van Hieu                *" << endl;
		cout <<         "                 *  SVTH: Phan Thi Ngoc Trinh-16T3       *" << endl;
		cout  << "                 *****************************************";
		cout << "\n\t   =================DANG NHAP HE THONG=================";

		cout << "        \n\tUsername: ";
		cin >> username;
		cout << "        \n\tPassword: ";
		password = inputPassword();

		if ((username == "admin") && (password == "123456"))
		{


			cout << "\nDANG NHAP THANH CONG. DANG KET NOI DEN HE THONG......\t\n";
			break;
		}
		else
			cout << "\n\tDANG NHAP KHONG THANH CONG. VUI LONG NHAN 1 DE DANG NHAP LAI .\n";

		cin >> kt;
	}
}

//Ham nhap ma tran
float **nhap_matran(int *n, int *m)
{
	float **matrix;
	cout << "          Nhap so hang: "; cin >> (*n);
	cout << "          Nhap so cot: "; cin >> (*m);
	matrix = new float *[*n];
	for (int i = 0; i < *n; i++)
	{
		matrix[i] = new float[*m];
		for (int j = 0; j < *m; j++)
		{
			cout << "          [" << i << "][" << j << "]: ";
			cin >> matrix[i][j];
		}
	}
	return matrix;
}

//Ham in ma tran ra man hinh
void xuat_matran(float **matrix, int n, int m)
{
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout<<"     " << setw(10) << matrix[i][j];
		}
		cout << endl;
	}
}



int int_randinrange(int lowest, int highest) {
	int random_integer;
	int range = (highest - lowest) + 1;
	random_integer = lowest + int(range*(rand() / (RAND_MAX + 1.0)));
	return random_integer;
}
float float_randinrange(int lowest, int highest) {
	int random_integer;
	int range = (highest - lowest) + 1;
	random_integer = lowest + int(range*(rand() / (RAND_MAX + 1.0)));
	return random_integer * 0.1;
}

float ** ma_tran_ngau_nhien(int n, int m)
{
	float **matrix = new float*[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new float[m];
		for (int j = 0; j < m; j++)
		{
			matrix[i][j] = float_randinrange(1, 10);
		}
	}
	return matrix;
}

void random_r(float **matrix, int h, int w, int *u, int *i, float *r)
{
	if (!matrix) return;
	do {
		*u = int_randinrange(0, h - 1);
		*i = int_randinrange(0, w - 1);
		*r = matrix[*u][*i];
	} while (*r == -1);
}
float **Nhanmt(float **A, int na, int ma, float **B, int nb, int mb)
{
	if (!A || !B) return 0;
	if (ma != nb) return 0;
	float **T = new float*[na];
	for (int i = 0; i < na; i++) {
		T[i] = new float[mb];
	}
	for (int i = 0; i < na; i++)
		for (int j = 0; j < mb; j++) {
			T[i][j] = 0;
			for (int k = 0; k < ma; k++)
				T[i][j] += A[i][k] * B[k][j];
		}

	return T;
}

void xoa_matran(float **&matrix, int n, int m) {
	if (!matrix) return;
	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void GhiMT(float **&Y, int n, int m)
{

	
	ofstream ghi("output.txt");
	
	
	ghi << "     Ma tran Y xap xi ma tran X la:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)

			ghi << setw(15) << Y[i][j];

		ghi << endl;
	}
	ghi.close();

}


int main()
{

	requestLogin();
	system("cls");//ham xoa man hinh trong thu vien Window.h
	srand(time(0));
	int U, I, K = 2, Iter = 30, u, i;
	float b = 0.1, d = 0.01;
	float r;
	float **X;
	cout <<endl<< "          Nhap ma tran danh gia X khong day du" << endl;
	X = nhap_matran(&U, &I);
	cout << "          Xuat ma tran X" << endl;
	xuat_matran(X, U, I);

	float **W, **H;
	W = ma_tran_ngau_nhien(U, K);
	H = ma_tran_ngau_nhien(K, I);
	//cout<<"W="<<endl;
	//xuat_matran(W, U, K);
	//cout << endl;
	//cout<<"H="<<endl;
	//xuat_matran(H, K, I);
	//cout << endl;
	for (int iter = 0; iter < Iter*U*I; iter++)
	{
		random_r(X, U, I, &u, &i, &r);
		float t_r = 0;
		for (int k = 0; k < K; k++)
		{

			t_r += W[u][k] * H[k][i];
		}
		float e = r - t_r;
		//	cout<<e<<endl;
		for (int k = 0; k < K; k++)
		{
			W[u][k] = W[u][k] + b * (e*H[k][i] - d * W[u][k]);
			H[k][i] = H[k][i] + b * (e*W[u][k] - d * H[k][i]);
		}
	}
	cout << "          W=" << endl;
	xuat_matran(W, U, K);
	
	cout << endl << "          H=" << endl;
	xuat_matran(H, K, I);
	cout << endl;
	float **Y = Nhanmt(W, U, K, H, K, I);
	cout << "          Ma tran Y xap xi ma tran X la:" << endl;
	xuat_matran(Y, U, I);
	GhiMT(Y, U, I);


	xoa_matran(X, U, I);
	xoa_matran(W, U, K);
	xoa_matran(H, K, I);
	xoa_matran(Y, U, I);
	
	system("pause");
	return 0;
}