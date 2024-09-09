namespace BlazorAppTest.Entites;

public class Character
{
    public Guid Id { get; set; }
    public string NickName { get; set; } = null!;
    public string Classes { get; set; } = null!;
    public int Level { get; set; }
    public DateTime DateCreated { get; set; }

    public Guid PlayerId { get; set; }
    public Player Player { get; set; } = null!;
}
