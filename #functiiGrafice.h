#include <fstream>
#include <cmath>
#include <cstring>
#include <graphics.h>
#include <winbgim.h>


void NumarInSir(tipDate numar,char sir[30]);

void TransformareLiniara(tipDate a,tipDate b,tipDate capat1,tipDate capat2,tipDate &m,tipDate &n);
void AflareMaxSiMin(stiva expresie,tipDate a,tipDate b,tipDate k,tipDate &yMin,tipDate &yMax);
void ReprezentareGrafic(stiva expresie,tipDate a,tipDate b);
void DesenareCareu(int stanga,int dreapta,int sus,int jos);
void DesenareAxeDeCoordonate(stiva functie,int stanga,int dreapta,int sus,int jos,tipDate a,tipDate b,int distantaSageata);

void NumarInSir(tipDate numar,char sir[30])
{
    int copie,numarCifre=0,i;
    if(numar<0)
    {
        numar*=-1;
        ++numarCifre;
        sir[0]='-';
    }
    copie=int(numar);
    do
    {
        ++numarCifre;
        copie/=10;
    }
    while(copie);
    sir[numarCifre]=0;
    i=numarCifre;
    copie=int(numar);
    do
    {
        sir[--numarCifre]=copie%10+48;
        copie/=10;
    }
    while(copie);
    copie=int((numar-int(numar))*1000);
    if(copie)
    {
        sir[i]='.';
        sir[i+4]=0;
        i+=4;
        while(copie)
        {
            sir[--i]=copie%10+48;
            copie/=10;
        }
    }
}
void TransformareLiniara(tipDate a,tipDate b,tipDate capat1,tipDate capat2,tipDate &m,tipDate &n)
{
    if(a!=b)
        m=(capat1-capat2)/(a-b);
    else
        m=1;
    n=capat1-m*a;
}
void AflareMaxSiMin(stiva functie,tipDate a,tipDate b,tipDate &yMin,tipDate &yMax)
{
    tipDate val,k=0.125;
    /// k=0.125
    ///Aleg valoarea 0.125 deoarece aceasta poate fi reprezentata exact de catre calculator.
    ///Prima data am ales valoarea 0.1 ,dar aceasta este 0.1[10]=0.0(0011)[2] care nu poate fi
    ///reprezentata corect pe PC, indiferent de cat de multa memorie ai ,si ,din cauza asta,
    ///cand aflam minimul si maximul pentru (x-2)^2 pe [-10,10] ,imi dadea valori incorecte,
    ///in loc de 0 imi dadea 1.23e-23 si la maxim putea sa dea ceva diferit de 12^2
    yMin=yMax=EvaluareExpresie(functie,a);
    a+=k;
    while(a<=b)
    {
        val=EvaluareExpresie(functie,a);
        if(yMin>val)
            yMin=val;
        if(yMax<val)
            yMax=val;
        a+=k;
    }
}
void DesenareCareu(int stanga,int dreapta,int sus,int jos)
{
    line(stanga,sus,dreapta,sus);
    line(stanga,jos,dreapta,jos);
    line(stanga,sus,stanga,jos);
    line(dreapta,sus,dreapta,jos);
}
void DesenareAxeDeCoordonate(stiva functie,int stanga,int dreapta,int sus,int jos,tipDate a,tipDate b,int distantaSageata)
{
    tipDate m1,m2,n1,n2,x1,x2,y1,y2,valSegment,valPunct1,valPunct2;
    int lungimeSageata=10,lungimeSegmentEcran,nrSegmente,raza=2,i,stangaCopie,dreaptaCopie,josCopie,susCopie;
    char Sir[30];
    stangaCopie=stanga;
    dreaptaCopie=dreapta;
    josCopie=jos;
    susCopie=sus;
    stanga+=distantaSageata;
    dreapta-=distantaSageata;
    jos-=distantaSageata;
    sus+=distantaSageata;
    nrSegmente=5; ///pe o latura
    if(jos-sus>dreapta-stanga)
        lungimeSegmentEcran=((jos-sus)/2)/nrSegmente;
    else
        lungimeSegmentEcran=((dreapta-stanga)/2)/nrSegmente;
    valSegment=1.0*(b-a)/(2*nrSegmente);
    TransformareLiniara(a,b,stanga,dreapta,m1,n1);
    TransformareLiniara(a,b,jos,sus,m2,n2);
    ///DesenareCareu(stangaCopie,dreaptaCopie,susCopie,josCopie);
    /// axa Oy
    x1=x2=n1;
    y1=susCopie;
    y2=josCopie;
    setcolor(BLACK);
    line(x1,y1,x2,y2);
    ///Grid
    setcolor(7);
    for(i=1; i<=dreapta; i=i+lungimeSegmentEcran)
    {
        if(i!=dreapta/2)
            line(i+28, 40, i+28, jos+40);
    }
    for(i=57; i<=jos; i+=lungimeSegmentEcran)
    {
        line(0, i+40, dreapta+29, i+40);
    }
    setcolor(BLACK);
    /// Sageata
    for(i=1; i<=lungimeSageata; ++i)
    {
        line(x1-i,y1+lungimeSageata,x1,y1);
        line(x1+i,y1+lungimeSageata,x1,y1);
    }
    ///Segmente
    x1=x2=n1;
    y1=y2=n2;
    valPunct1=valPunct2=0;
    while(1)
    {
        y1-=lungimeSegmentEcran;
        y2+=lungimeSegmentEcran;
        valPunct1+=valSegment;
        valPunct2-=valSegment;
        circle(x1,y1,raza);
        circle(x2,y2,raza);
        NumarInSir(valPunct1,Sir);
        outtextxy(x1-textwidth(Sir)-raza-4,y1-textheight(Sir)/2,Sir);
        NumarInSir(valPunct2,Sir);
        outtextxy(x2-textwidth(Sir)-raza-4,y2-textheight(Sir)/2,Sir);
        if(y1-lungimeSegmentEcran<sus)
            break;
        ///posibil bug la conditia asta in cazul in care lungimeEcran e numar real
    }
    /// axa Ox
    y1=y2=n2;
    x1=stangaCopie;
    x2=dreaptaCopie;
    line(x1,y1,x2,y2);
    /// Sageata
    for(i=1; i<=lungimeSageata; ++i)
    {
        line(x2-lungimeSageata,y2-i,x2,y2);
        line(x2-lungimeSageata,y2+i,x2,y2);
    }
    ///Segmente

    x1=x2=n1;
    y1=y2=n2;
    valPunct1=valPunct2=0;
    while(1)
    {
        x1-=lungimeSegmentEcran;
        x2+=lungimeSegmentEcran;
        valPunct1-=valSegment;
        valPunct2+=valSegment;
        circle(x1,y1,raza);
        circle(x2,y2,raza);
        NumarInSir(valPunct1,Sir);
        outtextxy(x1-textwidth(Sir)/2,y1+raza+4,Sir);
        NumarInSir(valPunct2,Sir);
        outtextxy(x2-textwidth(Sir)/2,y2+raza+4,Sir);
        if(x2+lungimeSegmentEcran>dreapta)
            break;
    }
    ///Originea
    circle(n1,n2,raza);
    outtextxy(n1-textwidth("0")-4,n2+raza+4,"0");
}
void ReprezentareGrafic(stiva functie,tipDate a,tipDate b)
{
    /*
    Puteri ale lui 0.5
    0.5
    0.25
    0.125
    0.0625
    0.03125
    0.015625
    0.0078125
    0.00390625 ----
    0.001953125
    0.0009765625
    */
    tipDate xCapat,yVal,xVal,yValCurenta,yValPrec,epsilon=0.5,yMax,yMin,m1,n1,m2,n2,stanga,dreapta,sus,jos,distantaCareu=0,distantaPuncte;
    tipDate m,n,alfa;
    int x1,y1,x2,y2,culoareGrafic,culoareBk,latime,inaltime,distantaSageata,nrSegmente=10;

    distantaSageata=30;
    latime=800;
    inaltime=600;
    distantaPuncte=1.0*(b-a)/(nrSegmente);
    /// distantaPuncte se refera la distanta pe care o pun de la x si x + distantaPuncte ca sa vad
    ///cat de multi pixeli sunt intre f(x) si f(x+distantaPuncte) si sa pot alege un epsilon bun
    culoareGrafic=3; //BLUE
    /*
    stanga=sus=distantaEcran;
    dreapta=latime-distantaEcran;
    jos=inaltime-distantaEcran;
    */
    stanga=0;
    dreapta=latime;
    sus=40;
    jos=inaltime;
    AflareMaxSiMin(functie,a,b,yMin,yMax);
    //DesenareCareu(stanga,dreapta,sus,jos);
    stanga+=distantaCareu;
    dreapta-=distantaCareu;
    sus+=distantaCareu;
    jos-=distantaCareu;
    if(esteBuna==true)
    {
        DesenareAxeDeCoordonate(functie,stanga,dreapta,sus,jos,a,b,distantaSageata);
        /// * -> functia desenare axe va face in zona pusa graficul functie pe intervalul [a,b]
        ///dar aceasta va face loc si pentru sagetile de la axele Ox si Oy
        TransformareLiniara(a,b,stanga+distantaSageata,dreapta-distantaSageata,m1,n1);
        TransformareLiniara(a,b,jos-distantaSageata,sus+distantaSageata,m2,n2);

        setcolor(culoareGrafic); ///-------------------

        /// abs(y2-y1)=e*sqrt(1+m*m)
        xVal=a;
        x1=m1*xVal+n1;

        yValCurenta=EvaluareExpresie(functie,xVal);
        y1=m2*yValCurenta+n2;
        if(yValCurenta>=a&&yValCurenta<=b)
            circle(x1,y1,1);   ///putpixel(x1,y1,culoareGrafic); ///circle(x1,y1,1);
        while(xVal<=b)
        {
            ///distanta y1 si y2 =1 abs(y2-y1)=1 x1 x1+e
            x2=m1*(xVal+epsilon)+n1;
            yValCurenta=EvaluareExpresie(functie,xVal+epsilon);
            y2=m2*yValCurenta+n2;
            m=fabs((y2-y1)/(m1*epsilon));
            m=1/(sqrt(1+m*m)*abs(m2));
            xVal+=m;
            x2=m1*xVal+n1;
            yValCurenta=EvaluareExpresie(functie,xVal);
            y2=m2*yValCurenta+n2;
            if(yValCurenta>=a&&yValCurenta<=b)
                circle(x2,y2,1);   ///putpixel(x2,y2,culoareGrafic); ///circle(x2,y2,1);
            y1=y2;
        }
    }
    else
        {
            settextstyle(0, 0 , 4);
            setcolor(RED);
            outtextxy(50, 250, "FUNCTIA NU ESTE VALIDA");
            setcolor(BLACK);
            settextstyle(0, 0 , 0);
            esteBuna=true;
        }
    getch();
    //closegraph();
}
