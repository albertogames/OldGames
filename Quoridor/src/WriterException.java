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
public class WriterException extends Exception
{
  private static final long serialVersionUID = 1;
  private Writer writer = null;
  private Exception exception = null;
  
  public WriterException(Writer writer)
  {
    this.writer = writer;
  }
  
  public WriterException(Writer writer, String s)
  {
    super(s);
    this.writer = writer;
  }
  
  public WriterException(Writer writer, Exception e)
  {
    this.writer = writer;
    exception = e;
  }
  
  public WriterException(Writer writer, String s, Exception e)
  {
    super(s);
    this.writer = writer;
    exception = e;
  }
  
  public Writer getWriter()
  {
    return writer;
  }
  
  public Exception getException()
  {
    return exception;
  }
}
