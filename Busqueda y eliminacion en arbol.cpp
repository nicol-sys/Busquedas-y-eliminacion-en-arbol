#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
};

void insertar(Nodo*&, int);
void MostrararbolPreorden(Nodo*);
void MostrararbolInorden(Nodo*);
void MostrararbolPosorden(Nodo*);
bool busquedapreorden(Nodo*, int);
bool busquedainorden(Nodo*, int);
bool busquedaposorden(Nodo*, int);

int main() {
    Nodo* arbol = NULL;
    int opcion, dato;

    while (true) {
        cout << "MENU" << endl;
        cout << "1. Insertar un número" << endl;
        cout << "2. Buscar en preorden" << endl;
        cout << "3. Buscar en inorden" << endl;
        cout << "4. Buscar en posorden" << endl;
        cout << "5. Eliminar un Nodo" << endl;
        cout << "6. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Digite un número: ";
                cin >> dato;
                insertar(arbol, dato);
                break;
            case 2:
                cout << "Digite un número: ";
                cin >> dato;
                if (busquedapreorden(arbol, dato)) {
                    cout << "El elemento " << dato << " ha sido encontrado en preorden" << endl;
                    MostrararbolPreorden(arbol);
                    cout << endl;
                } else {
                    cout << "El elemento " << dato << " no ha sido encontrado en preorden" << endl;
                }
                break;
            case 3:
                cout << "Digite un número: ";
                cin >> dato;
                if (busquedainorden(arbol, dato)) {
                    cout << "El elemento " << dato << " ha sido encontrado en inorden" << endl;
                    MostrararbolInorden(arbol);
                    cout << endl;
                } else {
                    cout << "El elemento " << dato << " no ha sido encontrado en inorden" << endl;
                }
                break;
            case 4:
                cout << "Digite un número: ";
                cin >> dato;
                if (busquedaposorden(arbol, dato)) {
                    cout << "El elemento " << dato << " ha sido encontrado en posorden" << endl;
                    MostrararbolPosorden(arbol);
                    cout << endl;
                } else {
                    cout << "El elemento " << dato << " no ha sido encontrado en posorden" << endl;
                }
                break;
            case 5:
                cout << "Digite un número a eliminar: ";
                cin >> dato;
                eliminar(arbol, dato);
                cout << "El elemento " << dato << " ha sido eliminado" << endl;
                break;
            case 6:
                cout << "Saliendo del programa." << endl;
                return 0;
            default:
                cout << "Opción no válida" << endl;
        }
    }

    return 0;
}

void insertar(Nodo*& arbol, int x) {
    if (arbol == NULL) {
        arbol = new Nodo();
        arbol->dato = x;
        arbol->izquierda = NULL;
        arbol->derecha = NULL;
        cout << "El elemento " << x << " ha sido insertado" << endl;
    } else if (arbol->dato == x) {
        cout << "El elemento " << x << " ya existe en el árbol" << endl;
    } else if (arbol->dato > x) {
        insertar(arbol->izquierda, x);
    } else {
        insertar(arbol->derecha, x);
    }
}

void MostrararbolPreorden(Nodo* arbol) {
    if (arbol != NULL) {
        cout << arbol->dato << " ";
        MostrararbolPreorden(arbol->izquierda);
        MostrararbolPreorden(arbol->derecha);
    }
}

void MostrararbolInorden(Nodo* arbol) {
    if (arbol != NULL) {
        MostrararbolInorden(arbol->izquierda);
        cout << arbol->dato << " ";
        MostrararbolInorden(arbol->derecha);
    }
}

void MostrararbolPosorden(Nodo* arbol) {
    if (arbol != NULL) {
        MostrararbolPosorden(arbol->izquierda);
        MostrararbolPosorden(arbol->derecha);
        cout << arbol->dato << " ";
    }
}

bool busquedapreorden(Nodo* arbol, int x) {
    if (arbol == NULL) {
        return false;
    }
    if (arbol->dato == x) {
        return true;
    }
    if (busquedapreorden(arbol->izquierda, x)) {
        return true;
    }
    return busquedapreorden(arbol->derecha, x);
}

bool busquedainorden(Nodo* arbol, int x) {
    if (arbol == NULL) {
        return false;
    }
    if (busquedainorden(arbol->izquierda, x)) {
        return true;
    }
    if (arbol->dato == x) {
        return true;
    }
    return busquedainorden(arbol->derecha, x);
}

bool busquedaposorden(Nodo* arbol, int x) {
    if (arbol == NULL) {
        return false;
    }
    if (busquedaposorden(arbol->izquierda, x)) {
        return true;
    }
    if (busquedaposorden(arbol->derecha, x)) {
        return true;
    }
    if (arbol->dato == x) {
        return true;
    }
    return false;
}

void eliminar(Nodo*& arbol, int x) {
    if (arbol == NULL) {
        return;
    }
    //si solo hay un Nodo pues eliminarlo
    if (x < arbol->dato) {
        eliminar(arbol->izquierda, x);
    } else if (x > arbol->dato) {
        eliminar(arbol->derecha, x);
    } else {
        //Nodo sin hijos o con un hijo
        if (arbol->izquierda == NULL) {
            Nodo* temp = arbol->derecha;
            delete arbol;
            arbol = temp;
        } else if (arbol->derecha == NULL) {
            Nodo* temp = arbol->izquierda;
            delete arbol;
            arbol = temp;
        } else {
            //Nodo con dos hijos
            // Encontrar el sucesor inorden (nodo más pequeño en subárbol derecho)
            Nodo* sucesor = arbol->derecha;
            while (sucesor->izquierda != NULL) {
                sucesor = sucesor->izquierda;
            }
            arbol->dato = sucesor->dato;
            // Eliminar el sucesor
            eliminar(arbol->derecha, sucesor->dato);
        }
    }