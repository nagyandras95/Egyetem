using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    public static class BiddingAmountValidator
    {
        public static BiddingAmountError Validate(Int32 biddingId, Int32? amount, Int32 currentAmount, Int32 starting)
        {
            if (amount == null && currentAmount < starting ||
                amount != null && currentAmount < amount)
            {

                return BiddingAmountError.TooFew;
            }

            return BiddingAmountError.None;
        }

    }

    public enum BiddingAmountError { TooFew, None }
}