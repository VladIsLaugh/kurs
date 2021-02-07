//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DonorInfo.h"


#include "MainUnit.h"
#include <string>
#include "Patient.h"
#include "Registry.h"
#include "Functions.h"
#include "AddUnit.h"
#include "HelpUnit.h"
#include <fstream>
using namespace std;

UnicodeString file_name = "";
TStringList *strfile = new TStringList;
CRegistry* journal = new CRegistry;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	//�������� ������������ ��������� �����
	//��� ������� ��������
	SGMain->Width=750;
	SGMain->Height=600;
	SGMain->Top=100;
	SGRecipients->Width=750;
	SGRecipients->Height=600;
	SGRecipients->Top=100;
	SGDonors->Width=750;
	SGDonors->Height=600;
	SGDonors->Top=100;


	SGMain->ColWidths[0]=45;
	SGMain->ColWidths[1]=150;
	SGMain->ColWidths[2]=150;
	SGMain->ColWidths[7]=130;
	SGMain->ColWidths[3]=85;
	SGMain->ColWidths[4]=85;
	SGMain->ColWidths[5]=85;
	SGMain->ColWidths[6]=150;

	SGMain->Cells[0][0]="�";
	SGMain->Cells[1][0]="�������";
	SGMain->Cells[2][0]="��'�";
	SGMain->Cells[3][0]="����� ����";
	SGMain->Cells[4][0]="�����";
	SGMain->Cells[5][0]="����";
	SGMain->Cells[6][0]="�����";

	SGRecipients->Cells[0][1]="����ﳺ�� ���:";
	SGDonors->Cells[0][1]="����� ���:";

	SGMain->Visible=true;
	SGRecipients->Visible=false;
	SGDonors->Visible=false;

	//�-��� ��� ���������� ������� ��������� �����
	//RHKSave: Ctrl+S
	bool RHKSave = RegisterHotKey(MainForm->Handle,0x01F, MOD_CONTROL, 0x53);
	//RHKSaveAs: Ctrl+Alt+S
	bool RHKSaveAs = RegisterHotKey(MainForm->Handle,0x02F, MOD_CONTROL+MOD_ALT, 0x53);
	//RHKOpen: Ctrl+O
	bool RHKOpen = RegisterHotKey(MainForm->Handle,0x03F, MOD_CONTROL, 0x4F);

}
//---------------------------------------------------------------------------

//�-��� ��� ���� ������� TabControl
void __fastcall TMainForm::TabControlChange(TObject *Sender)
{
	//���� ������� �����->����ﳺ��
	showDonors(SGDonors, journal->getRegistry());
	//���� ������� ����ﳺ��->�����
	showRecipients(SGRecipients, journal->getRegistry());

	if(TabControl->TabIndex==0){
		SGMain->Visible=true;
		SGRecipients->Visible=false;
		SGDonors->Visible=false;
		BBDelete->Enabled=true;
		menuDelete->Enabled=true;
	}
	else if(TabControl->TabIndex==1){
		SGMain->Visible=false;
		SGRecipients->Visible=true;
		SGDonors->Visible=false;
		BBDelete->Enabled=false;
		menuDelete->Enabled=false;
	}
	else if(TabControl->TabIndex==2){
		SGMain->Visible=false;
		SGRecipients->Visible=false;
		SGDonors->Visible=true;
		BBDelete->Enabled=false;
		menuDelete->Enabled=false;
	}
}
//---------------------------------------------------------------------------

//�-��� ������ "���������"
void __fastcall TMainForm::BSortClick(TObject *Sender)
{
	SGMain->Width=750;

	//���� ������ ������� ������ - �������� �����������
	try {
		if(journal->IsEmpty()) throw ("������ ������");
		if(RGSort->ItemIndex) {
			sortByPressure(journal->getRegistry(), 0, journal->getSize() - 1, 0);
		}
		else {
		   sortByPressure(journal->getRegistry(), 0, journal->getSize() - 1, 1);
		}
	}
	catch(const char * m) {ShowMessage(m);}

	//������� �������� ���������� � �������� �������
	journal->show(SGMain);
	showDonors(SGDonors, journal->getRegistry());
	showRecipients(SGRecipients, journal->getRegistry());


}
//---------------------------------------------------------------------------

//�-��� ������ "�����������"
void __fastcall TMainForm::BMessageClick(TObject *Sender)
{
	try {
		if(journal->IsEmpty()) throw ("������ ������");
		//�������� ����� ������� ������� ���
		//����������� �����������
		SGMain->Width=880;

		SGMain->Cols[7]->Clear();
		SGMain->Cells[7][0]="�����������";

		//����������� ��� �������� �
		//������� ������ �� 100 �� 130
		//������ ������ �� 70 �� 80
		int SPress, DPress;
		for(int i=0; i<journal->getSize(); i++)
		{
			SPress = (*journal)[i].getSPressure();
			DPress = (*journal)[i].getDPressure();
			if((SPress>=100)&&(SPress<=130)&&
				(DPress>=70)&&(DPress<=80)){
				SGMain->Cells[7][i+1] = "---��������!---";
			}
		}
	}
	catch(const char * m){ShowMessage(m);}
}
//---------------------------------------------------------------------------

