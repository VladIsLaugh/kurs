//---------------------------------------------------------------------------

#ifndef PatientH
#define PatientH
#include <stdlib>
#include <vcl.h>
#include <string>
#include <stdlib.h>
#include <Vcl.Grids.hpp>

using namespace std;

//���� CPatient ("�������")
//̳����� ���� ����������:
//		�������
//		��'�
//		����� ����
//		�����
//		������ ���� �����
//		����� ���� �����
//		�����

class CPatient
{
	string m_strName;
	string m_strSurname;
	int m_iBloodType;
	bool m_bRhFactor;
	int m_iSPressure; 	    	//systolic
	int m_iDPressure;  		//diastolic
	int m_iPulse;
 public:
	CPatient() {}
	CPatient(string Name, string Surname, int BloodType,
	bool RhFactor, int SPressure, int DPressure, int Pulse);

	//get-�������
	string getName() {return m_strName;}
	string getSurname() {return m_strSurname;}
	int getBloodType() {return m_iBloodType;}
	bool getRhFactor() {return m_bRhFactor;}
	int getSPressure() {return m_iSPressure;}
	int getDPressure() {return m_iDPressure;}
	int getPulse() {return m_iPulse;}
	//set-�������
	void setName(string Name) { m_strName=Name;}
	void setSurname(string Surname) { m_strSurname=Surname;}
	void setBloodType(int BloodType) { m_iBloodType=BloodType;}
	void setRhFactor(bool RhFactor) { m_bRhFactor=RhFactor;}
	void setSPressure(int SPressure) { m_iSPressure=SPressure;}
	void setDPressure(int DPressure) { m_iDPressure=DPressure;}
	void setPulse(int Pulse) { m_iPulse=Pulse;}
	//���� � �������
	void printToSG(TStringGrid *, int );

	CPatient& operator=(CPatient pat);
};
//---------------------------------------------------------------------------
#endif
