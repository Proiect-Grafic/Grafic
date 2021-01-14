#include <iostream>
#define MAX_LUNGIME 100
#define MAX_CUVANT 10
#define PI 3.141592
#define e  2.718281
#define inf 32767
typedef double tipDate;

bool esteBuna=true;
struct elementStiva
{
    char cuvant[MAX_CUVANT];
    tipDate val;
    elementStiva *prec;
};
struct stiva
{
    elementStiva *varf;
};

void CitireFunctie(char functie[MAX_LUNGIME]);
void CitireValoare(tipDate &val);
void CitireInterval(tipDate &a,tipDate &b);

void InitializareStiva(stiva & S);
bool StivaEsteVida(stiva S);
void AdaugareStiva(stiva & S,elementStiva *elemNou);
void StergereVarf(stiva &S);
void CitireVarf(stiva S,elementStiva* &elem);
void InversareStiva(stiva &S);
void AfisareStiva(stiva S);
void CopieStiva(stiva S,stiva &copie);
void AtribuireValoare(elementStiva &elem);

char TipulCaracterului(char caracter);
int Prioritate(elementStiva elem);
void CitireFunctie(char functie[MAX_LUNGIME]);
void CitireValoare(tipDate &val);
void CitireInterval(tipDate &a,tipDate &b);
void SpatiereSir(char sir[MAX_LUNGIME]);
void ExtragereCuvinte(char sir[MAX_LUNGIME],stiva & S);
void AflareExpresiePostfixata(stiva &cuvinte,stiva &expresie);
tipDate EvaluareExpresie(stiva expresie,tipDate x);

tipDate Calculeaza(tipDate val1,tipDate val2,char operatie);
bool AplicareOperator(stiva &termeni,elementStiva* operatie);
bool AplicareFunctie(stiva &termeni,elementStiva* elem);

void CitireInterval(tipDate &a,tipDate &b)
{
    printf("Introduceti intervalul functiei : \n");
    printf("a = ");
    std::cin>>a;
    printf("b = ");
    std::cin>>b;
}
void CitireValoare(tipDate &val)
{
    printf("Valoarea lui x = ");
    std::cin>>val;
}

