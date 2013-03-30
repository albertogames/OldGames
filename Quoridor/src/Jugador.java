import javax.microedition.rms.*;
class Jugador implements Serializable
{
	public String nombre;
	private int pGandas;
	private int pPerdidas;
	public int posX;
	public int posY;
	public int barreras;
	
	Jugador(String nombre)
	{
		this.nombre =  nombre;
		posX = 0;
		posY = 0;
		barreras = 8;
	}
	
	Jugador()
	{
		this.nombre =  null;
		posX = 0;
		posY = 0;
		barreras = 8;
	}

	public void read(Reader reader) throws ReaderException
	{
		nombre = reader.readString("Partida");
		posX = reader.readInt("Partida");
		posY = reader.readInt("Partida");
		barreras = reader.readInt("Partida");
	}
	public void write(Writer writer) throws WriterException
	{
		writer.write("Partida",this.nombre);
		writer.write("Partida",posX);
		writer.write("Partida",posY);
		writer.write("Partida",barreras);
	}
}