//�-��� ������ ����������
void __fastcall TMainForm::BGroupClick(TObject *Sender)
{
	SGMain->Width=750;

	//���� ������ ������ ������� �����������
	try {
		if(journal->IsEmpty()) throw ("������ ������");
		if(RGGroup->ItemIndex) {            //��������� �� �����-��������
			if(RGSort->ItemIndex){
				journal->groupRhFactor(0);  //��������� ����� ���
											//���������� �� ���������
			}
			else {
				journal->groupRhFactor(1);  //��������� �����  ���
											//���������� �� ����������
			}
		}
		else {
			journal->groupBloodType();      //��������� �� ������ ����
		}
	}
	catch(const char * m) { ShowMessage(m); }

	//���� �������� ���������� � �������� �������
	journal->show(SGMain);
	showDonors(SGDonors, journal->getRegistry());
	showRecipients(SGRecipients, journal->getRegistry());
}
//---------------------------------------------------------------------------

//�-��� ������ "��������� ���� ����"
void __fastcall TMainForm::ShowInfoClick(TObject *Sender)
{
	//������� ����� InfoDonor
   InfoDonor->Show();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� �������/�������� �����������
void __fastcall TMainForm::funcMessageClick(TObject *Sender)
{
    BMessage->Click();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� �������/�������� ��������� ���� ����
void __fastcall TMainForm::funcInfoClick(TObject *Sender)
{
    ShowInfo->Click();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� �������/��������� �� �����-��������
void __fastcall TMainForm::funcRhClick(TObject *Sender)
{
	RGGroup->ItemIndex=1;
	BGroup->Click();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� �������/��������� �� ������ ����
void __fastcall TMainForm::funcGroupClick(TObject *Sender)
{
	RGGroup->ItemIndex=0;
	BGroup->Click();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� �������/³���������� �� ������
void __fastcall TMainForm::funcSortClick(TObject *Sender)
{
    BSort->Click();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� �������/������ ��������
void __fastcall TMainForm::funcAddClick(TObject *Sender)
{
	BBAdd->Click();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� ����/�����
void __fastcall TMainForm::ExitClick(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------

//�-��� ������ ���� ����/�������� ��
//������ ���������� � �������� � ����
//� ������ ������� ������������
void __fastcall TMainForm::CtrlAltS1Click(TObject *Sender)
{
	AnsiString str;
	SGMain->Cols[7]->Clear();

	//���� ���������� ����� �� ��������� ������� ������������
	try {
		if(SaveDialog->Execute())
		{
			int f;
			//���� ���� � ����� ��'�� �� ���� �������� �����
			if(FileExists(SaveDialog->FileName)) {
				strfile->Clear();
				String fname = SaveDialog->FileName;
				strfile->SaveToFile(fname);
				f=FileOpen(SaveDialog->FileName, fmOpenWrite) ;
			}
			else
				f = FileCreate(SaveDialog->FileName);
			//����� ���������� � ����
			if(f != -1)
			{
				for(int i = 0; i < journal->getSize(); i++) {
					for(int j=0; j < SGMain->ColCount-1; j++) {
						str = SGMain->Cells[j+1][i+1];
						//���� ����������� ������� ����� ���� � ������� ��������
						if(j==2) {
							if(str=="I") str = "1";
							else if(str=="II") str = "2";
							else if(str=="III") str = "3";
							else if(str=="IV") str = 4;
							}
						str = str + " ";
						FileWrite(f, str.c_str(), str.Length());
					}
					str = "\r\n";
					FileWrite(f, str.c_str(), str.Length());
				}
				FileClose(f);
			}
			else throw("��������� �������� ����");
		}
	}
	catch(const char * m) { ShowMessage(m); }
	catch(...) {ShowMessage("��� ���������� ����� ������� �������, ��������� �� ���");}
}
//---------------------------------------------------------------------------

//�-��� ������ ���� ����/��������
void __fastcall TMainForm::CtrlS1Click(TObject *Sender)
{
	BBSave->Click();
}
//---------------------------------------------------------------------------

//������� ������ ��������
//������ �������� ���������� � �������� � ������� ����
void __fastcall TMainForm::BBSaveClick(TObject *Sender)
{
	//�������� ������� � ������������
	SGMain->Cols[7]->Clear();

	AnsiString str;

	//���� ������ ������ �� ���� �� ������ ������� ������������
	try {
		if(journal->IsEmpty()) throw ("������ ������");
		if(file_name=="") CtrlAltS1->Click();
		else {
			int f;
			if(FileExists(file_name)){
				strfile->Clear();
				//String fname = SaveDialog->FileName;
				strfile->SaveToFile(file_name);
				f=FileOpen(file_name, fmOpenWrite) ;
			}
			else
				throw("���� �� ������");
			if(f != -1)
			{
				for(int i = 0; i < journal->getSize(); i++) {
					for(int j=0; j < SGMain->ColCount-1; j++) {
						str = SGMain->Cells[j+1][i+1];
						//���� ����������� ������� ����� ���� � ������� ��������
						if(j==2) {
							if(str=="I") str = "1";
							else if(str=="II") str = "2";
							else if(str=="III") str = "3";
							else if(str=="IV") str = 4;
							}
						str = str + " ";
						FileWrite(f, str.c_str(), str.Length());
					}
					str = "\r\n";
					FileWrite(f, str.c_str(), str.Length());
				}
				FileClose(f);
			}
			else throw("��������� �������� ����");
		}
	}
	catch(const char * m) { ShowMessage(m); }
	catch(...) {ShowMessage("��� ���������� ����� ������� �������, ��������� �� ���");}

}
//---------------------------------------------------------------------------

//�-��� ������ ���� ����/³������
void __fastcall TMainForm::CtrlOClick(TObject *Sender)
{
	BBOpen->Click();
}
//---------------------------------------------------------------------------

//�-��� ��� ��������� ������� ��������� �����
void __fastcall TMainForm::ApplicationEvents1Message(tagMSG &Msg, bool &Handled)
{
	//RHKSave: Ctrl+S
	if (Msg.message == WM_HOTKEY)
	{
		if (Msg.wParam == 0x01F)
				{
					BBSave->Click();
				}
	}

	//RHKSaveAs: Ctrl+Alt+S
	if (Msg.message == WM_HOTKEY)
	{
		if (Msg.wParam == 0x02F)
				{
					CtrlAltS1->Click();
				}
	}

	//RHKOpen: Ctrl+O
	if (Msg.message == WM_HOTKEY)
	{
		if (Msg.wParam == 0x03F)
				{
					CtrlO->Click();
				}
	}
}
//---------------------------------------------------------------------------

//�-��� ������ ���� ������
void __fastcall TMainForm::menuHelpClick(TObject *Sender)
{
	//������� ���� FormHelp
	TFormHelp * FH = new TFormHelp(this);
	FH->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBOpenClick(TObject *Sender)
{
	SGMain->Width=750;

	int size;
	OpenTextFileDialog->FileName="";
	file_name="";
	OpenTextFileDialog->Execute();


	//���� ���� �� ���� ������ ������� ������������
	try{
		if(OpenTextFileDialog->FileName=="")
		throw "���� �� ������";
		file_name = OpenTextFileDialog->FileName;
		strfile->LoadFromFile(OpenTextFileDialog->FileName);
		size=strfile->Count;
		//������� ������� �������� � ����� �������� ����������
		journal->clear();
		journal->loadInfoFromFile(strfile);
	}
	catch(const char* message) {ShowMessage(message);}

	//���� �������� ���������� � �������� �������
	journal->show(SGMain);
	showDonors(SGDonors, journal->getRegistry());
	showRecipients(SGRecipients, journal->getRegistry());

}
//---------------------------------------------------------------------------

//�-��� ������ "������ ��������"
void __fastcall TMainForm::BBAddClick(TObject *Sender)
{
	SGMain->Width=750;

	//������� ����� FormAdd
	TFormAdd* FA = new TFormAdd(this);
	FA->ShowModal();

	//���� �� ����������� �������� ��������
	//� ����� ���������� � ��'��� ����� Patient
	//�� ������ ��'��� � CRegistry
	CPatient newPatient = FA->add;
	if(!FA->cancelFlag){
		journal->addPatient(newPatient);
		journal->show(SGMain);
		showDonors(SGDonors, journal->getRegistry());
		showRecipients(SGRecipients, journal->getRegistry());
	}
}
//---------------------------------------------------------------------------

//�-��� ������ ��������� ��������
void __fastcall TMainForm::BBDeleteClick(TObject *Sender)
{
	SGMain->Width=750;
	//���� � �������� ����� ���� ������ ������� ������������
	try{
	if(SGMain->Row>journal->getSize()) throw("������� ����� ������");
	//������� ��������� ������������ ��������� ��������
		if (MessageBox(0,"������ �������� �������� ��������?", "ϳ�������� ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			journal->deletePatient(SGMain->Row-1);
			journal->show(SGMain);
			showDonors(SGDonors, journal->getRegistry());
			showRecipients(SGRecipients, journal->getRegistry());
		}
	}
	catch(const char * m){ ShowMessage(m);}
	catch(...){ ShowMessage("������� ����� ������");}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuDeleteClick(TObject *Sender)
{
    BBDelete->Click();
}
//---------------------------------------------------------------------------

