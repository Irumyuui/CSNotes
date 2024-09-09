using BlazorAppTest.Contracts;
using BlazorAppTest.EntityFramework.Repositories;

namespace BlazorAppTest.EntityFramework;

public class RepositoryWrapper : IRepositoryWrapper
{
    private readonly GameManagementDbContext _gameDbContext;

    private IPlayerRepository? _player;

    private ICharacterRepository? _character;

    public IPlayerRepository Player => _player ??= new PlayerRepository(_gameDbContext);

    public ICharacterRepository Character => _character ??= new CharacterRepository(_gameDbContext);

    public RepositoryWrapper(GameManagementDbContext gameDbContext) => _gameDbContext = gameDbContext;

    public Task<int> SaveAsync() => _gameDbContext.SaveChangesAsync();
}
