namespace Fat12;

/// <summary>
/// FCB 扩展方法
/// </summary>
public static class FileControlBlockExtensions {
	public static bool IsDirectory(this in FileControlBlock fileControlBlock) 
		=> fileControlBlock.GetAttributeType() is FileControlBlockAttributeType.Directory;

	public static bool IsRegular(this in FileControlBlock fileControlBlock)
		=> fileControlBlock.GetAttributeType() is FileControlBlockAttributeType.Regular;

	public static bool IsLongFileNamePark(this in FileControlBlock fileControlBlock)
		=> fileControlBlock.GetAttributeType() is FileControlBlockAttributeType.LongFileName;
	
	public static bool IsHaveLongFileName(this in FileControlBlock fileControlBlock)
		=> fileControlBlock.LongFileNameBlockList != null;
}

// FCB
// [StructLayout(LayoutKind.Explicit, Size = 32)]
/// <summary>
/// 文件控制块
/// </summary>
public struct FileControlBlock {
	// private byte[] data;
	
	// len := 32
	/// <summary>
	/// 文件控制块字节数组
	/// 32 个字节
	/// </summary>
	public byte[] Data { get; set; }
	
	/// <summary>
	/// 这个本来是作为长文件名解析的，但是最后实现错误了
	/// </summary>
	public List<LongFileNameBlock>? LongFileNameBlockList { get; set; }
	
	/// <summary>
	/// 获取文件控制块对应字节
	/// </summary>
	// /// <param name="idx"></param>
	public byte this[int index] {
		get => Data[index];
		set => Data[index] = value;
	}
	

	// len := 8
	/// <summary>
	/// 文件名
	/// </summary>
	public ulong FileName {
		get {
			ulong ret = 0;
			for (int i = 7; i >= 0; i--) {
				ret <<= 8;
				ret |=  Data[i];
			}
			return ret;
		}
		set {
			for (int i = 0; i < 8; i++) {
				Data[i] =   (byte)(value & 0x0ff);
				value   >>= 8;
			}
		}
	}

	// len := 3
	/// <summary>
	/// 扩展名
	/// </summary>
	public uint Extension {
		get => (Data[8]) | ((uint)(Data[9]) << 8) | ((uint)(Data[10]) << 16);
		set {
			Data[10] = (byte)((value >> 16) & 0x0ff);
			Data[9] = (byte)((value >> 8) & 0x0ff);
			Data[8] = (byte)(value & 0x0ff);
		}
	}

	// len := 1
	/// <summary>
	/// 文件属性
	/// </summary>
	public byte Attribute {
		readonly get => Data[11];
		set => Data[11] = value;
	}

	// set => Data[11] = value;
	// len := 10
	/// <summary>
	/// 区域
	/// 参杂了一些
	/// </summary>
	public UInt128 Reserved {
		get {
			UInt128 ret = 0;
			for (int i = 21; i >= 12; i--) {
				ret <<= 8;
				ret |=  Data[i];
			}
			return ret;
		}
		set {
			for (int i = 12; i < 22; i++) {
				Data[i] =   (byte)(value & 0x0ff);
				value   >>= 8;
			}
		}
	}

	// len := 2
	/// <summary>
	/// 最后写入时间
	/// </summary>
	public ushort LastWriteTime {
		get => (ushort)((Data[23] << 8) | Data[22]);
		set {
			Data[23] = (byte)((value >> 8) & 0x0ff);
			Data[22] = (byte)(value & 0x0ff);
		}
	}

	/// <summary>
	/// 最后写入日期
	/// </summary>
	public ushort LastWriteDate {
		get => (ushort)((Data[25] << 8) | Data[24]);
		set {
			Data[25] = (byte)((value >> 8) & 0x0ff);
			Data[24] = (byte)(value & 0x0ff);
		}
	}

	/// <summary>
	/// 起始逻辑块
	/// </summary>
	public ushort FirstLogicalCluster {
		get => (ushort)((Data[27] << 8) | Data[26]);
		set {
			Data[27] = (byte)((value >> 8) & 0x0ff);
			Data[26] = (byte)(value & 0x0ff);
		}
	}

	/// <summary>
	/// 文件大小
	/// </summary>
	public uint FileSize {
		get => ((uint)(Data[31]) << 24)
		       | ((uint)(Data[30]) << 16)
		       | ((uint)(Data[29]) << 8)
		       | (Data[28]);
		set {
			Data[31] = (byte)((value >> 24) & 0x0ff);
			Data[30] = (byte)((value >> 16) & 0x0ff);
			Data[29] = (byte)((value >> 8) & 0x0ff);
			Data[28] = (byte)(value & 0x0ff);
		}
	}

	
	public FileControlBlock(in byte[] dataBytes, in List<LongFileNameBlock>? list = null) {
		if (dataBytes == null) {
			throw new ArgumentNullException(nameof(dataBytes));
		}
		if (dataBytes.Length != 32) {
			throw new Exception("FCB data byte array must be 32.");
		}
		
		Data                  = (byte[])dataBytes.Clone();
		LongFileNameBlockList = list?.ToList() ?? null;
	}
	
	public FileControlBlock(in Span<byte> dataByteSpan, in List<LongFileNameBlock>? list = null) {
		if (dataByteSpan.Length != 32) {
			throw new Exception("FCB data byte span must be 32.");
		}
		
		Data                  = dataByteSpan.ToArray();
		LongFileNameBlockList = list?.ToList() ?? null;
	}
	
