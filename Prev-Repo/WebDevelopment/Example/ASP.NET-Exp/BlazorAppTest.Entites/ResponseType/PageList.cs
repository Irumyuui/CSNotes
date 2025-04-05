namespace BlazorAppTest.Entites.ResponseType;

public class PageList<T> : List<T>
{
    public PageMetaData MetaData { get; set; }

    public PageList(IEnumerable<T> items, int count, int pageNumber, int pageSize)
    {
        MetaData = new PageMetaData
        {
            TotalCount = count,
            PageSize = pageSize,
            CurrentPage = pageNumber,
            TotalPage = (count + pageSize - 1) / pageSize
        };

        AddRange(items);
    }
}