//============================================================================
// Name        : Raid.cpp
// Author      : yp
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Disk.h"


using namespace std;

Disk* disco1 = new Disk("Disco1");
//vector<string> data_A_Agregar;

void copiaArchivo(const char archivoorigen[],const char archivodestino[]){
	unsigned int c;
	FILE *f1 = fopen(archivoorigen, "rb");
	FILE *f2 = fopen(archivodestino, "wb");

	if(f1 == NULL || f2 == NULL){
		printf("El archivo de origen o la ruta de destino son erroneas");
		exit(EXIT_FAILURE);
	}

	while(!feof(f1)){
		c = getc(f1);
		fputc(c, f2);
	}
	fclose(f1);
	fclose(f2);

}

void copiarTxt(string entrada1, string salida1){
	string linea;
	ifstream entrada (entrada1); //( "entrada.txt" );
	ofstream salida (salida1); //("salida.txt");

	if (salida.is_open()) {
		if (entrada.is_open()){
			while (getline (entrada,linea)) {
				salida << linea << endl;
			}
			entrada.close(); // No necesario, se cerrara al salir del bloque
		}
		else {
			cout << "No se ha podido abrir entrada.txt!"<<endl;
		}
		salida.close(); // No necesario, se cerrara al salir del bloque
	}
	else {
		cout << "No se ha podido crear salida.txt!!!!"<<endl;;
	}

}




void mirroring( int numeroNodos ){

	for(int i = 1; i <= numeroNodos; i++){
		try{
			string ruta1 = "/home/victork/Documentos/PROGRAMACION/Workspace/Raid de Prueba/DISCO 1/Block";
			string ruta2 = to_string(i) + ".txt";
			string rutaOrigen = ruta1 + ruta2;
			ruta1 = "/home/victork/Documentos/PROGRAMACION/Workspace/Raid de Prueba/Disco Espejo/Block";
			ruta2 = to_string(i) + ".txt";
			string rutaDestino = ruta1 + ruta2;

			copiarTxt(rutaOrigen, rutaDestino);
			//copiaArchivo(rutaOrigen.c_str(), rutaDestino.c_str());

		}
		catch(exception const& e){
			cout << "Erro al hacer Mirroring" << endl;
			break;
		}
	}
}

void anadirNewData(string dataBuffer[], int numBloque){
	for(int i = 0; i< 4; i++){
		disco1->saveDataBlock(dataBuffer[i], numBloque);
	}
	disco1->saveDataBlock(".", numBloque);
}

int main() {

	int j =0;
	while(j<5){
		for(int i =0; i<4;i++){
			disco1->saveDataBlock("000111", 0);
			//disco1->saveDataBlock("AAAAAAAAAAAAAAaaa", 0);
			//disco1->saveDataBlock(".", 0);
		}
		disco1->saveDataBlock(".", 0);
		j++;
	}

	mirroring( 3 );
	cout<<endl;
	disco1->leerBloque(0);

	string buffer_dataPorAgregar[] = {"VICTOR", "5123084", "CE","BALIN"};
	anadirNewData(buffer_dataPorAgregar, 0);
	mirroring( 3 );
	disco1->leerBloque(0);

	delete(disco1);

	return 0;
}
