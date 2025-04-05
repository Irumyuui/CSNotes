using BlazorAppTest.Entites;

namespace BlazorAppTest.EntityFramework.Repositories.Extensions;

public static class PlayerRepositoryExtensions
{
    public static IQueryable<Player> SearchByAccount(this IQueryable<Player> players, string? account)
    {
        if (string.IsNullOrWhiteSpace(account))
            return players;

        return players.Where(p => p.Account.ToLower().Contains(account.Trim().ToLower()));
    }
}
