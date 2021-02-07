//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddUnit.h"
#include <string>
#include <stdlib>
#include <locale>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAdd *FormAdd;




//---------------------------------------------------------------------------
__fastcall TFormAdd::TFormAdd(TComponent* Owner)
	: TForm(Owner)
{
    //��������� ����� ��������� ������ ��������
	cancelFlag=1;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdd::Button1Click(TObject *Sender)
{
	//���������� �������� ��� �-��� isalpha()
    locale loc_ru("");

	string surname, name;
	int spress, dpress, pulse;

	//���� � ���������� ��� ������� ������������ ������
	//������� ������������
	try{
		 surname=(AnsiString(LESurname->Text)).c_str();
		 name=AnsiString(LEName->Text).c_str();

		 if(LESurname->Text.IsEmpty())  throw("���� \"�������\" �����");
		 if(LEName->Text.IsEmpty()) throw("���� \"��'�\" �����");

		 for(int i=0; i<surname.size(); i++)
		 {
			if(!isalpha(surname[i], loc_ru))
			throw("����������� ������� �������");
		 }

		  for(int i=0; i<name.size(); i++)
		 {
			if(!isalpha(name[i], loc_ru))
			throw("����������� ������� ��'�");
		 }

         	if(CBGroup->ItemIndex==-1)
			throw("����� ���� �� ������");

			if(RGRh->ItemIndex==-1)
			throw("�����-������ �� �������");

			if(!TryStrToInt(LESPressure->Text, spress))
			throw("����������� ������� ������ ���� �����");
			if((spress<70)||(spress>170)) {
				ShowMessage("������ ���� ����� ��  ���� � ����� �� 70 �� 170");
			}

			if(!TryStrToInt(LEDPressure->Text, dpress))
			throw("����������� ������� ����� ���� �����");
			if((dpress<50)||(dpress>110)) {
				throw("����� ���� ����� ��  ���� � ����� �� 50 �� 110");
			}


			if(!TryStrToInt(LEPulse->Text, pulse))
			throw("����������� �������� �����");
			if((pulse<35)||(pulse>150)) {
				throw("����� �� ���� �� 35 �� 150");
			}

		 add.setSurname(surname);
		 add.setName(name);
		 add.setBloodType(CBGroup->ItemIndex+1);
		 if(RGRh->ItemIndex){
			add.setRhFactor(false);
		 }
		 else add.setRhFactor(true);

		 add.setSPressure(spress);
		 add.setDPressure(dpress);
		 add.setPulse(pulse);
		 cancelFlag=0;
		 this->Close();
	 }
	 catch(const char* message){ShowMessage(message);}

}
//---------------------------------------------------------------------------


void __fastcall TFormAdd::Button2Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

