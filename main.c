#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>



int main(){
    setlocale(LC_ALL, "Turkish");

    int zemin=zemin_olustur();

    zemin_yaz(zemin);
    menu(zemin);
}

void menu(int** zemin){
    int secim;
    printf("1- Sayi Gir \n2- Sayi Sil\n");
    scanf("%d",&secim);


    switch(secim){
    case 1: oyuncu_secim(zemin,zemin);
        break;
    case 2: deger_sil(zemin);
        break;
}
 return zemin;
}


int deger_sil(int** zemin, int satir, int sutun) { //
    zemin_yaz(zemin);
    int koordinatX,koordinaty;
    do {
        printf("\n Silmek istediginiz koordinati X Y seklinde giriniz:\n");
        scanf("%d %d", &koordinatX, &koordinaty);


        if((koordinatX > 9) || (koordinatX < 1) || (koordinaty> 9) || (koordinaty < 1) ){
            printf ( " \n Hatalı koordinat girişi yaptınız,lütfen uygun koordinatları giriniz \n " );
        }


    }while((koordinatX > 9) || (koordinatX < 1) || (koordinaty> 9) || (koordinaty < 1) );

    zemin [koordinaty-1][koordinatX-1] = 0;
    zemin_yaz(zemin);
    return zemin;
}


int zemin_olustur() {
    int i,j;
    int** zemin;
    int zemin_dizi[9][9] = {  5, 3, 0,   0, 7, 0,   0, 0, 0,
                              6, 0, 0,   1, 9, 5,   0, 0, 0,
                              0, 9, 8,   0, 0, 0,   0, 6, 0,

                              8, 0, 0,   0, 6, 0,   0, 0, 3,
                              4, 0, 0,   8, 0, 3,   0, 0, 1,
                              7, 0, 0,   0, 2, 0,   0, 0, 6,

                              0, 6, 0,   0, 0, 0,   2, 8, 0,
                              0, 0, 0,   4, 1, 9,   0, 0, 5,
                              0, 0, 0,   0, 8, 0,   0, 7, 9,  };

    zemin = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        zemin[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            zemin[i][j] = zemin_dizi[i][j];
        }
    }


    return zemin;
}


void zemin_yaz(int** zemin){
    int i, j, k;

   printf("\n");
   printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n");
   printf(" ---------------------------------\n") ;
   for (i=0, k = 1; i < 9; i++, k++){
       for (j=0; j < 9; j++){
            if (j == 0)
               printf(" %d |", k);
            else if ((j) % 3 == 0)
                printf("|");
            printf(" %d ", zemin[i][j]);
            if (j == 8)
                printf("|");
       }
       printf("\n");
       if ((i + 1) % 3 == 0)
           printf(" ---------------------------------\n");
   }
   printf(" Y\n");
}

bool kontrol_et(int** zemin, int satir, int sutun) { //
    int i, j;

    for (i = 0; i < 9; i++) {
        for ( j = 0; j < 9; j++){
             if (zemin [i][j] == 0) {
                 satir = i;
                 sutun = j;
                  return true;
             }
        }
    }

    return false;
}


bool hucre_kontrol_et(int** zemin, int satir, int sutun, int deg) {
     int i, j;
     int kare_satir, kare_sutun;

     //Satırı kontrol et
     for(j=0; j < 9; j++) {
            if (zemin[satir][j] == deg)
               return false;
     }

     //Sutunu kontrol et
     for (i = 0; i < 9; i++) {
         if (zemin[i][sutun] == deg)
             return false;
     }

     //Hüceyi kontrol et
     kare_satir = satir - satir % 3;
     kare_sutun = sutun - sutun % 3;

     for (i = kare_satir; i < kare_satir + 3; i++) {
        for (j = kare_sutun; j < kare_sutun + 3; j++) {
            if (zemin[i][j] == deg){
                printf("sonuc: %d",zemin[i][j]);
                return false;}
        }
     }

     return true;

}

int kopyala_zemin (int** zemin) {
    int i, j;
    int** yeni_zemin;

    yeni_zemin = (int**)malloc(sizeof(int*) * 9);
    for (i = 0; i < 9; i++) {
        yeni_zemin[i] = (int*)malloc(sizeof(int) *9);
        for(j = 0; j < 9; j++) {
                yeni_zemin [i][j] = zemin[i][j];
        }
    }
    return yeni_zemin;

}

void oyuncu_secim (int** oyuncu_zemin, int** gecici_zemin) {
    zemin_yaz(oyuncu_zemin);
    int i, j;
    int koordinatX, koordinaty, oyuncuDeg;
    char c;

    while(1){
    if (!kontrol_et (oyuncu_zemin, &i, &j)) {
         printf("\TEBRIKLER OYUNU BASARIYLA TAMAMLADINIZ!\n");
         return;
    }



    do{
        printf("\n Girmek istediginiz koordinati X Y seklinde giriniz:\n");
        scanf("%d %d", &koordinatX, &koordinaty);


        if((koordinatX > 9) || (koordinatX < 1) || (koordinaty> 9) || (koordinaty < 1) || (oyuncu_zemin[koordinaty - 1][koordinatX - 1] != 0)){
            printf ( " \n Hatali koordinat girisi yaptiniz,lutfen uygun koordinatlari giriniz \n " );
        }
         else {
               koordinatX -= 1 ;
               koordinaty -= 1 ;
            break ;
         }

    }while((koordinatX > 9) || (koordinatX < 1) || (koordinaty> 9) || (koordinaty < 1) || (oyuncu_zemin[koordinaty - 1][koordinatX - 1] != 0));



    do{
        printf ( " \n Lutfen 1 ile 9 arasi bir deger giriniz (1 ve 9 dahil) \n " );
            scanf ( " %d" , &oyuncuDeg);

    }while((oyuncuDeg > 9 ) || (oyuncuDeg < 1 ));

        if  (hucre_kontrol_et(oyuncu_zemin, koordinaty, koordinatX, oyuncuDeg)){
            oyuncu_zemin[koordinaty][koordinatX] = oyuncuDeg;

        }
        else
            printf ( " \n HATALI SAYI GIRDINIZ! %d %d\n " ,koordinatX + 1 , koordinaty + 1 );

        for (i = 0 ; i < 9 ; i++){
            for (j = 0 ; j < 9 ; j++){
                gecici_zemin[i][j] = oyuncu_zemin[i][j];
            }
        }


    getchar();
    zemin_yaz(oyuncu_zemin);
    menu(oyuncu_zemin);
    }
}















