namespace Fat12;

/// <summary>
/// 文件控制块中的日期读取
/// </summary>
public struct FatFileDate {
	/// <summary>
	/// 年
	/// </summary>
	public int Year {get; set;}
	
	/// <summary>
	/// 月
	/// </summary>
	public int Mouth {get; set; }
	
	/// <summary>
	/// 日
	/// </summary>
	public int Day {get; set; }

	/// <summary>
	/// 由提供的两个字节构造时间
	/// </summary>
	/// <param name="stamp"></param>
	public FatFileDate(ushort stamp) {
		Mouth = stamp & 0b01111;
		Day   = (stamp & 0b0111110000) >> 4;
		Year  = ((stamp & 0b01111111000000000) >> 9) + 1980;
	}

	public readonly override string ToString()
		=> $"{Year:0000}:{Mouth:00}:{Day:00}";

	/// <summary>
	/// 从时间转换为两个字节
	/// </summary>
	/// <returns></returns>
	public ushort ToUInt16()
		=> (ushort)((((uint)Year - 1980) << 9) | ((uint)Day << 4) | ((uint)Mouth));
}