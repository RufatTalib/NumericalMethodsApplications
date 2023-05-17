#include <iostream>
#include <cmath>

using namespace std;

float f(float x)
{
	return 1/(x*x*x-x*x+1);
}

float interpolate(float x, float* points, int n)
{
	float ust = 1;
	float alt = 1;
	float cvb = 0;

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

	return cvb;
}

int main()
{
	int n = 10;
	cout << "Noqte sayini daxil edin :"; cin >> n;
	float points[n+1];
	float x = 0.3;

	float a = 0.4;
	float b = 0.9;
	float c = (a+b)/2;
	float d = (b-a)/2;
	float alfa = M_PI / (2*n+2);

	// optimal noqteler
	// Cebisev coxhedlisinin kokleri massive yuklenir
	for (int k = 0; k <= n; k++)
	{
		points[k] = c + d * cos(alfa);

		alfa += 2;
	}


	float realValue = f(x);
	float interpolatedValue = interpolate(x, points, 9);

	cout.precision(9);
	cout << "Real qiymet ==> " << realValue << endl;
	cout << "Interpolyasiya ==> " << interpolatedValue << endl;
	cout << "Xeta ==> " << realValue - interpolatedValue << endl;
	

	return 0;
}
