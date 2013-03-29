import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class MenuList extends List implements CommandListener
{
	private Juego midlet;
	public MenuList(Juego midlet)
    {
		super("Elija opcion", List.IMPLICIT);
        this.midlet = midlet;
		append("Comenzar", null);
		append("Salir", null);
		
		setCommandListener(this);
    }
    public void commandAction(Command c, Displayable d)
    {
        if (c == List.SELECT_COMMAND)
        {
            int index = getSelectedIndex();
            switch (index)
            {
				case 0:	  //Comenzar
					midlet.menuListComenzarJuego();
					break;
                case 1:   // New game
                    midlet.menuListSalir();
                    break;
            }
         }
    }
}