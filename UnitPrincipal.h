// ---------------------------------------------------------------------------

#ifndef UnitPrincipalH
#define UnitPrincipalH

// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include <FMX.StdCtrls.hpp>
#include "IMC.h"

class Paciente;

// ---------------------------------------------------------------------------
class TFormPrincipal : public TForm {
__published: // IDE-managed Components
	TLayout *Layout1;
	TLayout *Layout2;
	TStringGrid *StringGrid1;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn7;
	TEdit *Edit1;
	TLabel *lbCodigo;
	TLabel *lbNome;
	TEdit *Edit2;
	TLayout *Layout3;
	TButton *btnCadastrar;

	void __fastcall btnCadastrarClick(TObject *Sender);
	void __fastcall Edit2KeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);

private: // User declarations

public: // User declarations
	__fastcall TFormPrincipal(TComponent* Owner);
    void limpaColunas();
	int atualizaGrid(Paciente* pacientes[1000], int qtdPacientes);
    void filtraGrid();
};

// ---------------------------------------------------------------------------
extern PACKAGE TFormPrincipal *FormPrincipal;
// ---------------------------------------------------------------------------
#endif


