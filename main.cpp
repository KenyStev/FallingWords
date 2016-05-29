#include <GL/gl.h>
#include <stdio.h>

#include "Rosalila/system.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

//SDL
#include "SDL2/SDL.h"
#include "Rosalila/RosalilaUtility/RosalilaUtility.h"
#include "Rosalila/RosalilaInputs/RosalilaInputs.h"
#include "Rosalila/RosalilaGraphics/RosalilaGraphics.h"
#include "Rosalila/RosalilaSound/RosalilaSound.h"

#ifdef LINUX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef WINDOWS
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef OSX
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif

#include "Font.h"
#include <time.h>
#include <stdlib.h>
#include <vector>

class Palabla{
public:
    int x, y;
    string palabra,palabra_correcta;
    Font *f;

    Palabla(string palabra1,string palabra_correcta1,int x1, int y1)
    {
        f = new Font("font.ttf");
        x = x1;
        y = y1;
        palabra = palabra1;
        palabra_correcta = palabra_correcta1;
        f->setColor(255,255,255);
        f->setSize(25);
    }

    void dibujar()
    {
        f->drawText(palabra,x,y);
        y++;
    }

    bool esCorrecta(string p)
    {
        return strcmp(palabra_correcta.c_str(),p.c_str()) == 0;
    }
};

Palabla *generarPalabraRandom(int ancho_de_pantalla,vector<Palabla*> *v)
{
    int i = rand()%v->size();
    cout<<"i: "<<i<<" p: "<<(*v)[i]->palabra.c_str()<<endl;
    (*v)[i]->x = rand()%ancho_de_pantalla;
    (*v)[i]->y = 0;
    return (*v)[i];
}

int main(int argc, char *argv[])
{
    srand (time(NULL));

    vector<Palabla*> vocabulario;

    vocabulario.push_back(new Palabla("3ztoy","ESTOY",0,0));
    vocabulario.push_back(new Palabla("aki","AQUI",0,0));
    vocabulario.push_back(new Palabla("kiero","QUIERO",0,0));
    vocabulario.push_back(new Palabla("etiketar","ETIQUETAR",0,0));
    vocabulario.push_back(new Palabla("3rmosa","HERMOSA",0,0));
    vocabulario.push_back(new Palabla("ermano","HERMANO",0,0));
    vocabulario.push_back(new Palabla("savia","SABIA",0,0));
    vocabulario.push_back(new Palabla("onduras","HONDURAS",0,0));
    vocabulario.push_back(new Palabla("deve","DEBE",0,0));
    vocabulario.push_back(new Palabla("muxas","MUCHAS",0,0));
    vocabulario.push_back(new Palabla("aser","HACER",0,0));
    //Clean the previous log
    clearLog();

    //Input receiver initialization
    Receiver* receiver = new Receiver();

    //Graphics initialization
    RosalilaGraphics* rosalila_graphics = new RosalilaGraphics();
    rosalila_graphics->video(rosalila_graphics);


    //buffer de palabra entrante
    string text = "";

    //vector de palabras
    vector<Palabla*> palabras;


    Palabla *p = new Palabla("ol@","HOLA",100,10);
    palabras.push_back(p);
    int supuntos = 0;
    int tiempo=0;

    while(true)
    {
        rosalila_graphics->drawText(toString(supuntos),1150,30);
        rosalila_graphics->drawText(text,100,rosalila_graphics->screen_height - 180);

        //guardar la palabra que escriba en la variable text
        for(int i=0; i<26;i++)
        {
            if(receiver->isKeyPressed(i+97))
            {
                char c = i+65;
                text+=c;
            }
            if(receiver->isKeyPressed(SDLK_SPACE)){
                text +=" ";
            }
        }
        if(receiver->isKeyPressed(SDLK_BACKSPACE)){
                    text ="";
        }

        //dinuja todas las palabras que tiene el vector
        for(unsigned int i=0; i<palabras.size();i++)
        {
            palabras[i]->dibujar();
        }

        //evalua si la palabra escrita es correcta con algua de las palabras del vector
        for(unsigned int i=0; i<palabras.size();i++)
        {
            if(palabras[i]->esCorrecta(text))
            {
                Palabla * p = palabras[i];
                supuntos = supuntos + 2;
                palabras.erase (palabras.begin()+i);
                text = "";
                delete p;
            }
        }

        if(tiempo%80==0)
        {
            Palabla *p = generarPalabraRandom(rosalila_graphics->screen_width,&vocabulario);
            palabras.push_back(new Palabla(p->palabra,p->palabra_correcta,p->x,p->y));
        }

        tiempo++;

        receiver->updateInputs();
        rosalila_graphics->updateScreen();
    }


    return 0;
}
