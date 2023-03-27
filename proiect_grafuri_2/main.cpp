#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

ifstream in("date.in");

int n, a[51][51], b[51][51],pozCursor=0, pozCursorMaxim=4;
bool areVirus[21];
char numePersoane[21][21];

int sol[101], k=1;//case 3

void citire()
{
    in>>n;
    for(int i=1; i<=n; ++i)
    {
        in>>numePersoane[i]>>areVirus[i];
    }
    int x,y;
    while(in>>x>>y)
    {
        a[x][y]=1;
        a[y][x]=1;
    }
    in.close();
}

void afisare(int x[][51])
{
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j)
            cout<<x[i][j]<<" ";
        cout<<endl;
    }
}

void matriceDeConexiune()
{
    for(int i=1 ; i<=n ; ++i)
    {
        for(int j=1 ; j<=n; ++j)
            b[i][j]=a[i][j];
    }

    for(int k = 1 ; k <= n ; ++k)
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= n ; ++j)
                if( i != j && b[i][j] == 0 &&  b[i][k] != 0 && b[k][j] != 0)
                    b[i][j] = k;
}

int bbNrdeCifre(int x)
{
    int c=0;
    while(x)
    {
        c++;
        x/=10;
    }
    return c;
}

void afisareNume()//case 0
{
    for(int i=1 ; i<=n ; ++i)
    {
        cout<<i<<".)  ";
        if(i<10)
            cout<<" ";
        cout<< numePersoane[i]<<endl;
    }
}

void afisareStatusPacienti()//case 1
{
    for(int i=1; i<=n; ++i)
    {
        cout<<i<<".)  ";
        if(i<10)
            cout<<" ";
        areVirus[i] ? cout<<numePersoane[i]<<setw(25-strlen(numePersoane[i]))<<"infectat" : cout<<numePersoane[i]<<setw(25-strlen(numePersoane[i]))<<"neinfectat";
        cout<<endl;
    }
}

void afisareStatusContact()//case 2
{
    for(int i=1; i<n ; ++i)
    {
        for(int j=i+1 ; j<=n ; ++j)
        {
            a[i][j] ? cout<<numePersoane[i]<<setw(35-strlen(numePersoane[i]))<<" a avut contact direct cu "<<setw(35-strlen(" nu a avut contact direct cu "))<<numePersoane[j] : cout<<numePersoane[i]<<setw(35-strlen(numePersoane[i]))
                          <<" nu a avut contact direct cu "<<setw(35-strlen(" nu a avut contact direct cu "))<<numePersoane[j];
            cout<<endl;
        }
        cout<<endl;
    }
}

void afisareConexiunePacienti()//case 3
{
    afisareStatusPacienti();

    cout<<"Intre ce pacienti vreti sa afisati conexiunea ?"<<endl;
    int x,y;
    cin>>x>>y;

    if(b[x][y])
    {
        cout<<numePersoane[x]<<" are o conexiune cu "<<numePersoane[y]<<endl;
        if(areVirus[x] || areVirus[y])
        {
            areVirus[x] ? cout<<numePersoane[x] : cout<<numePersoane[y];
            cout<<" are o sansa de "<<100/b[x][y]<<"% sa fie infectat"<<endl;
        }
        else cout<<"Au o sansa de 0% de a fi infectati"<<endl;
    }
    else cout<<numePersoane[x]<<" nu are o conexiune cu "<<numePersoane[y];


}

void afisareMeniu(int pozitieCursor)
{
    int spatii = 45;
    cout<<"1.Nume pacienti";
    pozitieCursor==0 ? cout<<setw(spatii-strlen("1.Nume pacienti"))<<"<>"<<endl : cout<<endl;
    cout<<"2.Status pacienti";
    pozitieCursor==1 ? cout<<setw(spatii-strlen("2.Status pacienti"))<<"<>"<<endl : cout<<endl;
    cout<<"3.Status de contact";
    pozitieCursor==2 ? cout<<setw(spatii-strlen("3.Status de contact"))<<"<>"<<endl : cout<<endl;
    cout<<"4.Conexiuni posibile intre 2 pacienti";
    pozitieCursor==3 ? cout<<setw(spatii-strlen("4.Conexiuni posibile intre 2 pacienti"))<<"<>"<<endl : cout<<endl;
    cout<<"5.Iesire";
    pozitieCursor==4 ? cout<<setw(spatii-strlen("5.Iesire"))<<"**"<<endl : cout<<endl;

}

void meniu()
{
    system("CLS");
    afisareMeniu(pozCursor);
    char sagetiMeniu;
    sagetiMeniu=_getch();
    switch(sagetiMeniu)
    {

    case 'w':
    {
        pozCursor--;
        if(pozCursor<0)
            pozCursor=pozCursorMaxim;
        meniu();
        break;
    }
    case 's':
    {
        pozCursor++;
        if(pozCursor>pozCursorMaxim)
            pozCursor=0;
        meniu();
        break;
    }
    case char(13)://tasta 'Enter' pt selectia din meniu
    {
        switch(pozCursor)
        {
        case 0:
        {
            system("CLS");
            afisareNume();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 1:
        {
            system("CLS");
            afisareStatusPacienti();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 2:
        {
            system("CLS");
            afisareStatusContact();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 3:
        {
            cout<<"4";
            system("CLS");


            afisareConexiunePacienti();


            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 4:
        {
            break;
        }
        default :
            break;
        }
    }
    default:
        break;
    }
}

int main()
{
    citire();
    matriceDeConexiune();
    meniu();
}

