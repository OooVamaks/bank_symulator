#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

connect(ui->wczytaj, SIGNAL(released()), this,SLOT(wczytajPressed()));

    ui->screen3->setPlainText("Wpisz ilu klientow chcesz wczytac i wciśnij wczytaj ");

}
int nowaLiczbaKlientow = 0;
double najwKwota = 0;
double obecnaWKwota;
double obecnaNKwota;
double najnKwota = 1000000;
string nowyNrKonta;
double nowaKwota;
bool exist = false;
bool scena1 = false;
bool zmienna2=false;
bool drukowanie=false;

bool zmienna6=false;
bool exist2;
int stage=0;
string schowek;
int wklient;
int schowek1;
double schowek3;

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::wczytajPressed(){

        ui->screen2->clear();
        QString qChoice = ui->screen1->toPlainText();
        int intChoice = qChoice.toInt();

        ui->screen1->clear();
        ifstream base;
        base.open(path);
        string line;
        for (int i=0;i<intChoice;i++) {
            getline(base, line);
            char* text = &line[0];

            imie = strtok(text, " ");
            nazwisko = strtok(NULL, " ");
            rok = stoi(strtok(NULL, " "));
            nrKonta = strtok(NULL, " ");
            nazwaBanku = strtok(NULL, " ");
            kwota = stod(strtok(NULL, " "));

            KlientBanku* klient = new KlientBanku(imie, nazwisko, rok, nrKonta, nazwaBanku, kwota);
            baza.emplace_back(klient);
            nowaLiczbaKlientow++;

             drukujKlientBanku(baza[i]);

        }
        base.close();
        ui->screen3->clear();
    }


KlientBanku::KlientBanku(const string& im, const string& naz, const int r, const string& nr, const string& nazwa, const double kw)
{
    imie = im;
    nazwisko = naz;
    rok = r;
    nrKonta = nr;
    nazwaBanku = nazwa;
    kwota = kw;
}




void MainWindow::drukujKlientBanku(KlientBanku *klient) const
{
    QString qimie = QString::fromStdString(klient->imie);
    ui->screen2->insertPlainText(qimie+"\n");
    QString qnazwisko = QString::fromStdString(klient->nazwisko);
    ui->screen2->insertPlainText(qnazwisko+"\n");
    QString qrok = QString::number(klient->rok);
    ui->screen2->insertPlainText(qrok+"\n");
    QString qnrKonta = QString::fromStdString(klient->nrKonta);
    ui->screen2->insertPlainText(qnrKonta+"\n");
    QString qnazwaBanku = QString::fromStdString(klient->nazwaBanku);
    ui->screen2->insertPlainText(qnazwaBanku+"\n");
    QString qkwota = QString::number(klient->kwota);
    ui->screen2->insertPlainText(qkwota+"\n\n");
}


void MainWindow::modyfikacjaKlienta(KlientBanku *klient)
{
    switch(stage){
    case 0:
        ui->screen1->clear();
        ui->screen2->setPlainText("Nowe imie");
        break;
    case 1:{
        QString displayVal = ui->screen4->toPlainText();
        ui->screen1->clear();
        ui->screen4->clear();
        schowek = displayVal.toStdString();
        klient->imie=schowek;
        ui->screen2->setPlainText("Nowe nazwisko");
        break;
    }
    case 2: {
        QString displayVal = ui->screen4->toPlainText();
        ui->screen1->clear();
        ui->screen4->clear();
        schowek = displayVal.toStdString();
        klient->nazwisko=schowek;
        ui->screen2->setPlainText("Nowe rok urodzenia");
        break;
    }
    case 3: {
        QString displayVal = ui->screen4->toPlainText();
        ui->screen1->clear();
        ui->screen4->clear();
        schowek1 = displayVal.toInt();
        klient->rok=schowek1;
        ui->screen2->setPlainText("Nowy numer konta");
        break;
    }
    case 4: {
        QString displayVal = ui->screen4->toPlainText();
        ui->screen1->clear();
        ui->screen4->clear();
        schowek = displayVal.toStdString();
        klient->nrKonta=schowek;
        ui->screen2->setPlainText("Nowy bank");
        break;
    }
    case 5: {
        QString displayVal = ui->screen4->toPlainText();
        ui->screen1->clear();
        schowek = displayVal.toStdString();
        klient->nazwaBanku=schowek;
        ui->screen2->setPlainText("Nowa kwota");
        break;
    }
    case 6: {
        QString displayVal = ui->screen4->toPlainText();
        ui->screen1->clear();
        ui->screen4->clear();
        schowek3 = displayVal.toDouble();
        klient->kwota=schowek3;
        stage=0;
        zmienna2=false;
        ui->screen2->clear();
        KlientBanku* klient = new KlientBanku(imie, nazwisko, rok, nrKonta, nazwaBanku, kwota);
        baza.emplace_back(klient);
        nowaLiczbaKlientow++;
        break;
    }
    }
}











