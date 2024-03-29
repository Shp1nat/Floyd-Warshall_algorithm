#include <iostream>
#include <iomanip> 
#include <vector>
using namespace std;
const int inf = 999;

class Matrix
{
private:
	vector<vector<int>> graph;
	int countOfVertices;
public:
	Matrix(int _countOfVertices)
	{
		vector<vector<int>> _graph(_countOfVertices, vector<int>(_countOfVertices, 0));
		graph = _graph;
		countOfVertices = _countOfVertices;
	}
	void AddToMatrix(int _i, int _j, int _value)
	{
		graph[_i][_j] = _value;
	}

	int GetFromMatrix(int _i, int _j)
	{
		return graph[_i][_j];
	}

	void setCountOFVertices(int _count)
	{
		countOfVertices = _count;
	}

	void getMatrix()
	{
		for (int i = 0; i < countOfVertices; i++)
		{
			for (int j = 0; j < countOfVertices; j++)
			{
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}

	int getCountOFVertices()
	{
		return countOfVertices;
	}

	Matrix floydWarshall(Matrix _startMatrix)
	{
		Matrix resultMat(5);
		resultMat = _startMatrix;
		for (int k = 0; k < countOfVertices; k++)
			for (int i = 0; i < countOfVertices; i++)
				for (int j = 0; j < countOfVertices; j++)
				{
					if (resultMat.GetFromMatrix(i, j) > (resultMat.GetFromMatrix(i, k) + resultMat.GetFromMatrix(k, j)) && (resultMat.GetFromMatrix(k, j) != inf) && (resultMat.GetFromMatrix(i, k) != inf))
					{
						int value = resultMat.GetFromMatrix(i, k) + resultMat.GetFromMatrix(k, j);
						resultMat.AddToMatrix(i, j, value);
					}
				}
		return resultMat;
	}
};

void createMatrix(int _countOfVertices, Matrix& _mat)
{
	int value = 0;
	for (int i = 0; i < _countOfVertices; i++)
	{
		for (int j = 0; j < _countOfVertices; j++)
		{
			if (i == j)
				_mat.AddToMatrix(i, j, 0);
			else
			{
				cout << "Введите длину пути из " << i + 1 << " в " << j + 1 << ": ";
				cin >> value;
				if (value == 0)
					_mat.AddToMatrix(i, j, inf);
				else
					_mat.AddToMatrix(i, j, value);
			}
		}
	}
}

void printMatrix(Matrix _mat)
{
	for (int i = 0; i < _mat.getCountOFVertices(); i++)
	{
		for (int j = 0; j < _mat.getCountOFVertices(); j++)
		{
			if (_mat.GetFromMatrix(i, j) == inf)
				cout << setfill(' ') << setw(5) << "INF";
			else
				cout << setfill(' ') << setw(5) << _mat.GetFromMatrix(i, j);
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int NumV = 0;
	bool _bool = true;
	char _char;
	do
	{
		cout << "Введите количество вершин: ";
		cin >> NumV;
		Matrix startMat(NumV);
		createMatrix(NumV, startMat);
		printMatrix(startMat);
		cout << "Матрица кротчайших путей: " << endl;
		printMatrix(startMat.floydWarshall(startMat));
		cout << "Ввести еще матрицу? (y/n): ";
		cin >> _char;
		cout << endl;
		if (_char != 'y')
			_bool = false;
	} while (_bool);

	return 0;
}