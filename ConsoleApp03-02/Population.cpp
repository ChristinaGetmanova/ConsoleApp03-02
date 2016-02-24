#include "stdafx.h"
#include "Population.h"
#include <random>
#include <vector>
#include <functional>

template<typename ValueType>
void Population<ValueType>::sp_truncation()
{
	double limit = 0.8;
	parent_vector.insert(parent_vector.end() - 1, childrn_vector.begin(), childrn_vector.end());
	sort(parent_vector.begin(), parent_vector.end(), !cmp);
	auto t = limit*parent_vector.size();
	auto size = parent_vector.size();

	for (size_t i = t; i < size; i++)
		parent_vector.pop_back();

	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, t);
	population.clear();

	for (size_t i = 0; i < number_of_genotype; i++)
		population.push_back(parent_vector[uniform_population(generator)]);

}

template<typename ValueType>
void Population<ValueType>::sp_elite()
{
	parent_vector.insert(parent_vector.end() - 1, childrn_vector.begin(), childrn_vector.end());
	sort(parent_vector.begin(), parent_vector.end(), !cmp);

	population.clear();
	for (size_t i = 0; i < number_of_genotype; i++)
	{
		population.push_back(parent_vector[i]);
	}
}

template<typename ValueType>
void Population<ValueType>::sp_exclusion()
{

}

template<typename ValueType>
void Population<ValueType>::sp_bolzman()
{
}

template<typename ValueType>
void Population<ValueType>::init()
{
	delegate_selection = vector<function<void()>>(5);
	delegate_recombination = vector<function<void()>>(10);
	delegate_mutation = vector<function<void()>>(0);
	delegate_sampling = vector<function<void()>>(4);
	
	delegate_selection[0] = s_panmixia;
	delegate_selection[1] = s_inbreeding; 
	delegate_selection[2] = s_outbreeding;
	delegate_selection[3] = s_tournament;
	delegate_selection[4] = s_roulette_wheel;

	delegate_recombination[0] = r_discrete;
	delegate_recombination[1] = r_intermediate;
	delegate_recombination[2] = r_line;
	delegate_recombination[3] = r_singlepoint;
	delegate_recombination[4] = r_doublepoint;
	delegate_recombination[5] = r_multipoint;
	delegate_recombination[6] = r_triadic;
	delegate_recombination[7] = r_uniform;
	delegate_recombination[8] = r_shuffler;
	delegate_recombination[9] = r_crossover_with_reduced_surrogate;

	//*********здесь должна быть мутация********

	delegate_sampling[0] = sp_truncation;
	delegate_sampling[1] = sp_elite;
	delegate_sampling[2] = sp_exclusion;
	delegate_sampling[3] = sp_bolzman;

};

template<typename ValueType>
Population<ValueType>::Population(const int number_of_genotype, vector<Genotype<ValueType>> population) :
	die_notigkeit_der_mutation(false), number_of_genotype(number_of_genotype)
{
	child = new Genotype<ValueType>();
	_child = new Genotype<ValueType>();
	this.population = population;
	init();
}

template<typename ValueType>
Population<ValueType>::~Population()
{

}

template<typename ValueType>
void Population<ValueType>::selection(_selection select)
{
	delegate_selection[select]();
	/*switch (select)
	{
	case panmixia:
		s_panmixia();
		break;

	case inbreeding:
		s_inbreeding();
		break;

	case outbreeding:
		s_outbreeding();
		break;

	case tournament:
		s_tournament();
		break;

	case roulette_wheel:
		s_roulette_wheel();
		break;

	default:
		break;
	}*/
}

template<typename ValueType>
void Population<ValueType>::recombination(_recombination recom)
{
	delegate_recombination[recom]();
	/*switch (recom)
	{
	case discrete:
		r_discrete();
		break;

	case intermediate:
		r_intermediate();
		break;

	case line:
		r_line();
		break;

	case singlepoint:
		r_singlepoint();
		break;

	case doublepoint:
		r_doublepoint();
		break;

	case multipoint:
		r_multipoint();
		break;

	case triadic:
		r_triadic();
		break;

	case uniform:
		r_uniform();
		break;

	case shuffler:
		r_shuffler();
		break;

	case crossover_with_reduced_surrogate:
		r_crossover_with_reduced_surrogate();
		break;

	default:
		break;
	}*/
}

