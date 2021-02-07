//---------------------------------------------------------------------------
#include <locale>
#include "Registry.h"
#include <sstream>
#include <string>
#include <stdlib.h>


void CRegistry::loadInfoFromFile(TStringList* sList)
{
	//���������� �������� ��� �-��� isalpha()
   locale loc_ru("");

   int err_counter=0;

	int len;

	AnsiString anstrCurr;
	string sCurr;
	string token;
	CPatient tmp;

	char *ptr=NULL;
	char *delim =" .,";

//���� ������ ������ �� �����, ����� - �� �����
 for(int i=0; i<sList->Count; i++)
 {
		int flag=0;
		sCurr =AnsiString(sList->Strings[i]).c_str() ;

		istringstream iss(sCurr);
		getline(iss, token, ' ');

		//���� ����� ������ ������ ������ ������� ����� ����� � ��������
		for(int j=0; j<token.size(); j++)
		 {
			if(!isalpha(token[j], loc_ru)){
				if(err_counter++<4)
				ShowMessage("����� �"+ IntToStr(i)+": ������������ ������ ����� (�������)");
				flag=1;
			}
		 }
		 if(flag) continue;
		tmp.setSurname(token);

		flag=0;
		getline(iss, token, ' ');
		for(int j=0; j<token.size(); j++)
		 {
			if(!isalpha(token[j], loc_ru)) {
				if(err_counter++<4)
				ShowMessage("����� �"+ IntToStr(i)+": ������������ ������ ����� (��'�)");
				flag=1;
			}
		 }
		 if(flag) continue;
		tmp.setName(token);

		getline(iss, token, ' ');
		int group = atoi(token.c_str());
		if(!(group==1||group==2||group==3||group==4)){
			if(err_counter++<4)
			ShowMessage(("����� �"+ IntToStr(i)+": ������������ ������ ����� (����� ����)"));
			continue;
		}
		tmp.setBloodType(group);

		getline(iss, token, ' ');
		if(!(token=="+"||token=="-")){
			ShowMessage("����� �"+ IntToStr(i)+": ������������ ������ ����� (�����-������)");
			continue;
		}
		if(token == "+"){
			tmp.setRhFactor(true);
		}
		else if(token == "-"){
			tmp.setRhFactor(false);
		}

		getline(iss, token, '/');
		int spress;
		if((!TryStrToInt(token.c_str(), spress))) {
			if(err_counter++<4)
			ShowMessage("����� �"+ IntToStr(i)+": ������������ ������ ����� (������ ���� �����)");
			continue;
		}
		if((spress<70)||(spress>170)) {
			if(err_counter++<4)
			ShowMessage("����� �"+ IntToStr(i)+": ������ ���� ����� ��  ���� � ����� �� 70 �� 170");
			continue;
		}
		tmp.setSPressure(spress);

		getline(iss, token, ' ');
		int dpress;
		if(!TryStrToInt(token.c_str(), dpress)) {
			if(err_counter++<4)
			ShowMessage("����� �"+ IntToStr(i)+": ������������ ������ ����� (����� ���� �����)");
			continue;
		}
		if((dpress<50)||(dpress>110)) {
			if(err_counter++<4)
			ShowMessage("����� �"+ IntToStr(i)+": ����� ���� ����� ��  ���� � ����� �� 50 �� 110");
			continue;
		}
		tmp.setDPressure(dpress);

		getline(iss, token, ' ');
		int pulse = atoi(token.c_str());
		if(!TryStrToInt(token.c_str(), pulse)) {
			if(err_counter++<4)
			ShowMessage("����� �"+ IntToStr(i)+": ������������ ������ ����� (�����)");
			continue;
		}
		if((pulse<35)||(pulse>150)) {
        	if(err_counter++<4)
			ShowMessage("����� �"+ IntToStr(i)+": ����� ���� ����� ��  ���� � ����� �� 35 �� 150");
			continue;
		}
		tmp.setPulse(pulse);

		vRegistry.push_back(tmp);
	}
}

void CRegistry::show(TStringGrid* SG)
{
	for(int i=0; i<SG->ColCount; i++) {
		SG->Cols[i]->Clear();

	}

	SG->Cells[0][0]="�";
	SG->Cells[1][0]="�������";
	SG->Cells[2][0]="��'�";
	SG->Cells[3][0]="����� ����";
	SG->Cells[4][0]="�����";
	SG->Cells[5][0]="����";
	SG->Cells[6][0]="�����";

	int row=0;
	for(int i=0; i<vRegistry.size(); i++) {
		if(++row==SG->RowCount) SG->RowCount++;
		vRegistry[i].printToSG(SG, i+1);
	}
	if(SG->RowCount>row)SG->RowCount=row+1;
}


void CRegistry::groupBloodType()
{
	vector<CPatient> tmp;
	for(int j=1; j>=0; j--){
		for(int i=0; i<vRegistry.size(); i++)
		{
			if(vRegistry[i].getRhFactor()==j)
			{
				tmp.push_back(vRegistry[i]);
			}
		}
	}

	vRegistry=tmp;
	tmp.clear();

	for(int j=1; j<=4; j++){
		for(int i=0; i<vRegistry.size(); i++)
		{
			if(vRegistry[i].getBloodType()==j)
			{
				tmp.push_back(vRegistry[i]);
			}
		}
	}

	vRegistry=tmp;

}

void CRegistry::groupRhFactor(bool increase)
{
	vector<CPatient> tmp1;
    vector<CPatient> tmp2;

		for(int i=0; i<vRegistry.size(); i++)
		{
			if(vRegistry[i].getRhFactor())
			{
				tmp1.push_back(vRegistry[i]);
			}
			else
			{
				tmp2.push_back(vRegistry[i]);
			}
		}

	if(!tmp1.empty()){
		if(increase) 	sortByPulse(tmp1, 0, tmp1.size()-1, 1);
		else 			sortByPulse(tmp1, 0, tmp1.size()-1, 0);
	}

	if(!tmp2.empty()){
		if(increase) 	sortByPulse(tmp2, 0, tmp2.size()-1, 1);
		else 			sortByPulse(tmp2, 0, tmp2.size()-1, 0);
	}

	vRegistry.clear();
	vRegistry=tmp1;
	if(!tmp2.empty()) {
		vRegistry.insert(vRegistry.end(), tmp2.begin(), tmp2.end());
	}
}

void CRegistry::addPatient(CPatient add)
{
    vRegistry.push_back(add);
}

bool CRegistry::IsEmpty()
{
	if(vRegistry.empty())  return 1;
	else return 0;
}

void CRegistry::deletePatient(int index)
{
    vRegistry.erase(vRegistry.begin()+index);
}