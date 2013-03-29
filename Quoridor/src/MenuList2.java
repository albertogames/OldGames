import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class MenuList2 extends List implements CommandListener
{
	private Juego midlet;
  private Command exitCommand;
	public MenuList2(Juego midlet)
    {
		super("Elija opcion", List.IMPLICIT);
        this.midlet = midlet;
		exitCommand = new Command("Salir", Command.EXIT,2);
		append("Nuevo juego", null);
		append("Cargar", null);
		addCommand(exitCommand);		
		setCommandListener(this);

    }
    public void commandAction(Command c, Displayable d)
    {
        if (c == List.SELECT_COMMAND)
        {
            int index = getSelectedIndex();
            switch (index)
            {
				case 0:	  //Nuevo Juego
					midlet.menuList2NuevoJuego();
					break;
				case 1:  //Cargar
					midlet.menuList2CargarJuego();
            }
         }
		 else if (c == exitCommand)
			midlet.volverPantallaPrincipal();
    }
 
}