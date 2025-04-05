namespace Fat12;

/// <summary>
/// 目录表
/// </summary>
public class DictionaryForFileControlBlockByte {
	/// <summary>
	/// 存储目录表字节
	/// </summary>
	public byte[] Data { get; set; }

	/// <summary>
	/// 获取目录表字节长度
	/// </summary>
	public int Length => Data.Length / 32;
	
	/// <summary>
	/// 获取对应的目录表项，解析为文件控制块
	/// </summary>
	/// <param name="idx"></param>
	public FileControlBlock this[int idx] {
		get {
			int offer = idx * 32;
			return new FileControlBlock(Data[offer..(offer + 32)]);
		}
		set {
			int offer = idx * 32;
			for (int i = offer; i < 32; i++) {
				Data[i] = value[i - offer];
			}
		}
	}

	public DictionaryForFileControlBlockByte(in byte[] data) {
		if (data == null) {
			throw new ArgumentNullException(nameof(data));
		}

		Data = (byte[])data.Clone();
	}
}