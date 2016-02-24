#include "stdafx.h"
#include "Genotype.h"


//template<typename ValueType>
// Genotype<ValueType>::Genotype(int number)
//{
//	fitness = 0;
//	number_of_genes = 0;
//}

//template<typename ValueType>
//Genotype<ValueType>::~Genotype()
//{
//}

//template <typename ValueType>
//Genotype<ValueType>::Genotype(int number, double fitness)
//{
//	_number_of_genes = number;
//	_fitness = fitness;
//}

//template<typename ValueType>
//double Genotype<ValueType>::get_fitness()
//{
//	if (_fitness == 0)
//		_fitness = count_fitness();
//	return _fitness;
//}

template<typename ValueType>
vector<Gene<ValueType>>* Genotype<ValueType>::get_genotype()
{
	return &genotype;
}

template<typename ValueType>
int Genotype<ValueType>::get_number_of_genes()
{
	return _number_of_genes;
}
