//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DonorInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInfoDonor *InfoDonor;
//---------------------------------------------------------------------------
__fastcall TInfoDonor::TInfoDonor(TComponent* Owner)
	: TForm(Owner)
{
	//�������� ������������ ���������� �����
    //�� ���� ���������� ��� ��������� ����
	SGRec->Width=150;
	SGRec->Height=90;
	SGRec->ColWidths[0]=150;
	SGRec->RowHeights[0]=90;
	SGRec->Cells[0][0]="����ﳺ��";

	SGRecGroups->Width=90;
	SGRecGroups->Height=250;
	SGRecGroups->ColWidths[0]=90;
	SGRecGroups->DefaultRowHeight=60;
	SGRecGroups->Cells[0][0]="IV �����";
	SGRecGroups->Cells[0][1]="II �����";
	SGRecGroups->Cells[0][2]="III �����";
	SGRecGroups->Cells[0][3]="I �����";

	SGRecRh->Width=60;
	SGRecRh->Height=250;
	SGRecRh->ColWidths[0]=60;
	SGRecRh->DefaultRowHeight=30;
	for(int i=0; i<8; i++){
	   if(!(i%2)){
			SGRecRh->Cells[0][i]="Rh+";
	   }
	   else SGRecRh->Cells[0][i]="Rh-";
	}

	SGDon->Width=480;
	SGDon->Height=30;
	SGDon->ColWidths[0]=480;
	SGDon->RowHeights[0]=30;
	SGDon->Cells[0][0]="�����";

	SGDonGroups->Width=480;
	SGDonGroups->Height=30;
	SGDonGroups->RowHeights[0]=30;
	SGDonGroups->DefaultColWidth=120;
	SGDonGroups->Cells[0][0]="I �����";
	SGDonGroups->Cells[1][0]="III �����";
	SGDonGroups->Cells[2][0]="II �����";
	SGDonGroups->Cells[3][0]="IV �����";

	SGDonRh->Width=480;
	SGDonRh->Height=280;
	SGDonRh->DefaultColWidth=60;
	SGDonRh->DefaultRowHeight=30;

	SGRec->Top=15;
	SGRec->Left=25;
	SGRecGroups->Top=105;
	SGRecGroups->Left=25;
	SGRecRh->Top=105;
	SGRecRh->Left=115;
	SGDon->Top=15;
	SGDon->Left=175;
	SGDonGroups->Top=45;
	SGDonGroups->Left=175;
	SGDonRh->Top=75;
	SGDonRh->Left=175;

	for(int i=0; i<8; i++){
	   if(!(i%2)){
			SGDonRh->Cells[i][0]="Rh-";
	   }
	   else SGDonRh->Cells[i][0]="Rh+";
	}

	for(int i=1; i<9; i++){
		SGDonRh->Cells[0][i]="+";
		SGDonRh->Cells[i][1]="+";
	}

	for(int i=0; i<8; i++){
		if(!(i%2)){
			SGDonRh->Cells[i][2]="+";
			SGDonRh->Cells[1][i+1]="+";
		}
	}

	for(int i=0; i<4; i++){
			SGDonRh->Cells[4][i+1]="+";
			SGDonRh->Cells[i][5]="+";
	}

	SGDonRh->Cells[2][6]="+";
	SGDonRh->Cells[5][3]="+";
}
//---------------------------------------------------------------------------
