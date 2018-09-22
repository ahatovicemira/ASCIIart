#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

const unsigned int sirina_prozora = 80;

char Nijanse(int n)
{
    if (n >= 239)
        return '.';
    else if (n >= 223)
        return ':';
    else if (n >= 207)
        return ';';
    else if (n >= 191)
        return '~';
    else if (n >= 175)
        return '+';
    else if (n >= 159)
        return '?';
    else if (n >= 143)
        return ')';
    else if (n >= 127)
        return 'x';
    else if (n >= 111)
        return 'c';
    else if (n >= 95)
        return '*';
    else if (n >= 79)
        return '#';
    else if (n >= 63)
        return 'M';
    else if (n >= 47)
        return 'W';
    else if (n >= 31)
        return '%';
    else if (n >= 15)
        return '@';
    else if (n >= 0)
        return '$';
}

int main()
{
    typedef int* point ;
    ifstream ulaz;
    ofstream izlaz;
    string ime_slike;

    do
    {
        cout<<"Koju sliku zelite?"<<endl;
        getline(cin, ime_slike);
        ime_slike = ime_slike + ".pgm";

        system("cls");
        ulaz.open(ime_slike.c_str()); //otvaramo sliku

    }
    while(ulaz.fail() || ulaz.bad());

    izlaz.open("znakovi.txt");
    if (izlaz.fail() || izlaz.bad())
        cout<<"doslo je do greske!"<<endl; //nije se dobro otvorio izlazni fajl

    string red;

    while (true) //ovom petljom prepisujemo sve iz ulaza u izlaz
            {
                getline(ulaz, red);
                izlaz << red << endl;
                if (ulaz.eof())
                    break;
            }

        izlaz.close();
        ulaz.close(); //zatvorili smo nase fajlove

        ulaz.open("znakovi.txt");

        if (ulaz.fail() or ulaz.bad())
            cout << "Doslo je do greske " << endl; //slika se nije dobro otvorila

       int br_redova, br_kolona, boja;

        // citamo broj redova iz fajla, broj kolona i kakve su nijanse sive
        for (int i = 1; i < 4; i++)
            {
                getline(ulaz, red);
                if (i == 2)
                        ulaz >> br_redova >> br_kolona;
                if (i == 3)
                        ulaz >> boja;
            }


        // sada pravimo niz u koji cemo spremiti sve vrijednosti piksela iz fajla
        point niz;

        niz = new int[br_kolona * br_redova];

        string vrijednosti_piksela;
        int a = 0, b = 0; // a -broj izvrsavanja petlje dok je b-indeks clanova niza

        while(!ulaz.eof())
            {
                int i = 0;
                int pomocna;
                ulaz >> vrijednosti_piksela;
                if (vrijednosti_piksela[i] <= '9' && vrijednosti_piksela[i] >= '0')
                    {
                        pomocna = int(vrijednosti_piksela[i]) - int('0');
                        i++;

                        while (vrijednosti_piksela[i] <= '9' && vrijednosti_piksela[i] >= '0')
                            {
                                pomocna = pomocna * 10;
                                pomocna = pomocna + int(vrijednosti_piksela[i]) - int('0');
                                i++;
                            }
                    }

                if (a < (br_kolona * br_redova))
                    {
                        niz[b] = pomocna;
                        b++;
                    }
                a++;
            }

        ulaz.close();


        int brojac = 0;
        point *matrica;
        matrica = new int* [br_kolona];

        for (int i = 0; i < br_kolona; i++)
                matrica[i] = new int[br_redova];

        for (int i = 0; i < br_kolona; i++)
            {
                for (int j = 0; j < br_redova; j++)
                    {
                        matrica[i][j] = niz[brojac];
                        brojac++;
                    }
            }

        izlaz.open("prva_slika.txt");

        for (int i = 0; i < br_kolona; i++)
            {
                for (int j = 0; j < br_redova; j++)
                {
                    izlaz << Nijanse(matrica[i][j]);
                }
            izlaz << endl;
            }
        izlaz.close();

        int red_z;
        int kolona_z;

        red_z = br_redova / sirina_prozora; //Ppostavljamo dimenzije
        kolona_z = br_kolona / sirina_prozora;

        point *mala_matrica;

        mala_matrica = new int *[sirina_prozora];

        for (int i = 0; i < sirina_prozora; i++)
            {
                mala_matrica[i] = new int[sirina_prozora];
            }


        point niz2;

        niz2 = new int[sirina_prozora * sirina_prozora];


        int srednja_boja = 0;
        brojac = 0;

        for (int i = 0; i < sirina_prozora; i++)
            {
                for (int j = 0; j < sirina_prozora; j++)
                    {
                        for (int k = 0; k < kolona_z; k++)
                            {
                                for (int l = 0; l< red_z; l++)
                                    {
                                        srednja_boja = srednja_boja + matrica[i * kolona_z + k][j * red_z + l];
                                    }
                            }
                        niz2[brojac] = srednja_boja / (kolona_z * red_z);
                        brojac++;
                        srednja_boja = 0;
                    }
            }

        brojac=0;
        for (int i = 0; i < sirina_prozora; i++)
            {
                for (int j = 0; j < sirina_prozora; j++)
                {
                    mala_matrica[i][j] = niz2[brojac];
                    brojac++;
                }
            }

        izlaz.open("projekat.txt");

        cout << endl;
        for (int i = 0; i < sirina_prozora; i++)
            {
                for (int j = 0; j < sirina_prozora; j++)
                {
                    cout << Nijanse(255 - mala_matrica[i][j]);
                    izlaz << Nijanse(mala_matrica[i][j]);
                }
            cout << endl;
            izlaz << endl;
            }

        izlaz.close();

        delete []niz2;

        for (int i = 0; i < sirina_prozora; i++)
            delete []mala_matrica[i];

        delete []mala_matrica;

        for (int i = 0; i < br_kolona; i++)
            delete []matrica[i];

        delete []matrica;

        delete []niz;

    return 0;
}
