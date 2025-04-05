using System.Collections;

namespace Fat12;

public class FileAllocationTableEnum : IEnumerator {
	private readonly FileAllocationTable _fileAllocationTable;
	private          int                 _position = -1;

	public FileAllocationTableEnum(FileAllocationTable fileAllocationTable) {
		_fileAllocationTable = fileAllocationTable;
	}

	public bool MoveNext() 
		=> (++_position) < _fileAllocationTable.Length;

	public void Reset() 
		=> _position = -1;

	public object Current 
		=> _fileAllocationTable[_position];
}

/// <summary>
/// 文件分配表项类型
/// </summary>
public enum FileAllocationTableItemState {
	Free,
	Reserved,
	ToNext,
	ReservedValue,
	Bad,
	FileLast,
}

/// <summary>
/// 文件分配表表项扩展方法
/// </summary>
public static class FileAllocationTableItemStateExtensions {
	public static bool IsUsed(this FileAllocationTableItemState state)
		=> state is FileAllocationTableItemState.ToNext or FileAllocationTableItemState.FileLast;

	public static bool IsFileEnd(this FileAllocationTableItemState state) 
		=> state is FileAllocationTableItemState.FileLast;

	public static bool IsFree(this FileAllocationTableItemState state) 
		=> state is FileAllocationTableItemState.Free;

	public static bool IsUsed(this FileAllocationTableItem item)
		=> item.GetFileAllocationTableItemState().IsUsed();

	public static bool IsFileEnd(this FileAllocationTableItem item)
		=> item.GetFileAllocationTableItemState().IsFileEnd();

	public static bool IsFree(this FileAllocationTableItem item)
		=> item.GetFileAllocationTableItemState().IsFree();
}

/// <summary>
/// 文件分配表表项
/// </summary>
public struct FileAllocationTableItem {
	public ushort Value { get; set; }

	/// <summary>
	/// 获取该表项指向的下一个表项的下标
	/// </summary>
	/// <returns></returns>
	public ushort GetNextItemIndex() => Value;
	
	public FileAllocationTableItem(in ushort value = 0) => Value = value;

	/// <summary>
	/// 获取文件分配表表项状态
	/// </summary>
	/// <returns>文件分配表表项状态</returns>
	public FileAllocationTableItemState GetFileAllocationTableItemState() {
		return Value switch {
			       0x000                 => FileAllocationTableItemState.Free,
			       0x001                 => FileAllocationTableItemState.Reserved,
			       >= 0x002 and <= 0xFEF => FileAllocationTableItemState.ToNext,
			       >= 0xFF0 and <= 0xFF6 => FileAllocationTableItemState.ReservedValue,
			       0xFF7                 => FileAllocationTableItemState.Bad,
			       _                     => FileAllocationTableItemState.FileLast
		       };
	}

	public override string ToString()
		=> $"{Value:x3}";

	/// <summary>
	/// 由提供的数字转化为表项
	/// </summary>
	/// <param name="value">来源12位数字</param>
	/// <returns>构造的文件分配表表项</returns>
	/// <exception cref="ArgumentOutOfRangeException">超过12位限制</exception>
	public static FileAllocationTableItem GetFileAllocationTableItem(in ushort value) {
		if (value >= 0xFFF) {
			throw new ArgumentOutOfRangeException(nameof(value),
			                                      $"Out of Ranges: {(uint)value:x}. In [0x000, 0xFFF]");
		}
		return new FileAllocationTableItem(value);
	}

	/// <summary>
	/// 由提供的数字转化为表项的状态
	/// </summary>
	/// <param name="value">来源12位数字</param>
	/// <returns>表项的状态</returns>
	/// <exception cref="ArgumentOutOfRangeException">超过12位限制</exception>
	public static FileAllocationTableItemState GetFileAllocationTableItemState(in ushort value) {
		if (value >= 0xFFF) {
			throw new ArgumentOutOfRangeException(nameof(value),
			                                      $"Out of Ranges: {(uint)value:x}. In [0x000, 0xFFF]");
		}
		FileAllocationTableItemState state;
		unsafe {
			var tmp = stackalloc FileAllocationTableItem[1];
			ref var tag = ref tmp[0];
			tag.Value = value;
			state     = tag.GetFileAllocationTableItemState();
		}
		return state;
	}
}

/// <summary>
/// 文件分配表
/// </summary>
public class FileAllocationTable {
	/// <summary>
	/// 文件分配表数据
	/// </summary>
	public byte[] Data { get; set; }

	/// <summary>
	/// 文件分配表的表项
	/// </summary>
	/// <param name="index">从0开始的表项编号</param>
	public FileAllocationTableItem this[int index] {
		get => index % 2 == 0
			       ? new FileAllocationTableItem((ushort)(Data[index * 3 / 2] |
			                                              ((ushort)(Data[index * 3 / 2 + 1] & 0x0f)) << 8))
			       : new FileAllocationTableItem((ushort)((Data[index * 3 / 2] & 0xf0) >> 4 |
			                                              Data[index * 3 / 2 + 1] << 4));
		set {
			if (index % 2 == 0) {
				Data[index * 3 / 2]     = (byte)(value.Value & 0x0ff);
				Data[index * 3 / 2 + 1] = (byte)((byte)((value.Value & 0xf00) >> 8) | (byte)(Data[index * 3 / 2 + 1] & 0xf0));
			} else {
				Data[index * 3 / 2]     = (byte)(((byte)(value.Value & 0x00f) << 4) | (byte)(Data[index * 3 / 2] & 0x0f));
				Data[index * 3 / 2 + 1] = (byte)((value.Value & 0xff0) >> 4);
			}
		}
	}

	public FileAllocationTableItem GetNext(int idx) 
		=> this[idx];
	
	/// <summary>
	/// 总字节数
	/// </summary>
	public int DataLength 
		=> Data.Length;

	/// <summary>
	/// 表项数
	/// </summary>
	public int Length
		=> Data.Length * 8 / 12;

	/// <summary>
	/// 从字节数组中构造文件分配表
	/// </summary>
	/// <param name="dataBytes">FAT字节数组</param>
	/// <exception cref="ArgumentNullException">字节数组不可为空</exception>
	public FileAllocationTable(in byte[] dataBytes) {
		if (dataBytes == null) {
			throw new ArgumentNullException(nameof(dataBytes));
		}
		Data = dataBytes.ToArray();
	}
	
	public FileAllocationTable(in Span<byte> dataSpan) 
		=> Data = dataSpan.ToArray();

	public IEnumerator GetEnumerator() 
		=> new FileAllocationTableEnum(this);

	/// <summary>
	/// 得到文件分配表的字符串列表
	/// 跳过没有被分配的文件分配表表项
	/// </summary>
	/// <returns>文件分配表的字符串列表</returns>
	public List<string> ToStringList() {
		List<string> list = new List<string>();		
		for (int i = 0; i < this.Length; i++) {
			var next = this[i];
			if (next.IsFree() == false) {
				list.Add($"[{i}] => 0x{next}");
			}
		}
		return list;
	}
}