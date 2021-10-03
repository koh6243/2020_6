  #include <SoftwareSerial.h>
  #include <LiquidCrystal.h>          // 引入 LCD 函式庫
  
  
  SoftwareSerial BT(10,11);   //Rx:10 -> BT:Tx, Tx:11-> BT:Rx
  LiquidCrystal lcd(12, 7, 5, 4, 3, 2);  // 初始化 LCD 模組
  
  int Data;      // 藍芽接收資料暫存器
  int ans[4] , guess[4];
  int A = 0, B = 0;
  char a=':';
  const byte button=A5;
  const byte buzzer=8;
  int mode=0;
  int a1=0;
void setup() {
  pinMode(button,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(38400);
  randomSeed(analogRead(A0));
  BT.begin(38400);//bluetooth baud rate
  lcd.begin(16, 2);        // 設定LCD字幕為 16*2
  lcd.print("input");         // 顯示字串
  lcd.print(a);         // 顯示字串
  lcd.setCursor(0,1);          // 移動游標至第9行第0列
  lcd.print("output");         // 顯示字串
  lcd.print(a);         // 顯示字串
  //rand4();
}

void rand4()  {
   
    int repeat;    /* 為了檢查是否產生重複的數字 */
    int i , j;    //宣告 index 變數
    ans[0]=random(10);
    for(i=1;i<4;i++){ /* 產生其餘數字 */
        do{ /* 產生新的數字直到沒有重複的情形發生 */
            repeat=0;    /* 一開始假設沒有產生重複數字的情況 */
            ans[i]=random(10);    /* 其他數字會是 0-9. */
            for(j=0;j<i;j++) {
                if(ans[i]==ans[j]) {
                    repeat=1;    /* 重複發生 */
                    break;
                }
            }
        }while(repeat==1);    //重複發生就繼續做
    }
    Serial.print("題目：");
    for(i=0;i<4;i++)
    Serial.print(ans[i]);
    Serial.print("\n");
}

void loop() {
  start:
  if(mode!=1){
  mode=1;
  rand4();
  delay(200);
  }
  if(analogRead(button)==0)
  mode=0;
  if (BT.available()){               //如果有串列資料進來     
    lcd.clear();
lcd.setCursor(0,0);
lcd.print("input");
lcd.print(a);
lcd.setCursor(0,1);
lcd.print("output");
lcd.print(a);
    Data=BT.read()-48;          //讀取串列資料
    guess[a1]=Data;
    a1++;}
  if(a1==4){
    Data=0;
    Serial.print("猜數：");
    lcd.setCursor(7,0);
    for(int j=0;j<4;j++){
    Serial.print(guess[j]);
    lcd.print(guess[j]);
    }
    a1=0;
    if(A!=4) {
    for(int i = 0;i < 4;i++){
      for(int j = 0;j < 4;j++){
        if(i == j && ans[i] == guess[j])
          A++;
        if(i != j && ans[i] == guess[j])
          B++;}}

          Serial.print("\n");
          if(A==4) {
    lcd.setCursor(7,1);
    lcd.print("Congrats!");
    Serial.print("Congrats!");
    tone(buzzer,500,300);
    A = 0;
    B = 0;
    rand4();
    
    goto start;
  }
    lcd.setCursor(7,1);
    lcd.print(A);
    Serial.print(A);
    lcd.print("A");
    Serial.print("A");
    lcd.print(B);
    Serial.print(B);
    lcd.print("B");
    Serial.print("B");
    A = 0;
    B = 0;
    }
    
  }

}
