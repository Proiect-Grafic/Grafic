#include <iostream>
#include <fstream>
#include <cstring>
#include <graphics.h>
#include <cmath>
#include <cstring>
#include <stdio.h>
#define MAX_LUNGIME 100
#define MAX_CUVANT 10
#define scale 1.01
#include "eval.h"
#include "functiiGrafice.h"
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct punct
{
    int x, y;
};
struct functie
{
    char s[101];

} f;

void CitireValoare(double &val);
void CitireFunctie(char functie[MAX_LUNGIME]);
void citesteSir(char s[MAX_LUNGIME],int x, int y);
double Calculeaza(double val1,double val2,char operatie);
void scalare(double lungime, double inaltime);
void desenInterfata(double lungime, double intaltime,stiva expresie);
void meniu(double lungime,double inaltime,stiva fct);
void zoom(double x1, double y1, double x2, double y2);
void reload(double lungime,double inaltime,stiva expresie);

int main()
{

    double inaltime, lungime;
    int x, y;
    char functie[MAX_LUNGIME];
    double val;

    fin>>lungime;
    fin>>inaltime;

    stiva expresie;
    InitializareStiva(expresie);

    initwindow(800, 600);
    meniu(lungime, inaltime,expresie);
    reload( lungime, inaltime, expresie);
    //desenInterfata(lungime, inaltime,expresie);

    getch();
    closegraph();
    return 0;
}

void meniu(double lungime, double inaltime,stiva fct)
{
    bool limba=0;//verifica daca e deschis meniul de limbi
    char limbaButon='R';//memoreaza limba selectata
    bool esteApasat=0;//memoreaza dc este apasat butonul principal
    POINT CursorPosition;
    readimagefile("bckbround.jpg", 0, 0, 800, 600);
    readimagefile("buton.jpg", 300, 150, 500, 225);
    readimagefile("romania.jpg", 700, 15, 775, 50);
    while(1)
    {
        GetCursorPos(&CursorPosition);
        if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=15&&CursorPosition.y<=50)//meniu de limbi
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(esteApasat==0)
                {
                    limba=1;
                    readimagefile("buton.jpg", 300, 150, 500, 225);
                    readimagefile("usa.jpg", 700, 65, 775, 100);
                    readimagefile("germana.jpg", 700, 115, 775, 150);
                    readimagefile("franceza.jpg", 700, 165, 775, 200);
                }

            }

        if(esteApasat==0)
        {
            if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=15&&CursorPosition.y<=50)
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    readimagefile("buton.jpg", 300, 150, 500, 225);
                    limbaButon='R';//romana
                }
            if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=65&&CursorPosition.y<=100&& limba==1)//schimbarea limbii pt butoane
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    readimagefile("butonen.jpg", 300, 150, 500, 225);
                    limbaButon='E';//engleza
                }
            if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=115&&CursorPosition.y<=150&& limba==1)
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    readimagefile("butonde.jpg", 300, 150, 500, 225);
                    limbaButon='D';//germana
                }
            if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=165&&CursorPosition.y<=200&& limba==1)
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    readimagefile("butonfr.jpg", 300, 150, 500, 225);
                    limbaButon='F';//franceza
                }
            if(CursorPosition.x >=300&&CursorPosition.x<=500&&CursorPosition.y>=150&&CursorPosition.y<=225)//hover pt butoane
            {
                {
                    if(limbaButon=='R')
                        readimagefile("buton2.jpg", 300, 150, 500, 225);
                    if(limbaButon=='E')
                        readimagefile("butonen2.jpg", 300, 150, 500, 225);
                    if(limbaButon=='D')
                        readimagefile("butonde2.jpg", 300, 150, 500, 225);
                    if(limbaButon=='F')
                        readimagefile("butonfr2.jpg", 300, 150, 500, 225);
                }
            }
            else//de-hover pt butoane
            {
                {
                    if(limbaButon=='R')
                        readimagefile("buton.jpg", 300, 150, 500, 225);
                    if(limbaButon=='E')
                        readimagefile("butonen.jpg", 300, 150, 500, 225);
                    if(limbaButon=='D')
                        readimagefile("butonde.jpg", 300, 150, 500, 225);
                    if(limbaButon=='F')
                        readimagefile("butonfr.jpg", 300, 150, 500, 225);
                }
            }
        }
        if(CursorPosition.x >=300&&CursorPosition.x<=500&&CursorPosition.y>=150&&CursorPosition.y<=225)
            if(GetAsyncKeyState(VK_LBUTTON))//butonul care duce la grafic
            {
                esteApasat=1;
                delay(500);
                cleardevice();
                desenInterfata(lungime, inaltime,fct);
                break;
            }

    }
}

