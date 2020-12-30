void meniu(double lungime, double inaltime)
{
    bool limba=0;//verifica daca e deschis meniul de limbi
    char limbaButon='R';//memoreaza limba selectata
    
    POINT CursorPosition;
    
    initwindow(800, 600);
    
    readimagefile("bckbround.jpg", 0, 0, 800, 600);
    readimagefile("buton.jpg", 300, 150, 500, 225);
    readimagefile("romania.jpg", 700, 15, 775, 50);
    
    while(1)
    {
        GetCursorPos(&CursorPosition);
        if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=15&&CursorPosition.y<=50)//meniu de limbi
        {
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                limba=1;
                readimagefile("buton.jpg", 300, 150, 500, 225);
                readimagefile("usa.jpg", 700, 65, 775, 100);
                readimagefile("germana.jpg", 700, 115, 775, 150);
                readimagefile("franceza.jpg", 700, 165, 775, 200);
            }
        }
        if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=65&&CursorPosition.y<=100&& limba==1)//schimbarea limbii pt butoane
            if(GetAsyncKeyState(VK_LBUTTON))
                {
                    readimagefile("butonen.jpg", 300, 150, 500, 225);
                    limbaButon='E';//engleza
                }
        if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=115&&CursorPosition.y<=150&& limba==1)
            if(GetAsyncKeyState(VK_LBUTTON))
                {
                    readimagefile("butonde.jpg", 300, 150, 500, 225);
                    limbaButon='D';//germana
                }
        if(CursorPosition.x >=700&&CursorPosition.x<=775&&CursorPosition.y>=165&&CursorPosition.y<=200&& limba==1)
            if(GetAsyncKeyState(VK_LBUTTON))
                {
                    readimagefile("butonfr.jpg", 300, 150, 500, 225);
                    limbaButon='F';//franceza
                }
        if(CursorPosition.x >=300&&CursorPosition.x<=500&&CursorPosition.y>=150&&CursorPosition.y<=225)//hover pt butoane
        {
            if(limbaButon=='R')
                readimagefile("buton2.jpg", 300, 150, 500, 225);
            if(limbaButon=='E')
                readimagefile("butonen2.jpg", 300, 150, 500, 225);
            if(limbaButon=='D')
                readimagefile("butonde2.jpg", 300, 150, 500, 225);
            if(limbaButon=='F')
                readimagefile("butonfr2.jpg", 300, 150, 500, 225);

            if(GetAsyncKeyState(VK_LBUTTON))//butonul care duce la grafic
            {
                delay(500);
                cleardevice();
                desenInterfata(lungime, inaltime);
            }
        }
        else//de-hover pt butoane 
        {
            if(limbaButon=='R')
                readimagefile("buton.jpg", 300, 150, 500, 225);
            if(limbaButon=='E')
                readimagefile("butonen.jpg", 300, 150, 500, 225);
            if(limbaButon=='D')
                readimagefile("butonde.jpg", 300, 150, 500, 225);
            if(limbaButon=='F')
                readimagefile("butonfr.jpg", 300, 150, 500, 225);
        }


    }
}