void MainWindow::on_button1_clicked()
{  ui->screen2->clear();
            for (int i = 0; i < nowaLiczbaKlientow; i++) {
        drukujKlientBanku(baza[i]);
    }


}


void MainWindow::on_button2_clicked()
{  ui->screen2->clear();
            for(int i=0;i<nowaLiczbaKlientow;i++){
        obecnaWKwota = baza[i]->kwota;
        if (obecnaWKwota>najwKwota){
            najwKwota=obecnaWKwota;
        }
    }
            for(int i=0;i<nowaLiczbaKlientow;i++){
                if(najwKwota<=baza[i]->kwota)
                    drukujKlientBanku(baza[i]);
            }



}


void MainWindow::on_button3_clicked()
{  ui->screen2->clear();
    for(int i=0;i<nowaLiczbaKlientow;i++){
        obecnaNKwota = baza[i]->kwota;
        if(obecnaNKwota<najnKwota){
            najnKwota=obecnaNKwota;
        }
    }
    for(int i=0;i<nowaLiczbaKlientow;i++){
        if(najnKwota>=baza[i]->kwota){
            drukujKlientBanku(baza[i]);
        }
    }

}


void MainWindow::on_button4_clicked()
{

            QString displayVal = ui->screen1->toPlainText();
            nowyNrKonta = displayVal.toStdString();
            for (int i=0;i<nowaLiczbaKlientow;i++){
                if(nowyNrKonta.compare(baza[i]->nrKonta)==0){
                    exist = true;


            }}
    if(exist==true){
        ui->screen1->clear();
        ui->screen2->setPlainText("Podaj na pierwszym ekranie kwote jaka chcesz dodac.");
        zmienna2=true;
        exist=false;
    } else{
        ui->screen2->setPlainText("Podany numer konta nie istnieje.");


    }
    if(zmienna2==true){
       QString displayVal = ui->screen4->toPlainText();
            nowaKwota = displayVal.toDouble();
            ui->screen1->clear();
            ui->screen2->clear();
            for (int i=0;i<nowaLiczbaKlientow;i++){
                if(nowyNrKonta.compare(baza[i]->nrKonta)==0){
                    baza[i]->kwota=baza[i]->kwota+nowaKwota;
                    drukujKlientBanku(baza[i]);
                }
}
}}

void MainWindow::on_button7_clicked()
{
qApp->quit();
}




void MainWindow::on_button6_clicked()
{
            ui->screen2->clear();
            QString displayVal = ui->screen1->toPlainText();
            nowyNrKonta = displayVal.toStdString();
            for(int i=0;i<nowaLiczbaKlientow;i++){
                if(nowyNrKonta.compare(baza[i]->nrKonta)==0){
                    exist2=true;
                    wklient=i;
                }
            }
    if(exist2==true){
        zmienna6=true;

    } else {
        ui->screen2->setPlainText("Podano zly numer konta");


    }

   if(zmienna6==true){
    modyfikacjaKlienta(baza[wklient]);
    stage++;
    KlientBanku* klient = new KlientBanku(imie, nazwisko, rok, nrKonta, nazwaBanku, kwota);
    baza.emplace_back(klient);
    nowaLiczbaKlientow++;
    drukujKlientBanku(baza[wklient]);

}
}


