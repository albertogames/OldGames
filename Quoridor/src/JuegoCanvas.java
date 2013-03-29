import javax.microedition.rms.*;
import java.util.Random;
import java.util.Vector;
import javax.microedition.lcdui.*;
import java.io.*;


class JuegoCanvas extends Canvas implements CommandListener,Serializable
{
	private Casilla[][] mesa;
	private CasillaMover casillaMover;
	private BarreraMover barreraMover;
	private int alto;
	private int ancho;
	private int sAncho;
	private int sAlto;
	private int rAncho;
	private int numJugadores;
	private Jugador[] jugadores;
	private Command salir;
	private Command barrera;
	private Command guardar;
	private Juego midlet;
	private Jugador jCurso;
	private int vjCurso = -1;
	private int estado = 0; //mover o poner barrera
	private int partidaGanada = -1;
	public WriterJ2MERMS WriterJ2ME;
	public ReaderJ2MERMS ReaderJ2ME;
	JuegoCanvas(Juego midlet,Jugador [] jug)
	{
		this.midlet = midlet;
		barrera = new Command("Barrera",Command.OK,0);
		salir = new Command("Salir",Command.EXIT,1);
		guardar = new Command("Guardar",Command.EXIT,2);
		this.addCommand(barrera);
		this.addCommand(guardar);
		this.addCommand(salir);
		this.setCommandListener(this);
			
		barreraMover = new BarreraMover(); 
			
		casillaMover = new CasillaMover();
		alto = getHeight();
		ancho = getWidth();
		sAncho = ancho / 100;
		sAlto = alto / 100;
		rAncho =  (ancho - sAncho*2)/9;
			
		this.mesa = new Casilla[9][9];
		for (int x = 0 ; x < 9 ; x++)
			for (int y = 0 ; y < 9; y++)
				mesa[x][y] =  new Casilla();
		if (jug != null)
		{
			jugadores = jug;
			int cont;
			for (cont = 0; cont < 4 && jugadores[cont] != null;cont++);
			numJugadores = cont;
			
			for (int  i = 0; i < 4 ;i++)
				if (jugadores[i] != null)
				{
					int x = 0;
					int y = 0;
					//Colocar a los jugadores en sus respectivas posiciones
					if (i == 0)
					{
						x = 4; 
						y = 8;
					}
					else if (i == 1)
					{
						x = 4;
						y = 0;
					}
					else if ( i == 2)
					{
						x = 0;
						y = 4;
					}
					else if ( i == 3)
					{
						x = 8;
						y = 4; 
					}
					jugadores[i].posX = x; 
					jugadores[i].posY = y;
					//Puntero desde la casilla hasta le jugador que este en ella
					mesa[x][y].jugador = jugadores[i];
				}
			
			cambiarJugador();
		}
		else
		{
			try{
				read(new ReaderJ2MERMS());
			}
			catch (ReaderException ex){
			}	
		}
		this.repaint();
	}
	protected void keyPressed(int keyCode) {
	if (estado != -1)
	{
		switch(getGameAction(keyCode)){
			case Canvas.DOWN: 
			{	
				if (estado == 0)
				{
					if (casillaMover.y < 8)
						casillaMover.y++;
				}
				else
				{
					if (barreraMover.horizontal == true && barreraMover.y1 < 8)
						barreraMover.y1++;
					else if (barreraMover.horizontal == false && barreraMover.y1  + 1< 8)
						barreraMover.y1++;
				}	
				break; 
			}
			case Canvas.LEFT: 
			{ 
				if (estado == 0)
				{
					if (casillaMover.x > 0)
						casillaMover.x--;
				}
				else
				{
					if (barreraMover.horizontal == true && barreraMover.x1  + 1 > 1)
						barreraMover.x1--;
					else if (barreraMover.horizontal == false && barreraMover.x1 > 1)
						barreraMover.x1--;
				}
				break;
			}
			case Canvas.UP: 
			{ 
				if (estado == 0)
				{
					if (casillaMover.y > 0)
						casillaMover.y--;
				}
				else
				{
					if (barreraMover.horizontal == true && barreraMover.y1 > 1)
						barreraMover.y1--;
					else if (barreraMover.horizontal == false && barreraMover.y1  + 1> 1)
						barreraMover.y1--;
				}
				break;
			}
			case Canvas.RIGHT:
			{ 
				if (estado == 0)
				{
					if (casillaMover.x < 8)
						casillaMover.x++;
				}
				else
				{
					if (barreraMover.horizontal == true && barreraMover.x1 + 1 < 8)
						barreraMover.x1++;
					else if (barreraMover.horizontal == false && barreraMover.x1 < 8)
						barreraMover.x1++;
				}
				break;
			}
			case Canvas.FIRE:
			{
				if (estado == 0)
				{	
					if (mesa[casillaMover.x][casillaMover.y].posible == true)
					{
						mesa[jCurso.posX][jCurso.posY].jugador = null;
						jCurso.posX = casillaMover.x;
						jCurso.posY = casillaMover.y;
						mesa[jCurso.posX][jCurso.posY].jugador = jCurso;
						cambiarJugador();
					}
				}
				else
				{
					if (barreraMover.horizontal == true)
					{
						if ( mesa[barreraMover.x1][barreraMover.y1 - 1].abajo ==  false && mesa[barreraMover.x1 + 1][barreraMover.y1 - 1].abajo ==  false
						    && (mesa[barreraMover.x1][barreraMover.y1 - 1].derecha ==  false || mesa[barreraMover.x1][barreraMover.y1].derecha ==  false))
						{	
							mesa[barreraMover.x1][barreraMover.y1 - 1].abajo =  true;
							mesa[barreraMover.x1 + 1][barreraMover.y1 - 1].abajo =  true;
							jCurso.barreras--;
							estado = 0;
							cambiarJugador();
						}
					}
					else
					{
						if (mesa[barreraMover.x1 - 1][barreraMover.y1].derecha ==  false && mesa[barreraMover.x1 - 1 ][barreraMover.y1 + 1].derecha ==  false
						    && (mesa[barreraMover.x1 - 1][barreraMover.y1].abajo ==  false || mesa[barreraMover.x1][barreraMover.y1].abajo ==  false) )
						{	
							mesa[barreraMover.x1 - 1][barreraMover.y1].derecha =  true;
							mesa[barreraMover.x1 - 1 ][barreraMover.y1 + 1].derecha =  true;
							jCurso.barreras--;
							estado = 0;
							cambiarJugador();
						}
					}

				}
				break;
			}
		}
		switch (keyCode)
		{
			case Canvas.KEY_POUND:
			{
				if (estado == 1)
				{
					if (barreraMover.horizontal == true)
					{
						barreraMover.horizontal = false;
						barreraMover.y1--;
						barreraMover.x1++;
					}
					else
					{
						barreraMover.horizontal = true;
						barreraMover.y1++; 
						barreraMover.x1--; 
					}
				}
				break;
			}
		}
		this.repaint();
	}
	}
	public void cambiarJugador()
	{
		//utilizar mejor variable estatica del procedimieto
		if (vjCurso == 0 && jCurso.posY == 0)
			partidaGanada = 0;
		else if (vjCurso == 1 && jCurso.posY == 8)
			partidaGanada = 1;
		else if (vjCurso == 2 && jCurso.posX == 8)
			partidaGanada = 2;
		else if (vjCurso == 3 && jCurso.posX == 0)
			partidaGanada = 3;
		
		if (partidaGanada == -1)
		{
			if (vjCurso == 3 || jugadores[++vjCurso] == null)
				vjCurso = 0;
			jCurso = jugadores[vjCurso];
			calcularCasillasPosibles();
		}
		else
			estado = -1;
	}

