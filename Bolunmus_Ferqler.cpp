#include <iostream>
#include <cmath>
#include <conio.h>

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

void bolunmus_ferqler(double* points, int n)
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
}



int main()
{
	int n = 0;
	cout << "Noqte sayini daxil edin:";cin>>n;
	double points[n+1];

	cout << "Noqteleri daxil edin,\n";

	for (int k = 0; k <= n; k++)
	{
		cout << " x" << k << " = ";cin>>points[k];
	}

	bolunmus_ferqler(points, n);

	cout << "Cixmaq ucun her hansisa duymeye vurun...";
	getch();

	return 0;
}