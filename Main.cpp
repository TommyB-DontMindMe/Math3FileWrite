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
	int Assignment = 0;

	int PolynomialDegree = 0;
	vector<float> PolynomCoefficients;

	float FunctionStart, FunctionEnd;
	int Resolution;
	float Interval;

	fstream MyFile;

	string Input;

	std::cout << "Please select task:" << endl;
	while (Assignment == 0)
	{
		cin >> Input;

		try
		{
			Assignment = stoi(Input);
		}
		catch (const std::exception&)
		{
			std::cout << "Unable to parse, please try again." << endl;
		}
		if (Assignment >= 3)
		{
			std::cout << "There is currently no task 3 or above." << endl;
			std::cout << "Please try again" << endl;
			Assignment = 0;
		}
	}
	switch (Assignment)
	{
	case 1:
		std::cout << "Please select polynomial degree:" << endl;
		while (PolynomialDegree == 0)
		{
			cin >> Input;

			try
			{
				PolynomialDegree = stoi(Input);
			}
			catch (const std::exception&)
			{
				std::cout << "Unable to parse, please try again." << endl;
			}
			if (PolynomialDegree <= 0)
			{
				std::cout << "I do not know how to handle a polynom with " << PolynomialDegree << " terms" << endl;
				std::cout << "Please try again." << endl;
			}
		}

		for (size_t i = 0; i <= PolynomialDegree; i++)
		{
			std::cout << "Please specify " << (i < 1 ? "constant" : Ordinal(i) + " coefficient") << endl;

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
					std::cout << "Unable to parse, please try again." << endl;
				}
				ValidCoefficient = true;
			}
		}
		break;

	default:
		break;
	}
	

	// Determine start and end values
	std::cout << "Specify starting value" << endl;
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
			std::cout << "Unable to parse, please try again." << endl;
		}
		ValidInput = true;
	}
	std::cout << "Now, specify end value" << endl;
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
			std::cout << "Unable to parse, please try again." << endl;
		}
		ValidInput = true;
	}

	// Determine intervals
	std::cout << "Decide amount of intervalls" << endl;
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
			std::cout << "Unable to parse, please try again." << endl;
		}
		ValidInput = true;
	}
	Interval = (FunctionEnd - FunctionStart) / Resolution;


	MyFile.open("Test.txt", ios::out);
	if (MyFile.is_open())
	{
		MyFile << Resolution * 2 << endl;

		float CurrentValue = FunctionStart;

		switch (Assignment)
		{
		case 1:
		{
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
		}
			break;
		case 2:
		{
			Vertex VertexA;

			VertexA.x = cos(CurrentValue);
			VertexA.y = sin(CurrentValue);
			VertexA.z = CurrentValue;

			VertexA.r = 1.0f;
			VertexA.b = 1.0f;

			for (size_t i = 1; i <= Resolution; i++)
			{
				Vertex VertexB;

				CurrentValue += Interval;

				VertexB.x = cos(CurrentValue);
				VertexB.y = sin(CurrentValue);
				VertexB.z = CurrentValue;

				MyFile << VertexA << endl;
				MyFile << VertexB << endl;

				VertexA = VertexB;
			}
		}
			break;
		default:
			break;
		}
		
		MyFile.close();
	}
	// if (N < N-1) { Color = (1, 0, 0) }
	// else { Color = (0, 1, 0) }

}
