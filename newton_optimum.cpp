#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
	return 1/(x*x+1);
}

void print_array(double* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

double interpolate(double x, double* points, int n)
{
	int memsize = n*(n+1)/2 + n;

	cout << "\nYaddasda b massivi ucun ayrilmis yer: " << memsize * sizeof(double) << " bayt\n" << endl; 

	double b[memsize] = {0};
	double fx;

	for (int i = 0; i < n; ++i)
	{
		cout << "x" << i << " = "<< points[i] << endl;
	}

	for (int i = 0; i < n; i++)
	{
		b[i] = points[i];
		fx = f(points[i]);
		b[n+i] = fx;

		cout << "f(x" << i << ") = " << fx << endl;
	}

	int c = 2*n;
	int k = n-1;
	int L,R;



	while (k > 0)
	{

		for (int i = 0; i < k; i++)
		{
			L = i;
			R = n-k + i;
			b[c] = (b[c-k] - b[c-k-1])/(b[R] - b[L]);

			cout << "f(";
			for (int t = 0; t < n-k+1; t++)
			{
				cout << "x" << t+i;
				if(t < n-k)
					cout << ";";
			}
			cout << ") = " << b[c] << endl;
			c++;
		}
		cout << endl;

		k--;
	}

	int fi = 0;
	int fk = n;
	double N = f(points[0]);
	double HASIL = 1.0;
	int i = 0;
	int iterCount = 1;


	while( fk > 0 )
	{
		HASIL *= (x - points[i]);
		i++;

		fi += fk;
		N += HASIL * b[fi + n];
		fk--;

		iterCount++;
	}

	return N;
}



int main()
{	
	int precision = 6;
	cout.precision(precision);

	int n = 0;
	cout << "Noqte sayini daxil edin:";cin>>n;
	double points[n+1];

	double x = 0.6;

	double a = 0.4;
	double b = 0.9;
	double c = (a+b)/2;
	double d = (b-a)/2;
	double alfa = M_PI / (2*n+2);

	// optimal noqteler
	// Cebisev coxhedlisinin kokleri massive yuklenir
	for (int k = 0; k <= n; k++)
	{
		points[k] = c + d * cos(alfa);

		alfa += 2;
	}

	cout << "\nNoqte sayi, n = " << n << endl;
	cout << "Axtarilan noqte, x = " << x << endl;


	double realValue = f(x);
	double interpolatedValue = interpolate(x, points, n);

	cout << "\nDeqiqlik : " << precision << endl;
	cout << "Qiymet : " << realValue << endl;
	cout << "Interpolyasiya : " << interpolatedValue << endl;
	cout << "Xeta : " << realValue - interpolatedValue << endl;
	cout << endl;


	return 0;
}