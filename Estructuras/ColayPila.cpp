#include <cstdlib>
#include <iostream>
#include <conio.h>

using namespace std;
	

struct Pila{
	int inf ;
	struct Pila *sigP;
	struct Pila *antP;
};

struct Cola{
	int inf;
	struct Cola *sigC;
	struct Cola *antC;
	struct Pila *SigFam;
};

struct Cola *priC,*ultC,*nueC,*auxC;
struct Pila *priP,*nueP,*auxP,*ultP;


int opcion;

void iniciar(void){
	auxC = priC;
	while (auxC != NULL){
		auxP = auxC->SigFam;
		while (auxP!=NULL){
			priP = auxP->sigP;
			delete (auxP);
			auxP = priP;
		}
		priC = auxC->sigC;
		delete (auxC);
		auxC = priC;
	}
	cout << "\nEstructura inicializada\n";
	system("pause");
}

void ins_Principal(void)
{
	if (priC == NULL)
	{
		cout << "Ingresar Primer principal: ";
		priC = new Cola();
		cin >> priC -> inf;
		ultC = priC;

		///Enlace Anterior a NULL
		ultC -> sigC = NULL; 
		///Enlace Anterior a NULL
        ultC -> antC = NULL; //New Line
 
		priC -> SigFam = NULL;
	}
	else
	{
		cout << "Ingresar Nuevo Principal: ";
		nueC = new Cola();
		cin >> nueC -> inf;
		auxC = priC;
		while (auxC != NULL && auxC -> inf != nueC -> inf)
		{
		   auxC = auxC -> sigC;
		}
		if (auxC != NULL)
		{
			cout << "El Principal ya existe\n";
			delete (nueC);
			system("pause");
		}
		else
		{
            //Enlace SIGUIENTE al nuevo nodo
			ultC -> sigC = nueC;
            // Enlace ANTERIOR del nuevo nodo
            nueC -> antC = ultC; // New Line
            
			ultC = nueC;
			ultC -> sigC = NULL;
			ultC -> SigFam = NULL;
		}
	}
}

void ins_familia (void)
{
 int principal;
 if (priC==NULL)
 {
		cout << "No hay datos...\n";
		system("pause");
 }
 else
 {
  cout << "\nIngresar familia = ";
  nueP = new Pila();
		cin >> nueP->inf;
		cout << "\nPerteneciente al principal  ";
		cin >> principal;
		auxC = priC;
		while (auxC != NULL && auxC->inf != principal )
  		{
			auxC = auxC -> sigC;
		}
		if (auxC == NULL){
			cout << "El principal no existe\n";
			delete (nueP);
			system("pause");
		}
		else{
			if (auxC -> SigFam == NULL){
				auxC -> SigFam = nueP;

				nueP -> sigP = NULL; 
                nueP -> antP = NULL; //new line


                priP = nueP; //newline
                ultP = nueP; //newline
			}
			else{
				//nueP->sigP = auxC->SigFam; //Quite esta linea
                
                //el padre apunta al nuevo
				auxC->SigFam = nueP;
                //Nuevo apunta al primero de la pila con el enlace siguiente
                nueP->sigP = priP; //new line
                //El primero de la pila apunto al nuevo con el enlace anterior
                priP->antP = nueP; // new line
                // el nuevo es ahora el primero en la pila
                priP=nueP;

			}
		}
	}
}


void lis_Principal(void){
	if (priC==NULL){
		cout << "No hay datos\n";
		system("pause");
	}
	else{
		auxC=priC;
		while(auxC!=NULL){
			cout << "\nPrincipal= " << auxC->inf;
			auxC= auxC->sigC;
		}
		cout << endl;
		system("pause");
	}
}

void lis_familia (void){
 int principal;
	if (priC==NULL){
		cout << "No hay datos...\n";
		system("pause");
	}
	else{
		cout << "\nPrincipal =  ";
		cin >> principal ;
		auxC = priC;
		while (auxC!=NULL && auxC ->inf != principal){
			auxC= auxC->sigC;
		}
		if (auxC == NULL){
			cout << "Principal no existe\n";
			system("pause");
		}
		else{
			auxP=auxC->SigFam;
			while (auxP!=NULL){
				cout << "\nfamilia = " << auxP->inf;
				auxP = auxP->sigP;
			}
			cout << endl;
			system("pause");
		}
	}
}

void lis_estructura()
{
 if(priC == NULL)     
   cout << "\nNo hay datos.";
 else
 {
   auxC = priC;
   while(auxC != NULL)        
   {
    cout << "\n\nPrincipal: " << auxC->inf;
    auxP = auxC->SigFam;
    while(auxP != NULL)
    {
     cout << "\n\tfamilia : " << auxP->inf;
     auxP = auxP->sigP;
    }
    auxC=auxC->sigC;
   }
 }
 cout << endl;
 system("pause");
}

int main(int argc, char *argv[])
{

	priC = NULL;
	do{
		system("cls");
		cout << "\n1. Inicializar";
		cout << "\n2. Insertar Principal";
		cout << "\n3. Insertar familia ";
		cout << "\n4. Listar Principals";
		cout << "\n5. Listar familia s";
		cout << "\n6. Listar Estructura";
		cout << "\n9. Salir\n";
		cout << "\n   Digite Opcion: ";
		cin >> opcion;
		switch (opcion){
			case 1:  //inicializar
				iniciar();
				break;
			case 2:	//insertar Principal
				ins_Principal();
				break;
			case 3:	//insertar familias
				ins_familia ();
				break;
			case 4:	//listar Principals
				lis_Principal();
				break;
			case 5: //listar familia s
				lis_familia ();
				break;
			case 6: //listar familias
				lis_estructura();
				break;
		}
	}
	while (opcion!=9);
    return EXIT_SUCCESS;
}