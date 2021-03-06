#INCLUDE    <18F4550.H>
#DEVICE     ADC=10
#FUSES      NOWDT,PUT,HS,NOPROTECT,NOLVP,CPUDIV1
#USE        I2C(MASTER,SLOW,SDA=PIN_B0,SCL=PIN_B1)
#USE        DELAY(CLOCK=20000000)
//#USE        rs232(baud=9600, xmit=PIN_C6,rcv=PIN_C7)
//NUT NHAN:
#DEFINE  BT0     PIN_B5
#DEFINE  BT1     PIN_B4
#DEFINE  BT2     PIN_B3
#DEFINE  BT3     PIN_B2

#DEFINE  ON      BT0       //DK LED DON, MOTOR
#DEFINE  OFF     BT1
#DEFINE  INV     BT2

#DEFINE  UP      BT0    //DK LED DON
#DEFINE  MOD     BT1
#DEFINE  DW      BT2
#DEFINE  CLR     BT3

#DEFINE  STOP    BT3

#DEFINE  ON1     BT0     
#DEFINE  OFF1    BT1
#DEFINE  ON2     BT2       
#DEFINE  OFF2    BT3
#define  trigger      pin_e2
#define  echo         pin_e1

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#DEFINE      ENABLE_573A      PIN_D1         
#DEFINE      ENABLE_573B      PIN_D0        
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#DEFINE      SSDO             PIN_E2         
#DEFINE      SSCK             PIN_E0         
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#DEFINE      RCK_4LED7DOAN    PIN_D7         
#DEFINE      G_4LED7DOAN      PIN_D6         
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
#DEFINE      RCK_MATRANLED    PIN_D7         
#DEFINE      G_MATRANLED      PIN_D6         
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#DEFINE      RCK_32LEDDON        PIN_D5         
#DEFINE      G_32LEDDON          PIN_D4         
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
#DEFINE      RCK_8LEDQUET     PIN_D5        
#DEFINE      G_8LEDQUET       PIN_D4         
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#DEFINE      RCK_LCD20X4      PIN_D3         
#DEFINE      G_LCD20X4        PIN_D2        
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
#DEFINE      RCK_BUZERRELAY    PIN_D3     
#DEFINE      G_BUZERRELAY      PIN_D2       

//#DEFINE      ENABLE_573A      PIN_D6         //CS0 CUA A
//#DEFINE      ENABLE_573B      PIN_D7         //CS1 CUA B
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//#DEFINE      SSDO             PIN_E0         //CHUNG TAT CA
//#DEFINE      SSCK             PIN_E1         //CHUNG TAT CA

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//#DEFINE      RCK_4LED7DOAN    PIN_D0         //A - 4 BYTE
//#DEFINE      G_4LED7DOAN      PIN_D1         //A - 4 BYTE
   
//#DEFINE      RCK_MATRANLED    PIN_D0         //B - 3 BYTE DAO
//#DEFINE      G_MATRANLED      PIN_D1         //B - 3 BYTE DAO
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//#DEFINE      RCK_32LED        PIN_D2         //A - 4 BYTE
//#DEFINE      G_32LED          PIN_D3         //A - 4 BYTE

//#DEFINE      RCK_8LEDQUET     PIN_D2         //B - 2 BYTE DAO
//#DEFINE      G_8LEDQUET       PIN_D3         //B - 2 BYTE DAO

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//#DEFINE      RCK_LCD20X4      PIN_D4         //A - 2 BYTE DAO
//#DEFINE      G_LCD20X4         PIN_D5         //A - 2 BYTE DAO

//#DEFINE      RCK_BUZERELAY    PIN_D4     //B - 1 BYTE 
//#DEFINE      G_BUZERELAY       PIN_D5         //B - 1 BYTE 

VOID XUAT_LCD20X4(UNSIGNED INT8 LCD_SIGNAL,LCD_INS_HTHI);

VOID XUAT_BUZZER_RELAY();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   
#DEFINE     CHOT_2_IC_74573_A_B  OUTPUT_D(0XFC)

