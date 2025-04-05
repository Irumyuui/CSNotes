namespace BlazorAppTest.Entites.Dtos;

public class PlayerWithCharactersDto : PlayerDto
{
    public IEnumerable<CharacterDto> Characters { get; set; } = [];
}