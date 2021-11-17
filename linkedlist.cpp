#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct liste
{
    int numara;
    char *ad;
    char *soyad;
    struct liste  *sonraki;
    int sayi;
    //struct hanesayisi hane[10];
    
}bliste;
bliste *ilk=NULL,*ptr=NULL,*ptr2=NULL,*temp,*son=NULL,*bironceki=NULL;




void listele()//bagli listeyi listeleyip ekrana yazdiracak eleman
{
    ptr=ilk;
    if(ptr==0)printf("bagli liste bostur");
    else
    while(ptr)
    {
        printf("%d\t%s\t%s\n",ptr->numara,ptr->ad,ptr->soyad);
        ptr=ptr->sonraki;
    }
    
}

int ara(int n)//istenilen degeri listeden arayan fonksiyon
{
  	ptr=ilk;
  	int sayac=0;
  	while(ptr)
  	{
    	if(ptr->numara==n) return sayac+1;
    	else
    	{
    		ptr=ptr->sonraki;
    		sayac++;  
    	}
  	}
  	return 0;
}

bliste *sirala(int a,int b)
{
    ptr2=ilk;
    if(ilk->numara%10!=a)
    for(int i=0;i<b;i++)
	{
    	ptr=ilk;
    	while(ptr!=NULL)
		{
            if(ptr->sonraki!=NULL && ptr->sonraki->numara%10==a)
			{
                bironceki=ptr->sonraki;
                if(ptr->sonraki->sonraki!=NULL)  ptr->sonraki=ptr->sonraki->sonraki;
                else ptr->sonraki=NULL;
                bironceki->sonraki=ilk;
                ilk = bironceki; 
            }
             ptr=ptr->sonraki;
        }
    }   
}
 bliste *siralama()
 {
    int dizi[10],temp,temp2=0,i=0,j,a;
    ptr=ilk;
    //dizinin elemanlarin sifirla
	for(i=0;i<10;i++)dizi[i]=0;
    //son elemanlarin 
    while(ptr!=NULL)
	{
        temp = ptr->numara%10;
        dizi[temp]=dizi[temp]+1;
        ptr=ptr->sonraki;
    }
    for(i=0;i<10;i++)
    {    
        ptr=ilk;
        while(ptr!=NULL)
		{
            if( ptr->numara%10 == i )
			{
                ptr->sayi=dizi[i];
            }
        	ptr=ptr->sonraki;
        }
    }
    for(i=0;i<10;i++)
	{
        temp2=10;
        for(j=0;j<10;j++)
		{
            if(dizi[j]!=0 && temp2>dizi[j])
			{
                temp2=dizi[j];
                temp=j;
            }
        }
        if(temp !=-1)
        sirala(temp,dizi[temp]);
        dizi[temp]=0;
        temp=-1;
	}
        ptr=ilk;
        while(ptr->sonraki!=NULL)ptr=ptr->sonraki;
        son=ptr;
}