UNSIGNED INT8 TIN_HIEU_DK_74573_A;
#BIT G_4A         = TIN_HIEU_DK_74573_A.6
#BIT G_32A        = TIN_HIEU_DK_74573_A.4
#BIT G_LCDA       = TIN_HIEU_DK_74573_A.2
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         
#DEFINE     MO_32_LED_DON        G_32A=0; 
#DEFINE     TAT_32_LED_DON       G_32A=1; 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         
#DEFINE     MO_4_LED_7DOAN       G_4A=0;  
#DEFINE     TAT_4_LED_7DOAN      G_4A=1; 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
#DEFINE     MO_GLCD_LCD           G_LCDA=0; 
#DEFINE     TAT_GLCD_LCD          G_LCDA=1; 

UNSIGNED INT8 TIN_HIEU_DK_74573_B;  
#BIT G_MTB        = TIN_HIEU_DK_74573_B.6
#BIT G_8B         = TIN_HIEU_DK_74573_B.4
#BIT G_RBDCB      = TIN_HIEU_DK_74573_B.2
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
#DEFINE     MO_LED_MATRAN        G_MTB=0; 
#DEFINE     TAT_LED_MATRAN       G_MTB=1; 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       
#DEFINE     MO_8_LED_QUET        G_8B=0;  
#DEFINE     TAT_8_LED_QUET       G_8B=1;  
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         
#DEFINE     MO_RELAY_BUZZER_DC   G_RBDCB=0;  
#DEFINE     TAT_RELAY_BUZZER_DC  G_RBDCB=1;  

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH KIEM TRA PHIM BT1
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
UNSIGNED INT8 DL_BTN=0;
INT1 PHIM_BT0(UNSIGNED INT16 DL)
{  
    IF (!INPUT(BT0))
    {  
      DL_BTN++;
      IF (DL_BTN>= DL)
      {
         DL_BTN = 0;
         RETURN(1);
      }
      ELSE RETURN(0);
    }
    ELSE         RETURN(0);    
} 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH KIEM TRA PHIM BT1
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
INT1 PHIM_BT1(UNSIGNED INT16 DL )
{  
   IF (!INPUT(BT1))
    {  
      DL_BTN++;
      IF (DL_BTN>= DL)
      {
         DL_BTN = 0;
         RETURN(1);
      }
      ELSE RETURN(0);
    }
    ELSE         RETURN(0);    
} 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH KIEM TRA PHIM BT2      
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                                    
INT1 PHIM_BT2(UNSIGNED INT16 DL )
{                                        
   IF (!INPUT(BT2))
    {  
      DL_BTN++;
      IF (DL_BTN>= DL)
      {
         DL_BTN = 0;
         RETURN(1);
      }
      ELSE RETURN(0);
    }
    ELSE         RETURN(0);                                               
}      
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH KIEM TRA PHIM BT3
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
INT1 PHIM_BT3(UNSIGNED INT16 DL )
{  
    IF (!INPUT(BT3))
    {  
      DL_BTN++;
      IF (DL_BTN>= DL)
      {
         DL_BTN = 0;
         RETURN(1);
      }
      ELSE RETURN(0);
    }
    ELSE         RETURN(0);   
} 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//KHAI BAO  MODULE RELAY, TRIAC, BUZZER, DONG CO
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
UNSIGNED INT16 RBDC;
#BIT STEP_MOTOR_ENABLE  = RBDC.0    
#BIT STEP_MOTOR_IN1     = RBDC.1    
#BIT STEP_MOTOR_IN2     = RBDC.2
#BIT STEP_MOTOR_IN3     = RBDC.3
#BIT STEP_MOTOR_IN4     = RBDC.4
#BIT DC_ENABLE          = RBDC.5    
#BIT PWRKEY             = RBDC.6    

#BIT BUZZER             = RBDC.8    //1=ON,0=OFF
#BIT TRIAC_1            = RBDC.9    //1=ON,0=OFF
#BIT TRIAC_2            = RBDC.10   //1=ON,0=OFF
#BIT RELAY_1            = RBDC.11   //0=ON,1=OFF
#BIT RELAY_2            = RBDC.12   //0=ON,1=OFF

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 103: CHUONG TRINH CON KHOI TAO IC CHOT
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         
#DEFINE     CHO_IC_74573_A_GOI_DU_LIEU     OUTPUT_HIGH(ENABLE_573A)
#DEFINE     CHOT_IC_74573_A_GOI_DU_LIEU    OUTPUT_LOW(ENABLE_573A)

