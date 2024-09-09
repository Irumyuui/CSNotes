namespace BlazorAppTest.Entites.Dtos;

public class PlayerDto
{
    public Guid Id { get; set; }
    public string? Account { get; set; }
    public string? AccountType { get; set; }
    public DateTime DateCreated { get; set; }
}
