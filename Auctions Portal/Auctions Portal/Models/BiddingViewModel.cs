using System;
using System.Web.Mvc;

namespace Auctions_Portal.Models
{
    public class BiddingViewModel
    {
        [HiddenInput(DisplayValue = false)]
        public Int32 BiddingId { get; set; }

        public Bidding Bidding { get; internal set; }
        /// <summary>
        /// The amount of bidding
        /// </summary>
        public Int32 Amount { get; set; }
        
    }
}