// ConsoleApp03-02.cpp: определ€ет точку входа дл€ консольного приложени€.
//
#include "stdafx.h"
#include "Gene.h"
#include "Genotype.h"
#include "Population.h"
#include <random>
#include <vector>
#include "Read_File.h"
#include <fstream>
#include <stdio.h>
#include <algorithm>

using namespace std;

class Genotype2 : public Genotype<int> //источником данных в этом классе будет массив (это конкретна€ реализаци€)
{
public:
	Genotype2(double** mas, int number) : Genotype(number), matrix(mas)
	{
		Distr distribution(1, _number_of_genes);
		for (size_t i = 0; i < _number_of_genes; i++)
		{
			Gene<int> g;
			g.get_gene_ref().push_back(distribution());
			genotype.push_back(move(g));
		}
		Genotype<int>::get_fitness();
	}
	//конструктор копировани€
	Genotype2(const Genotype2& other) : Genotype<int>(other._number_of_genes, other._fitness), matrix(nullptr)
	{
		if (this != &other)
		{
			auto lenght = other.genotype.size();
			genotype = vector<Gene<int>>(lenght);
			copy(other.genotype.begin(), other.genotype.end(), genotype.begin());

			matrix = other.matrix;
		}
	}
	//конструктор перемещени€ дл€ ускорени€ обработки данных в векторах,
	//основнополагающие типы также должны поддерживать этот конструктор
	Genotype2(Genotype2&& other)
	{
		genotype = vector<Gene<int>>(move(other.genotype));

		_number_of_genes = other._number_of_genes;
		_fitness = other._fitness;
		matrix = other.matrix;
		other.matrix = nullptr;
	}

private:
	double** matrix;
	static const int line_in_genes = 1;
	static const int column_in_genes = 3;

	//класс дл€ получени€ равномерного распределени€ без повторений
	class Distr
	{
		random_device rd;
		mt19937 generator;
		uniform_int_distribution<> distrib;

		int a, b;
		vector<int> chisla;

	public:
		Distr(int a, int b) : a(a), b(b)
		{
			generator = mt19937(rd());
			distrib = uniform_int_distribution<>(a, b);
		}

		int operator() () {
			while (true)
			{
				auto temp = distrib(generator);
				if (!binary_search(chisla.begin(), chisla.end(), temp))
				{
					chisla.push_back(temp);
					return temp;
				}
				/*if (find(chisla.begin(), chisla.end(), temp) == chisla.end())
				{
				chisla.push_back(temp);
				return temp;
				}*/
			}
		}
	};

	bool checked(Gene<int> gene)
	{
		/*auto val = find(genotype.begin(), genotype.end(), number);
		auto v = genotype.end() - 1;*/
		if (find(genotype.begin(), genotype.end(), gene) == genotype.end())
			return true;
		return false;
	}

	double count_fitness() override
	{
		int n_l, n_c;
		double fitness = 0;
		for (auto& gen : genotype)
		{
			for (auto item : gen.get_gene_ref())
			{
				int num_of_gene = --item;
				n_l = line_in_genes * (num_of_gene / 159);
				n_c = column_in_genes * (num_of_gene % 159);

				for (size_t i = n_c; i < n_c + column_in_genes; i++)
					fitness += matrix[n_l][i];
			}
		}
		return fitness;
	}
};

class Population2 : public Population<int>
{
public:
	Population2(const int number_of_genotype, vector<Genotype<int>> gens) : Population(number_of_genotype, gens),
		young_population_fitness(0)
	{ }

	void genotype_sort()
	{
		sort(population.begin(), population.end(), cmp);
		auto count = population.size();
		for (int i = count; i > count / 2; i--)
			population.pop_back();
	}

private:
	double young_population_fitness;

	double count_fitness()
	{
		double temp = 0;
		for (auto& item : population)
		{
			auto t = item.get_fitness();
			temp += t;
		}
	}
	static bool cmp(Genotype<int> g1, Genotype<int> g2)
	{
		return (g1.get_fitness() < g2.get_fitness());
	}
};

int main()
{
	setlocale(0, "RUS");

	/*Gene<int> g(2);
	*g[0] = 1;
	*g[1] = 4;*/

	string file_name = "matrix.txt";
	Read_File *file = new Read_File(file_name);

	const int line = file->get_line();
	const int column = file->get_column();

	double **matrix = new double*[line];
	for (int i = 0; i < line; i++)
		matrix[i] = new double[column];

	double value;
	for (int i = 0; i < line; i++)
		for (int j = 0; j < column; j++)
		{
			*(file->get_file()) >> value;
			matrix[i][j] = value;
		}

	vector<Genotype<int>> vec;

	//рассмотреть этот подход
	for (size_t i = 0; i < 100; i++)
	{
		Genotype2 g(matrix, 7807);//—ам класс Genotype2 нужен дл€ реализации логики формировани€ и загрузки данных
		vec.push_back(dynamic_cast<Genotype<int>&>(g));//динамическое приведение дл€ того, чтобы передать в конструктор класса Population2, все данные уже готовы дл€ работы в попул€ции
	}
	
	//отредактировать реализации, компил€тор не может получить доступ к реализации функций в .cpp файле (ошибка неразрешенный внешний символ), компил€тор идиот или €
	//Population2 pop(100, vec);
	for (size_t i = 0; i < 500; i++)
	{

	}
	return 0;
}