void silme(int n)
{
  			ptr=ilk;
  
  		while(ptr)//silinecek degerin konumunu bul
  		{
   			if(ptr->numara==n)break;
    		bironceki=ptr;
    		ptr=ptr->sonraki;
  		}
  		if(ptr!=NULL)
   		{
      		if(ptr==ilk)
      		{
        		if(ilk==son)//silinecek deger basta ve tek eleman ise
        		{
      				ilk=NULL;
        			son=NULL;
        		}
        	else{
            	ilk=ilk->sonraki;//silinecek deger basta ama tek olmayan eleman ise
            	}
        
    		}
    	else if(ptr==son) //silinecek deger son eleman ise
    	{  
     		bironceki->sonraki=NULL;
    		son=bironceki;
    	}	  
    	else{
         	bironceki->sonraki=ptr->sonraki;//silinecek deger ortadan bir eleman ise
      		}
  		}
  
}

   
bliste *bilgial(int num,char ad[],char soyad[])//her yeni gelen kayidi bagli listeye ekleyecek fonksiyon
{
    
    if(ilk==NULL)//ilk eleman ekleme
    {
        ilk=(bliste*)malloc(sizeof(bliste));
        ilk->numara=num;
        ilk->ad=(char*)malloc(sizeof(char));
        for(int i=0;ad[i]!=NULL;i++) *(ilk->ad+i)=ad[i];
        ilk->soyad=(char*)malloc(sizeof(char));
		for(int i=0;soyad[i]!=NULL;i++) *(ilk->soyad)=soyad[i];
        ptr=ilk;
        ilk->sonraki=NULL;
    }
    else
    {
        ptr=ilk;
        ptr2=(bliste*)malloc(sizeof(bliste));
        ptr2->numara=num;
        ptr2->ad=(char*)malloc(sizeof(char));
        for(int i=0;ad[i]!=NULL;i++) *(ptr2->ad+i)=ad[i];
        ptr2->soyad=(char*)malloc(sizeof(char));
        for(int i=0;soyad[i]!=NULL;i++) *(ptr2->soyad+i)=soyad[i];
        while(ptr->sonraki!=NULL)
        {
            if(ptr->sonraki->numara%10==ptr2->numara%10 && ptr->sonraki->numara!=ptr2->numara)
			{
           		ptr2->sonraki=ptr->sonraki;
            	ptr->sonraki=ptr2;    
            	break;
            }
            ptr=ptr->sonraki;
        }
        if(ptr->sonraki==NULL)
		{
		ptr->sonraki=ptr2;
        ptr2->sonraki=NULL;
        son=ptr2;
        }
        siralama();
    }
}

int main()
{
    FILE *dosya;
    dosya=fopen("veridosyasi.txt","r");
    int a;
    char b[13],c[13];
    while(!(feof(dosya)))
    {
    fscanf(dosya,"%d",&a);
    fscanf(dosya,"%s",b);
    fscanf(dosya,"%s",c);
    bilgial(a,b,c);//her gelen kayidi listeye eklemek icin
    } fclose(dosya);
    char secim;
    printf("Veridosyasi ismindeki dosyadan veri okuma islemi basariyla tamamlandi:)\n\n");
    
    do
    {
	printf("\nDevam etmek icin asagidan yapmak istediginiz islemi secin:\n'e'-veri ekleme\n'l'-bagli listeyi ekranimda listele\n'a'-listede arama islemi yap\n's'-listeden deger sil\n'd'-butun islemi sonlandir ve bagli listeyi veridosyasi isimli dosyaya aktar\n");
	printf("Sizin seciminiz)))->");
    secim=getch();
    	switch(secim)
    	{
    		case 'e':	printf("\nNumarasini giriniz:");scanf("%d",&a);
        				printf("\nAdini giriniz:"); scanf("%s",b);
        				printf("\nSoyadini giriniz:"); scanf("%s",c);
        				bilgial(a,b,c);
        				break;
        	case 'l':	listele();
        				break;
        	case 'a':	int aradeger,sonuc;
     					printf("\nListeden aratmak istediginiz degeri giriniz:");
    					scanf("%d",&aradeger);
    					sonuc=ara(aradeger);
    					if(sonuc>0)printf("Aradiginiz deger %d adimda bulundu:)\n",sonuc);
    					else if(sonuc==0)printf("Aradiginiz deger listede bulunmadi:(\n");
    					break;
    		case 's':	int sil;
   						printf("\nListeden silmek istediginiz degeri giriniz:");
    					scanf("%d",&sil);
    					silme(sil);
    					siralama();
    					break;
    		default:	if(secim=='d')
    					printf("\nBagli listeniz basariyla dosyaniza aktarilmistir.Hoscakalin:)");
    					else
						printf("\nMenude olmayan bir secenek yaptiniz..."); break;
		}
	}while(secim!='d');
    
    //butun islemin sonunda dosyaya aktarma
	dosya=fopen("veridosyasi.txt","w");
	ptr=ilk;
	while(ptr)
	{
	fprintf(dosya,"%d\t%s\t%s\n",ptr->numara,ptr->ad,ptr->soyad);
	ptr=ptr->sonraki;
	}   
	fclose(dosya);
    return 0;
}
