namespace Fat12;

/// <summary>
/// 文件属性类型
/// </summary>
public enum FileControlBlockAttributeType : ushort {
	/// <summary>
	/// 只读
	/// </summary>
	ReadOnly = 0x01,
	
	/// <summary>
	/// 隐藏
	/// </summary>
	Hide = 0x02,
	
	/// <summary>
	/// 系统
	/// </summary>
	System = 0x04,
	
	/// <summary>
	/// 卷标
	/// </summary>
	Label = 0x08,
	
	/// <summary>
	/// 目录
	/// </summary>
	Directory = 0x10,
	
	/// <summary>
	/// 文件
	/// </summary>
	Regular = 0x20,
	
	/// <summary>
	/// 设备
	/// </summary>
	Devices = 0x40,
	
	/// <summary>
	/// 未使用
	/// </summary>
	NotUsed = 0x80,
	
	/// <summary>
	/// 长文件名
	/// </summary>
	LongFileName = 0x0F,
	
	/// <summary>
	/// WTF
	/// </summary>
	Wtf
}