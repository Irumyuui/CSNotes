using BlazorAppTest.Entites;

namespace BlazorAppTest.EntityFramework;

internal static class DataSeed
{
    private static readonly Guid[] _guids = [
        Guid.NewGuid(),
        Guid.NewGuid()
    ];

    public static Player[] Players { get; } = [
        new Player {
            Id = _guids[0],
            Account = "1",
            AccountType = "Free",
            DateCreated = DateTime.Now,
        },
        new Player {
            Id = _guids[1],
            Account = "2",
            AccountType = "DeFree",
            DateCreated = DateTime.Now,
        },
    ];

    public static Character[] Characters { get; } = [
        new Character {
            Id = Guid.NewGuid(),
            NickName = "A",
            Classes = "AA",
            Level = 1,
            PlayerId = _guids[0],
            DateCreated = DateTime.Now,
        },
        new Character {
            Id = Guid.NewGuid(),
            NickName = "B",
            Classes = "BB",
            Level = 2,
            PlayerId = _guids[0],
            DateCreated = DateTime.Now,
        },
        new Character {
            Id = Guid.NewGuid(),
            NickName = "C",
            Classes = "CC",
            Level = 3,
            PlayerId = _guids[1],
            DateCreated = DateTime.Now,
        },
        new Character {
            Id = Guid.NewGuid(),
            NickName = "D",
            Classes = "DD",
            Level = 4,
            PlayerId = _guids[1],
            DateCreated = DateTime.Now,
        },
    ];
}
