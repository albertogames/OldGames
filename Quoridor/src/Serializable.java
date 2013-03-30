/*
 * Created on 08-may-2005
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
public interface Serializable
{
  public void read(Reader reader) throws ReaderException;
  public void write(Writer writer) throws WriterException;
}
