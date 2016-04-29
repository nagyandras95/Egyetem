using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AuctionsPortal.Data
{
    public class ImageDTO
    {

        /// <summary>
        /// Azonosító lekérdezése, vagy beállítása.
        /// </summary>
        public Int32 Id { get; set; }

        /// <summary>
        /// Épület azonosító lekérdezése, vagy beállítása.
        /// </summary>
        public Int32 ItemId { get; set; }

        /// <summary>
        /// Kis kép lekérdezése, vagy beállítása.
        /// </summary>
        public Byte[] Image { get; set; }
    }
}
