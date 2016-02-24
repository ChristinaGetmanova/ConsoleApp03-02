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
	int number_of_genotype;//����� ���������

	Genotype<ValueType>* parent, *_parent;//�����, ������� ����� ����������
	Genotype<ValueType>* child, *_child;
	vector<Genotype<ValueType>> parent_vector;
	vector<Genotype<ValueType>> childrn_vector;

	// ��������� �������� ���������-------------------------------------------------------

	//��������� �����������
	virtual void s_panmixia();
	//����� ����������� ������ ������
	virtual void s_inbreeding();
	//����� ����������� ��������� ������
	virtual void s_outbreeding();
	//��������� ����� (������� t ������ �� ��������� -> �� ��� ������)
	virtual void s_tournament();
	//����������� ������ �������� ������� �����������������
	virtual void s_roulette_wheel();

	// ��������� ������������ (���������������) - ���������� � ������������ --------------------------------------------

	//���������� ������������
	virtual void r_discrete();
	//������������� ������������
	virtual void r_intermediate();
	//�������� ������������
	virtual void r_line();

	// ������ �������������

	//������������ ������������
	virtual void r_singlepoint();
	//������������ ������������
	virtual void r_doublepoint();
	//������������� ������������
	virtual void r_multipoint();
	//�������� ������������
	virtual void r_triadic();
	//���������� ������������
	virtual void r_uniform();
	//�������������� ������������
	virtual void r_shuffler();
	//������������ � ����������� ������
	virtual void r_crossover_with_reduced_surrogate();


	// ��������� ������� ----------------------------------------------------


	// ��������� ������ ������ � ����� ��������� -----------------------------

	//����� ���������
	virtual void sp_truncation();
	//��������� �����
	virtual void sp_elite();
	//����� �����������
	virtual void sp_exclusion();
	//����� ���������
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

