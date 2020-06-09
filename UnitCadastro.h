// ---------------------------------------------------------------------------

#ifndef UnitCadastroH
#define UnitCadastroH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>


// ---------------------------------------------------------------------------
class TFormCadastro : public TForm {
__published: // IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TEdit *Edit2;
	TLabel *Label3;
	TEdit *Edit3;
	TLabel *Label4;
	TEdit *Edit4;
	TLabel *Label5;
	TEdit *Edit5;
	TLabel *Label6;
	TButton *Button1;

	void __fastcall Button1Click(TObject *Sender);

private: // User declarations
public: // User declarations
	String* krl;
	Paciente* paciente;
	bool usuarioRegistrou = false;
	__fastcall TFormCadastro(TComponent* Owner);
	__fastcall TFormCadastro(Paciente* paciente, TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFormCadastro *FormCadastro;
// ---------------------------------------------------------------------------
#endif
