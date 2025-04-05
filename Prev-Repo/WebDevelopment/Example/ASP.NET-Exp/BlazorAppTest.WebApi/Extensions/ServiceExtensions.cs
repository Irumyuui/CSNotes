using BlazorAppTest.Contracts;
using BlazorAppTest.EntityFramework;
using Microsoft.EntityFrameworkCore;

namespace BlazorAppTest.WebApi.Extensions;

public static class ServiceExtensions
{
    public static void ConfigureCore(this IServiceCollection service) =>
        service.AddCors(opts => opts.AddPolicy("AnyPolicy", builder => builder.AllowAnyOrigin().AllowAnyMethod().AllowAnyHeader()));

    public static void ConfigureMySqlContext(this IServiceCollection service, IConfiguration config) =>
        service.AddDbContext<GameManagementDbContext>(
            builder => builder.UseMySql(config.GetConnectionString("GameDb") ?? throw new ArgumentNullException("ConnectionString not found."), MySqlServerVersion.LatestSupportedServerVersion));

    public static void ConfigureRepositoryWrapper(this IServiceCollection services)
        => services.AddScoped<IRepositoryWrapper, RepositoryWrapper>();
}
