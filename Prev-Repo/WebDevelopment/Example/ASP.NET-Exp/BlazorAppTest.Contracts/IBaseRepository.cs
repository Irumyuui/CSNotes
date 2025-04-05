using System.Linq.Expressions;

namespace BlazorAppTest.Contracts;

public interface IBaseRepository<TSource>
{
    IQueryable<TSource> FindAll();
    IQueryable<TSource> FindByCondition(Expression<Func<TSource, bool>> expression);
    void Create(TSource entity);
    void Update(TSource entity);
    void Delete(TSource entity);
}
