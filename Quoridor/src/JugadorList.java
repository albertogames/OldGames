import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;

public class JugadorList extends List implements CommandListener
{
  private Juego midlet;
  private Command exitCommand , okCommand;
  public JugadorList(Juego midlet)
  {
    super("Seleccione numero de jugadores", List.EXCLUSIVE);
	this.midlet = midlet;
	exitCommand = new Command("Salir", Command.EXIT,2);
    okCommand = new Command("OK",Command.OK,1);
    append("2", null);
    append("3", null);
	append("4", null);
	addCommand(exitCommand);
	addCommand(okCommand);
	
	setCommandListener(this);
  }
  
   public void commandAction(Command c, Displayable d)
    {
        if (c == exitCommand)
			midlet.volverPantallaPrincipal();
		else if(c == okCommand)
		{
            int index = getSelectedIndex();
			midlet.jugadorListOk(index + 2);
         }
    }
}