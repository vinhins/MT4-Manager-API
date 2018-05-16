//+------------------------------------------------------------------+
//|                                    MetaTrader Manager API Sample |
//|                 Copyright © 2001-2005, MetaQuotes Software Corp. |
//|                                         http://www.metaquotes.ru |
//+------------------------------------------------------------------+
unit Pumping;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ManagerAPI, StdCtrls;

//---- common settings
const
   SERVER    = 'localhost:443';            // server
   MAN_LOGIN = 11;                         // manager login
   MAN_PASS  = 'Manager11';                // manager password

//---- our pumping message
var
  ExtPumpingMsg: UINT;

//+------------------------------------------------------------------+
//| Form type                                                        |
//+------------------------------------------------------------------+
type
  TForm1 = class(TForm)
  ListBox1: TListBox;
  constructor Construct;
  procedure FormCreate(Sender: TObject);
  procedure FormDestroy(Sender: TObject);
  procedure WndProc(var Msg: TMessage); override;
  procedure OnUpdateTrades;
  procedure OnUpdateBidAsk;
private
//---- members
  factory : TManagerFactory;              // manager factory
  manapi  : IManagerInterface;            // manager interface
  trades  : PATradeRecord;                // trades array
  total   : integer;                      // total trades
end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

//+------------------------------------------------------------------+
//| Constructor                                                      |
//+------------------------------------------------------------------+
constructor TForm1.Construct;
begin
  //---- init trades
  Form1.trades := nil;
  Form1.total  := 0;
end;
//+------------------------------------------------------------------+
//| Create                                                           |
//+------------------------------------------------------------------+
procedure TForm1.FormCreate(Sender: TObject);
var
  err : integer;
begin
  //---- create factory
  factory := TManagerFactory.Create('..\mtmanapi.dll');
  if factory = nil then exit;
  //---- create manager interface
  manapi := factory.CreateAPI;
  if manapi = nil then
  begin
    Form1.Close;
    exit;
  end;
  //---- connect to the server
  err := manapi.Connect(SERVER);
  if  err <> RET_OK then
  begin
    ShowMessage('Unable connect to server: '+manapi.ErrorDescription(err));
    Form1.Close;
    exit;
  end;
  //---- login
  err := manapi.Login(MAN_LOGIN,MAN_PASS);
  if err <> RET_OK then
  begin
    ShowMessage('Login failed: '+manapi.ErrorDescription(err));
    Form1.Close;
    exit;
  end;
  //---- switch to the pumping mode
  err := manapi.PumpingSwitch(nil,Form1.WindowHandle,ExtPumpingMsg,0);
  if err <> RET_OK then
  begin
    ShowMessage('Pumping switch failed: '+manapi.ErrorDescription(err));
    Form1.Close;
    exit;
  end;
  //---- add symbols
  manapi.SymbolAdd('EURUSD');
  manapi.SymbolAdd('GBPUSD');
  manapi.SymbolAdd('USDCHF');
  manapi.SymbolAdd('USDJPY');
end;
//+------------------------------------------------------------------+
//| Destroy                                                          |
//+------------------------------------------------------------------+
procedure TForm1.FormDestroy(Sender: TObject);
begin
  if manapi <> nil then
  begin
    //---- do not forget to free trades memory
    if trades <> nil then
    begin
      manapi.MemFree(trades);
      total := 0;
    end;
    //---- disconnect and free manager interface
    manapi.Disconnect;
    manapi := nil;
  end;
  //---- cleanup winsock and deinit factory
  if factory <> nil then begin
    factory.Free;
  end;
end;
//+------------------------------------------------------------------+
//| Initialization                                                   |
//+------------------------------------------------------------------+
procedure TForm1.WndProc(var Msg: TMessage);
begin
  inherited;
  //---- test for our pumping message
  if Msg.Msg = ExtPumpingMsg then
  begin
    //---- switch pumping codes
    case msg.WParam of
      PUMP_UPDATE_TRADES: // update trades
      begin
        OnUpdateTrades;
      end;
      PUMP_UPDATE_BIDASK:
      begin
        OnUpdateBidAsk;
      end;
      // other PUMP_* codes
    end;
  end;
end;
//+------------------------------------------------------------------+
//| On update trades                                                 |
//+------------------------------------------------------------------+
procedure TForm1.OnUpdateTrades;
var
  str : string;
begin
  //---- free old trades
  if trades <> nil then manapi.MemFree(trades);
  //---- get new trades
  trades := manapi.TradesGet(total);
  //---- add status message
  str := 'PUMP_UPDATE_TRADES: ' + IntToStr(total) + ' total trades';
  ListBox1.Items.Add(str);
  //----
  //---- or manapi.TradeRecordGet by order#
end;
//+------------------------------------------------------------------+
//| On update bid/ask                                                |
//+------------------------------------------------------------------+
procedure TForm1.OnUpdateBidAsk;
var
  count: integer;
  si   : array [0..31] of TSymbolInfo;
  str  : string;
begin
  count := 32;
  //---- get updated symbols
  while count > 0 do begin
    count := 32;
    count := manapi.SymbolInfoUpdated(@si,count);
    //---- add status message
    if count > 0 then begin
      str := 'PUMP_UPDATE_BIDASK: ' + IntToStr(count) + ' total quotes';
      ListBox1.Items.Add(str);
    end;
  end;
end;
//+------------------------------------------------------------------+
//| Initialization                                                   |
//+------------------------------------------------------------------+
initialization
  //---- register pumping message
  ExtPumpingMsg := RegisterWindowMessage('DelphiPumpingMessage');
end.
