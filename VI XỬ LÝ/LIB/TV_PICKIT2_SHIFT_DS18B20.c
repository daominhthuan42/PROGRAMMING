#DEFINE     TOUCH_PIN PIN_A5
#INCLUDE    <TOUCH.c>
#DEFINE       SKIP_ROM              0xCC
#DEFINE       CONVERT_T             0x44
#DEFINE       READ_SCRATCHPAD       0xBE
#DEFINE       WRITE_SCRATCHPAD      0x4E
#DEFINE       COPY_SCRATCHPAD       0x48    
UNSIGNED INT8     DS18AL, DS18AH, DS18A_TAM;
UNSIGNED INT16    DS18A;
INT32 NGUYEN,TP,T;
VOID  KHOI_TAO_DS18B20(UNSIGNED CHAR DOPHANGIAI)
{                         
      TOUCH_PRESENT();
      TOUCH_WRITE_BYTE(SKIP_ROM);      
      TOUCH_WRITE_BYTE(WRITE_SCRATCHPAD);    
      TOUCH_WRITE_BYTE(0x0);       // ghi 2 byte rong
      TOUCH_WRITE_BYTE(0x0);       //
      TOUCH_WRITE_BYTE(DOPHANGIAI);      //THAY DOI CAU HINH THAY DOI NGAY CHO NAY

      TOUCH_PRESENT();
      TOUCH_WRITE_BYTE(SKIP_ROM);      
      TOUCH_WRITE_BYTE(COPY_SCRATCHPAD); 
}
VOID  DOC_GIATRI_DS18B20(UNSIGNED INT32 HESO)
{ 
      TOUCH_PRESENT();
      TOUCH_WRITE_BYTE(SKIP_ROM);
      TOUCH_WRITE_BYTE (CONVERT_T);   
      TOUCH_PRESENT();
      TOUCH_WRITE_BYTE(SKIP_ROM);
      TOUCH_WRITE_BYTE(READ_SCRATCHPAD);  
      DS18AL = TOUCH_READ_BYTE();
      DS18AH = TOUCH_READ_BYTE();      
      DS18A   =  MAKE16(DS18AH,DS18AL);   
      NGUYEN = DS18A>>4;
      TP = (DS18A&0X000F)*HESO/16;
      T=(INT32)DS18A*625;
      //9 BIT NHAN 10
      //10 BIT LA NHAN 100
      //11 BIT LA NHAN 1000
      //12 BIT NHAN 10000
}
            

