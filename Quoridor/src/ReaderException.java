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
public class ReaderException extends Exception
{
  private static final long serialVersionUID = 1;
  private Reader reader = null;
  private Exception exception = null;
  
  public ReaderException(Reader reader)
  {
    this.reader = reader;
  }
  
  public ReaderException(Reader reader, String s)
  {
    super(s);
    this.reader = reader;
  }
  
  public ReaderException(Reader reader, Exception e)
  {
    this.reader = reader;
    exception = e;
  }
  
  public ReaderException(Reader reader, String s, Exception e)
  {
    super(s);
    this.reader = reader;
    exception = e;
  }
  
  public Reader getReader()
  {
    return reader;
  }
  
  public Exception getException()
  {
    return exception;
  }
}
