using System.Collections;
using System.Text;

namespace Fat12;

// [StructLayout(LayoutKind.Sequential, Pack = 1)]

// BPB
/// <summary>
/// Boot Sector of FAT12.
/// </summary>
public struct BIOSPramBlock__IsNotUse {
	/// <summary>
	/// 跳转指令
	/// </summary>
	public byte[] JmpBOOT {get; set; }  // 一个跳转指令 3

	/// <summary>
	/// 厂商名
	/// </summary>
	public byte[] OEMName {get; set; }  // 厂商名 8
	
	/// <summary>
	/// 每扇区字节数
	/// </summary>
	public ushort BytePerSec {get; set; }  //  2
	
	/// <summary>
	/// 每簇扇区数
	/// </summary>
	public byte SecPerClus {get; set; }  // 1
	
	/// <summary>
	/// 保留扇区数
	/// 包括启动扇区
	/// </summary>
	public ushort ResvdSecCnt {get; set; }  // 2
	
	/// <summary>
	/// 文件分配表数目
	/// </summary>
	public byte NumFATs {get; set; }  // 1
	
	/// <summary>
	/// 最大根目录条目个数
	/// </summary>
	public ushort RootEndCnt {get; set; }  // 2
	
	/// <summary>
	/// 总扇区数
	/// </summary>
	public ushort TotSec16 {get; set; }  // 2
	
	/// <summary>
	/// 介质描述
	/// </summary>
	public byte Media {get; set; }  // 1
	
	/// <summary>
	/// 每个文件分配表的扇区数
	/// </summary>
	public ushort FATSz16 {get; set; }  // 2
	
	/// <summary>
	/// 每磁道的扇区
	/// </summary>
	public ushort SecPerTrk {get; set; }
	
	/// <summary>
	/// 磁头数
	/// </summary>
	public ushort NumHeads {get; set; }
	
	/// <summary>
	/// 隐藏扇区数
	/// </summary>
	public uint HiddSec {get; set; }
	
	/// <summary>
	/// 总扇区数
	/// 如果 TotSec16 范围超过将启用该属性
	/// </summary>
	public uint TotSec32 {get; set;}
	
	/// <summary>
	/// 驱动号
	/// </summary>
	public byte DrvNum {get; set; }

	/// <summary>
	/// 保留位
	/// </summary>
	public byte Reserved1 {get; set; }
	
	/// <summary>
	/// 扩展引导标记
	/// </summary>
	public byte BootSig {get; set; }

	/// <summary>
	/// 卷序列号
	/// </summary>
	public uint VolID {get; set; }

	/// <summary>
	/// 卷标
	/// </summary>
	public byte[] VolLab {get; set; }  // 11
	
	/// <summary>
	/// 文件系统类型
	/// </summary>
	public byte[] FileSysType {get; set; }  // 8
	
	/// <summary>
	/// 使用读入流初始化
	/// </summary>
	/// <param name="stream">读入流</param>
	public BIOSPramBlock__IsNotUse(Stream stream) {
		using var reader = new BinaryReader(stream, Encoding.Default, true);
		JmpBOOT     = reader.ReadBytes(3);
		OEMName     = reader.ReadBytes(8);
		BytePerSec  = reader.ReadUInt16();
		SecPerClus  = reader.ReadByte();
		ResvdSecCnt = reader.ReadUInt16();
		NumFATs     = reader.ReadByte();
		RootEndCnt  = reader.ReadUInt16();
		TotSec16    = reader.ReadUInt16();
		Media       = reader.ReadByte();
		FATSz16     = reader.ReadUInt16();
		SecPerTrk   = reader.ReadUInt16();
		NumHeads    = reader.ReadUInt16();
		HiddSec     = reader.ReadUInt32();
		TotSec32    = reader.ReadUInt32();
		DrvNum      = reader.ReadByte();
		Reserved1   = reader.ReadByte();
		BootSig     = reader.ReadByte();
		VolID       = reader.ReadUInt32();
		VolLab      = reader.ReadBytes(11);
		FileSysType = reader.ReadBytes(8);
	}

	/// <summary>
	/// UTF8 编码下的厂商名
	/// </summary>
	public string DiskOEMName
		=> System.Text.Encoding.UTF8.GetString(OEMName);
	
	/// <summary>
	/// UTF8 编码下的卷标
	/// </summary>
	public string Volumelabel 
		=> System.Text.Encoding.UTF8.GetString(VolLab);
	
	/// <summary>
	/// UTF8 编码下的文件系统类型
	/// </summary>
	public string FileSystemType 
		=> System.Text.Encoding.UTF8.GetString(FileSysType);

	/// <summary>
	/// 引导块结束位置字节的后一个字节
	/// </summary>
	public readonly int BIOSPramBlockEnd             
		=> ResvdSecCnt * BytePerSec;
	
	/// <summary>
	/// FAT 表的字节大小
	/// </summary>
	public readonly int FATTableSize                 
		=> FATSz16 * BytePerSec;
	
	/// <summary>
	/// 根目录表起始字节
	/// </summary>
	public readonly int RootDirectoryEntryStart
		=> BIOSPramBlockEnd + FATSz16 * BytePerSec * 2;

	/// <summary>
	/// 根目录表总字节大小
	/// </summary>
	public readonly int RootDictionaryEntryBytesCount 
		=> RootEndCnt * 32;

	/// <summary>
	/// 获取目标簇的第一个字节位置
	/// </summary>
	/// <param name="logicalCluster">目标簇号</param>
	/// <returns>目标簇的第一个字节位置</returns>
	public int GetTargetDataAreaStart(in int logicalCluster)
		=> (logicalCluster - 2) 
		   * (BytePerSec * SecPerClus) 
		   + (ResvdSecCnt + NumFATs * FATSz16) 
		   * BytePerSec + RootEndCnt * 32;
	// {
	// 	Console.WriteLine($"({logicalCluster} - 2) * ({BytePerSec} * {SecPerClus}) + ({ResvdSecCnt} + {NumFATs} * {FATSz16}) * {SecPerClus} + {RootEndCnt} * 32");
	// 	return (logicalCluster - 2) * (BytePerSec * SecPerClus) + (ResvdSecCnt + NumFATs * FATSz16) * SecPerClus +
	// 	RootEndCnt * 32;
	// }

	/// <summary>
	/// 一个 FAT 表的总字节数
	/// </summary>
	public readonly int FATBytesSize 
		=> FATSz16 * BytePerSec; 

	public override string ToString()
		=> string.Join('\n',
		               $"制造商: {DiskOEMName}",
		               $"文件系统类型: {FileSystemType}",
		               $"卷标ID: {VolID}",
		               $"卷标名: {Volumelabel}",
		               $"每个扇区的字节数: {BytePerSec}",
		               $"每个簇的扇区数: {SecPerClus}",
		               $"保留扇区总数: {ResvdSecCnt}",
		               $"FAT数量: {NumFATs}",
		               $"根目录条目数量上限: {RootEndCnt}",
		               $"每个FAT占用扇区数: {FATSz16}",
		               $"扇区总数: {(TotSec16 == 0 ? TotSec32 : TotSec16)}"
		              );
}

// Same style
// Is it can zero GC ?