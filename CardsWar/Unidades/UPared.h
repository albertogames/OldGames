#ifndef ParedH
#define ParedH

#include <vcl.h>
class TPared
{
    bool rio;
    TImage* imagen;
    public:

        TPared ( int x,int y,char* dibujo,bool r = false, TForm* paren = NULL,int w = 0,int h=0)
        {
            int ancho;
            int alto;

            imagen = new TImage(Application);
            imagen->Left = x;
            imagen->Top = y;
            imagen->Picture->LoadFromFile(dibujo);
            imagen->AutoSize = true;
            imagen->AutoSize = false;
            imagen->Stretch = true;

            imagen->Width = w;
            imagen->Height = h;
            imagen->Parent = paren;
            rio = r;
        }
        ~TPared()
        {
            if (imagen != NULL)
                delete imagen;
        }
        TPared(const TPared & p)
        {
            imagen = new TImage(Application);
            imagen->Left = p.imagen->Left;
            imagen->Top = p.imagen->Top;
            imagen->Picture = p.imagen->Picture;

            imagen->Width = p.imagen->Width;
            imagen->Height = p.imagen->Height;
            imagen->Parent = p.imagen->Parent;
            imagen->Stretch = true;

            rio = p.rio;
        }
        TPared & operator=(const TPared& p )
        {
            imagen->Picture = p.imagen->Picture;

            imagen->Left = p.imagen->Left;
            imagen->Top = p.imagen->Top;
            imagen->Width = p.imagen->Width;
            imagen->Height = p.imagen->Height;
            imagen->Parent = p.imagen->Parent;
            rio = p.rio;
            return * this;
        }

        TImage* & getImagen() {return imagen;}
        bool getRio(){return rio;}
        void setRio(bool b) {rio = b;}
};





#endif
