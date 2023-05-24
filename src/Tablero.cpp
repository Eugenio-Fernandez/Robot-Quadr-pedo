#include "Tablero.h"
#include <stdio.h>
#include "freeglut.h"
#include "ETSIDI.h"
#include <iostream>
using namespace std;

/*Blancas + y negras -
Alfil 1
Caballo 2
Pe�n 3
Reina 4
Rey 5
Torre 6
Vac�a 0*/

int Tablero::start[8][8] = { {6,2,1,5,4,1,2,6} , {3,3,3,3,3,3,3,3} , {0,0,0,0,0,0,0,0} , {0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0} , {0,0,0,0,0,0,0,0} , {-3,-3,-3,-3,-3,-3,-3,-3} , {-6,-2,-1,-5,-4,-1,-2,-6} };

Tablero::Tablero() {
    // Inicializar las casillas del tablero
    for (int fila = 0; fila < TAM_TABLERO; fila++) {
        for (int columna = 0; columna < TAM_TABLERO; columna++) {
            casillas[fila][columna] = nullptr;
        }
    }
}

void Tablero::inicio()
{
    for (int i = 0; i < TAM_TABLERO; i++) {
        for (int j = 0; j < TAM_TABLERO; j++) {
            tablero[i][j] = start[i][j];
        }
    }
    for (int i = 0; i < 2; i++) {
        Coordenada pos = coordTab[0 + 56 * i];
        Torre* aux = new Torre(pos, i);
        piezas.agregar(aux);
        pos = coordTab[7 + 56 * i];
        Torre* aux1 = new Torre(pos, i);
        piezas.agregar(aux1);
        pos = coordTab[2 + 56 * i];
        Alfil* aux2 = new Alfil(pos, i);
        piezas.agregar(aux2);
        pos = coordTab[5 + 56 * i];
        Alfil* aux3 = new Alfil(pos, i);
        piezas.agregar(aux3);
        pos = coordTab[1 + 56 * i];
        Caballo* aux4 = new Caballo(pos, i);
        piezas.agregar(aux4);
        pos = coordTab[6 + 56 * i];
        Caballo* aux5 = new Caballo(pos, i);
        piezas.agregar(aux5);
        pos = coordTab[3 + 56 * i];
        Reina* aux6 = new Reina(pos, i);
        piezas.agregar(aux6);
        pos = coordTab[4 + 56 * i];
        Rey* aux7 = new Rey(pos, i);
        piezas.agregar(aux7);
        for (int j = 0; j < 8; j++)
        {
            pos = coordTab[j + 48 * i];
            Peon* auxp = new Peon(pos, i);
            piezas.agregar(auxp);
        }
    }
}

void Tablero::setCoord()
{
    int k = 0;
    for (int j = 0; j < TAM_TABLERO; j++) {
        for (int i = 0; i < TAM_TABLERO; i++) {
            coordTab[k].x = (1.0001 - i * 0.25);
            coordTab[k].y = (0.99 - j * 0.25);
            k++;
            //std::cout << coordTab[k-1].x << " , " << coordTab[k-1].y << " , " << k << "\n";
        }
    }
}

Tablero::~Tablero() {
    // Eliminar todas las piezas del tablero
    for (int fila = 0; fila < TAM_TABLERO; fila++) {
        for (int columna = 0; columna < TAM_TABLERO; columna++) {
            if (casillas[fila][columna] != nullptr) {
                delete casillas[fila][columna];
                casillas[fila][columna] = nullptr;
            }
        }
    }
}

void Tablero::dibuja() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Tablero.png").id);
    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0, 1); glVertex2f(-1,-1);
    glTexCoord2d(1, 1); glVertex2f(1, -1);
    glTexCoord2d(1, 0); glVertex2f(1, 1);
    glTexCoord2d(0, 0); glVertex2f(-1, 1);
    glEnd();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    

}

void Tablero::dibuja_selector() {
    sprite_selector.setSize(0.25, 0.25);
    sprite_selector.setCenter(1 + ((-1.0) * selector.getFila() / 4), 1.0 - 1.0 * selector.getColumna() / 4);
    sprite_selector.draw();
    glPopMatrix();
}

void Tablero::tecla_selector(unsigned char key) {
    selector.mover(key);

    if ((interaccion.getAccion() == TRUE)&&(key == ' ')) {
        interaccion.mover_pieza(selector, piezas, accion);
    }

    if (key == ' ') {
        selector.setOrigen();
        interaccion.setAccion();
    }   
}