public class Utilidades
{
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
  
  public static byte[] booleanToByteArray(boolean b)
  {
	int x;
	if (b)
		x = 1;
	else
		x = 0;
		
	return intToByteArray(x);
  }
  
  public static boolean byteArrayToBoolean(byte[] bytes)
  {
	boolean b;
	if (byteArrayToInt(bytes) == 0)
		b = false;
	else
		b = true;
    return b;
  }
  
  
  public static byte[] addIndexToByteArray(byte[] byteArray, int index)
  {
  	byte[] newByteArray = new byte[byteArray.length + 4];
  	byte[] indexByteArray = intToByteArray(index);
  	System.arraycopy(indexByteArray, 0, newByteArray, 0,
indexByteArray.length);
  	System.arraycopy(byteArray, 0, newByteArray, indexByteArray.length,
byteArray.length);
  	return newByteArray;
  }
  
  public static byte[] extractIndexFromByteArray(byte[] byteArray)
  {
  	byte[] newByteArray = new byte[byteArray.length - 4];
  	System.arraycopy(byteArray, 4, newByteArray, 0,
newByteArray.length);
  	return newByteArray;
  }
  
  public static int getIndexFromByteArray(byte[] byteArray)
  {
  	return byteArrayToInt(byteArray);
  }  
}