import javax.microedition.rms.RecordComparator;

public class RMSIndexRecordComparator implements RecordComparator
{
	public int compare(byte[] data0, byte[] data1)
	{
		int indexData0 = Utilidades.getIndexFromByteArray(data0);  
		int indexData1 = Utilidades.getIndexFromByteArray(data1);  
		if (indexData0 < indexData1)
		{
			return RecordComparator.PRECEDES;
		}
		else if (indexData0 > indexData1)
		{
			return RecordComparator.FOLLOWS;
		}
		else
		{
			return RecordComparator.EQUIVALENT;
		}
	}
}