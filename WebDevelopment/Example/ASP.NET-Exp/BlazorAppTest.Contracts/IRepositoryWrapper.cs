namespace BlazorAppTest.Contracts;

public interface IRepositoryWrapper
{
    IPlayerRepository Player { get; }

    ICharacterRepository Character { get; }

    Task<int> SaveAsync();
}
