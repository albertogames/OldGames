/*
 * Created on 08-may-2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */


import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;
import javax.microedition.rms.RecordStoreFullException;
import javax.microedition.rms.RecordStoreNotFoundException;
import javax.microedition.rms.RecordStoreNotOpenException;
import javax.microedition.rms.InvalidRecordIDException;


/**
 * @author JudaX
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ReaderJ2MERMS implements Reader
{
  protected RecordStore recordStore = null;
//  protected RecordEnumeration records = null;
  protected int id = 1;

  public void open(String resourceName) throws ReaderException
  {
    try
    {
      recordStore = RecordStore.openRecordStore(resourceName, true);
//      records = recordStore.enumerateRecords(null, new RMSIndexRecordComparator(), true);
      id = 1;
    }
    catch(RecordStoreNotFoundException rsnfe)
    {
  		throw new ReaderException(this, getClass().getName() + ".open(" + resourceName + "): RecordStoreNotFoundException.");
    }
    catch(RecordStoreFullException rsfe)
    {
  		throw new ReaderException(this, getClass().getName() + ".open(" + resourceName + "): SRecordStoreFullException.");
    }
    catch(RecordStoreException rse)
    {
  		throw new ReaderException(this, getClass().getName() + ".open(" + resourceName + "): RecordStoreException.");
    }
  }
  
  public void close() throws ReaderException
  {
    try
    {
      recordStore.closeRecordStore();
      id = 1;
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
  		throw new ReaderException(this, getClass().getName() + ".close(): RecordStoreNotOpenException.");
    }
    catch(RecordStoreException rse)
    {
  		throw new ReaderException(this, getClass().getName() + ".close(): RecordStoreException.");
    }
  }
  
  public byte readByte(String name) throws ReaderException
  {
    byte b = 0;
    try
    {
//      byte[] data = records.nextRecord();
//      data = judax.java.lang.Math.extractIndexFromByteArray(data);
    	byte[] data = recordStore.getRecord(id);
      b = Math.byteArrayToByte(data);
      id++;
    }
    catch(InvalidRecordIDException iride)
    {
  		throw new ReaderException(this, getClass().getName() + ".readByte(" + name + "): InvalidRecordIDException.");
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
  		throw new ReaderException(this, getClass().getName() + ".readByte(" + name + "): RecordStoreNotOpenException.");
    }
    catch(RecordStoreException rse)
    {
  		throw new ReaderException(this, getClass().getName() + ".readByte(" + name + "): RecordStoreException.");
    }
    return b;
  }
  
  public int readInt(String name) throws ReaderException
  {
    int i = 0;
    try
    {
//      byte[] data = records.nextRecord();
//      data = judax.java.lang.Math.extractIndexFromByteArray(data);
    	byte[] data = recordStore.getRecord(id);
      i = Math.byteArrayToInt(data);
      id++;
    }
    catch(InvalidRecordIDException iride)
    {
  		throw new ReaderException(this, getClass().getName() + ".readInt(" + name + "): InvalidRecordIDException.");
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
  		throw new ReaderException(this, getClass().getName() + ".readInt(" + name + "): RecordStoreNotOpenException.");
    }
    catch(RecordStoreException rse)
    {
  		throw new ReaderException(this, getClass().getName() + ".readInt(" + name + "): RecordStoreException.");
    }
    return i;
  }
  
  public boolean readBoolean(String name) throws ReaderException
  {
    boolean b = false;
    try
    {
//      byte[] data = records.nextRecord();
//      data = judax.java.lang.Math.extractIndexFromByteArray(data);
    	byte[] data = recordStore.getRecord(id);
      b = Math.byteArrayToBoolean(data);
      id++;
    }
    catch(InvalidRecordIDException iride)
    {
  		throw new ReaderException(this, getClass().getName() + ".readBoolean(" + name + "): InvalidRecordIDException.");
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
  		throw new ReaderException(this, getClass().getName() + ".readBoolean(" + name + "): RecordStoreNotOpenException.");
    }
    catch(RecordStoreException rse)
    {
  		throw new ReaderException(this, getClass().getName() + ".readBoolean(" + name + "): RecordStoreException.");
    }
    return b;
  }
  
  public String readString(String name) throws ReaderException
  {
    String s = "";
    try
    {
//      byte[] data = records.nextRecord();
//      data = judax.java.lang.Math.extractIndexFromByteArray(data);
    	byte[] data = recordStore.getRecord(id);
      s = new String(data);
      id++;
    }
    catch(InvalidRecordIDException iride)
    {
  		throw new ReaderException(this, getClass().getName() + ".readString(" + name + "): InvalidRecordIDException.");
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
  		throw new ReaderException(this, getClass().getName() + ".readString(" + name + "): RecordStoreNotOpenException.");
    }
    catch(RecordStoreException rse)
    {
  		throw new ReaderException(this, getClass().getName() + ".readString(" + name + "): RecordStoreException.");
    }
    return s;
  }

  public byte[] readBytes(String name) throws ReaderException
  {
    byte[] bytes = null; 
    try
    {
//      byte[] data = records.nextRecord();
//      data = judax.java.lang.Math.extractIndexFromByteArray(data);
    	byte[] data = recordStore.getRecord(id);
      bytes = data;
      id++;
    }
    catch(InvalidRecordIDException iride)
    {
  		throw new ReaderException(this, getClass().getName() + ".readBytes(" + name + "): InvalidRecordIDException.");
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
  		throw new ReaderException(this, getClass().getName() + ".readBytes(" + name + "): RecordStoreNotOpenException.");
    }
    catch(RecordStoreException rse)
    {
  		throw new ReaderException(this, getClass().getName() + ".readBytes(" + name + "): RecordStoreException.");
    }
    return bytes;
  }
}
