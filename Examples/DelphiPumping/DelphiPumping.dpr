program DelphiPumping;

uses
  Forms,
  Pumping in 'Pumping.pas' {Form1},
  ManagerAPI in 'ManagerAPI.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
