#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>

using namespace std;

ifstream in("date.in");

int n, a[51][51], b[51][51],pozCursor=0, pozCursorMaxim=5;
bool areVirus[21];
char numePersoane[21][21];


///Imprumutate de la Miron

void SetColor(int ForgC);

void SetColor(int ForgC)
{
     WORD wColor;


     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;


     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {

          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


void SetColorAndBackground(int ForgC, int BackC); ///declararea functitiei de highlight a textului

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}



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
        SetColor(15);
        cout<<i<<".)  ";
        if(i<10)
            cout<<" ";
        cout<<numePersoane[i]<<setw(25-strlen(numePersoane[i]));
        if(areVirus[i])
        {
            SetColor(12);
            cout<<"infectat";
        }
        else
        {
            cout<<"neinfectat";
        }
        cout<<endl;
    }
}

void afisareStatusContact()//case 2
{
    for(int i=1; i<n ; ++i)
    {
        for(int j=i+1 ; j<=n ; ++j)
        {
            a[i][j] ? cout<<numePersoane[i]<<setw(45-strlen(numePersoane[i]))<<" a avut contact direct cu "<<setw(45-strlen(" nu a avut contact direct cu "))<<numePersoane[j] : cout<<numePersoane[i]<<setw(45-strlen(numePersoane[i]))
                          <<" nu a avut contact direct cu "<<setw(45-strlen(" nu a avut contact direct cu "))<<numePersoane[j];
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

            if(areVirus[x]==1 && areVirus[y]==1)
            {
                cout<<numePersoane[x]<<" si "<<numePersoane[y]<<" sunt 100% infectati"<<endl;
            }
            else
            {
                areVirus[y] ? cout<<numePersoane[x] : cout<<numePersoane[y];
                cout<<" are o sansa de "<<100/b[x][y]<<"% sa fie infectat/a"<<endl;
            }
        }
        else cout<<"Au o sansa de 0% de a fi infectati"<<endl;
    }
    else cout<<numePersoane[x]<<" nu are o conexiune cu "<<numePersoane[y];


}

void afisareInformatiiPacient()//case 4
{
    afisareNume();
    cout<<"Despre ce pacient vreti sa afisati informatii ?"<<endl;
    short x;
    cin>>x;

    int nrInfectatiCunoscuti = 0, nrNeinfectatiCunoscuti = 0;
    for(int i=1 ; i<=n; ++i)
    {
        if(a[x][i]==1 && x!=i)
        {
            areVirus[i] ? nrInfectatiCunoscuti++ : nrNeinfectatiCunoscuti++;
        }
    }
    system("CLS");
    cout<<numePersoane[x]<<" are conexiune cu "<<nrInfectatiCunoscuti<<" infectat/i si "<<nrNeinfectatiCunoscuti<<" neinfectat/i"<<endl;
}

void setSpace(int x)
{
    for(int i=1 ; i<=x ; ++i)
        cout<<"  ";
}

void afisareMeniu(int pozitieCursor)
{
    int spatii = 25,x=25;
    cout<<endl<<endl<<endl;
    setSpace(x);
    cout<<"/>Nume pacienti";
    setSpace(x);
    pozitieCursor==0 ? cout<<setw(spatii-strlen("/>Nume pacienti"))<<"<1>"<<endl : cout<<endl;
    setSpace(x);
    cout<<"/>Status pacienti";
    setSpace(x);
    pozitieCursor==1 ? cout<<setw(spatii-strlen("/>Status pacienti"))<<"<2>"<<endl : cout<<endl;
    setSpace(x);
    cout<<"/>Status de contact";
    setSpace(x);
    pozitieCursor==2 ? cout<<setw(spatii-strlen("/>Status de contact"))<<"<3>"<<endl : cout<<endl;
    setSpace(x);
    cout<<"/>Conexiuni 2 pacienti";
    setSpace(x);
    pozitieCursor==3 ? cout<<setw(spatii-strlen("/>Conexiuni 2 pacienti"))<<"<4>"<<endl : cout<<endl;
    setSpace(x);
    cout<<"/>Informatii Pacient";
    setSpace(x);
    pozitieCursor==4 ? cout<<setw(spatii-strlen("/>Inforamatii pacient"))<<"  <5>"<<endl : cout<<endl;
    setSpace(x);
    SetColor(4);
    cout<<"/>Iesire";
    setSpace(x);
    pozitieCursor==5 ? cout<<setw(spatii-strlen("/>Iesire"))<<"*6*"<<endl : cout<<endl;
    setSpace(x);
}

