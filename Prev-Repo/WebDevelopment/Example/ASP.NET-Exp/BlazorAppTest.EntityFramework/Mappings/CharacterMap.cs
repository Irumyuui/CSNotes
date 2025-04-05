using BlazorAppTest.Entites;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BlazorAppTest.EntityFramework.Mappings;

public class CharacterMap : IEntityTypeConfiguration<Character>
{
    public void Configure(EntityTypeBuilder<Character> builder)
    {
        builder.Property(c => c.NickName).HasMaxLength(20);
        builder.Property(c => c.Classes).HasMaxLength(20);

        builder.HasIndex(c => c.NickName).IsUnique();

        builder.HasOne(c => c.Player).WithMany(p => p.Characters).HasForeignKey(c => c.PlayerId);
    }
}
