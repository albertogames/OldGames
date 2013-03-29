/*
 * Created on 07-may-2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */


import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;
import javax.microedition.rms.RecordStoreNotFoundException;
import javax.microedition.rms.RecordStoreFullException;
import javax.microedition.rms.RecordStoreNotOpenException;


/**
 * @author JudaX
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class WriterJ2MERMS implements Writer
{
  protected RecordStore recordStore = null;
//  protected int index = 0;
  
  public void open(String resourceName) throws WriterException
  {
    try
    {
      try
      {
        RecordStore.deleteRecordStore(resourceName);
      }
      catch(RecordStoreNotFoundException rsnfe)
      {
        // Do not do anything...
      }
      catch(RecordStoreException rse)
      {
        // Do not do anything...
      }
      recordStore = RecordStore.openRecordStore(resourceName, true);
//      index = 0;
    }
    catch(RecordStoreNotFoundException rsnfe)
    {
      throw new WriterException(this, getClass().getName() + ".open(" + resourceName + "): RecordStoreNotFoundException while openning.", rsnfe);
    }
    catch(RecordStoreFullException rsfe)
    {
      throw new WriterException(this, getClass().getName() + ".open(" + resourceName + "): RecordStoreFullException while openning.", rsfe);
    }
    catch(RecordStoreException rse)
    {
      throw new WriterException(this, getClass().getName() + ".open(" + resourceName + "): RecordStoreException while openning.", rse);
    }
  }
  
  public void close() throws WriterException
  {
    try
    {
      recordStore.closeRecordStore();
//      index = 0;
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
      throw new WriterException(this, getClass().getName() + ".close(): RecordStoreNotOpenException while closing.", rsnoe);
    }
    catch(RecordStoreException rse)
    {
      throw new WriterException(this, getClass().getName() + ".close(): RecordStoreException while closing.", rse);
    }
  }
  
  
  public void write(String name, int value) throws WriterException
  {
    try
    {
      byte[] data = Math.intToByteArray(value);
//      data = judax.java.lang.Math.addIndexToByteArray(data, index);
      recordStore.addRecord(data, 0, data.length);
//      index++;
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreNotOpenException while writing a int.", rsnoe);
    }
    catch(RecordStoreFullException rsfe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreFullException while writing a int.", rsfe);
    }
    catch(RecordStoreException rse)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreException while writing a int.", rse);
    }
  }
  
  
  public void write(String name, boolean value) throws WriterException
  {
    try
    {
      byte[] data = Math.booleanToByteArray(value);
//      data = judax.java.lang.Math.addIndexToByteArray(data, index);
      recordStore.addRecord(data, 0, data.length);
//      index++;
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreNotOpenException while writing a boolean.", rsnoe);
    }
    catch(RecordStoreFullException rsfe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreFullException while writing a boolean.", rsfe);
    }
    catch(RecordStoreException rse)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreException while writing a boolean.", rse);
    }
  }
  
  
  public void write(String name, String value) throws WriterException
  {
    try
    {
      byte[] data = value.getBytes();
//      data = judax.java.lang.Math.addIndexToByteArray(data, index);
      recordStore.addRecord(data, 0, data.length);
//      index++;
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreNotOpenException while writing a String.", rsnoe);
    }
    catch(RecordStoreFullException rsfe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreFullException while writing a String.", rsfe);
    }
    catch(RecordStoreException rse)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreException while writing a String.", rse);
    }
  } 

  public void write(String name, byte[] value) throws WriterException
  {
    try
    {
//      value = judax.java.lang.Math.addIndexToByteArray(value, index);
      recordStore.addRecord(value, 0, value.length);
//      index++;
    }
    catch(RecordStoreNotOpenException rsnoe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreNotOpenException while writing a byte[].", rsnoe);
    }
    catch(RecordStoreFullException rsfe)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreFullException while writing a byte[].", rsfe);
    }
    catch(RecordStoreException rse)
    {
      throw new WriterException(this, getClass().getName() + ".write(" + name + ", " + value + "): RecordStoreException while writing a byte[].", rse);
    }
  } 
 
}