	public void commandAction(Command c, Displayable d){
		if (c == salir){		
			midlet.volverPantallaPrincipal();
		}
		if (c == barrera && partidaGanada == -1){
			//0 mover,1 barrera
			if (estado == 0)
			{
				if (jCurso.barreras > 0)
					estado = 1;
			}
			else
			{	
				estado = 0;
				calcularCasillasPosibles();
			}
			this.repaint(); //redibujar para que se borre o se vuelva a poner el cuadro que indica donde se va a mover
		}
		if (c == guardar)
		{
				try {
					write(new WriterJ2MERMS());
				}
				catch (WriterException ex){
				}
		}
	}	
	
	public void calcularCasillasPosibles()
	{
		casillaMover.x = jCurso.posX;
		casillaMover.y = jCurso.posY;
		
		for (int x = 0 ; x < 9 ; x++)
			for (int y = 0 ; y < 9; y++)
				mesa[x][y].posible = false;
		
		if (jCurso.posX < 8 && mesa[jCurso.posX][jCurso.posY].derecha == false && mesa[jCurso.posX + 1][jCurso.posY].jugador == null)
			mesa[jCurso.posX + 1  ][jCurso.posY].posible = true;

		if (jCurso.posX > 0 && mesa[jCurso.posX - 1][jCurso.posY].derecha == false && mesa[jCurso.posX - 1][jCurso.posY].jugador == null)
			mesa[jCurso.posX - 1][jCurso.posY].posible = true;

		if (jCurso.posY < 8 && mesa[jCurso.posX][jCurso.posY].abajo == false && mesa[jCurso.posX][jCurso.posY + 1 ].jugador == null)
			mesa[jCurso.posX][jCurso.posY + 1].posible = true;

		if (jCurso.posY > 0 && mesa[jCurso.posX][jCurso.posY - 1].abajo == false && mesa[jCurso.posX][jCurso.posY - 1].jugador == null)	
			mesa[jCurso.posX][jCurso.posY - 1].posible = true;
		
		//SALTAR AL JUGADOR 
		if (jCurso.posX > 1 && mesa[jCurso.posX-1][jCurso.posY].jugador != null)
		{
			if( mesa[jCurso.posX-2][jCurso.posY].derecha == false && mesa[jCurso.posX-2][jCurso.posY].jugador == null)
				mesa[jCurso.posX-2][jCurso.posY].posible = true;
			else
			{
				if(mesa[jCurso.posX-1][jCurso.posY-1].abajo == false && mesa[jCurso.posX-1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX-1][jCurso.posY-1].posible = true;
				if(mesa[jCurso.posX-1][jCurso.posY].abajo ==  false && mesa[jCurso.posX-1][jCurso.posY+1].jugador == null)
					mesa[jCurso.posX-1][jCurso.posY+1].posible = true;
			}
		}
		
		if (jCurso.posX < 7 && mesa[jCurso.posX+1][jCurso.posY].jugador != null)
		{	
			if( mesa[jCurso.posX+1][jCurso.posY].derecha == false && mesa[jCurso.posX+2][jCurso.posY].jugador == null)
				mesa[jCurso.posX+2][jCurso.posY].posible = true;
			else
			{
				if(mesa[jCurso.posX+1][jCurso.posY-1].abajo == false && mesa[jCurso.posX+1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX+1][jCurso.posY-1].posible = true;
				if(mesa[jCurso.posX+1][jCurso.posY].abajo ==  false && mesa[jCurso.posX+1][jCurso.posY+1].jugador == null)
					mesa[jCurso.posX+1][jCurso.posY+1].posible = true;
			}
		}
		
		if (jCurso.posY > 1 && mesa[jCurso.posX][jCurso.posY-1].jugador != null)
		{	
			if( mesa[jCurso.posX][jCurso.posY-2].abajo == false && mesa[jCurso.posX][jCurso.posY-2].jugador == null)
				mesa[jCurso.posX][jCurso.posY-2].posible = true;
			else
			{
				if(mesa[jCurso.posX-1][jCurso.posY-1].derecha == false && mesa[jCurso.posX-1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX-1][jCurso.posY-1].posible = true;
				if(mesa[jCurso.posX][jCurso.posY-1].derecha ==  false && mesa[jCurso.posX+1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX+1][jCurso.posY-1].posible = true;
			}
		}
		if (jCurso.posY < 7 && mesa[jCurso.posX][jCurso.posY+1].jugador != null)
		{	
			if( mesa[jCurso.posX][jCurso.posY+1].abajo == false && mesa[jCurso.posX][jCurso.posY+2].jugador == null)
				mesa[jCurso.posX][jCurso.posY+2].posible = true;
			else
			{
				if(mesa[jCurso.posX-1][jCurso.posY+1].derecha == false && mesa[jCurso.posX-1][jCurso.posY+1].jugador == null)
					mesa[jCurso.posX-1][jCurso.posY+1].posible = true;
				if(mesa[jCurso.posX][jCurso.posY+1].derecha ==  false && mesa[jCurso.posX+1][jCurso.posY+1].jugador == null)
					mesa[jCurso.posX+1][jCurso.posY+1].posible = true;
			}
		}
		
		
		
		
		
		
		
		if (jCurso.posX == 1 && mesa[jCurso.posX-1][jCurso.posY].jugador != null)
		{
				if(mesa[jCurso.posX-1][jCurso.posY-1].derecha == false && mesa[jCurso.posX-1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX-1][jCurso.posY-1].posible = true;
				if(mesa[jCurso.posX][jCurso.posY-1].derecha ==  false && mesa[jCurso.posX+1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX+1][jCurso.posY-1].posible = true;
		}
		
		if (jCurso.posX == 7 && mesa[jCurso.posX+1][jCurso.posY].jugador != null)
		{	
			if(mesa[jCurso.posX+1][jCurso.posY-1].abajo == false && mesa[jCurso.posX+1][jCurso.posY-1].jugador == null)
				mesa[jCurso.posX+1][jCurso.posY-1].posible = true;
			if(mesa[jCurso.posX+1][jCurso.posY].abajo ==  false && mesa[jCurso.posX+1][jCurso.posY+1].jugador == null)
				mesa[jCurso.posX+1][jCurso.posY+1].posible = true;
		}
		if (jCurso.posY == 1 && mesa[jCurso.posX][jCurso.posY-1].jugador != null)
		{	
			if( mesa[jCurso.posX][jCurso.posY-2].abajo == false && mesa[jCurso.posX][jCurso.posY-2].jugador == null)
				mesa[jCurso.posX][jCurso.posY-2].posible = true;
			else
			{
				if(mesa[jCurso.posX-1][jCurso.posY-1].derecha == false && mesa[jCurso.posX-1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX-1][jCurso.posY-1].posible = true;
				if(mesa[jCurso.posX][jCurso.posY-1].derecha ==  false && mesa[jCurso.posX+1][jCurso.posY-1].jugador == null)
					mesa[jCurso.posX+1][jCurso.posY-1].posible = true;
			}
		}
		if (jCurso.posY == 7 && mesa[jCurso.posX][jCurso.posY+1].jugador != null)
		{	
			if(mesa[jCurso.posX-1][jCurso.posY+1].derecha == false && mesa[jCurso.posX-1][jCurso.posY+1].jugador == null)
				mesa[jCurso.posX-1][jCurso.posY+1].posible = true;
			if(mesa[jCurso.posX][jCurso.posY+1].derecha ==  false && mesa[jCurso.posX+1][jCurso.posY+1].jugador == null)
				mesa[jCurso.posX+1][jCurso.posY+1].posible = true;
		}
	}
	
	public void paint(Graphics g) 
	{
		g.setColor(255,255,255);
		g.fillRect (0, 0, getWidth(), getHeight());
		
		//dibujar casillas
		g.setColor(0,0,0);
		for (int i = 0;i < 10;i++)
			g.drawLine (sAncho,sAlto + i*rAncho,rAncho*9 + sAncho,sAlto + i*rAncho);
		for (int i = 0; i < 10; i++)
			g.drawLine (sAncho + i*rAncho,sAlto,sAncho + i*rAncho,rAncho*9 + sAlto );
	
		//dibujar jugadores
		/*por punteros de la mesa al jugador
		for (int x = 0 ; x < 9 ; x++)
			for (int y = 0 ; y < 9; y++)
				if (mesa[x][y].j != null)
				{
					g.setColor(mesa[x][y].j.color[0],mesa[x][y].j.color[1],mesa[x][y].j.color[2]);
					g.fillArc(mesa[x][y].j.posX * rAncho + sAncho + 2 ,mesa[x][y].j.posY * rAncho + sAlto + 2,rAncho - 4,rAncho - 4,0,360);
				}*/	
		//porjugadores
		for (int i = 0; i < 4 ; i++)
			{
				if (jugadores[i] != null)
				{
					if (i == 0)
						g.setColor(255,0,0);
					else if (i == 1)
						g.setColor(0,255,0);
					else if (i == 2)
						g.setColor(0,0,255);
					else if (i == 3)
						g.setColor(255,220,80);
					g.fillArc(jugadores[i].posX * rAncho + sAncho + 2 ,jugadores[i].posY * rAncho + sAlto + 2,rAncho - 4,rAncho - 4,0,360);				
				}
			}
		//dibujar casillas movimiento
		if (estado == 0)
			for (int x = 0 ; x < 9 ; x++)
				for (int y = 0 ; y < 9; y++)
					if (mesa[x][y].posible == true)
					{
						g.setColor(200,200,200);
						g.fillRect(x * rAncho + sAncho + 2,y*rAncho + sAlto + 2,rAncho - 3,rAncho - 3);
				}		
		//casilla a mover
		if (estado == 0)
		{
			g.setColor(0,0,0);
			g.fillRect(casillaMover.x * rAncho + sAncho + 2,casillaMover.y*rAncho + sAlto + 2,rAncho - 3,rAncho - 3);
		}
		
		//dibujar barreras
		g.setColor(0,0,0);
		for (int x = 0 ; x < 9 ; x++)
			for (int y = 0 ; y < 9; y++)
			{
				if (mesa[x][y].abajo == true)
					g.fillRect( x * rAncho + 3, ( y + 1 ) * rAncho + 1 , rAncho - 1 ,3 );
				if (mesa[x][y].derecha == true)
					g.fillRect( ( x + 1 ) * rAncho + 1, y * rAncho + 3, 3 , rAncho - 1);
			}
		
		
		//dibujar barrera mover
		if (estado == 1)
		{
			g.setColor(255,0,0);
			if (barreraMover.horizontal == true)
				g.fillRect( barreraMover.x1 * rAncho + 3 , barreraMover.y1 * rAncho + 1 , rAncho * 2 - 1 , 3);
			else
				g.fillRect( barreraMover.x1 * rAncho + 1 , barreraMover.y1 * rAncho + 3 , 3 , rAncho * 2 - 1);
		}
		
		//Dibujar informacion
		g.setColor(0,0,0);
		Font fuente = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_BOLD, Font.SIZE_MEDIUM);
		g.setFont(fuente);
		for (int i = 0 ; i < 4; i ++)
		{
				if (jugadores[i] != null)
					g.drawString( "" + jugadores[i].barreras, jugadores[i].posX * rAncho + rAncho/2, jugadores[i].posY * rAncho + rAncho/2, Graphics.BASELINE| Graphics.LEFT);
		}
		
		
		//jugador ganador
		if (partidaGanada != -1)
		{
			g.setColor(200,100,200);
			fuente = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_BOLD, Font.SIZE_LARGE);
			g.setFont(fuente);
			g.drawString("HA GANADO ", getWidth()/2, getHeight()/2, Graphics.TOP| Graphics.HCENTER);
			g.drawString(jCurso.nombre, getWidth()/2, getHeight()/2 + rAncho, Graphics.TOP| Graphics.HCENTER); 
		}
		
		
	}
	
	public void read(Reader reader) throws ReaderException
	{
		reader.open("Partida");
		vjCurso = reader.readInt("Partida");
		numJugadores = reader.readInt("Partida");
		for (int x = 0 ; x < 9 ; x++)
			for (int y = 0 ; y < 9; y++)
			{
				mesa[x][y].read(reader);
			}
		jugadores = new Jugador[4];
		for (int i = 0;i < numJugadores;i++)
		{
			jugadores[i] = new Jugador();
			jugadores[i].read(reader);
		}
		jCurso = jugadores[vjCurso];
		reader.close();
		calcularCasillasPosibles();
		estado = 0;
	}
	public void write(Writer writer) throws WriterException
	{	
		writer.open("Partida");
		writer.write("Partida", vjCurso);
		writer.write("Partida", numJugadores);
		for (int x = 0 ; x < 9 ; x++)
			for (int y = 0 ; y < 9; y++)
			{
				mesa[x][y].write(writer);
			}	
		for (int i = 0;i < numJugadores;i++)
		{
			jugadores[i].write(writer);
		}
		writer.close();
	}
	

}