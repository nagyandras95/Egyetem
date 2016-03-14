namespace Auctions_Portal.Models
{
    using System;
    using System.Data.Entity;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Linq;

    public partial class AuctionsPortalEntityModel : DbContext
    {
        public AuctionsPortalEntityModel()
            : base("name=AuctionsPortalEntityModel")
        {
        }

        public virtual DbSet<Advetiser> Advetiser { get; set; }
        public virtual DbSet<Catgory> Catgory { get; set; }
        public virtual DbSet<Item> Item { get; set; }
        public virtual DbSet<Users> Users { get; set; }
        public virtual DbSet<Bidding> Bidding { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Advetiser>()
                .Property(e => e.Name)
                .IsUnicode(false);

            modelBuilder.Entity<Advetiser>()
                .Property(e => e.UserName)
                .IsUnicode(false);

            modelBuilder.Entity<Advetiser>()
                .Property(e => e.Password)
                .IsUnicode(false);

            modelBuilder.Entity<Catgory>()
                .Property(e => e.CatgoryName)
                .IsUnicode(false);

            modelBuilder.Entity<Catgory>()
                .HasMany(e => e.Item)
                .WithRequired(e => e.Catgory)
                .WillCascadeOnDelete(false);

            modelBuilder.Entity<Item>()
                .Property(e => e.Name)
                .IsUnicode(false);

            modelBuilder.Entity<Item>()
                .Property(e => e.Description)
                .IsUnicode(false);

            modelBuilder.Entity<Item>()
                .HasMany(e => e.Bidding)
                .WithRequired(e => e.Item)
                .WillCascadeOnDelete(false);

            modelBuilder.Entity<Users>()
                .Property(e => e.Name)
                .IsUnicode(false);

            modelBuilder.Entity<Users>()
                .Property(e => e.UserName)
                .IsUnicode(false);

            modelBuilder.Entity<Users>()
                .Property(e => e.EMail)
                .IsUnicode(false);

            modelBuilder.Entity<Users>()
                .HasMany(e => e.Bidding)
                .WithRequired(e => e.Users)
                .WillCascadeOnDelete(false);
        }
    }
}
