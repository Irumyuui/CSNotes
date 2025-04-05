using BlazorAppTest.Entites;
using BlazorAppTest.EntityFramework.Mappings;
using Microsoft.EntityFrameworkCore;

namespace BlazorAppTest.EntityFramework
{
    public class GameManagementDbContext : DbContext
    {
        public GameManagementDbContext(DbContextOptions<GameManagementDbContext> opts) : base(opts)
        {
        }

        public DbSet<Player> Players { get; set; }

        public DbSet<Character> Characters { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            //modelBuilder.ApplyConfigurationsFromAssembly(Assembly.Get)

            modelBuilder.ApplyConfiguration(new PlayerMap());
            modelBuilder.ApplyConfiguration(new CharacterMap());

            modelBuilder.Entity<Player>().HasData(DataSeed.Players);
            modelBuilder.Entity<Character>().HasData(DataSeed.Characters);
        }
    }
}
