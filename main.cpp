#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <vector>
#include <cstdio>

using namespace std;

int max_id =0;

struct Adresat
{
    int id =0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};


void dodajAdresataDoKsiazkiAdresowej (vector <Adresat> &adresaci)
{
    string imie, nazwisko, numerTelefonu, adres, email;
    system("cls");

    Adresat adresat;

    cout << "Podaj imie. " << endl;
    cin >> imie;
    cout << "Podaj nazwisko. " << endl;
    cin >> nazwisko;

    cout << "Podaj numer telefonu adresata." << endl;
    cin >> numerTelefonu;

    cout << "Podaj adres zamieszkania adresata." << endl;
    cin.ignore();
    getline(cin,adres);

    cout << "Podaj e-mail adresata." << endl;
    cin>> email;

    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.adres = adres;
    adresat.id = (max_id + 1 );
    adresat.email = email;

    adresaci.push_back(adresat);

    max_id++;

    fstream plik;
    if(plik.good())
    {
        plik.open("ksiazka_adresowa.txt",ios::out | ios::app);

        plik<<adresat.id<<"|"<<imie<<"|"<<nazwisko<<"|"<<numerTelefonu<<"|"<<adres<<"|"<<email<<"|"<<endl;

        plik.close();

        cout << "Adresat dodany." << endl;
        Sleep(1000);
    }

    else
    {
        cout << "Nie mozna otworzyc pliku: ksiazka_adresowa.txt" << endl;
    }


}

void wyswietlAdresatowOPodanymImieniu (vector <Adresat> adresaci)
{
    string imie;
    system("cls");
    cout << "Podaj imie" << endl;
    cin >> imie;


    for (int i=0; i < adresaci.size(); i++)
    {
        if (adresaci[i].imie == imie)
        {
            cout << adresaci[i].id<< endl;
            cout << adresaci[i].imie<<endl;
            cout << adresaci[i].nazwisko<< endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].adres << endl;
            cout << adresaci[i].email << endl << endl;
        }
    }
    Sleep(3000);
}


void wyswietlAdresatowOPodanymNazwisku (vector <Adresat> adresaci)
{
    string nazwisko;
    system("cls");
    cout << "Podaj nazwisko" << endl;
    cin >> nazwisko;


    for (int i=0; i<adresaci.size(); i++)
    {

        if (adresaci[i].nazwisko == nazwisko)
        {
            cout << adresaci[i].id<< endl;
            cout << adresaci[i].imie<<endl;
            cout << adresaci[i].nazwisko<< endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].adres << endl;
            cout << adresaci[i].email << endl << endl;
        }
    }
    Sleep(3000);

}

void wyswietlDaneWszystkichAdresatow (vector <Adresat> adresaci)
{
    int i =0;
    system("cls");
    while (i < adresaci.size())
    {

        cout << adresaci[i].id << endl;
        cout << adresaci[i].imie <<endl;
        cout << adresaci[i].nazwisko << endl;
        cout << adresaci[i].numerTelefonu << endl;
        cout << adresaci[i].adres << endl ;
        cout << adresaci[i].email << endl << endl;

        i++;
    }

    Sleep(3000);
}

void ZapiszStruktureDoPliku (vector <Adresat> &Adresaci)
{

    fstream plik;
    if(plik.good())
    {
        plik.open("ksiazka_adresowa.txt", fstream::out | fstream::trunc);

        for(int i=0; i<Adresaci.size(); i++)
        {
            plik<<Adresaci[i].id<<"|"<<Adresaci[i].imie<<"|"<<Adresaci[i].nazwisko<<"|"<<Adresaci[i].numerTelefonu<<"|"<<Adresaci[i].adres<<"|"<<Adresaci[i].email<<"|"<<endl;
        }
        plik.close();

    }
}


void wczytajDaneZPlikuDoStruktury (vector <Adresat> &Adresaci)
{
    int nr_linii = 1;

    string linia;
    Adresat adresat;

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in);

    if (plik.good() == false)
    {
        cout<<"Nie udalo sie otworzyc pliku";
        Sleep(1000);
    }
    else
    {

        while (getline(plik, linia))
        {
            char linijka[linia.length()];

            for (int j =0; j<linia.length(); j++)
            {
                linijka[j] = linia[j];
            }

            char *pch;
            string tablica[6];
            int i =0;

            pch = strtok (linijka, "|");
            while (pch != NULL && i<6)
            {

                tablica[i] = ("%s", pch);
                pch = strtok (NULL, "|");
                i++;
            }


            adresat.id = atoi(tablica[0].c_str());

            adresat.imie = tablica[1];

            adresat.nazwisko = tablica[2];

            adresat.numerTelefonu = tablica[3];

            adresat.email = tablica[4];

            adresat.adres = tablica[5];


            Adresaci.push_back(adresat);

            if (adresat.id > max_id)
                max_id = adresat.id;

            nr_linii++;
        }
    }
    plik.close();

}

