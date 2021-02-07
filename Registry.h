//---------------------------------------------------------------------------

#ifndef RegistryH
#define RegistryH

#include "Patient.h"
#include "Functions.h"
#include <vector>
#include <algorithm>

//�����  CRegistry ("������")
//������ ������ ��'���� ����� CPatient
//�� �-��� ��� ������ � ���

class CRegistry
{
	vector<CPatient> vRegistry;
   public:
	CRegistry() {;}
	//���������� ����
	CRegistry(CRegistry & rg) {vRegistry = rg.getRegistry();}
	//������� ��������
	int getSize() {return vRegistry.size();}
	vector<CPatient> & getRegistry(){return vRegistry;}
	CPatient operator[](int i){return vRegistry[i];}
	//�-��� ������������ ������� �������� � ������ �����
	void loadInfoFromFile(TStringList *);
	//���� ������� �������� � �������
	void show(TStringGrid* );
	//������� ������� ��������
	void clear() {vRegistry.clear();}
	//���������� ������� �������� �� ������ ����
	void groupBloodType();
	//���������� ������� �������� �� �������
	void groupRhFactor(bool);
	//��������� ������ ��������
	void addPatient(CPatient);
	//�������� �� ������ �������� ������
	bool IsEmpty();
    //��������� �������� �������� �� ��������
    void deletePatient(int );
};


//---------------------------------------------------------------------------
#endif
