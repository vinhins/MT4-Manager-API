//+------------------------------------------------------------------+
//|                                    MetaTrader Manager API Sample |
//|                 Copyright © 2001-2005, MetaQuotes Software Corp. |
//|                                         http://www.metaquotes.ru |
//+------------------------------------------------------------------+
unit Sample;
interface
uses Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
     StdCtrls,ManagerAPI;

//---- описание общих настроек
const
   SERVER     = 'localhost';                // сервер, по-умолчанию порт 443
   MAN_LOGIN  = 11;                         // логин менеджера
   MAN_PASS   = 'Manager11';                // пароль менеджера
   MAN_NAME   = 'Manager11';
   MAIL_BODY  = 'Please check your balance.';
   USER_MAIL  = 'some@some.ru';
   USER_PASS  = 'Som5e';
   USER_NAME  = 'ManAPI Test User';
   USER_GROUP = 'demoforex';                  // demo-группа
//+------------------------------------------------------------------+
//| Класс формы                                                      |
//+------------------------------------------------------------------+
type
TForm1 = class(TForm)
//---- members
   Button1: TButton;
//---- methods
   procedure Button1Click(Sender: TObject);
end;

var
  Form1: TForm1;

implementation
{$R *.DFM}
//+------------------------------------------------------------------+
//| Обработчик нажатия на кнопку Test                                |
//| Весь функционал собран здесь                                     |
//+------------------------------------------------------------------+
procedure TForm1.Button1Click(Sender: TObject);
var
  factory: TManagerFactory;
  manapi : IManagerInterface;
  err    : integer;
  user   : TUserRecord;
  money  : TTradeTransInfo;
  mail   : TMailBox;
  logins : array [0..1] of integer;
begin
  //---- создадим фабрику
  factory := TManagerFactory.Create('..\mtmanapi.dll');
  if factory=nil then exit;
  //---- ...и от нее получим API
  manapi := factory.CreateAPI;
  if manapi=nil then
  begin
    factory.Free;
    exit;
  end;
  //---- подключимся к серверу
  err:=manapi.Connect(SERVER);
  if  err<> RET_OK then
  begin
    ShowMessage('Unable connect to server: '+manapi.ErrorDescription(err));
    manapi:=nil; // так надо делать всегда при выходе!
    factory.Free;
    exit;
  end;
  //---- авторизуемся
  err:=manapi.Login(MAN_LOGIN,MAN_PASS);
  if err<> RET_OK then
  begin
    ShowMessage('Login failed: '+manapi.ErrorDescription(err));
    manapi.Disconnect;
    manapi:=nil;
    factory.Free;
    exit;
  end;
  //---- откроем счет
  ZeroMemory(@user,SizeOf(user));
  user.login:=0;                    // авто-выделение номера
  StrCopy(user.group,USER_GROUP);   // группа
  StrCopy(user.name,USER_NAME);     // имя
  StrCopy(user.password,USER_PASS); // пароль
  StrCopy(user.email,USER_MAIL);    // e-mail
  user.leverage:=100;               // плечо
  user.enable:=1;                   // разрешить счет
  err:=manapi.UserRecordNew(user);
  if err<> RET_OK then
  begin
    ShowMessage('Creating new account failed: '+manapi.ErrorDescription(err));
    manapi.Disconnect;
    manapi:=nil;
    factory.Free;
    exit;
  end;
  //---- начислим деньги
  ZeroMemory(@money,SizeOf(money));
  money.trtype :=TT_BR_BALANCE;
  money.cmd    :=OP_BALANCE;
  money.orderby:=user.login; // в данном случае это поле д/б логином
  money.price  :=10000.50;
  StrCopy(money.comment,'lucky man');
  err:=manapi.TradeTransaction(money);
  if err<> RET_OK then
  begin
    ShowMessage('Trade transaction failed: '+manapi.ErrorDescription(err));
    manapi.Disconnect;
    manapi:=nil;
    factory.Free;
    exit;
  end;
  //---- отошлем письмо
  //---- в настройках сервера, менеджер должен иметь непустое имя ящика
  //---- для внутренней почты 
  ZeroMemory(@mail,SizeOf(mail));
  mail.sender :=MAN_LOGIN;
  StrCopy(mail.from,MAN_NAME);
  StrCopy(mail.subject,'Balance');
  logins[0]   :=user.login; // мы отсылаем одному юзеру
  mail.fromto :=1;          // хотя можно и большему кол-ву
  mail.body   :=pchar(MAIL_BODY);
  mail.bodylen:=StrLen(MAIL_BODY);
  err:=manapi.MailSend(mail,@logins);
  if err<> RET_OK then
  begin
    ShowMessage('Send mail failed: '+manapi.ErrorDescription(err));
    manapi.Disconnect;
    manapi:=nil;
    factory.Free;
    exit;
  end;
  //---- на выход: освобождаем все
  ShowMessage('All tests successed.');
  manapi.Disconnect;
  manapi:=nil;
  factory.Free;
end;
end.
//+------------------------------------------------------------------+

