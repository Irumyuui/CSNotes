//using AutoMapper;

using BlazorAppTest.Entites;
using BlazorAppTest.Entites.Dtos;

namespace BlazorAppTest.WebApi;

public class MappingProfile : AutoMapper.Profile
{
    public MappingProfile()
    {
        CreateMap<Player, PlayerDto>();
        CreateMap<Player, PlayerWithCharactersDto>();
        CreateMap<Character, CharacterDto>();

        CreateMap<PlayerForCreationDto, Player>();
        CreateMap<PlayerForUpdateDto, Player>();
    }
}
