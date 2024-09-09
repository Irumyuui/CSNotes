using BlazorAppTest.Entites.ResponseType;
using Microsoft.EntityFrameworkCore;

namespace BlazorAppTest.Entites.RequestFeatures;

public static class PagedExtensions
{
    public static async Task<PageList<TSource>> ToPageListAsync<TSource>(this IQueryable<TSource> source, int pageNumber, int pageSize, CancellationToken cancellationToken = default)
    {
        var count = source.Count();
        var items = await source.Skip((pageNumber - 1) * pageSize)
                          .Take(pageSize)
                          .ToListAsync(cancellationToken);
        return new PageList<TSource>(items, count, pageNumber, pageSize);
    }
}