void citesteSir(char s[MAX_LUNGIME],int x, int y)
{
    setbkcolor(WHITE);
    strcpy(s,"");
    char s1[MAX_LUNGIME];
    char t[2];
    char tasta;
    t[0]=tasta;
    t[1]='\0';
    strcpy(t, "");
    strcpy(s,t);
    strcpy(s1,s);
    strcat(s1,"_");
    setcolor(BLACK);//
    outtextxy(x,y,s1);
    do
    {
        tasta=getch();
        if (tasta==8) // backspace
            if (strlen(s)>0)
            {
                setcolor(WHITE);
                strcpy(s1,s);
                strcat(s1,"_");
                outtextxy(x,y,s1);
                s[strlen(s)-1]='\0';
                strcpy(s1,s);
                strcat(s1,"_");
                outtextxy(x,y,s1);
                setcolor(BLACK);//
                outtextxy(x,y,s1);
            }
            else
                Beep(1000,100);
        else
        {
            t[0]=tasta;
            t[1]='\0';
            strcat(s,t);
            strcpy(s1,s);
            strcat(s1,"_");
            setcolor(BLACK);//
            outtextxy(x,y,s1);
        }
    }
    while (tasta!=13);
    t[0]=tasta;
    t[1]='\0';
    strcat(s,t);
    strcpy(s1,s);
    strcat(s1,"_");
    setcolor(BLACK);//
    outtextxy(x,y,s1);
    strcpy(s, s1);

}

void desenInterfata(double lungime, double inaltime, stiva expresie)
{
    stiva S;
    InitializareStiva(S);
    InitializareStiva(expresie);

    POINT CursorPosition;

    readimagefile("grid01.jpg", 0, 0, 800, 600);
    readimagefile("chenar-titlu-01.jpg", 0, 0, 800, 40);
    readimagefile("functie-01.jpg", 320, 10, 390, 40);
    //readimagefile("reload-01.jpg", 240, 10, 280, 30);

    citesteSir(f.s, 400, 15);

    SpatiereSir(f.s);
    ExtragereCuvinte(f.s,S);
    AflareExpresiePostfixata(S,expresie);


    tipDate a,b;
    a=-10;
    b=10;
    ReprezentareGrafic(expresie,a,b);

    while(1)
    {
        if(getch()=='r')
        {
            cleardevice();
            desenInterfata(lungime, inaltime, expresie);
            break;
        }
    }


    //zoom(-1, -1, 800, 600);

    /*while(1)
    {

        GetCursorPos(&CursorPosition);
        if(CursorPosition.x >=0&&CursorPosition.x<=200&&CursorPosition.y>=0&&CursorPosition.y<=39)
            if(GetAsyncKeyState(VK_LBUTTON))
                meniu(lungime, inaltime,expresie);

    }*/

}

void zoom(double x1, double y1, double x2, double y2)
{
    while(getch()!= 27)
    {
        if(getch()=='q')
        {
            x1=x1*scale;
            x2=x2*scale;
            y1=y1*scale;
            y2=y2*scale;
            readimagefile("grid-01.jpg", x1, y1, x2, y2);
            readimagefile("chenar-titlu-01.jpg", 0, 0, 800, 39);
            //zoom(x1, y1, x2, y2);
        }
        if(getch()=='e')
        {
            x1=x1/scale;
            x2=x2/scale;
            y1=y1/scale;
            y2=y2/scale;
            readimagefile("grid-01.jpg", x1, y1, x2, y2);
            readimagefile("chenar-titlu-01.jpg", 0, 0, 800, 39);
            //zoom(x1, y1, x2, y2);
        }
    }

}
void reload(double lungime,double inaltime,stiva expresie)
{
    bool ok=false;
    int x, y;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>=240 && x<=280 && y>=10 && y<=30)
            {
                cleardevice();
                desenInterfata(lungime,  inaltime,  expresie);
            }
        }
    }
}
