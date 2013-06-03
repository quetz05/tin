#include "dodawanie.h"
#include "ui_dodawanie.h"


dodawanie::dodawanie(QWidget *parent, BramaZnajomych *bramaZnajomych, int socket) :
    QDialog(parent),
    ui(new Ui::dodawanie)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui->setupUi(this);

    gniazdo = socket;

    brama = bramaZnajomych;
    oknoInformacji = NULL;
    znajomy.first = "";
    znajomy.second = 0;


    connect(ui->pushOK, SIGNAL(clicked()), this, SLOT(wyjscie()));
    connect(ui->pushDodaj, SIGNAL(clicked()), this, SLOT(dodajZnajomego()));

    connect(ui->Nick, SIGNAL(textChanged(const QString &)), this, SLOT(czytajNick(QString)));
    connect(ui->ID, SIGNAL(textChanged(const QString &)), this, SLOT(czytajID(QString)));

    //wyswietlanie loga
    QGraphicsScene *scene =  new QGraphicsScene();
    QPixmap pixmap(":/images/dodaj.jpg");
    scene->addPixmap(pixmap);
    ui->picture->setScene(scene);
    ui->picture->show();


}

dodawanie::~dodawanie()
{
    //oknoInformacji = NULL;
    //brama = NULL;
    delete brama;
    delete oknoInformacji;
    delete ui;
}

void dodawanie::wyjscie()
{
    emit zakoncz();
}

void dodawanie::czytajID(const QString &id)
{
    znajomy.second = id.toInt();

}

void dodawanie::czytajNick(const QString &nick)
{
    znajomy.first = nick;

}

void dodawanie::dodajZnajomego()
{

    if(oknoInformacji)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    if(znajomy.second==0)
        oknoInformacji = new info(this, "Bez ID to ja funkcji dodawania znajomych nie wywołam...",false);

    else if(znajomy.first=="")
        oknoInformacji = new info(this, "Takich bez nicku to mamy bez liku... Wpisz proszę nick znajomego.",false);

    else if(brama->czyWBazie(znajomy.second))
        oknoInformacji = new info(this, "Albo mnie mylą zera i jedynki, albo masz już na liście znajomego o tym ID", false);

    else if(brama->dodajZnajomego(znajomy.second, znajomy.first))
         {

            oknoInformacji = new info(this, "Znajomy dodany!",true);

         }
    else
       oknoInformacji = new info(this, "Coś się zepsuło i nie mogłem dodać znajomego. Pewnie twórcy coś skopali w kodzie...",false);


    /*
        Szyfrator szyfr;
        Wiadomosc wiad(CZY_ISTNIEJE, znajomy.second,znajomy.first,gniazdo);
        unsigned int wielkosc;
        char *wiadomosc = szyfr.szyfruj(&wiad,0,&wielkosc);

        if(wiad.wyslijDoSerwera(wiadomosc, wielkosc)==-1){
            qDebug()<<"Błąd pry sprawdzaniu istnienia znajomego";
        }*/

}

void dodawanie::sprawdzenieIstnienie(const int odp)
{


    if(oknoInformacji)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    if(odp!=0)
    {

        if(brama->dodajZnajomego(znajomy.second, znajomy.first))
             {

                oknoInformacji = new info(this, "Znajomy dodany!",true);

             }
        else
           oknoInformacji = new info(this, "Coś się zepsuło i nie mogłem dodać znajomego. Pewnie twórcy coś skopali w kodzie...",false);
    }
    else
        oknoInformacji = new info(this, "Brak znajomego o podanych danych w bazie :( Na pewno masz innych kolegów!",false);


}
