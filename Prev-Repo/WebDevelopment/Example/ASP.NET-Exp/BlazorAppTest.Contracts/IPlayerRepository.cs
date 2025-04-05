using BlazorAppTest.Entites;
using BlazorAppTest.Entites.RequestFeatures;
using BlazorAppTest.Entites.ResponseType;

namespace BlazorAppTest.Contracts;

public interface IPlayerRepository : IBaseRepository<Player>
{
    Task<List<Player>> GetPlayersAsync();

    Task<PageList<Player>> GetPlayersAsync(PlayerParameter parameter);

    Task<Player?> GetPlayerByIdAsync(Guid playerId);
    
    Task<Player?> GetPlayerWithCharactersAsync(Guid playerId);

    //void CreatePlayerAsync(Player player);
}