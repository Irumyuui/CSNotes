// using FAT;

using System.Text;

namespace Fat12;

/// <summary>
/// Disk 管理
/// </summary>
public class DiskManager {
	/// <summary>
	/// 磁盘
	/// </summary>
	public FatDisk Disk     { get; set;  }
	
	/// <summary>
	/// 磁盘文件名
	/// </summary>
	public string  DiskName { get; set; }

	public DiskManager(in string? diskName) {
		DiskName = diskName ?? throw new ArgumentNullException(nameof(diskName));
		Disk     = FatDisk.Load(diskName);
	}

	/// <summary>
	/// Load FAT Table from disk
	/// </summary>
	public void LoadDiskFatTable() {
		using var fs           = File.OpenRead(DiskName);
		fs.Seek(Disk.BPB.FatTableStartByteAddr, SeekOrigin.Begin);
		using var binaryReader = new BinaryReader(fs, Encoding.Default, true);
		Disk.FatList1 = new FileAllocationTable(binaryReader.ReadBytes(Disk.BPB.FatBytesSize));
		Disk.FatList2 = new FileAllocationTable(binaryReader.ReadBytes(Disk.BPB.FatBytesSize));
	}

	/// <summary>
	/// Write FAT Table into disk
	/// </summary>
	public void WriteDiskFatTable() {
		using var fs = File.OpenWrite(DiskName);
		fs.Seek(Disk.BPB.FatTableStartByteAddr, SeekOrigin.Begin);
		using var binaryWriter = new BinaryWriter(fs, Encoding.Default, true);
		binaryWriter.Write(Disk.FatList1.Data);
		binaryWriter.Write(Disk.FatList2.Data);
	}
	
	/// <summary>
	/// Load Root Dictionary Entry from disk
	/// </summary>
	public void LoadDiskRootDictionaryEntry() {
		Disk.RootDictionaryEntry.Data =
			ReadBytes(Disk.BPB.RootDirectoryEntryStartBytePosition, Disk.BPB.RootDictionaryEntryBytesCount);
	}
	
	/// <summary>
	/// Write Root Dictionary Entry Into disk
	/// </summary>
	public void WriteDiskRootDictionaryEntry() {
		using var fs = File.OpenWrite(DiskName);
		fs.Seek(Disk.BPB.RootDirectoryEntryStartBytePosition, SeekOrigin.Begin);
		using var binaryWriter = new BinaryWriter(fs, Encoding.Default, true);
		binaryWriter.Write(Disk.RootDictionaryEntry.Data);
	}

	/// <summary>
	/// 读取指定个数簇的大小
	/// </summary>
	/// <param name="clusterIndex">开始簇</param>
	/// <param name="readCount">指定簇的个数</param>
	/// <returns>所读字节数组</returns>
	public byte[] ReadClusterBytes(in int clusterIndex, in int readCount = 1) {
		return ReadBytes(Disk.BPB.GetClusterStartBytePosition(clusterIndex),
		                           Disk.BPB.ClusterByteCount * readCount);
	}

	/// <summary>
	/// 从硬盘中读取指定字节
	/// </summary>
	/// <param name="offset">偏移量</param>
	/// <param name="bytesCount">字节数</param>
	/// <returns></returns>
	public byte[] ReadBytes(int offset, int bytesCount) {
		using var fs = File.OpenRead(DiskName);
		fs.Seek(offset, SeekOrigin.Begin);
		using var binaryReader = new BinaryReader(fs, Encoding.Default, true);
		var       data         = binaryReader.ReadBytes(bytesCount);
		return data;
	}
	
	/// <summary>
	/// 从根目录装载已用文件目录表表项列表
	/// </summary>
	/// <returns>已用文件目录表表项列表</returns>
	public List<(FileControlBlock, int)> GetRootDirectoryFolderList() {
		// List<List< (FileControlBlock, int)>> folder = new(512);

		List<(FileControlBlock, int)> rootFolder = new(512);
		__InitFileDictionaryList(Disk.RootDictionaryEntry, ref rootFolder);

// 		List<LongFileNameBlock>? longFileNameBlocks = null;
//
// 		for (int i = 0; i < Disk.RootDictionaryEntry.Length; i++) {
// #if DEBUG
// 			Console.WriteLine($"Item idx: {i}");
// 			longFileNameBlocks
// 				?.ForEach(x => Console.WriteLine(x));
// #endif
// 			var              preItem = Disk.RootDictionaryEntry[i];
// 			FileControlBlock item;
// 			if (preItem.IsDeleteFile()) {
// 				longFileNameBlocks?.Clear();
// 			}
//
// 			if (preItem.IsLongFileNamePark()) {
// 				longFileNameBlocks ??= new List<LongFileNameBlock>();
// 				longFileNameBlocks.Add(new LongFileNameBlock(preItem.Data));
// 				continue;
// 			} else {
// 				longFileNameBlocks?.Reverse();
// 				item               = new FileControlBlock(preItem.Data, longFileNameBlocks);
// 				longFileNameBlocks = null;
// 			}
//
// 			if (item.IsEmptyFile()) {
// 				continue;
// 			}
//
// 			if (item.IsEmptyFileWithLater()) {
// 				break;
// 			}
//
// 			try {
// 				var attr = item.GetAttributeType();
// 				if (attr is FileControlBlockAttributeType.Directory or FileControlBlockAttributeType.Regular) {
// 					rootFolder.Add((item, i));
// 				}
// 			} catch (Exception e) {
// 				// ignored
// 				Console.ForegroundColor = ConsoleColor.Yellow;
// 				Console.Error.WriteLine(e);
// 				Console.ResetColor();
// 			}
// 		}

#if DEBUG
		rootFolder
			.ToList()
			.OrderBy(x => x.Item1.Attribute)
			.ThenBy(x => x.Item1.FileName)
			.ToList()
			.ForEach(x => Console.WriteLine(x));
#endif

		return rootFolder
			.OrderBy(x => x.Item1.Attribute)
			.ThenBy(x => x.Item1.FileName)
			.ToList();
	}

