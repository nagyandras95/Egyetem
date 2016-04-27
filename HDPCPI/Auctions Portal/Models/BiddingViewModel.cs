using System;
using System.Web.Mvc;

namespace Auctions_Portal.Models
{
    public class BiddingViewModel
    {

        public Item Item { get; internal set; }
        /// <summary>
        /// The amount of bidding
        /// </summary>
        public Int32 Amount { get; set; }
        
    }
}