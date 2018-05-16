program SampleProject;

uses
  Forms,
  Sample in 'Sample.pas' {Form1},
  ManagerAPI in 'ManagerAPI.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
