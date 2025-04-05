using System.Text;

namespace Fat12; 

/// <summary>
/// FAT12 设备
/// </summary>
public class FatDisk {
	/// <summary>
	/// 主启动区
	/// </summary>
	// public BIOSPramBlock BPB { get; set; }
	public BiosPramBlock BPB { get; set; }
	// public FileAllocationTable[] FATList { get; set; }
	
	/// <summary>
	/// 文件分配表1
	/// </summary>
	public FileAllocationTable FatList1 { get; set; }
	
	/// <summary>
	/// 文件分配表2
	/// </summary>
	public FileAllocationTable FatList2 { get; set; }
	// public FileControlBlock[]  FCBList  { get; set; }

	/// <summary>
	/// 根目录
	/// </summary>
	public DictionaryForFileControlBlockByte RootDictionaryEntry { get; set; }
	
	/// <summary>
	/// 使用读入流初始化设备
	/// </summary>
	/// <param name="stream">读入流</param>
	public FatDisk(Stream stream) {
		// 读取引导区
		stream.Seek(0, SeekOrigin.Begin);
		using (var binaryReader = new BinaryReader(stream, Encoding.Default, true)) {
			BPB = new BiosPramBlock(binaryReader.ReadBytes(BiosPramBlock.BiosPramBlockBytesCount));
		}

		// 跳过保留扇区
		stream.Seek(BPB.FatTableStartByteAddr, SeekOrigin.Begin);
		using (var binaryReader = new BinaryReader(stream, Encoding.Default, true)) {
			FatList1 = new FileAllocationTable(binaryReader.ReadBytes(BPB.FatTableByteCount));
			FatList2 = new FileAllocationTable(binaryReader.ReadBytes(BPB.FatTableByteCount));
			RootDictionaryEntry =
				new DictionaryForFileControlBlockByte(binaryReader.ReadBytes(BPB.RootDictionaryEntryBytesCount));
		}
	}

	/// <summary>
	/// 装载设备
	/// </summary>
	/// <param name="diskName">设备名</param>
	/// <returns>设备的描述对象</returns>
	public static FatDisk Load(string diskName) {
		using var fs   = File.OpenRead(diskName);
		var   disk = new FatDisk(fs);
		return disk;
	}
}