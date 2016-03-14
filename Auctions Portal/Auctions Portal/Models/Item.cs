namespace Auctions_Portal.Models
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("Item")]
    public partial class Item
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2214:DoNotCallOverridableMethodsInConstructors")]
        public Item()
        {
            Bidding = new HashSet<Bidding>();
        }

        public int ItemID { get; set; }

        [StringLength(30)]
        public string Name { get; set; }

        public int CagoryID { get; set; }

        [StringLength(100)]
        public string Description { get; set; }

        public int StartingCall { get; set; }

        [Column(TypeName = "date")]
        public DateTime? CloseDate { get; set; }

        [Required]
        public byte[] Image { get; set; }

        public virtual Catgory Catgory { get; set; }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<Bidding> Bidding { get; set; }
    }
}
