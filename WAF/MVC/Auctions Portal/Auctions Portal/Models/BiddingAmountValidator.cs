using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    public static class BiddingAmountValidator
    {
        public static BiddingAmountError Validate(Int32 starting, Int32 lastAmount, Int32 currentAmount)
        {
            if (currentAmount < starting || currentAmount < lastAmount)
                return BiddingAmountError.TooFew;
            
            return BiddingAmountError.None;
        }

    }

    public enum BiddingAmountError { TooFew, None }
}