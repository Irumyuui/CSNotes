using BlazorAppTest.Entites;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BlazorAppTest.EntityFramework.Mappings;

public class PlayerMap : IEntityTypeConfiguration<Player>
{
    public void Configure(EntityTypeBuilder<Player> builder)
    {
        builder.Property(player => player.Account).HasMaxLength(50);
        builder.Property(player => player.AccountType).HasMaxLength(10);
        builder.HasIndex(player => player.Account).IsUnique();
    }
}
