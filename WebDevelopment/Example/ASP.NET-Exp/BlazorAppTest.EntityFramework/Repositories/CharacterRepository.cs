using BlazorAppTest.Contracts;
using BlazorAppTest.Entites;

namespace BlazorAppTest.EntityFramework.Repositories;

public class CharacterRepository : BaseRepository<Character>, ICharacterRepository
{
    public CharacterRepository(GameManagementDbContext repositoryContext) : base(repositoryContext)
    {
    }
}
