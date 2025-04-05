namespace Fat12;

public struct FileControlBlock__IsNotUse {
	// [FieldOffset(0)]
	// private UInt128 _date1;
	// [FieldOffset(0)]
	// private UInt128 _date2;

	// [FieldOffset(0)]
	private UInt64 _FileName;
	// [FieldOffset(8)]
	private UInt32 _Extension;
	// [FieldOffset(11)]
	private Byte _Attribute;
	// [FieldOffset(12)]
	// private UInt16 _Reserved;
	// // [FieldOffset(14)]
	// private UInt16 _CreateTime;
	// // [FieldOffset(16)]
	// private UInt16 _CreateDate;
	// // [FieldOffset(18)]
	// private UInt16 _LastAccessDate;
	// // [FieldOffset(20)]
	// private UInt16 _IgnoreInFAT12;
	// [FieldOffset(22)]
	private UInt128 _Reserved;
	private UInt16  _LastWriteTime;
	// [FieldOffset(22)]
	private UInt16 _LastWriteDate;
	// [FieldOffset(26)]
	private UInt16 _FirstLogicalCluster;
	// [FieldOffset(28)]
	private UInt32 _FileSize;	

	public UInt64 FileName {
		get => _FileName;
		set => _FileName = value;
	}
	public UInt32 Extension {
		get => _Extension;
		set => _Extension = (value & 0xffffff);
	}
	public Byte Attribute {
		get => _Attribute; set => _Attribute = value;
	}
	// public UInt16 Reserved {
	// 	get => _Reserved; set => _Reserved = value;
	// }
	// public UInt16 CreateTime {
	// 	get => _CreateTime; set => _CreateTime = value;
	// }
	// public UInt16 CreateDate {
	// 	get => _CreateDate; set => _CreateDate = value;
	// }
	// public UInt16 LastAccessDate {
	// 	get => _LastAccessDate; set => _LastAccessDate = value;
	// }
	// public UInt16 IgnoreInFAT1 {
	// 	get => _IgnoreInFAT12; set => _IgnoreInFAT12 = value;
	// }
	public UInt128 Reserved {
		get => _Reserved;
		set => _Reserved = value;
	}
	public UInt16 LastWriteTime {
		get => _LastWriteTime; set => _LastWriteTime = value;
	}
	public UInt16 LastWriteDate {
		get => _LastWriteDate; set => _LastWriteDate = value;
	}
	public UInt16 FirstLogicalCluste {
		get => _FirstLogicalCluster; set => _FirstLogicalCluster = value;
	}
	public UInt32 FileSize {
		get => _FileSize; set => _FileSize = value;
	}

	// public UInt128 Date1 {
	// 	get => _date1; set => _date1 = value;
	// }
	// public UInt128 Date2 {
	// 	get => _date2; set => _date2 = value;
	// }

	public Byte[] GetFileNameBytes() {
		// Console.WriteLine($"{FileName:x}");
		var arr = new Byte[8];
		for (int i = 0; i < 8; i++) {
			arr[i] = (Byte)((FileName >> (i * 8)) & 0xff);
		}
		// Console.WriteLine(String.Join(' ', arr.Select(x => $"{x:x}")));
		return arr;
	}
	public Byte[] GetExtensionBytes() {
		var arr = new Byte[3];
		for (int i = 2; i >= 0; i --) {
			arr[i] = (Byte)(Extension >> (i * 4));
		}			
		return arr;
	}

	// public FileControlBlock() {}
	public FileControlBlock__IsNotUse(in Span<byte> buf) {
		FileName = 0;
		for (int i = 0; i < 8; i++) {
			FileName <<= 8;
			FileName |=  buf[7 - i];
		}

		Extension = (UInt16)(((UInt16)(buf[9]) << 8) | buf[10]);
		Attribute = buf[11];

		Reserved = 0;
		for (int i = 12; i < 22; i++) {
			Reserved <<= 8;
			Reserved |=  buf[21 - i];
		}
		
		LastWriteTime      = (UInt16)(((UInt16)(buf[22]) << 8) | buf[23]);;
		LastWriteDate      = (UInt16)(((UInt16)(buf[24]) << 8) | buf[25]);
		FirstLogicalCluste = (UInt16)(((UInt16)(buf[26]) << 8) | buf[27]);
		
		// Console.WriteLine($"{FileName:x} {LastWriteDate:x} {LastWriteTime:x}");
		
		FileSize = 0;
		for (int i = 28; i < 32; i++) {
			FileSize <<= 8;
			FileSize |=  buf[31 - i];
		}

	}
	// public FileControlBlock(UInt128 date1, UInt128 date2) {
	// Date1 = date1; Date2 = date2;
		
	// }
	// public FileControlBlock(Stream stream) {
	// 	using (var rd = new BinaryReader(stream, Encoding.Default, true)) {
	// 		Span<Byte> buf = stackalloc Byte[32];
	// 		rd.Read(buf);
	// 		UInt128 tmp = 0;
	// 		for (int i = 0; i < 16; i ++)  {
	// 			tmp |= buf[i];
	// 			tmp <<= 8;
	// 		}
	// 		Date1 = tmp;
	// 		tmp = 0;
	// 		for (int i = 16; i < 32; i ++)  {
	// 			tmp |= buf[i];
	// 			tmp <<= 8;
	// 		}
	// 		Date2 = tmp;
	// 	}
	// }

	public string GetFileNameStr()  => System.Text.Encoding.ASCII.GetString(GetFileNameBytes());
	public string GetExtensionStr() => System.Text.Encoding.ASCII.GetString(GetExtensionBytes());

	public FatFileDate GetLastWriteDate() => new FatFileDate(LastWriteDate);
	public FatFileTime GetLastWriteTime() => new FatFileTime(LastWriteTime);

	public override string ToString() 
		=> $"{GetFileNameStr()}\t{GetExtensionStr()}\t{(Attribute == (Byte)FileControlBlockAttributeType.Directory ? "Directory" : "Regular")}\t{FileSize}\t{GetLastWriteDate()}\t{GetLastWriteTime()}";

}