void meniu()
{
    SetColor(15);
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
            SetColor(15);
            afisareNume();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 1:
        {
            system("CLS");
            SetColor(15);
            afisareStatusPacienti();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 2:
        {
            system("CLS");
            SetColor(15);
            afisareStatusContact();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 3:
        {
            cout<<"4";
            SetColor(15);
            system("CLS");
            afisareConexiunePacienti();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 4:
        {
            system("CLS");
            SetColor(15);
            afisareInformatiiPacient();
            sagetiMeniu=_getch();
            pozCursor=0;
            meniu();
            break;
        }
        case 5:
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

void logo()
{
    SetColor(4);
    cout<<R"(
                                                              ..         ..
                                                           .~7!^         :~!~:
                                                         .7J!.             .^77^
                                                       .^J?.                  ~Y!:
                                                      .~?7                     ~5~^
                                                     .~~:                       7?~:
                                                     ^~~                         ~~~
                                                     ^~~.                        ~~~.
                                                     ^~~^                       ^~~~
                                                     .~~~^.    .::^^^^^::.     ^~~~:
                                                     .~~~~:.  :^^^:::^^^^.  :~~~~:
                                                  ...::^~~~~~^:.         ..^~~~~~^:::...
                                              .:^~~~~~~~~~~~~~~~~^^: :^^~~~~~~~~~~~~~~~~~^:.
                                            :^~!~^::::::^^~~~~~~~~~: .^~~~~~~~~~^^:::::^~!!~^:
                                          .~!!^:.        . .^~~~~^     :~~~~^:.          .:~7!^.
                                         :!!:           :~^   :~^.      :^^.  :^^           .~7!.
                                        .7!             .~~:    .:^:::^^:    ~!~:             :7!.
                                        ~7               .~~:   .~~~~~~~^   ~!~^               :?^
                                       .7^                .^~^:  ^~~~~~~. :!!~:                 ~!
                                        ~.                  .^~. :~~~~~~. ^^:                   :~
                                                                 ^~~~~~~:
                                                                :~~~~~~~~.
                                                                .^~~~~.:~~~~.
                                             ~:             :~~~~~^.  .^~~~^:.             ^^
                                             ~??7!^^::::^~~!!~~^:.      .^~~~!!!~^::::^~!7J?^
                                               .:~!!77!!!~~^::.            .:^^~!!77777!~:.
                                                   ...                           ...)"<<endl<<endl;

            cout<<"                             ";

            for(int i=1 ;i<=40;i++)
            {
                cout<<char(219)<<char(219);
                usleep(i*700);
            }
            cout<<endl<<endl;
            setSpace(33);
            SetColor(12);
            cout<<"<Enter>";
            char c;
            c=_getch();
}

void iesire()
{
    system("CLS");
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<endl<<endl<<endl<<endl<<endl;
    setSpace(35);
    cout<<"<Iesire>"<<endl;
    cout<<"                                   ";

            for(int i=1 ;i<=40;i++)
            {
                cout<<char(219)<<char(219);
                usleep(i*700);
            }
}

int main()
{
     logo();
    citire();
    matriceDeConexiune();
    meniu();
    iesire();
    SetColorAndBackground(0,0);
}

