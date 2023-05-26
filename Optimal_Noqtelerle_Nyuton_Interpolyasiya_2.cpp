#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include <conio.h>
#include <chrono>

using namespace std;

double f(double x)
{
	return 1/(x*x*x*x-x*x+10);
}

double interpolate(double a_, double b_, double x, long long n)
{
	double* points = new double[n+1];
	double c_Cebisev = (a_ + b_)/2;
	double d_Cebisev = (b_ - a_)/2;
	double alfa = M_PI / (2*n+2);

	// optimal noqteler
	// Cebisev coxhedlisinin kokleri massive yuklenir
	for (int k = 0; k <= n; k++)
	{
		points[k] = c_Cebisev + d_Cebisev * cos(alfa);
		alfa += 2;
	} 

	// bolunmus ferqler hesablanir
	long long memsize = n*(n+1)/2 + n;
	double* b = new double[memsize];
	double fx;

	for (int i = 0; i < n; i++)
	{
		b[i] = points[i];
		fx = f(points[i]);
		b[n+i] = fx;
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
			c++;
		}
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

	delete points;
	delete b;

	return N;
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
	cout << "       x^4 - x^2 + 10" << endl;
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
			cout << "| " << n << "\t" << realValue << "\t\t" << interpolatedValue << "\t\t" << error << "\t\t" << (n*(n+1)/2 + n)*sizeof(double) << " bayt\n";

		if(error < epsilon || maxIterState)
		{
			if(!isnanvalue)
				cout << "| " << n << "\t" << realValue << "\t\t" << interpolatedValue << "\t\t" << error << "\t\t" << ((error == 0) ? "\t" : "") << (n*(n+1)/2 + n)*sizeof(double) << " bayt\n";

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
			cout << "       x^4 - x^2 + 10" << endl;
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
