/*
 * Created on 07-may-2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */


/**
 * @author JudaX
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public interface Reader 
{
	public void open(String resourceName) throws ReaderException;
	public void close() throws ReaderException;
	public int readInt(String name) throws ReaderException;
	public boolean readBoolean(String name) throws ReaderException;
	public String readString(String name) throws ReaderException;
  public byte[] readBytes(String name) throws ReaderException;
}
