import javax.microedition.rms.*;
class Casilla implements Serializable
{
	public boolean abajo;
	public boolean derecha;
	public Jugador jugador;
	boolean posible;
	boolean visitada;
	Casilla()
	{
		abajo = false;
		derecha = false;
		jugador = null;
		posible = false;
		visitada = false;
	}

	public void read(Reader reader) throws ReaderException
	{
		abajo = reader.readBoolean("Partida");
		derecha = reader.readBoolean("Partida");
	}
	public void write(Writer writer) throws WriterException
	{
		writer.write("Partida",abajo);
		writer.write("Partida",derecha);
	}
}
	
