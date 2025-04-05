using ConsoleTables;

namespace Fat12;

// BPB
/// <summary>
/// Boot Sector of FAT12.
/// </summary>
public struct BiosPramBlock {
	/// <summary>
	/// BPB 数据
	/// </summary>
	public byte[] Data { get; set; }

	public byte this[int index] {
		get => Data[index];
		set => Data[index] = value;
	}

	/// <summary>
	/// 跳转指令
	/// </summary>
	public uint JumpBoot {
		get => BitConverter.ToUInt32(Data[0..3]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8),
			                                        (byte)((value & 0xff0000) >> 16)
		                                        });
	}
	
	/// <summary>
	/// 厂商名
	/// </summary>
	public byte[] OemName {
		get => Data[3..11];
		set => Data.RangeCopy(value, 3);
	}

	/// <summary>
	/// 每扇区字节数
	/// </summary>
	public ushort BytePerSec {
		get => BitConverter.ToUInt16(Data[11..13]);
		set =>
			Data.RangeCopy((stackalloc byte[] {
				                                  (byte)(value & 0xff),
				                                  (byte)((value & 0xff00) >> 8)
			                                  }), 11);
	}

	/// <summary>
	/// 每簇扇区数
	/// </summary>
	public byte SecPerClus {
		get => Data[13];
		set => Data[13] = value;
	}

	/// <summary>
	/// 保留扇区数
	/// 包括启动扇区
	/// </summary>
	public ushort ResvdSecCnt {
		get => BitConverter.ToUInt16(Data[14..16]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8)
		                                        }, 14);
	}

	/// <summary>
	/// 文件分配表数目
	/// </summary>
	public byte NumFaTs {
		get => Data[16];
		set => Data[16] = value;
	}
	
	/// <summary>
	/// 最大根目录条目个数
	/// </summary>
	public ushort RootEndCnt {
		get => BitConverter.ToUInt16(Data[17..19]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8)
		                                        }, 17);
	}

	/// <summary>
	/// 总扇区数
	/// </summary>
	public ushort TotSec16 {
		get => BitConverter.ToUInt16(Data[19..21]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8)
		                                        }, 19);
	}
	
	/// <summary>
	/// 介质描述
	/// </summary>
	public byte Media {
		get => Data[21];
		set => Data[21] = value;
	}

	/// <summary>
	/// 每个文件分配表的扇区数
	/// </summary>
	public ushort FatSz16 {
		get => BitConverter.ToUInt16(Data[22..24]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8)
		                                        }, 22);
	}
	
	/// <summary>
	/// 每磁道的扇区
	/// </summary>
	public ushort SecPerTrk {
		get => BitConverter.ToUInt16(Data[24..26]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8)
		                                        }, 26);
	}
	
	/// <summary>
	/// 磁头数
	/// </summary>
	public ushort NumHeads {
		get => BitConverter.ToUInt16(Data[26..28]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8)
		                                        }, 26);
	}
	
	/// <summary>
	/// 隐藏扇区数
	/// </summary>
	public uint HiddSec {
		get => BitConverter.ToUInt16(Data[28..32]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8),
			                                        (byte)((value & 0xff0000) >> 16),
			                                        (byte)((value & 0xff000000) >> 24)
		                                        }, 28);
	}
	
	/// <summary>
	/// 总扇区数
	/// 如果 TotSec16 范围超过将启用该属性
	/// </summary>
	public uint TotSec32 {
		get => BitConverter.ToUInt16(Data[32..36]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8),
			                                        (byte)((value & 0xff0000) >> 16),
			                                        (byte)((value & 0xff000000) >> 24)
		                                        }, 32);
	}

	/// <summary>
	/// 驱动号
	/// </summary>
	public byte DrvNum {
		get => Data[36];
		set => Data[36] = value;
	}

	/// <summary>
	/// 保留位
	/// </summary>
	public byte Reserved1 {
		get => Data[37];
		set => Data[37] = value;
	}

	/// <summary>
	/// 扩展引导标记
	/// </summary>
	public byte BootSig {
		get => Data[38];
		set => Data[38] = value;
	}


	/// <summary>
	/// 卷序列号
	/// </summary>
	public uint VolId {
		get => BitConverter.ToUInt32(Data[39..43]);
		set => Data.RangeCopy(stackalloc byte[] {
			                                        (byte)(value & 0xff),
			                                        (byte)((value & 0xff00) >> 8),
			                                        (byte)((value & 0xff0000) >> 16),
			                                        (byte)((value & 0xff000000) >> 24)
		                                        }, 32);
	}

	/// <summary>
	/// 卷标
	/// </summary>
	public byte[] VolLab {
		get => Data[43..54];
		set => Data.RangeCopy(value, 43);
	}

	/// <summary>
	/// 文件系统类型
	/// </summary>
	public byte[] FileSysType {
		get => Data[54..64];
		set => Data.RangeCopy(value, 54);
	}

	/// <summary>
	/// 汇编代码
	/// </summary>
	public byte[] AsmCode {
		get => Data[64..510];
		set => Data.RangeCopy(value, 64);
	}

	/// <summary>
	/// 结束标志
	/// </summary>
	public byte[] EndTag {
		get => Data[510..512];
		set => Data.RangeCopy(value, 510);
	}
	
	
	public BiosPramBlock(in byte[] dataBytes) {
		if (dataBytes == null) {
			throw new ArgumentNullException(nameof(dataBytes));
		}

		Data = (byte[])dataBytes.Clone();
	}

	public BiosPramBlock(in Span<byte> dataBytesSpan)
		=> Data = dataBytesSpan.ToArray();

	/// <summary>
	/// UTF8 编码下的厂商名
	/// </summary>
	public string GetDiskOemNameByUtf8String() 
		=> System.Text.Encoding.UTF8.GetString(OemName);

	/// <summary>
	/// UTF8 编码下的卷标
	/// </summary>
	public string GetVolumeLabelByUtf8String() => System.Text.Encoding.UTF8.GetString(VolLab);

	/// <summary>
	/// UTF8 编码下的文件系统类型
	/// </summary>
	public string GetFileSystemTypeByUtf8String() 
		=> System.Text.Encoding.UTF8.GetString(FileSysType);

	/// <summary>
	/// 引导块结束位置字节的后一个字节
	/// </summary>
	public int BiosPramBlockEnd             
		=> ResvdSecCnt * BytePerSec;

	/// <summary>
	/// FAT表起始字节位置 / 保留扇区结束位置
	/// </summary>
	public int FatTableStartByteAddr
		=> ResvdSecCnt * BytePerSec;
	
	/// <summary>
	/// FAT 表的字节大小
	/// </summary>
	public int FatTableByteCount                 
		=> FatSz16 * BytePerSec;
	
	/// <summary>
	/// 根目录表起始字节
	/// </summary>
	public int RootDirectoryEntryStartBytePosition
		=> FatTableStartByteAddr + FatSz16 * BytePerSec * 2;
	
	/// <summary>
	/// 根目录表总字节大小
	/// </summary>
	public int RootDictionaryEntryBytesCount 
		=> RootEndCnt * 32;

	/// <summary>
	/// 目录表总字节大小
	/// </summary>
	public int DictionaryEntryBytesCount
		=> RootEndCnt * 32;
	
	/// <summary>
	/// 获取目标簇的第一个字节位置
	/// </summary>
	/// <param name="logicalCluster">目标簇号</param>
	/// <returns>目标簇的第一个字节位置</returns>
	public int GetClusterStartBytePosition(in int logicalCluster)
		=> (logicalCluster - 2) 
		   * (BytePerSec * SecPerClus) 
		   + (ResvdSecCnt + NumFaTs * FatSz16) 
		   * BytePerSec + RootEndCnt * 32;
	
	/// <summary>
	/// 一个 FAT 表的总字节数
	/// </summary>
	public int FatBytesSize 
		=> FatSz16 * BytePerSec;

	/// <summary>
	/// 一个簇的字节数量
	/// </summary>
	public int ClusterByteCount
		=> SecPerClus * BytePerSec;
	
	public const int BiosPramBlockBytesCount = 512;

	public override string ToString()
		=> string.Join('\n',
		               $"制造商: {GetDiskOemNameByUtf8String()}",
		               $"文件系统类型: {GetFileSystemTypeByUtf8String()}",
		               $"卷标ID: {VolId}",
		               $"卷标名: {GetVolumeLabelByUtf8String()}",
		               $"每个扇区的字节数: {BytePerSec}",
		               $"每个簇的扇区数: {SecPerClus}",
		               $"保留扇区总数: {ResvdSecCnt}",
		               $"FAT数量: {NumFaTs}",
		               $"根目录条目数量上限: {RootEndCnt}",
		               $"每个FAT占用扇区数: {FatSz16}",
		               $"扇区总数: {(TotSec16 == 0 ? TotSec32 : TotSec16)}"
		              );

	public ConsoleTable GetPrintConsoleTable() {
		var consoleTable = new ConsoleTable(new ConsoleTableOptions() {
			                                                              Columns         = new[] { "Key", "Value" },
			                                                              EnableCount     = false,
			                                                              NumberAlignment = Alignment.Right
		                                                              });

		consoleTable
			.AddRow(new object[] { "OEM", GetDiskOemNameByUtf8String() })
			.AddRow(new object[] { "File System Type", GetFileSystemTypeByUtf8String() })
			.AddRow(new object[] { "Volume ID", VolId })
			.AddRow(new object[] { "Volume Label", GetVolumeLabelByUtf8String() })
			.AddRow(new object[] { "Sector Byte Size", BytePerSec })
			.AddRow(new object[] { "Sectors Per Cluster", SecPerClus })
			.AddRow(new object[] { "Reserved Sectors Count", ResvdSecCnt })
			.AddRow(new object[] { "FAT Count", NumFaTs })
			.AddRow(new object[] { "Root Directory Entries Count", RootEndCnt })
			.AddRow(new object[] { "Sector Occupied Count By Each FAT", FatSz16 })
			.AddRow(new object[] { "Sector Count", (TotSec16 == 0 ? TotSec32 : TotSec16) });
		return consoleTable;
	}
}