	/// <summary>
	/// 从根目录装载已用文件目录表表项列表
	/// </summary>
	/// <param name="rootFolder">已用文件目录表表项列表</param>
	/// <exception cref="ArgumentNullException">已用文件目录表表项列表不可为null</exception>
	public void GetRootDirectoryFolderList(ref List< (FileControlBlock, int)> rootFolder) {
		if (rootFolder == null) {
			throw new ArgumentNullException(nameof(rootFolder));
		}
		
		rootFolder.Clear();
		__InitFileDictionaryList(Disk.RootDictionaryEntry, ref rootFolder);
		rootFolder
			.Sort((x, y) 
				      => x.Item1.Attribute != y.Item1.Attribute 
					         ? x.Item1.Attribute.CompareTo(y.Item1.Attribute) 
					         : x.Item1.FileName.CompareTo(y.Item1.FileName));
	}

	/// <summary>
	/// 重新加载根目录表
	/// </summary>
	public void ReLordRootDirectoryEntry()
		=> Disk.RootDictionaryEntry.Data = ReadBytes(Disk.BPB.RootDirectoryEntryStartBytePosition,
		                                             Disk.BPB.RootDictionaryEntryBytesCount);

	/// <summary>
	/// 从传递的文件目录表装载已用文件目录表表项列表
	/// </summary>
	/// <param name="fileDictionary">来源文件目录表</param>
	/// <param name="resultList">已用文件目录表表项列表</param>
	/// <exception cref="ArgumentNullException">已用文件目录表表项列表不可为空，来源文件目录表不可为空</exception>
	private static void __InitFileDictionaryList(in DictionaryForFileControlBlockByte fileDictionary, ref List<(FileControlBlock, int)> resultList) {
#if DEBUG
		if (fileDictionary == null) throw new ArgumentNullException(nameof(fileDictionary));
		if (resultList == null) throw new ArgumentNullException(nameof(resultList));
#endif
		if (resultList.Any()) resultList.Clear();
		
		for (var i = 0; i < fileDictionary.Length; i++) {
			var item = fileDictionary[i];
			if (item.IsEmptyFile()) continue;
			if (item.IsEmptyFileWithLater()) break;

			try {
				var attr = item.GetAttributeType();
				if (attr is FileControlBlockAttributeType.Directory or FileControlBlockAttributeType.Regular)
					resultList.Add((item, i));
			} catch (Exception e) {
				Console.ForegroundColor = ConsoleColor.Yellow;
				Console.WriteLine(e);
				Console.ResetColor();
				// throw;
			}
		}
	}

	/// <summary>
	/// 从目标簇块的文件目录表装载已用文件目录表表项列表，抛弃不可用的表项
	/// </summary>
	/// <param name="targetFileLogicBlockId">目标簇块</param>
	/// <returns>已用文件目录表表项列表</returns>
	public List<(FileControlBlock, int)> GetFileDictionaryList(in int targetFileLogicBlockId) {
		var fileDictionary = new
			DictionaryForFileControlBlockByte(ReadBytes(Disk.BPB.GetClusterStartBytePosition(targetFileLogicBlockId),
			                                            Disk.BPB.RootDictionaryEntryBytesCount));
		List<(FileControlBlock, int)> resultList = new(512);
		__InitFileDictionaryList(fileDictionary, ref resultList);
		return resultList;
	} 
	
	/// <summary>
	/// 从目标簇块的文件目录表装载已用文件目录表表项列表，抛弃不可用的表项
	/// </summary>
	/// <param name="targetFileLogicBlockId">目标簇块</param>
	/// <param name="resultList">已用文件目录表表项列表</param>
	/// <returns>被读取的目录表项</returns>
	/// <exception cref="ArgumentNullException">resultList必须不为空</exception>
	public DictionaryForFileControlBlockByte ReloadFileDictionaryList(in int targetFileLogicBlockId, ref List<(FileControlBlock, int)> resultList) {
#if DEBUG
		if (resultList == null) throw new ArgumentNullException(nameof(resultList));
#endif
		var dictionaryFcbByte =
			new DictionaryForFileControlBlockByte(ReadBytes(Disk.BPB.GetClusterStartBytePosition(targetFileLogicBlockId),
			                                                Disk.BPB.RootDictionaryEntryBytesCount));
		resultList.Clear();
		__InitFileDictionaryList(dictionaryFcbByte, ref resultList);
		return dictionaryFcbByte;
	} 
}