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
    //прапорець відміни додавання нового пацієнта
	cancelFlag=1;
}
//---------------------------------------------------------------------------
void __fastcall TFormAdd::Button1Click(TObject *Sender)
{
	//локалізація кирилиці для ф-ції isalpha()
    locale loc_ru("");

	string surname, name;
	int spress, dpress, pulse;

	//якщо у відповідному полі введено неправильний символ
	//вивести попередження
	try{
		 surname=(AnsiString(LESurname->Text)).c_str();
		 name=AnsiString(LEName->Text).c_str();

		 if(LESurname->Text.IsEmpty())  throw("Поле \"Прізвище\" пусте");
		 if(LEName->Text.IsEmpty()) throw("Поле \"Ім'я\" пусте");

		 for(int i=0; i<surname.size(); i++)
		 {
			if(!isalpha(surname[i], loc_ru))
			throw("Неправильно введене прізвище");
		 }

		  for(int i=0; i<name.size(); i++)
		 {
			if(!isalpha(name[i], loc_ru))
			throw("Неправильно введене ім'я");
		 }

         	if(CBGroup->ItemIndex==-1)
			throw("Група крові не обрана");

			if(RGRh->ItemIndex==-1)
			throw("Резус-фактор не обраний");

			if(!TryStrToInt(LESPressure->Text, spress))
			throw("Неправильно введена верхня межа тиску");
			if((spress<70)||(spress>170)) {
				ShowMessage("Верхня межа тиску має  бути у межах від 70 до 170");
			}

			if(!TryStrToInt(LEDPressure->Text, dpress))
			throw("Неправильно введена нижня межа тиску");
			if((dpress<50)||(dpress>110)) {
				throw("Нижня межа тиску має  бути у межах від 50 до 110");
			}


			if(!TryStrToInt(LEPulse->Text, pulse))
			throw("Неправильно введений пульс");
			if((pulse<35)||(pulse>150)) {
				throw("Пульс має бути від 35 до 150");
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

