#include <iostream>
#include <fstream>

/*
 * Variables necessaries per determinar l'ubicació de l'executable
 * del programa.
 */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else

#include <unistd.h>

#define GetCurrentDir getcwd
#endif


using namespace std;

string personalitats[20][2];
int numPersonalitats = 0;

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

void mostraPersonalitats(){
        for(int i = 0; i<numPersonalitats;i++){
            printf("%s ", personalitats[i][0].c_str());
    }
}



void mostraMenu(){
    cout << "- BENVINGUTS RANQUING DE PROESES -" <<  endl;
    cout << "PERSONALITATS INICIALS:" << endl;
    mostraPersonalitats();

}


int main() {
    getCurrentDir();
    llegirFitxer();
    ordenarPersonalitats();
    mostraMenu();


    return 0;
}