using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AuctionsPortal.Data
{
    public class BiddingDTO
    {
        public int BiddingId { get; set; }
        public int ItemId { get; set; }
        public System.DateTime CallDate { get; set; }
        public UserDTO User { get; set; }
        public Int32 UserId { get; set; }
        public Int32 Amount { get; set; }

    }
}
