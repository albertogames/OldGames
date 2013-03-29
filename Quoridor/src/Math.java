/*
 * Created on 12-abr-2005
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
public final class Math 
{
	private Math()
	{
	}

  public static byte[] byteToByteArray(byte b)
  {
    byte[] bytes = { b };
    return bytes;
  }
  
  public static byte byteArrayToByte(byte[] bytes)
  {
    return bytes[0];
  }
  
  public static byte[] booleanToByteArray(boolean b)
  {
    byte[] bytes = { b?(byte)1:(byte)0 };
    return bytes;
  }
  
  public static boolean byteArrayToBoolean(byte[] bytes)
  {
    boolean b = bytes[0] != 0?true:false;
    return b;
  }
  
  public static byte[] charToByteArray(char c)
  {
    byte[] bytes = new byte[2];
    bytes[0] = (byte) ((c >> 8) & 0x00FF);
    bytes[1] = (byte) (c & 0x00FF);
    return bytes;
  }
  
  public static char byteArrayToChar(byte[] bytes)
  {
    char c = (char)(
      (((int)bytes[0] << 8) & 0xFF00) | 
      ((int)bytes[1] & 0x00FF)
      );
    return c;
  }
  
  public static byte[] intToByteArray(int i)
  {
    byte[] bytes = new byte[4];
    bytes[0] = (byte) ((i >> 24) & 0x000000FF);
    bytes[1] = (byte) ((i >> 16) & 0x000000FF);
    bytes[2] = (byte) ((i >>  8) & 0x000000FF);
    bytes[3] = (byte) ( i        & 0x000000FF);
    return bytes;
  }
  
  public static int byteArrayToInt(byte[] bytes)
  {
    int i = 
      (((int)bytes[0] << 24) & 0xFF000000) | 
      (((int)bytes[1] << 16) & 0x00FF0000) | 
      (((int)bytes[2] <<  8) & 0x0000FF00) | 
      ((int) bytes[3]        & 0x000000FF);
    return i;
  }
  
  
  public static byte[] addIndexToByteArray(byte[] byteArray, int index)
  {
  	byte[] newByteArray = new byte[byteArray.length + 4];
  	byte[] indexByteArray = intToByteArray(index);
  	System.arraycopy(indexByteArray, 0, newByteArray, 0, indexByteArray.length);
  	System.arraycopy(byteArray, 0, newByteArray, indexByteArray.length, byteArray.length);
  	return newByteArray;
  }
  
  public static byte[] extractIndexFromByteArray(byte[] byteArray)
  {
  	byte[] newByteArray = new byte[byteArray.length - 4];
  	System.arraycopy(byteArray, 4, newByteArray, 0, newByteArray.length);
  	return newByteArray;
  }
  
  public static int getIndexFromByteArray(byte[] byteArray)
  {
  	return byteArrayToInt(byteArray);
  }
  
}
