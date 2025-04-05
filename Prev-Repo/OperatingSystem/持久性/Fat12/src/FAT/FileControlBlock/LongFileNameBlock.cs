namespace Fat12; 

public struct LongFileNameBlock {
	public byte[] Data { get; set; }

	public byte this[int index] {
		get => Data[index];
		set => Data[index] = value;
	}

	public byte LongFileIdx {
		get => Data[0];
		set => Data[0] = value;
	}

	public byte[] FirstFileNameBlock {
		get => Data[1..11];
		set => Data.RangeCopy(value, 1);
	}

	public byte Attribute {
		get => Data[11];
		set => Data[11] = value;
	}

	public byte Reserved1 {
		get => Data[12];
		set => Data[12] = value;
	}

	public byte CheckSum {
		get => Data[13];
		set => Data[13] = value;
	}

	public byte[] SecondFileNameBlock {
		get => Data[14..25];
		set => Data.RangeCopy(value, 14);
	}
	
	public byte[] Reserved2 {
		get => Data[25..27];
		set => Data.RangeCopy(value, 25);
	}
	
	public byte[] ThirdFileNameBlock {
		get => Data[28..32];
		set => Data.RangeCopy(value, 28);
	}

	public byte[] GetLongFileBytes()
		=> (new byte[26]).RangeCopy(FirstFileNameBlock)
			.RangeCopy(SecondFileNameBlock, 10)
			.RangeCopy(ThirdFileNameBlock, 22);

	public LongFileNameBlock(in byte[] data) {
		if (data == null) {
			throw new ArgumentNullException(nameof(data));
		}

		this.Data = (byte[])data.Clone();
	}

	public LongFileNameBlock(in Span<byte> data) {
		this.Data = data.ToArray();
	}
}