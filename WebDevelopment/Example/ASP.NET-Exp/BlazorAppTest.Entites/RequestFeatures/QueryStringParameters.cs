namespace BlazorAppTest.Entites.RequestFeatures;

public abstract class QueryStringParameters
{
    private const int MAX_PAGE_SIZE = 100;
    public int PageNumber { get; set; } = 1;

    private int _pageSize = 10;

    public int PageSize { 
        get => _pageSize; 
        set => _pageSize = int.Min(value, MAX_PAGE_SIZE);
    }


    public string? OrderBy { get; set; }
}