void usunAdresata (vector <Adresat> &Adresaci)
{
    int id;

    cout<< "Podaj id adresata, ktorego chcesz usunac."<<endl;
    cin>> id;


    for (int i=0; i<Adresaci.size(); i++)
    {
        if (Adresaci[i].id == id)
        {
            cout<< "Czy na pewno chcesz usunac wybranego adresata? Je?li tak, wpisz litere 't'." <<endl;
            cout<< "Jesli nie, nacisnij dowolny przycisk (inny niz litera 't')."<<endl;


            char znak;
            cin>> znak;

            if (znak == 't'){
                if (Adresaci[i].id == max_id)
                    max_id--;

                Adresaci.erase(Adresaci.begin() + i);


            cout << "Adresat usuniety. " << endl;
            Sleep(1000);
            }
        }
    }

    ZapiszStruktureDoPliku (Adresaci);
}



void edytujAdresata (vector <Adresat> &Adresaci)
{

    int id;

    cout<< "Podaj id adresata, ktorego dane chcesz edytowac."<<endl;
    cin>> id;



    for (int i=0; i<Adresaci.size(); i++)
    {
        if (Adresaci[i].id == id)
        {
            cout << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - e-mail" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;

            cout<< endl <<"Podaj numer opcji, ktora chcesz zmienic u wybranego uzytkownika : "<<endl;

            char wybor;
            cin >> wybor;

            if(wybor == '1')
            {
                string imie;
                cout << "Podaj nowe imie uzytkownika."<< endl;
                cin >> imie;

                Adresaci[i].imie = imie;
                cout << endl << "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '2')
            {
                string nazwisko;
                cout<< "Podaj nowe nazwisko uzytkownika."<< endl;
                cin>> nazwisko;
                Adresaci[i].nazwisko = nazwisko;

                cout << endl<<"Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }


            else if (wybor == '3')
            {
                string numerTelefonu;
                cout<< "Podaj nowy numer telefonu uzytkownika."<< endl;
                cin>> numerTelefonu;
                Adresaci[i].numerTelefonu = numerTelefonu;
                cout << endl<< "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '4')
            {
                string email;
                cout << "Podaj nowy adres e-mail uzytkownika."<< endl;
                cin >> email;
                Adresaci[i].email = email;
                cout << endl<< "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '5')
            {
                string adres;
                cout << "Podaj nowy adres uzytkownika."<< endl;
                cin >> adres;
                Adresaci[i].adres = adres;
                cout << endl << "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '6')
            {
                system("cls");
            }

            else
            {
                cout << "Wybierz poprawny numer dostepnych opcji." << endl;
                Sleep(1500);
            }
        }
    }

    ZapiszStruktureDoPliku(Adresaci);
}



int main()
{
    vector <Adresat> Adresaci;
    wczytajDaneZPlikuDoStruktury(Adresaci);

    char wybor;

    while(true)
    {
        system ("cls");
        cout << "1. Dodaj adresata." << endl;
        cout << "2. Wyszukaj po imieniu." << endl;
        cout << "3. Wyszukaj po nazwisku." << endl;
        cout << "4. Wyswietl wszystkich adresatow." << endl;
        cout << "5. Usun adresata." << endl;
        cout << "6. Edytuj adresata." << endl;
        cout << "9. Zakoncz program." << endl;

        cout<< endl <<"Twoj wybor: "<<endl;
        cin >> wybor;


        if(wybor == '1')
        {
            dodajAdresataDoKsiazkiAdresowej (Adresaci);
        }

        else if (wybor == '2')
        {
            wyswietlAdresatowOPodanymImieniu (Adresaci);

        }


        else if (wybor == '3')
        {
            wyswietlAdresatowOPodanymNazwisku (Adresaci);
        }

        else if (wybor == '4')
        {
            wyswietlDaneWszystkichAdresatow (Adresaci);

        }

        else if (wybor == '5')
        {
            usunAdresata(Adresaci);
        }

        else if (wybor == '6')
        {
            edytujAdresata(Adresaci);
        }

        else if (wybor == '9')
        {
            exit(0);
        }


        else
        {
            cout << "Wybierz poprawny numer dostepnych opcji." << endl;
            Sleep(1500);
        }
    }

    return 0;
}