void InitializareStiva(stiva & S)
{
    S.varf=NULL;
}
bool StivaEsteVida(stiva S)
{
    return S.varf==NULL;
}
void AdaugareStiva(stiva & S,elementStiva *elemNou)
{
    elementStiva *elem;
    elem=new elementStiva;
    strcpy(elem->cuvant,elemNou->cuvant);
    elem->val=elemNou->val;
    elem->prec=NULL;
    if(StivaEsteVida(S))
    {
        S.varf=elem;
    }
    else
    {
        elem->prec=S.varf;
        S.varf=elem;
    }
}
void StergereVarf(stiva &S)
{
    elementStiva *elem;
    if(!StivaEsteVida(S))
    {
        elem=S.varf;
        S.varf=S.varf->prec;
        delete elem;
    }
}
void CitireVarf(stiva S,elementStiva* &elem)
{
    if(StivaEsteVida(S))
        elem=NULL;
    else
        elem=S.varf;
}
tipDate Calculeaza(tipDate val1,tipDate val2,char operatie)
{
    if(operatie=='+')
        return val1+val2;
    if(operatie=='-')
        return val1-val2;
    if(operatie=='*')
        return val1*val2;
    if(operatie=='/')
    {
        if(val2==0)
            return inf;
        return val1/val2;
    }
    if(operatie=='^')
    {
        if(val1<0&&int(val2)!=val2)
            return inf;
        if(val1==0&&val2==0)
            return inf;
        if(val1==0&&val2<0)
            return inf;
        if(val1==0||val1==1)
            return val1;
        return pow(val1,val2);
    }
    if(operatie=='<')
        return val1<val2;
    if(operatie=='>')
        return val1>val2;
    if(operatie=='=')
        return val1==val2;
    if(operatie=='#')
        return val1!=val2;
    if(operatie==char(243)) /// <=
        return (val1<=val2);
    if(operatie==char(242)) /// >=
        return (val1>=val2);
    return 0;
}
bool AplicareOperator(stiva &termeni,elementStiva* operatie)
{
    char op=operatie->cuvant[0],op2=operatie->cuvant[1];
    elementStiva *elem1,*elem2;
    tipDate val=0;
    if(op2!=0)
    {
        if(op=='=')
        {
            char aux;
            aux=op;
            op=op2;
            op2=aux;
        }
        if(op=='<')
            op=243; /// <=
        else if(op=='>')
            op=242; /// >=
    }
    CitireVarf(termeni,elem2);
    StergereVarf(termeni);
    CitireVarf(termeni,elem1);
    StergereVarf(termeni);
    val=Calculeaza(elem1->val,elem2->val,op);
    if(val==inf)
        return false;
    elem1->val=val;
    AdaugareStiva(termeni,elem1);
    return true;
}
bool AplicareFunctie(stiva &termeni,elementStiva* elem)
{
    elementStiva *elem1,*elem2;
    CitireVarf(termeni,elem2);
    StergereVarf(termeni);
    if(strcmp(elem->cuvant, "cos")==0)
    {
        elem->val=cos(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "sin")==0)
    {
        elem->val=sin(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "cosh")==0)
    {
        elem->val=cosh(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "sinh")==0)
    {
        elem->val=sinh(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "exp")==0)
    {
        elem->val=exp(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "ceil")==0)
    {
        elem->val=ceil(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "floor")==0)
    {
        elem->val=floor(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "abs")==0)
    {
        elem->val=abs(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "tan")==0 || strcmp(elem->cuvant, "tg")==0)
    {
        elem->val=tan(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "tanh")==0)
    {
        elem->val=tanh(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "ctg")==0)
    {
        tipDate sinx, cosx;
        sinx=sin(elem2->val);
        cosx=cos(elem2->val);
        if(sinx==0)
            return false;
        elem->val=(cosx/sinx);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "arcsin")==0)
    {
        elem->val=asin(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "arccos")==0)
    {
        elem->val=acos(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "arctg")==0)
    {
        elem->val=atan(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "ln")==0)
    {
        if(elem2->val<=0)
            return false;
        elem->val=log(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "log")==0)
    {
        if(elem2->val<=0)
            return false;
        elem->val=log2(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "sqrt")==0)
    {
        elem->val=sqrt(elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    CitireVarf(termeni,elem1);
    StergereVarf(termeni);
    if(strcmp(elem->cuvant, "min")==0)
    {
        elem->val=std::min(elem1->val,elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    if(strcmp(elem->cuvant, "max")==0)
    {
        elem->val=std::max(elem1->val,elem2->val);
        AdaugareStiva(termeni, elem);
        return true;
    }
    esteBuna=false;
    return false;
}
void InversareStiva(stiva &S)
{
    stiva InversaS;
    elementStiva *elem;
    InitializareStiva(InversaS);
    while(!StivaEsteVida(S))
    {
        CitireVarf(S,elem);
        AdaugareStiva(InversaS,elem);
        StergereVarf(S);
    }
    S=InversaS;
}
void CopieStiva(stiva S,stiva &copie)
{
    elementStiva *elem;
    CitireVarf(S,elem);
    while(elem!=NULL)
    {
        AdaugareStiva(copie,elem);
        elem=elem->prec;
    }
    InversareStiva(copie);
}
double SirInNumar(char sir[MAX_CUVANT])
{
    tipDate val=0;
    long long i=0,p=10;
    bool negativ=false;
    if(sir[i]=='-')
    {
        negativ=true;
        ++i;
    }
    while(sir[i]!='.'&&sir[i]!=0)
    {
        val=val*10+sir[i++]-'0';
    }
    if(sir[i]=='.')
    {
        ++i;
        while(sir[i]!=0)
        {
            val=val+1.0*(sir[i++]-'0')/p;
            p*=10;
        }
    }
    if(negativ)
        val*=-1;
    return val;
}
void AtribuireValoare(elementStiva* &elem)
{
    tipDate val=SirInNumar(elem->cuvant);
    elem->val=val;
}
void AfisareStiva(stiva S)
{
    elementStiva *elem;
    elem=S.varf;
    while(elem!=NULL)
    {
        printf("%s ",elem->cuvant);
        elem=elem->prec;
    }
    printf("\n");
}
char TipulCaracterului(char caracter)
{
    /*
    (  )                    ->  P - Paranteze
    +  -  *  /  ^  # < = >  ->  O - Operatori
    0 1 ... 9 .             ->  N - Numar
    x                       ->  V - Variabila
    a b ... z               ->  F - Functii
    ,                       ->  , - virgula
    PI,e                    ->  C - constante
    */
    if(caracter=='P'||caracter=='I')
        return 'C';
    if(caracter=='('||caracter==')')
        return 'P';
    if(caracter=='+'||caracter=='-')
        return 'O';
    if(caracter=='*'||caracter=='/')
        return 'O';
    if(caracter=='^')
        return 'O';
    if(caracter=='#'||caracter=='='||caracter=='<'||caracter=='>')
        return 'R';
    if(caracter=='.'||(caracter>='0'&&caracter<='9'))
        return 'N';
    if(caracter=='x')
        return 'V';
    if(caracter>='a'&&caracter<='z')
        return 'F';
    if(caracter==',')
        return 'v';
    return 0;
}
void SpatiereSir(char sir[MAX_LUNGIME])
{
    char sirSpatiat[MAX_LUNGIME],tipCaracterCurent,tipCaracter;
    int lungimeSirSpatiat=0,lungimeSir,i,contor=1;
    bool parantezaPerioada=false;
    lungimeSir=strlen(sir);
    tipCaracterCurent=TipulCaracterului(sir[0]);
    if(sir[0]=='-')
    {
        sirSpatiat[lungimeSirSpatiat++]='0';
        sirSpatiat[lungimeSirSpatiat++]=' ';
    }
    if(sir[0]=='(')
        contor=0;
    sirSpatiat[lungimeSirSpatiat++]=sir[0];
    for(i=1; i<lungimeSir; ++i)
    {
        tipCaracter=TipulCaracterului(sir[i]);
        if(contor==0&&sir[i]=='-')
        {
            sirSpatiat[lungimeSirSpatiat++]=' ';
            sirSpatiat[lungimeSirSpatiat++]='0';
        }
        if(sir[i]=='x'&&TipulCaracterului(sir[i-1])=='F')
            tipCaracter='F';
        if(tipCaracterCurent=='N'&&sir[i]=='(')
        {
            tipCaracter='N';
            parantezaPerioada=true;
        }
        if(parantezaPerioada&&sir[i]==')')
        {
            parantezaPerioada=false;
            tipCaracter='N';
        }
        if(tipCaracter!=tipCaracterCurent)
        {
            sirSpatiat[lungimeSirSpatiat++]=' ';
            tipCaracterCurent=tipCaracter;
        }
        sirSpatiat[lungimeSirSpatiat++]=sir[i];
        ++contor;
        if(sir[i]=='('||sir[i]==','||sir[i]=='='||sir[i]=='#'||sir[i]=='<'||sir[i]=='>')
            contor=0;
    }
    sirSpatiat[lungimeSirSpatiat]=0;
    strcpy(sir,sirSpatiat);
}
void ExtragereCuvinte(char sir[MAX_LUNGIME],stiva & S)
{
    char *adrCuvant,copie[MAX_LUNGIME];
    strcpy(copie,sir);
    SpatiereSir(sir);
    elementStiva *elem;
    elem=new elementStiva;
    elem->val=0;
    adrCuvant=strtok(sir," ");
    while(adrCuvant!=NULL)
    {
        strcpy(elem->cuvant,adrCuvant);
        AdaugareStiva(S,elem);
        adrCuvant=strtok(NULL," ");
    }
    InversareStiva(S);
    strcpy(sir,copie);
}
int Prioritate(elementStiva * elem)
{
    char caracter=elem->cuvant[0];
    if(caracter=='('||caracter==')')
        return 0;
    if(caracter==',')
        return 1;
    if(caracter=='#'||caracter=='='||caracter=='<'||caracter=='>')
        return 2;
    if(caracter=='+')
        return 3;
    if(caracter=='-')
        return 4;
    if(caracter=='*'||caracter=='/')
        return 5;
    if(caracter=='^')
        return 6;
    if((caracter>='a'&&caracter<='z')&&caracter!='x')
        return 7;
    if(caracter=='x'||(caracter>='0'&&caracter<='9')||caracter=='P')
        return 8;
    return -1;
}
void AflareExpresiePostfixata(stiva &cuvinte,stiva &expresie)
{
    stiva operatori;
    elementStiva *elem,*varf;
    int prioritateVarf,prioritateElem;
    char primulCaracter;
    elem=new elementStiva;
    elem->val=0;
    InitializareStiva(operatori);
    InitializareStiva(expresie);
    while(!StivaEsteVida(cuvinte))
    {
        CitireVarf(cuvinte,elem);
        CitireVarf(operatori,varf);
        primulCaracter=elem->cuvant[0];
        if(primulCaracter==')')
        {
            while(varf->cuvant[0]!='(')
            {
                AdaugareStiva(expresie,varf);
                StergereVarf(operatori);
                CitireVarf(operatori,varf);
            }
            if(primulCaracter==')')
                StergereVarf(operatori);
        }
        else if(primulCaracter=='-'||primulCaracter==',')
        {
            while(1)
            {
                if(StivaEsteVida(operatori))
                    break;
                if(varf->cuvant[0]=='(')
                    break;
                if(TipulCaracterului(varf->cuvant[0])=='R')
                    break;
                AdaugareStiva(expresie,varf);
                StergereVarf(operatori);
                CitireVarf(operatori,varf);
            }
            AdaugareStiva(operatori,elem);
        }
        else
        {
            prioritateElem=Prioritate(elem);
            if(varf==NULL)
                prioritateVarf=-1;
            else
                prioritateVarf=Prioritate(varf);
            while(prioritateElem<prioritateVarf&&prioritateElem>0)
            {
                AdaugareStiva(expresie,varf);
                StergereVarf(operatori);
                CitireVarf(operatori,varf);
                if(varf==NULL)
                    prioritateVarf=-1;
                else
                    prioritateVarf=Prioritate(varf);
            }
            AdaugareStiva(operatori,elem);
        }
        StergereVarf(cuvinte);
    }
    while(!StivaEsteVida(operatori))
    {
        CitireVarf(operatori,varf);
        AdaugareStiva(expresie,varf);
        StergereVarf(operatori);
    }
    InversareStiva(expresie);
}
tipDate EvaluareExpresie(stiva expresie,tipDate val)
{
    stiva copieExpresie,termeni;
    elementStiva *elem;
    char tipElement;
    bool operatieValida;
    InitializareStiva(copieExpresie);
    InitializareStiva(termeni);
    CopieStiva(expresie,copieExpresie);
    while(!StivaEsteVida(copieExpresie))
    {
        CitireVarf(copieExpresie,elem);
        tipElement=TipulCaracterului(elem->cuvant[0]);
        if(tipElement=='N')
        {
            AtribuireValoare(elem);
            AdaugareStiva(termeni,elem);
        }
        if(tipElement=='V')
        {
            elem->val=val;
            AdaugareStiva(termeni,elem);
        }
        if(tipElement=='O'||tipElement=='R')
        {
            operatieValida=AplicareOperator(termeni,elem);
            if(!operatieValida)
                return inf;
        }
        if(tipElement=='F')
        {
            ///Codul nu mergea bine pentru sin(x^2) deoarece se implementeaza sin(val),unde val e valoarea variabilei x
            ///De fapt trebuie sa iei ultima valoare de pe stiva si din valoarea aceea sa aplici functia
            operatieValida=AplicareFunctie(termeni,elem);
            if(!operatieValida)
                return inf;
        }
        if(tipElement=='C')
        {
            if(elem->cuvant[0]=='P')
                elem->val=PI;
            if(elem->cuvant[0]=='e')
                elem->val=e;
            AdaugareStiva(termeni,elem);
        }
        StergereVarf(copieExpresie);
    }
    CitireVarf(termeni,elem);
    return elem->val;
}
