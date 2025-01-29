#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Vertex.h"
using namespace std;

string Ordinal(int Cardinal)
{
	if (Cardinal <= 0)
		return "";

	switch (Cardinal)
	{
	case 1:
		return "1st";
	case 2:
		return "2nd";
	case 3:
		return "3rd";
	default:
		return Cardinal + "th";
	}
}

float SolvePolynom(const vector<float> Coefficients, float Indeterminate)
{
	float Solution = 0;
	int Degree = Coefficients.size();
	for (size_t i = 0; i < Degree; i++)
	{
		Solution = Indeterminate * Solution + Coefficients[Degree - 1 - i];
	}
	return Solution;
}

int main()
{
	int PolynomialDegree = 0;
	vector<float> PolynomCoefficients;

	float FunctionStart, FunctionEnd;
	int Resolution;
	float Interval;

	fstream MyFile;

	string Input;

	cout << "Please select polynomial degree:" << endl;
	while (PolynomialDegree == 0)
	{
		cin >> Input;

		try
		{
			PolynomialDegree = stoi(Input);
		}
		catch (const std::exception&)
		{
			cout << "Unable to parse, please try again." << endl;
		}
		if (PolynomialDegree <= 0)
		{
			cout << "I do not know how to handle a polynom with " << PolynomialDegree << " terms" << endl;
			cout << "Please try again." << endl;
		}
	}

	for (size_t i = 0; i <= PolynomialDegree; i++)
	{
		cout << "Please specify " << (i < 1 ? "constant" : Ordinal(i) + " coefficient") << endl;

		bool ValidCoefficient = false;
		while (!ValidCoefficient)
		{
			cin >> Input;
			try
			{
				PolynomCoefficients.push_back(stof(Input));
			}
			catch (const std::exception&)
			{
				cout << "Unable to parse, please try again." << endl;
			}
			ValidCoefficient = true;
		}
	}

	// Determine start and end values
	cout << "Specify starting value" << endl;
	bool ValidInput = false;
	while (!ValidInput)
	{
		cin >> Input;
		try
		{
			FunctionStart = stof(Input);
		}
		catch (const std::exception&)
		{
			cout << "Unable to parse, please try again." << endl;
		}
		ValidInput = true;
	}
	cout << "Now, specify end value" << endl;
	ValidInput = false;
	while (!ValidInput)
	{
		cin >> Input;
		try
		{
			FunctionEnd = stof(Input);
		}
		catch (const std::exception&)
		{
			cout << "Unable to parse, please try again." << endl;
		}
		ValidInput = true;
	}

	// Determine intervals
	cout << "Decide amount of intervalls" << endl;
	ValidInput = false;
	while (!ValidInput)
	{
		cin >> Input;
		try
		{
			Resolution = stoi(Input);
		}
		catch (const std::exception&)
		{
			cout << "Unable to parse, please try again." << endl;
		}
		ValidInput = true;
	}
	Interval = (FunctionEnd - FunctionStart) / Resolution;


	MyFile.open("Test.txt", ios::out);
	if (MyFile.is_open())
	{
		MyFile << Input << endl;

		float CurrentValue = FunctionStart;
		float Result = SolvePolynom(PolynomCoefficients, CurrentValue);
		for (size_t i = 1; i <= Resolution; i++)
		{
			Vertex StartVertex;
			StartVertex.x = CurrentValue;
			StartVertex.y = Result;

			CurrentValue = FunctionStart + i * Interval;
			float NewResult = SolvePolynom(PolynomCoefficients, CurrentValue);
			Vertex EndVertex;
			EndVertex.x = CurrentValue;
			EndVertex.y = NewResult;

			if (NewResult < Result)
			{
				StartVertex.r = 1;
				EndVertex.r = 1;
			}
			else
			{
				StartVertex.g = 1;
				EndVertex.g = 1;
			}


			MyFile << StartVertex << endl;
			MyFile << EndVertex << endl;

			Result = NewResult;
		}
		MyFile.close();
	}
	// if (N < N-1) { Color = (1, 0, 0) }
	// else { Color = (0, 1, 0) }

}
