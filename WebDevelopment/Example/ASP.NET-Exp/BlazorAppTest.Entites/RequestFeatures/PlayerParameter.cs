namespace BlazorAppTest.Entites.RequestFeatures;

public class PlayerParameter : QueryStringParameters
{
    public DateTime MinDateCreated { get; set; }
    public DateTime MaxDateCreated { get; set; } = DateTime.Now;

    public bool ValidDateCreatedRange => MaxDateCreated >= MinDateCreated;

    public string? Account { get; set; }

    //public string OrderBy { get; set; } = "Account";

    public PlayerParameter() { OrderBy = "Account"; }
}