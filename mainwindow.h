#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <string.h>
#include<QDebug>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <QFile>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class KlientBanku
{
public:
    string imie;
    string nazwisko;
    int rok;
    string nrKonta;
    string nazwaBanku;
    double kwota;
    KlientBanku(const string& im, const string& naz, const int r, const string& nr, const string& nazwaB, const double kw);
    KlientBanku();
    ~KlientBanku();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    string path = "/Users/maxus/OneDrive/Dokumenty/nienazwany/baza_danych.txt";

    int rok;
    double kwota;
    vector<KlientBanku*> baza;
    string imie, nazwisko, nrKonta, nazwaBanku;
    void drukujKlientBanku(KlientBanku *klient) const;
    void modyfikacjaKlienta(KlientBanku *klient);




private:
    Ui::MainWindow *ui;

private slots:
    void wczytajPressed();
    void on_button1_clicked();
    void on_button4_clicked();void on_button6_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button7_clicked();




}
;


#endif // MAINWINDOW_H