#DEFINE     CHO_IC_74573_B_GOI_DU_LIEU     OUTPUT_HIGH(ENABLE_573B)
#DEFINE     CHOT_IC_74573_B_GOI_DU_LIEU    OUTPUT_LOW(ENABLE_573B)
VOID MO_IC_74573_A_THONG_DL();

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   
CONST UNSIGNED CHAR MA7DOAN[16]= {0XC0,0XF9,0xA4,0XB0,0X99,0X92,0X82,0XF8,
0X80,0X90,0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E,};
CONST UNSIGNED CHAR MA7DOAN2[16]= {0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,
0X00,0X10,0X08,0X03,0X46,0X21,0X06,0X0E};
#DEFINE     MASO0    0XC0
#DEFINE     MASO1    0XF9
#DEFINE     MASO2    0XA4
#DEFINE     MASO3    0XB0
#DEFINE     MASO4    0X99
#DEFINE     MASO5    0X92
#DEFINE     MASO6    0X82
#DEFINE     MASO7    0XF8
#DEFINE     MASO8    0X80
#DEFINE     MASO9    0X90
#DEFINE     MACHU_A       0X88
#DEFINE     MACHU_B       0X83
#DEFINE     MACHU_C       0XC6
#DEFINE     MACHU_D       0XA1
#DEFINE     MACHU_E       0X86
#DEFINE     MACHU_F       0X8E





