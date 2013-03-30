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
public interface Writer 
{
	public void open(String resourceName) throws WriterException;
	public void close() throws WriterException;
	public void write(String name, boolean value) throws WriterException;
	public void write(String name, int value) throws WriterException;
	public void write(String name, String value) throws WriterException;
  public void write(String name, byte[] value) throws WriterException;
}
