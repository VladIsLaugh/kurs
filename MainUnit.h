//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TOpenTextFileDialog *OpenTextFileDialog;
	TStringGrid *SGMain;
	TButton *BSort;
	TButton *BMessage;
	TButton *BGroup;
	TButton *ShowInfo;
	TTabControl *TabControl;
	TStringGrid *SGRecipients;
	TStringGrid *SGDonors;
	TMainMenu *MainMenu;
	TMenuItem *menuFile;
	TMenuItem *CtrlO;
	TMenuItem *menuFunc;
	TRadioGroup *RGSort;
	TRadioGroup *RGGroup;
	TMenuItem *CtrlS1;
	TMenuItem *CtrlAltS1;
	TMenuItem *N2;
	TMenuItem *Exit;
	TMenuItem *funcAdd;
	TMenuItem *funcSort;
	TMenuItem *funcGroup;
	TMenuItem *funcRh;
	TMenuItem *funcInfo;
	TMenuItem *funcMessage;
	TSaveDialog *SaveDialog;
	TBitBtn *BBSave;
	TApplicationEvents *ApplicationEvents1;
	TMenuItem *menuHelp;
	TBitBtn *BBOpen;
	TBitBtn *BBAdd;
	TBitBtn *BBDelete;
	TMenuItem *menuDelete;
	void __fastcall BSortClick(TObject *Sender);
	void __fastcall BMessageClick(TObject *Sender);
	void __fastcall BGroupClick(TObject *Sender);
	void __fastcall ShowInfoClick(TObject *Sender);
	void __fastcall TabControlChange(TObject *Sender);
	void __fastcall funcMessageClick(TObject *Sender);
	void __fastcall funcInfoClick(TObject *Sender);
	void __fastcall funcRhClick(TObject *Sender);
	void __fastcall funcGroupClick(TObject *Sender);
	void __fastcall funcSortClick(TObject *Sender);
	void __fastcall funcAddClick(TObject *Sender);
	void __fastcall ExitClick(TObject *Sender);
	void __fastcall CtrlAltS1Click(TObject *Sender);
	void __fastcall CtrlS1Click(TObject *Sender);
	void __fastcall BBSaveClick(TObject *Sender);
	void __fastcall CtrlOClick(TObject *Sender);
	void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
	void __fastcall menuHelpClick(TObject *Sender);
	void __fastcall BBOpenClick(TObject *Sender);
	void __fastcall BBAddClick(TObject *Sender);
	void __fastcall BBDeleteClick(TObject *Sender);
	void __fastcall menuDeleteClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
