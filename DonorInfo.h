//---------------------------------------------------------------------------

#ifndef DonorInfoH
#define DonorInfoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TInfoDonor : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *SGRec;
	TStringGrid *SGRecGroups;
	TStringGrid *SGRecRh;
	TStringGrid *SGDon;
	TStringGrid *SGDonGroups;
	TStringGrid *SGDonRh;
private:	// User declarations
protected:
    virtual void __fastcall CreateParams(TCreateParams &Params)
    {
        TForm::CreateParams(Params);
        Params.WndParent = ::GetDesktopWindow(); // <--- ����� ���� ����������
    }
public:		// User declarations
	__fastcall TInfoDonor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInfoDonor *InfoDonor;
//---------------------------------------------------------------------------
#endif
