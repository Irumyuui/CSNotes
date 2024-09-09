using BlazorAppTest.Contracts;
using BlazorAppTest.Entites;
using BlazorAppTest.Entites.RequestFeatures;
using BlazorAppTest.Entites.ResponseType;
using BlazorAppTest.EntityFramework.Repositories.Extensions;
using Microsoft.EntityFrameworkCore;

namespace BlazorAppTest.EntityFramework.Repositories;

public class PlayerRepository : BaseRepository<Player>, IPlayerRepository
{
    public PlayerRepository(GameManagementDbContext repositoryContext) : base(repositoryContext)
    {
    }

    public async Task<Player?> GetPlayerByIdAsync(Guid playerId) =>
        await FindByCondition(player => player.Id == playerId).FirstOrDefaultAsync();

    public async Task<List<Player>> GetPlayersAsync() =>
        await FindAll().OrderBy(p => p.DateCreated).ToListAsync();

    public async Task<PageList<Player>> GetPlayersAsync(PlayerParameter parameter) =>
        await FindByCondition(player => player.DateCreated.Date >= parameter.MinDateCreated.Date && player.DateCreated.Date <= parameter.MaxDateCreated.Date)
                .SearchByAccount(parameter.Account)
                .OrderByQuery(parameter.OrderBy)
                //.OrderBy(p => p.DateCreated)
                .ToPageListAsync(parameter.PageNumber, parameter.PageSize);
    //await FindAll().OrderBy(p => p.DateCreated).ToPageListAsync(parameter.PageNumber, parameter.PageSize);

    //public async Task<PageList<Player>> GetPlayersAsync(PlayerParameter parameter) =>
    //    await FindAll().OrderBy(p => p.DateCreated).ToPageListAsync(parameter.PageNumber, parameter.PageSize);

    //public async Task<List<Player>> GetPla
    //await FindAll().OrderBy(p => p.DateCreated).Skip((parameter.PageNumber - 1) * parameter.PageSize).Take(parameter.PageSize).ToListAsync();

    public async Task<Player?> GetPlayerWithCharactersAsync(Guid playerId) =>
        await FindByCondition(player => player.Id == playerId).Include(player => player.Characters).FirstOrDefaultAsync();
}