	/// <summary>
	/// 这个本来是作为长文件名解析的，但是最后实现错误了
	/// </summary>
	/// <returns></returns>
	public string GetFileNameUtf8String() {
		if (this.IsHaveLongFileName() == false) {
			if (this.IsDirectory()) {
				return this.GetFileNameWithoutExtensionUtf8String();
			} else {
				return this.GetFileNameWithoutExtensionUtf8String() + "." + GetExtensionUtf8String();
			}
		}
		
		var ret = GetLongFileNameUtf8String();
#if DEBUG
		Console.WriteLine(ret + " " + "1");
		Console.WriteLine(this.IsHaveLongFileName());
#endif		
		if (this.IsDirectory()) {
			return ret;
		}

		ret += "." + this.GetExtensionUtf8String();
#if DEBUG
		Console.WriteLine(ret + " " + "2");
#endif
		return ret;
	}

	/// <summary>
	/// 这个本来是作为长文件名解析的，但是最后实现错误了
	/// </summary>
	/// <returns></returns>
	public string GetLongFileNameUtf8String() {
		if (this.IsHaveLongFileName() == false) {
			return GetFileNameWithoutExtensionUtf8String();
		}
		List<byte> byteList = new List<byte>(LongFileNameBlockList!.Count * 26);
		foreach (var item in LongFileNameBlockList!) {
			var bytes = item.GetLongFileBytes();
			foreach (var @byte in bytes) {
				byteList.Add(@byte);
			}
		}
		while (byteList.Any() && byteList.Last() == 0xFF) {
			byteList.RemoveBack();
		}
		return System.Text.Encoding.Unicode.GetString(byteList.ToArray());
	}
	
	/// <summary>
	/// 解析文件控制块的文件名
	/// </summary>
	/// <returns>UTF8 文件名</returns>
	public readonly string GetFileNameWithoutExtensionUtf8String()
		=> System.Text.Encoding.ASCII.GetString(Data[0..8]).TrimEnd();
	
	/// <summary>
	/// 解析文件控制块的扩展名
	/// </summary>
	/// <returns>UTF8 扩展名</returns>
	public readonly string GetExtensionUtf8String()
		=> System.Text.Encoding.ASCII.GetString(Data[8..11]).TrimEnd();

	/// <summary>
	/// 获取文件的最后写入日期
	/// </summary>
	/// <returns>文件最后写入日期</returns>
	public FatFileDate GetLastWriteDate()
		=> new FatFileDate(LastWriteDate);

	/// <summary>
	/// 获取文件的最后写入时间
	/// </summary>
	/// <returns>文件最后写入时间</returns>
	public FatFileTime GetLastWriteTime()
		=> new FatFileTime(LastWriteTime);

	/// <summary>
	/// 获取文件的类型/属性
	/// </summary>
	/// <returns>文件的类型/属性</returns>
	public readonly FileControlBlockAttributeType GetAttributeType()
		=> (FileControlBlockAttributeType)Attribute switch {
			   FileControlBlockAttributeType.ReadOnly     => FileControlBlockAttributeType.ReadOnly,
			   FileControlBlockAttributeType.Hide         => FileControlBlockAttributeType.Hide,
			   FileControlBlockAttributeType.System       => FileControlBlockAttributeType.System,
			   FileControlBlockAttributeType.Label        => FileControlBlockAttributeType.Label,
			   FileControlBlockAttributeType.Directory    => FileControlBlockAttributeType.Directory,
			   FileControlBlockAttributeType.Regular      => FileControlBlockAttributeType.Regular,
			   FileControlBlockAttributeType.Devices      => FileControlBlockAttributeType.Devices,
			   FileControlBlockAttributeType.NotUsed      => FileControlBlockAttributeType.NotUsed,
			   FileControlBlockAttributeType.LongFileName => FileControlBlockAttributeType.LongFileName,
			   _                         => FileControlBlockAttributeType.Wtf  // 因为出现了一个 16 的东西，查明是来自 windows
			   // _ => throw new ArgumentOutOfRangeException(nameof(Attribute),
			   // $"Can not find this attribute {(uint)Attribute:x}. Which file name is {GetFileNameStr()}.{GetExtensionStr()}"),
		   };

	/// <summary>
	/// 判断文件是否是被删除的文件
	/// </summary>
	public bool IsDeleteFile()
		=> Data[0] == 0xE5;
	
	/// <summary>
	/// 判断文件是否是空文件
	/// </summary>
	public bool IsEmptyFile()
		=> Data[0] == 0xE5;

	/// <summary>
	/// 判断文件为空，标志目录表结束
	/// </summary>
	public bool IsEmptyFileWithLater()
		=> Data[0] == 0x00;
	
	public static string[] GetStringsTitle() => 
		new[] { "文件名", "文件扩展名", "属性", "大小", "最后写入日期", "最后写入时间", "索引逻辑块" };

	public static int GetStringsCount => 7;

	public string[] GetStrings() =>
		new[] {
			      GetFileNameWithoutExtensionUtf8String(),
			      GetExtensionUtf8String(),
			      GetAttributeType().ToString(),
			      FileSize.ToString(),
			      GetLastWriteDate().ToString(),
			      GetLastWriteTime().ToString(),
			      $"{FirstLogicalCluster:X4}"
		      };
	
	public override string ToString()
		=> string.Join('\t',
		               GetFileNameWithoutExtensionUtf8String(),
		               GetExtensionUtf8String(),
		               (GetAttributeType()),
		               FileSize,
		               GetLastWriteDate(),
		               GetLastWriteTime(),
		               $"{FirstLogicalCluster:X4}"
		              );
}