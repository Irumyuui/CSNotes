namespace BlazorAppTest.Entites;

public class Player
{
    public Guid Id { get; set; }
    public string Account { get; set; } = null!;
    public string AccountType { get; set; } = null!;
    public DateTime DateCreated { get; set; } = DateTime.Now;
    public ICollection<Character> Characters { get; set; } = null!;
}
