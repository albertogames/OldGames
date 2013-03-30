import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.lang.String;

public class Juego extends MIDlet 
{
	public MenuList menuList;
	public MenuList2 menuList2;
	private JugadorList jugaList;
	private JuegoCanvas jCanvas;
	public Jugador[] jugadores;
	public List list = new List("Nuevo Jugador",List.EXCLUSIVE);
	
	public Juego()
	{
		this.jugadores = new Jugador[4];	
		menuList = new MenuList(this);
		menuList2 = new MenuList2(this);
		jugaList = new JugadorList(this);
		Display.getDisplay(this).setCurrent(menuList);
	}
	
	public void startApp()
    {
    }
	public void pauseApp()
    {
    }
    public void destroyApp(boolean unconditional)
    {
	}
	public void jugadorListOk(int i)
	{
		for (int a = 0; a < 4; a++)
			jugadores[a] = null;
		for (int a = 0;a < i; a++)
			jugadores[a] = new Jugador("Jugador" + a);	
		jCanvas = new JuegoCanvas(this,jugadores);
		Display.getDisplay(this).setCurrent(jCanvas);
	}
	////////////////////////////////////////////////
	public void menuListComenzarJuego()
	{
		Display.getDisplay(this).setCurrent(menuList2);
	}
	public void menuListPuntuaciones()
	{

	}
	///////////////////////////////////////////////////
	public void menuList2NuevoJuego()
	{
		Display.getDisplay(this).setCurrent(jugaList);
	}
	public void menuList2CargarJuego()
	{
		jCanvas = new JuegoCanvas(this,null);
		Display.getDisplay(this).setCurrent(jCanvas);
	}
	////////////////////////////////////////////////////
	public void volverPantallaPrincipal()
	{
		Display.getDisplay(this).setCurrent(menuList);
	}
	public void menuListCreditos()
	{

	}
	public void menuListSalir()
	{
		destroyApp(false);
        notifyDestroyed();
	}
}