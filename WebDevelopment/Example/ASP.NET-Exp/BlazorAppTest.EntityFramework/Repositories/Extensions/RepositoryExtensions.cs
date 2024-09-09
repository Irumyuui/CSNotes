using System.Reflection;
using System.Text;
using System.Linq.Dynamic.Core;

namespace BlazorAppTest.EntityFramework.Repositories.Extensions;

public static class RepositoryExtensions
{
    public static IQueryable<T> OrderByQuery<T>(this IQueryable<T> queryable, string? queryString)
    {
        if (string.IsNullOrWhiteSpace(queryString))
            return queryable;

        var orderParams = queryString.Trim().Split(',');
        var propertyInfos = typeof(T).GetProperties(BindingFlags.Public | BindingFlags.Instance);

        var orderQueryBuilder = new StringBuilder();
        foreach (var orderParam in orderParams) {
            if (string.IsNullOrWhiteSpace(orderParam))
                continue;

            var propertyFromQueryName = orderParam.Split(' ')[0];
            var objectProperty = propertyInfos.FirstOrDefault(p => p.Name.Equals(propertyFromQueryName, StringComparison.InvariantCultureIgnoreCase));
            if (objectProperty is null)
                continue;

            var sortingOrder = orderParam.EndsWith(" desc") ? "descending" : "ascending";
            orderQueryBuilder.Append($"{objectProperty.Name} {sortingOrder}, ");
        }

        var orderQueryString = orderQueryBuilder.ToString().TrimEnd(',', ' ');
        return queryable.OrderBy(orderQueryString);
    }
}