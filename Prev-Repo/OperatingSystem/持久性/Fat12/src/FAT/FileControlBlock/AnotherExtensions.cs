namespace Fat12;

/// <summary>
/// 扩展方法
/// 想不到名字
/// </summary>
public static class AnotherExtensions  {
	public static T[] Slice<T>(this T[] source, int start, int end) {
		if (end < 0) {
			end = source.Length + end;
		}
		var len = end - start;
		var res = new T[len];
		for (var i = 0; i < len; i++) {
			res[i] = source[i + start];
		}
		return res;
	}

	/// <summary>
	/// 拷贝数组
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="wic"></param>
	/// <param name="start"></param>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	public static T[] RangeCopy<T>(this T[] arr, T[] wic, int start = 0) {
		for (int i = 0; i < wic.Length; i++) {
			arr[i + start] = wic[i];
		}
		return arr;
	}
	
	public static T[] RangeCopy<T>(this T[] arr, Span<T> wic, int start = 0) {
		for (int i = 0; i < wic.Length; i++) {
			arr[i + start] = wic[i];
		}
		return arr;
	}
}