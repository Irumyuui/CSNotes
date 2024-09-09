using BlazorAppTest.Contracts;
using Microsoft.EntityFrameworkCore;
using System.Linq.Expressions;

namespace BlazorAppTest.EntityFramework.Repositories;

public abstract class BaseRepository<T> : IBaseRepository<T> where T : class
{
    protected GameManagementDbContext GameDbContext { get; set; }

    protected BaseRepository(GameManagementDbContext repositoryContext) =>
        GameDbContext = repositoryContext;

    public IQueryable<T> FindAll() =>
        GameDbContext.Set<T>().AsNoTracking();

    public IQueryable<T> FindByCondition(Expression<Func<T, bool>> expression) =>
        GameDbContext.Set<T>().Where(expression).AsNoTracking();

    public void Create(T entity) =>
        GameDbContext.Set<T>().Add(entity);

    public void Update(T entity) =>
        GameDbContext.Set<T>().Update(entity);

    public void Delete(T entity) =>
        GameDbContext.Set<T>().Remove(entity);
}
