namespace Fat12;

/// <summary>
/// 文件控制块 时间
/// </summary>
public struct FatFileTime {
	/// <summary>
	/// 小时
	/// </summary>
	public int Hour   {get; set; }
	
	/// <summary>
	/// 分钟
	/// </summary>
	public int Minute {get; set; }

	public FatFileTime(ushort stamp) {
		Hour   = (stamp & 0b1111100000000000) >> 11;
		Minute = (stamp & 0b0000011111100000) >> 5;
	}
	public readonly override string ToString() 
		=> $"{Hour:00}:{Minute:00}";

	public readonly ushort ToUInt16() 
		=> (ushort)((Hour << 6) | Minute);
}