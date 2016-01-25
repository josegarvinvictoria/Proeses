#include <iostream>
#include <fstream>
#include <vector>

/*
 * Variables necessaries per determinar l'ubicació de l'executable
 * del programa.
 */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else

#define GetCurrentDir getcwd
#endif


using namespace std;

//int tempsPersonalitats[20][2];
string personalitats[20][2];
int numPersonalitats = 0;

void mostraBenvinguda();


/*
 * Funció per determinar l'ubicació de l'arxiu executable del programa.
 */
string getCurrentDir() {

    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
        return "Error";
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

    return cCurrentPath;
}

string obtenirInformacio(string linia, int informacioAcercar) {

    int pos = linia.find_first_of("-");
    string info;
    //Si informacioAcercar == 0, entendrem que es vol cercar
    //el nom del jugador, si informacioAcercar != 0 es voldrà cercar l'equip.
    if (informacioAcercar == 0) {
        info = linia.substr(0, pos);
    } else {
        info = linia.substr(pos + 1, sizeof(linia));
    }


    return info;
}

void canviOrdre(int index) {
    //cout << "Cal reordenar a " + personalitats[index][0] << endl;
    string temp1 = personalitats[index][0];
    string temp2 = personalitats[index][1];
    personalitats[index][0] = personalitats[index + 1][0];
    personalitats[index][1] = personalitats[index + 1][1];
    personalitats[index + 1][0] = temp1;
    personalitats[index + 1][1] = temp2;


}

void ordenarPersonalitats() {
    for (int i = 0; i < numPersonalitats - 1; i++) {


        if (personalitats[i][0].at(0) > personalitats[i + 1][0].at(0)) {
            canviOrdre(i);

        } else {

        }
        //cout << personalitats[i] << endl;

    }
}


void llegirFitxer() {
    ifstream file("entrada.txt");
    string linia;


    if (file.fail()) {
        cout << "Error a l'obrir l'arxiu!" << endl;
    } else {
        while (getline(file, linia)) {
            if (linia != "#") {
                string nomJugador = obtenirInformacio(linia, 0);
                string nomEquip = obtenirInformacio(linia, 1);
                personalitats[numPersonalitats][0] = nomJugador;
                personalitats[numPersonalitats][1] = nomEquip;
                numPersonalitats++;
            } else {
                break;
            }

        }
        printf("S'han afegit %i personalitats noves! \n", numPersonalitats);
    }

}

void mostraPersonalitats() {
    for (int i = 0; i < numPersonalitats; i++) {
        printf("%s ", personalitats[i][0].c_str());
    }
}


void menuNovaInformacio() {
    cout << "(i) NOVA INFORMACIO - (b) BAIXA - (s) SORTIR:" << endl;

    char opcio;
    cin >> opcio;

    switch (opcio) {
        case 'i':
            cout << "Nova info" << endl;

        case 'b':
            cout << "Baixa" << endl;

        case 's':
            mostraBenvinguda();
    }
}


void mostraBenvinguda() {
    cout << "- BENVINGUTS RANQUING DE PROESES - \n" << endl;
    cout << "PERSONALITATS INICIALS: " << endl;


    mostraPersonalitats();
    int opcio;
    cout << " \n \n 1- INTRODUCCIO D'INFORMACIO | 2- MOSTRAR RANKING | 3- SORTIR" << endl;

    cin >> opcio;

    switch (opcio) {
        case 1:

            menuNovaInformacio();

            break;
        case 2:
            //MenuRanking
            cout << "Opcio2" << endl;
            break;

        case 3:
            exit(EXIT_SUCCESS);

    }

}


void mostrarMenu1() {

}


int main() {
    getCurrentDir();
    llegirFitxer();
    ordenarPersonalitats();
    mostraBenvinguda();


    return 0;
}