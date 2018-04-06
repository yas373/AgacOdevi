//
//  main.c
//  AgacOdevi
//
//  Created by Yasin Turpcu on 5.04.2018.
//  Copyright © 2018 Yasin Turpcu. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SENTINEL -100000000

struct dugum {
    int icerik;
    struct dugum *sol;
    struct dugum *sag;
};

struct ikili_arama_agaci{
    struct dugum *kok;
};

void ikili_arama_agaci_olustur(struct ikili_arama_agaci **agac){
    *agac=(struct ikili_arama_agaci*)malloc(sizeof(struct ikili_arama_agaci));
    if(*agac==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    (*agac)->kok=NULL;
}


struct dugum* dugum_olustur(int icerik){
    struct dugum *d = (struct dugum*)malloc(sizeof(struct dugum));
    if(d==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    d->icerik = icerik;
    d->sol=d->sag=NULL;
    return d;
}


void ekle(struct ikili_arama_agaci *agac,int icerik){
    struct dugum *dugum;
    struct dugum *d;
    struct dugum *geri;
    
    d=agac->kok;
    while(d!=NULL){
        geri=d;
        if(icerik < d->icerik) d=d->sol;
        else if(icerik > d->icerik) d= d->sag;
        else return;
    }
    dugum=dugum_olustur(icerik);
    if(agac->kok==NULL){
        agac->kok = dugum;
        return;
    }
    if(icerik < geri->icerik) geri->sol = dugum;
    else geri->sag = dugum;
    
}
static int toplam =0;

void hesapla(struct dugum *kok, int derinlik){
    
    if(kok==NULL) return;
    if(kok->sag != NULL || kok->sol != NULL){
        derinlik++;
        if(kok->sol != NULL){
            toplam =toplam + derinlik;
            hesapla(kok->sol,derinlik);
        }
        
        if(kok->sag != NULL)
        {
            toplam =toplam + derinlik;
            hesapla(kok->sag,derinlik);
        }
    }
    
}

void listele(struct dugum* node)
{
    if (node == NULL)
        return;
    
    listele(node->sol);
    
    printf("%d ", node->icerik);
    
    listele(node->sag);
}

int main(int argc, char** argv) {
    struct ikili_arama_agaci *agac;
    ikili_arama_agaci_olustur(&agac);
    int i =0;
    int n =0;
    int r = 0;
    printf("Bir sayi giriniz : ");
    scanf("%d",&n);
    srand(time(NULL));
    for (i=0;i<n;i++)
    {
        
        r = rand()%1000;
        printf("%d \n",r);
        ekle(agac,r);
    }
    hesapla(agac->kok,0);
    printf("Inorder Siralanmis Hali : \n");
    listele(agac->kok);
    printf("\nToplam : %d \n",toplam/n);
    return (EXIT_SUCCESS);
}

