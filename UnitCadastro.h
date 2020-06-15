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

class Paciente;


// ---------------------------------------------------------------------------
class TFormCadastro : public TForm {
__published: // IDE-managed Components
	TLabel *Label1;
	TEdit *EditNome;
	TLabel *Label2;
	TEdit *EditSexo;
	TLabel *Label3;
	TEdit *EditDataNascimento;
	TLabel *Label4;
	TEdit *EditPeso;
	TLabel *Label5;
	TEdit *EditAltura;
	TLabel *Label6;
	TButton *btnConfirmar;

	void __fastcall btnConfirmarClick(TObject *Sender);

private: // User declarations
public: // User declarations
	Paciente* paciente;
	bool usuarioRegistrou = false;
	__fastcall TFormCadastro(TComponent* Owner);
	__fastcall TFormCadastro(Paciente* paciente, TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFormCadastro *FormCadastro;
// ---------------------------------------------------------------------------
#endif
