#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include <conio.h>
#include <chrono>

using namespace std;

double f(double x)
{
	return 1/(x*x+1);
}

float interpolate(double a, double b, double x, long long n)
{
	double* points = new double[n+1];
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

	double ust = 1;
	double alt = 1;
	double cvb = 0;

	for (int i = 0; i <= n; i++)
	{
		ust = alt = 1;

		// Boyuk hasil emeliyyati
		for (int j = 0; j <= n; j++)
		{
			if(i != j)
			{
				ust *= (x - points[j]);
				alt *= (points[i] - points[j]);
			}
		}

		cvb += (ust/alt) * f(points[i]);
	}

	delete points;

	return cvb;
}

double get_time(chrono::steady_clock::time_point begin)
{
	return chrono::duration_cast<std::chrono::microseconds>(chrono::steady_clock::now() - begin).count() / 1000;
}



int main()
{
	string state;
	system("cls");

	double a,b,x,epsilon,realValue,interpolatedValue,error;
	cout << "Bu proqramda istifade olunan funksiya asagidaki sekildedir,\n";	
	cout << "               1     " << endl;
	cout << "f(x) = --------------" << endl;
	cout << "           x^2 + 1" << endl;
	cout << endl;
	cout << "Bu funksiyanin interpolyasiyasi ucun ideal parca [0,1]-dir.\n";
	cout << endl;
	cout << "Zehmet olmasa noqtenin daxil oldugu parcani daxil edin,\na = "; cin >> a; cout << "b = "; cin >> b;
	while(b <= a)
	{cout << "Zehmet olmasa noqtenin daxil oldugu parcani duzgun daxil edin, burada b > a olmalidir !\na = "; cin >> a; cout << "b = "; cin >> b;}

	cout << "Noqteni daxil edin, x = "; cin >> x;
	cout << "Zehmet olmasa epsilon deqiqliyini daxil edin, epsilon (0,1) araliginda mumkun qeder kicid ededdir, \nEpsilon = "; cin >> epsilon;

	bool maxIterState = false;
	int maxNofIteration = 10000;
	int iterationChecker = 10;
	int k = 1;
	int n = 1;
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	bool isnanvalue;
	cout << "\n| N\tReal qiymet\tInterpolyasiya\tXetanin modulu\t\tYaddasda tutulan hecm\t|\n";

	while(1)
	{
		realValue = f(x);
		interpolatedValue = interpolate(a,b,x, n);
		error = abs(realValue - interpolatedValue);

		if(maxNofIteration > iterationChecker)
		{
			iterationChecker += 10;
			k++;
		}
		isnanvalue = isnan(interpolatedValue);
		maxIterState = (isnanvalue || maxNofIteration == 0);


		if(maxNofIteration%k == 0 && !maxIterState )
			cout << "| " << n << "\t" << realValue << "\t\t" << interpolatedValue << "\t\t" << error << "\t\t" << (n+1)*sizeof(double) << " bayt\n";

		if(error < epsilon || maxIterState)
		{
			if(!isnanvalue)
				cout << "| " << n << "\t" << realValue << "\t\t" << interpolatedValue << "\t\t" << error << "\t\t" << (n+1)*sizeof(double) << " bayt\n";

			cout << "\nButun prosess ucun serf olunan zaman ==> " << get_time(begin) << " Millisaniye" << endl;
			
			if(maxIterState)
				cout << "Xeta epsilondan kicik qiymet ala bilmedi.\nProses maksimum iterasiya sayina catdi ve dayandirildi.\n" << endl;
			else
				cout << "Xeta epsilondan kicik qiymet aldi ve proses dayandirildi.\n" << endl;

			cout << '\n' << "Davam etmek isteyirsinizse, her hansisa duymeye basin, cixmaq isteyirsinizse pencereni baglayin.";
			getch();
			system("cls");
			maxNofIteration = 10000;
			iterationChecker = 10;
			k = 1;
			n = 1;
			
			cout << "Bu proqramda istifade olunan funksiya asagidaki sekildedir,\n";	
			cout << "               1     " << endl;
			cout << "f(x) = --------------" << endl;
			cout << "           x^3 + 1" << endl;
			cout << endl;
			cout << "Bu funksiyanin interpolyasiyasi ucun ideal parca [0,1]-dir.\n";
			cout << endl;
			cout << "Zehmet olmasa noqtenin daxil oldugu parcani daxil edin,\na = "; cin >> a; cout << "b = "; cin >> b;
			while(b <= a)
			{cout << "Zehmet olmasa noqtenin daxil oldugu parcani duzgun daxil edin, burada b > a olmalidir !\na = "; cin >> a; cout << "b = "; cin >> b;}

			cout << "Noqteni daxil edin, x = "; cin >> x;
			cout << "Zehmet olmasa epsilon deqiqliyini daxil edin, epsilon (0,1) araliginda mumkun qeder kicid ededdir,\nEpsilon = "; cin >> epsilon;

			cout << "\n| N\tReal qiymet\tInterpolyasiya\tXetanin modulu\t\tYaddasda tutulan hecm\t|\n";
			begin = chrono::steady_clock::now();

		}


		n++;
		maxNofIteration--;
	}

	
	return 0;
}
