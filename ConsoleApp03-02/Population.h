#pragma once
#include "Gene.h"
#include <vector>
#include "Genotype.h"
#include <functional>

using namespace std;

template<typename ValueType> class Population
{
private:
	vector<function<void()>> delegate_selection;
	vector<function<void()>> delegate_recombination;
	vector<function<void()>> delegate_mutation;
	vector<function<void()>> delegate_sampling;

	bool die_notigkeit_der_mutation;
	int number_of_genotype;//объем попул€ции

	Genotype<ValueType>* parent, *_parent;//особи, которые будут родител€ми
	Genotype<ValueType>* child, *_child;
	vector<Genotype<ValueType>> parent_vector;
	vector<Genotype<ValueType>> childrn_vector;

	// ќператоры селекции родителей-------------------------------------------------------

	//свободное скрещивание
	virtual void s_panmixia();
	//отбор максимально схожих особей
	virtual void s_inbreeding();
	//отбор максимально различных особей
	virtual void s_outbreeding();
	//турнирный отбор (выбрать t особей из попул€ции -> из них лучшую)
	virtual void s_tournament();
	//веро€тность отбора согласно функции приспособленности
	virtual void s_roulette_wheel();

	// ќператоры рекомбинации (воспроизведени€) - дискретна€ и кроссинговер --------------------------------------------

	//дискретна€ рекомбинаци€
	virtual void r_discrete();
	//промежуточна€ рекомбинаци€
	virtual void r_intermediate();
	//линейна€ рекомбинаци€
	virtual void r_line();

	// ћетоды кроссинговера

	//одноточечный кроссинговер
	virtual void r_singlepoint();
	//двухточечный кроссинговер
	virtual void r_doublepoint();
	//многоточечный кроссинговер
	virtual void r_multipoint();
	//триадный кроссинговер
	virtual void r_triadic();
	//однородный кроссинговер
	virtual void r_uniform();
	//перетасовочный кроссинговер
	virtual void r_shuffler();
	//кроссинговер с уменьшением замены
	virtual void r_crossover_with_reduced_surrogate();


	// ќператоры мутаций ----------------------------------------------------


	// ќператоры отбора особей в новую попул€цию -----------------------------

	//отбор усечением
	virtual void sp_truncation();
	//элитарный отбор
	virtual void sp_elite();
	//отбор вытеснением
	virtual void sp_exclusion();
	//метод Ѕольцмана
	virtual void sp_bolzman();

	void init();

protected: Population(const int, vector<Genotype<ValueType>>);
		   vector<Genotype<ValueType>> population;

public:

	enum _selection { panmixia, inbreeding, outbreeding, tournament, roulette_wheel };
	enum _recombination { discrete, intermediate, line, singlepoint, doublepoint, multipoint, triadic, uniform, shuffler, crossover_with_reduced_surrogate };
	enum _mutation {};
	enum _sampling { truncation, elite, exclusion, bolzman };

	virtual ~Population();

	virtual void selection(_selection);
	virtual void recombination(_recombination);
	virtual void mutation();
	virtual void selection_population(_sampling);
};