template<typename ValueType>
void Population<ValueType>::mutation()
{

}

template<typename ValueType>
void Population<ValueType>::selection_population(_sampling samp)
{
	delegate_sampling[samp]();
}

template<typename ValueType>
void Population<ValueType>::s_panmixia()
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, number_of_genotype);
	auto t = uniform_population(generator),
		tt = uniform_population(generator);
	if (t != tt)
	{
		parent = &population[t];
		_parent = &population[tt];
	}
	parent_vector.push_back(parent);
	parent_vector.push_back(_parent);
}

template<typename ValueType>
void Population<ValueType>::s_inbreeding()
{
	sort(population.begin(), population.end(), cmp);
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, number_of_genotype);
	auto t = uniform_population(generator);
	parent = &population[t];
	if (t != population.size() - 1)
		_parent = &population[t + 1];
	else _parent = &population[t - 1];

	parent_vector.push_back(parent);
	parent_vector.push_back(_parent);
}

template<typename ValueType>
void Population<ValueType>::s_outbreeding()
{
}

template<typename ValueType>
void Population<ValueType>::s_tournament()
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, number_of_genotype);
	vector<Genotype<ValueType>> rand_genotype;
	vector<Genotype<ValueType>> mas;
	int t = 0.2*number_of_genotype;

	for (size_t i = 0; i < number_of_genotype; i++)
	{
		for (size_t k = 0; k < t; k++)
			rand_genotype.push_back(population[uniform_population(generator)]);

		sort(population.begin(), population.end(), cmp);
		mas.push_back(rand_genotype[0]);
	}

	uniform_int_distribution<> distr(0, mas.size());
	parent = &mas[distr(generator)];
	_parent = &mas[distr(generator)];
	parent_vector.push_back(parent);
	parent_vector.push_back(_parent);
}

template<typename ValueType>
void Population<ValueType>::s_roulette_wheel()
{
}

template<typename ValueType>
void Population<ValueType>::r_discrete()
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_int_distribution(0, 1);
	vector<int> parents[] = { *parent->get_genotype(), *_parent->get_genotype() };

	for (size_t i = 0; i < *parent->get_number_of_genes(); i++)
	{
		auto n = static_cast<bool>(uniform_int_distribution(generator));
		*child->get_genotype()->push_back(parents[n][i]);
		n = static_cast<bool>(uniform_int_distribution(generator));
		*_child->get_genotype()->push_back(parents[n][i]);
	}

	childrn_vector.push_back(child);
	childrn_vector.push_back(_child);
}

template<typename ValueType>
void Population<ValueType>::r_intermediate()
{
}

template<typename ValueType>
void Population<ValueType>::r_line()
{
}

template<typename ValueType>
void Population<ValueType>::r_singlepoint()
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_int_distribution(0, *parent->get_number_of_genes());
	auto point = uniform_int_distribution(generator);

	for (size_t i = 0; i < point; i++)
	{
		*child->get_genotype()->push_back(parent[i]);
		*_child->get_genotype()->push_back(_parent[i]);
	}

	for (size_t i = point; i < *parent->get_number_of_genes(); i++)
	{
		*child->get_genotype()->push_back(_parent[i]);
		*_child->get_genotype()->push_back(parent[i]);
	}
	childrn_vector.push_back(child);
	childrn_vector.push_back(_child);
}

template<typename ValueType>
void Population<ValueType>::r_doublepoint()
{
}

template<typename ValueType>
void Population<ValueType>::r_multipoint()
{
}

template<typename ValueType>
void Population<ValueType>::r_triadic()
{
}

template<typename ValueType>
void Population<ValueType>::r_uniform()
{
}

template<typename ValueType>
void Population<ValueType>::r_shuffler()
{
}

template<typename ValueType>
void Population<ValueType>::r_crossover_with_reduced_surrogate()
{
}