//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
//HAM 102: XUAT 1 BYTE RA THANH GHI DICH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
VOID XUAT_1BYTE(UNSIGNED INT8 X)
{
   UNSIGNED INT8   SB;   
   #BIT msb  = X.7;  

   FOR (SB=0;SB<8;SB++)
      {                                                 
         OUTPUT_BIT(SSDO,msb);    
         OUTPUT_LOW(SSCK); OUTPUT_HIGH(SSCK);
         X= X<<1;         
     }
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 301: CHUONG TRINH CON XUAT 4 BYTE RA 32 LED DON
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_32LED_DON_4BYTE(UNSIGNED INT8 BLD3,BLD2,BLD1,BLD0)
{     
      XUAT_1BYTE(BLD3);          
      XUAT_1BYTE(BLD2);
      XUAT_1BYTE(BLD1);          
      XUAT_1BYTE(BLD0);            
            
      MO_IC_74573_A_THONG_DL();            
      OUTPUT_HIGH(RCK_32LEDDON);    OUTPUT_LOW(RCK_32LEDDON);
      MO_32_LED_DON;
      CHOT_IC_74573_A_GOI_DU_LIEU;      
}



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 302: CHUONG TRINH CON XUAT 2 WORD 16 BIT RA 32 LED DON
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_32LED_DON_2WORD(UNSIGNED INT16 WLD1, UNSIGNED INT16 WLD0)
{     
     UNSIGNED INT8  B3,B2,B1,B0;
     B3 = WLD1>>8;  B2 = WLD1; 
     B1 = WLD0>>8;  B0 = WLD0;
     XUAT_32LED_DON_4BYTE(B3,B2,B1,B0);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 303: CHUONG TRINH CON XUAT 1 DOUBLE WORD RA 32 LED DON
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_32LED_DON_1DW(UNSIGNED LONG LONG DWLD)
{     
     UNSIGNED INT16  WD1,WD0;
     WD1 = DWLD>>16;  WD0 = DWLD;
     XUAT_32LED_DON_2WORD(WD1,WD0);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 304: CHUONG TRINH CON XUAT 1 BYTE RA 32 LED DON
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_32LED_DON_1BYTE(UNSIGNED INT8 B0)
{     
     XUAT_32LED_DON_4BYTE(0,0,0,B0);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
//XUAT 1 BIT ROI TRA LAI KET QUA SAU KHI DICH DI 1 BIT
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
UNSIGNED  INT8 XUAT_1BIT(UNSIGNED INT8 BYTEXUAT)
{
      UNSIGNED INT8   XBITX;   
      #BIT BSERIX  = XBITX.0
      XBITX = BYTEXUAT;
                                            
      OUTPUT_BIT(SSDO,BSERIX);    
      OUTPUT_LOW(SSCK); OUTPUT_HIGH(SSCK);
      XBITX= XBITX>>1;   
      RETURN(XBITX);  
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
//HAM 101: HAM KHOI TAO CAC PORT VA IC CHOT
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
VOID SET_UP_PORT_IC_CHOT()
{     
      SET_TRIS_D(0x00);    SET_TRIS_a(0xFF);
      SET_TRIS_E(0X00);
      OUTPUT_D(0XFF);
      TIN_HIEU_DK_74573_A=0XFF;  
      TIN_HIEU_DK_74573_B=0XFF;      
      CHOT_IC_74573_A_GOI_DU_LIEU;
      CHOT_IC_74573_B_GOI_DU_LIEU;  
      RBDC=0;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
//HAM 104: XUAT C�C THIEU DIEU KHIEN 
//GIU NGUYEN CAC TRANG THAI CUA 2 MODULE KHAC
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
VOID MO_IC_74573_A_THONG_DL()
{     
      OUTPUT_D(0X00);
      OUTPUT_BIT(G_32LEDDON,G_32A);
      OUTPUT_BIT(G_4LED7DOAN,G_4A);
      OUTPUT_BIT(G_LCD20X4,G_LCDA);  
      CHO_IC_74573_A_GOI_DU_LIEU;
}
VOID MO_IC_74573_B_THONG_DL()
{     
      OUTPUT_D(0X00);
      OUTPUT_BIT(G_MATRANLED,G_MTB);
      OUTPUT_BIT(G_8LEDQUET,G_8B);
      OUTPUT_BIT(G_BUZERRELAY,G_RBDCB); 
      CHO_IC_74573_B_GOI_DU_LIEU;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 401: CHUONG TRINH CON XUAT 4 BYTE RA 4 LED 7 DOAN
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_4LED_7DOAN_4SO(UNSIGNED INT BL743,BL742,BL741,BL740)
{     
      XUAT_1BYTE(BL740);   XUAT_1BYTE(BL741);
      XUAT_1BYTE(BL742);   XUAT_1BYTE(BL743);
      
      MO_4_LED_7DOAN;
      MO_IC_74573_A_THONG_DL();
       
      OUTPUT_LOW(RCK_4LED7DOAN);   OUTPUT_HIGH(RCK_4LED7DOAN); 
      CHOT_IC_74573_A_GOI_DU_LIEU;
}
//ham 404
VOID XUAT_4LED_7DOAN_3SO(UNSIGNED INT BL742,BL741,BL740)
{     
     XUAT_4LED_7DOAN_4SO(0XFF,BL742,BL741,BL740);
}
//ham 403
VOID XUAT_4LED_7DOAN_2SO(UNSIGNED INT BL741,BL740)
{     
     XUAT_4LED_7DOAN_4SO(0XFF,0XFF,BL741,BL740);
}
//ham 402
VOID XUAT_4LED_7DOAN_1SO(UNSIGNED INT BL740)
{     
     XUAT_4LED_7DOAN_4SO(0XFF,0XFF,0XFF,BL740);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 405: CHUONG TRINH CON HIEN THI DU LIEU 16 BIT TREN 4 LED 7 DOAN
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
UNSIGNED CHAR DONVI4,CHUC4,TRAM4,NGAN4;
VOID  XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (UNSIGNED INT16 TAM)
{         
      DONVI4 = MA7DOAN[TAM %10];         
      CHUC4  = MA7DOAN[TAM/10%10];
      TRAM4  = MA7DOAN[TAM/100%10]; 
      NGAN4  = MA7DOAN[TAM/1000%10];       
      IF (NGAN4==0XC0)
      {
         NGAN4=0XFF;
         IF (TRAM4==0XC0)
         {
            TRAM4=0XFF;
            IF (CHUC4==0XC0)   CHUC4=0XFF;
         }
      }
      XUAT_4LED_7DOAN_4SO(NGAN4,TRAM4,CHUC4,DONVI4);   
}

UNSIGNED CHAR DONVI14,CHUC14,TRAM14,NGAN14;
VOID  XUAT_4LED_7DOAN_GIAIMA_XOA_SO02 (UNSIGNED INT16 TAM)
{         
      DONVI14 = MA7DOAN2[TAM %10];         
      CHUC14  = MA7DOAN2[TAM/10%10];
      TRAM14  = MA7DOAN2[TAM/100%10]; 
      NGAN14  = MA7DOAN2[TAM/1000%10];       
      IF (NGAN14==0X40)
      {
         NGAN14=0XFF;
         IF (TRAM14==0X40)
         {
            TRAM14=0XFF;
            IF (CHUC14==0X40)   CHUC14=0XFF;
         }
      }
      XUAT_4LED_7DOAN_4SO(NGAN14,TRAM14,CHUC14,DONVI14);   
}







//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 406: CHUONG TRINH CON HIEN THI DU LIEU 2BYTE TREN 4 LED 7 DOAN
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID  XUAT_4LED_7DOAN_2SO_4LED (UNSIGNED INT8 BH,BL)
{         
      XUAT_4LED_7DOAN_4SO(MA7DOAN[BH/10%10],MA7DOAN[BH%10],MA7DOAN[BL/10%10],MA7DOAN[BL%10]);   
}
UNSIGNED INT8 LCDDATA=0; 
UNSIGNED INT8 LCDCONTROL=0;
UNSIGNED INT8 GLCDDATA=0;
UNSIGNED INT8 GLCDCONTROL=0; 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 701: CHUONG TRINH CON XUAT DU LIEU 4 BYTE RA GLCD VA LCD
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_GLCD_LCD()
{      
    XUAT_1BYTE(GLCDCONTROL);             
    XUAT_1BYTE(GLCDDATA);
    XUAT_1BYTE(LCDCONTROL);       
    XUAT_1BYTE(LCDDATA);      
      
    MO_GLCD_LCD;
    MO_IC_74573_A_THONG_DL();            
    OUTPUT_HIGH(RCK_LCD20X4);     
    OUTPUT_LOW(RCK_LCD20X4);
    CHOT_IC_74573_A_GOI_DU_LIEU;
}
//HAM 702
VOID XUAT_LCD20X4(UNSIGNED INT8 LCD_SIGNAL,LCD_INS_HTHI)
{     
    LCDCONTROL = ~LCD_SIGNAL;
    LCDDATA    = ~LCD_INS_HTHI;      
    XUAT_GLCD_LCD();
}
//HAM 703
VOID XUAT_GLCD128X64(UNSIGNED INT8 GLCD_SIGNAL,GLCD_INS_HTHI)
{     
    GLCDCONTROL = ~GLCD_SIGNAL;
    GLCDDATA    = ~GLCD_INS_HTHI;     
    XUAT_GLCD_LCD();
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 501: CHUONG TRINH CON XUAT 2 BYTE RA DK 1 LED QUET SANG
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_8LED_7DOAN_QUET_1(UNSIGNED INT MA,SO_HTHI)
{     
      XUAT_1BYTE(~MA);   XUAT_1BYTE(~SO_HTHI);
      
      
      MO_IC_74573_B_THONG_DL();
      
      OUTPUT_HIGH(RCK_8LEDQUET); OUTPUT_LOW(RCK_8LEDQUET);
      MO_8_LED_QUET;
      CHOT_IC_74573_B_GOI_DU_LIEU;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 502: CHUONG TRINH CON XUAT 2 BYTE RA TAT 8 LED QUET
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_8LED_7DOAN_QUET_TAT_LED()
{
   XUAT_8LED_7DOAN_QUET_1(0XFF,0XFF);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 503: CHUONG TRINH CON HIEN THI LED THEO THU TU
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
CONST UNSIGNED CHAR TTLEDQUET[8]= {0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
VOID XUAT_8LED_7DOAN_QUET_2(UNSIGNED INT THUTULED,SO_HTHI)
{         
      XUAT_1BYTE(~ (TTLEDQUET[THUTULED]));   XUAT_1BYTE(~SO_HTHI);     
      MO_8_LED_QUET;
      MO_IC_74573_B_THONG_DL();
      OUTPUT_HIGH(RCK_8LEDQUET); OUTPUT_LOW(RCK_8LEDQUET);
      CHOT_IC_74573_B_GOI_DU_LIEU;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 504: CHUONG TRINH CON HIEN THI 8 SO TREN 8 LED QUET - CO KIEM TRA
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
UNSIGNED CHAR LED_7DQ[8]={0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF};
UNSIGNED INT8 TT8LED=0;
VOID HIEN_THI_8LED_7DOAN_QUET()
{     
      FOR(TT8LED=0;TT8LED<8;TT8LED++)
         IF (LED_7DQ[TT8LED]!=0XFF)
         {           
            XUAT_8LED_7DOAN_QUET_2(TT8LED, LED_7DQ[TT8LED]);
            DELAY_US(100);
            XUAT_8LED_7DOAN_QUET_TAT_LED();           
            }
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 505: CHUONG TRINH CON HIEN THI 8 SO TREN 8 LED QUET - KHONG KIEM TRA
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID HIEN_THI_8LED_7DOAN_QUET_ALL()
{     
      FOR(TT8LED=0;TT8LED<8;TT8LED++)         
         {           
            XUAT_8LED_7DOAN_QUET_2(TT8LED, LED_7DQ[TT8LED]);
            DELAY_US(100);
            XUAT_8LED_7DOAN_QUET_TAT_LED();           
            }
}

VOID DELAY_QUET_8LED(UNSIGNED INT16 DL)
{ 
      UNSIGNED INT8 I;
      FOR (I=0; I<DL;I++)
      HIEN_THI_8LED_7DOAN_QUET_ALL();
} 

VOID GIAI_MA_GAN_CHO_8LED_QUET_16_XOA(UNSIGNED INT16 X)
{     
      LED_7DQ[0]= MA7DOAN [X %10];    
      LED_7DQ[1]= MA7DOAN [X/10%10];
      LED_7DQ[2]= MA7DOAN [X/100%10];    
      LED_7DQ[3]= MA7DOAN [X/1000%10];
      LED_7DQ[4]= MA7DOAN [X/10000%10];
      IF (LED_7DQ[4]==MASO0) 
      {
            LED_7DQ[4]=0XFF;
            IF (LED_7DQ[3]==MASO0) 
            {
               LED_7DQ[3]=0XFF;
               IF (LED_7DQ[2]==MASO0) 
               {
                  LED_7DQ[2]=0XFF;
                  IF (LED_7DQ[1]==MASO0) 
                  {
                     LED_7DQ[1]=0XFF;
                  }
               }
            }
      }
            
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         
VOID XUAT_2BYTE(UNSIGNED INT16 BYTE2XUAT)
{
   INT8 SBB;
   UNSIGNED INT16   XX;   //SHORT  BSERI;
   #BIT BSERIX  = XX.15
   XX = BYTE2XUAT;
   FOR (SBB=0;SBB<16;SBB++)
      {                                                 
         OUTPUT_BIT(SSDO,BSERIX);    
         OUTPUT_LOW(SSCK);         OUTPUT_HIGH(SSCK);
         XX= XX<<1;         
     }
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH CON XUAT RA LED MA TRAN
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_MATRANLED(UNSIGNED INT16 MAHANG,UNSIGNED INT16 MACOT1,
UNSIGNED INT16 MACOT2,UNSIGNED INT16 MACOT3)
{      
      XUAT_2BYTE(MACOT3);
      XUAT_2BYTE(MACOT2);
      XUAT_2BYTE(MACOT1);
      XUAT_2BYTE(MAHANG);
      
      MO_LED_MATRAN;
      MO_IC_74573_B_THONG_DL();
      
      OUTPUT_HIGH(RCK_MATRANLED); OUTPUT_LOW(RCK_MATRANLED); 
      CHOT_IC_74573_B_GOI_DU_LIEU;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH CON XUAT RA LED MA TRAN
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID TAT_MATRANLED()
{      
      XUAT_2BYTE(0);
      XUAT_2BYTE(0);
      XUAT_2BYTE(0);
      XUAT_2BYTE(0);           
      OUTPUT_HIGH(RCK_MATRANLED); OUTPUT_LOW(RCK_MATRANLED); 
}
UNSIGNED  INT8 HIEU_CHINH_4BIT_CAO(UNSIGNED INT8 XZY)
{
      INT1  BTG;
      UNSIGNED INT8   BX;   
      #BIT BIT4  = BX.4
      #BIT BIT5  = BX.5
      #BIT BIT6  = BX.6
      #BIT BIT7  = BX.7
      BX=XZY;
      BTG=BIT4;   BIT4=BIT7;  BIT7=BTG;
      BTG=BIT5;   BIT5=BIT6;  BIT6=BTG;      
      RETURN(BX);  
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//HAM 601: MODULE DIEU KHIEN RELAY,TRIAC, BUZZER, DONG CO, SIM
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_BUZZER_RELAY()
{     
   UNSIGNED INT8 RBDC1,RBDC2;
      RBDC1=RBDC; RBDC2=RBDC>>8;      
      XUAT_1BYTE(RBDC2);      XUAT_1BYTE(RBDC1);      
      MO_RELAY_BUZZER_DC;
      MO_IC_74573_B_THONG_DL();
      
      OUTPUT_HIGH(RCK_BUZERRELAY);   OUTPUT_LOW(RCK_BUZERRELAY);
      CHOT_IC_74573_B_GOI_DU_LIEU;
}
//HAM 602
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID BUZZER_ON()
{    
      BUZZER=1;
      XUAT_BUZZER_RELAY();         
}
//HAM 603
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID BUZZER_OFF()
{     
      BUZZER=0;
      XUAT_BUZZER_RELAY();
}
//HAM 604
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_1_ON()
{    
      RELAY_1=1;
      XUAT_BUZZER_RELAY();         
}
//HAM 603
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_1_OFF()
{    
      RELAY_1=0;
      XUAT_BUZZER_RELAY();         
}
//HAM 604
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_2_ON()
{    
      RELAY_2=1;
      XUAT_BUZZER_RELAY();         
}
//HAM 607
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_2_OFF()
{    
      RELAY_2=0;
      XUAT_BUZZER_RELAY();         
}
//HAM 608
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_1_RELAY_2_ON()
{    
      RELAY_1=1;  RELAY_2=1;
      XUAT_BUZZER_RELAY();         
}
//HAM 609
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_1_RELAY_2_OFF()
{    
      RELAY_1=0;  RELAY_2=0;
      XUAT_BUZZER_RELAY();         
}
//HAM 610
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID TRIAC_1_ON()
{    
      TRIAC_1=1;
      XUAT_BUZZER_RELAY();         
}
//HAM 611
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID TRIAC_1_OFF()
{    
      TRIAC_1=0;
      XUAT_BUZZER_RELAY();         
}
//HAM 612
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID TRIAC_2_ON()
{    
      TRIAC_2=1;
      XUAT_BUZZER_RELAY();         
}
//HAM 613
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID TRIAC_2_OFF()
{    
      TRIAC_2=0;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

VOID GGMMAA()
{
   UNSIGNED INT8   X;   
   X=MA7DOAN[1];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// CHUONG TRINH CHONG DOI NUT NHAN
INT1 INPUTTD(INT16 CHAN, INT8 TIME)
{
   IF (!INPUT(CHAN))
   {
      DELAY_MS(TIME);
      IF (!INPUT(CHAN))
      {
         WHILE (!INPUT(CHAN));
         RETURN 0;
      }
   }
   RETURN 1;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH NUT NHAN CO DELAY_HIENTHI LAF VONG LAP CO 8 LED QUET
UNSIGNED INT8 I1;
VOID DELAY_HIENTHI(INT8 TIME)
{
   FOR(I1=0;I1<TIME;I1++)  HIEN_THI_8LED_7DOAN_QUET_ALL();
}
INT1 INPUTTD2(INT16 CHAN, INT8 TIME)
{
   IF (!INPUT(CHAN))
   {
      DELAY_HIENTHI(TIME);
      IF (!INPUT(CHAN))
      {
         WHILE (!INPUT(CHAN));
         RETURN 0;
      }
   }
   RETURN 1;
}

