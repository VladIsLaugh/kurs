//---------------------------------------------------------------------------

#ifndef AddUnitH
#define AddUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "vector"
#include "Patient.h"
//---------------------------------------------------------------------------
class TFormAdd : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LEPulse;
	TLabeledEdit *LESurname;
	TLabeledEdit *LEName;
	TLabeledEdit *LESPressure;
	TRadioGroup *RGRh;
	TButton *Button1;
	TButton *Button2;
	TComboBox *CBGroup;
	TLabeledEdit *LEDPressure;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormAdd(TComponent* Owner);
	CPatient add;
    bool cancelFlag;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAdd *FormAdd;
//---------------------------------------------------------------------------
#endif
