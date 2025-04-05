namespace BlazorAppTest.Entites.Dtos;

public record CharacterDto(Guid Id, string? NickName, string? Classes, int Level, DateTime DateCreated);
