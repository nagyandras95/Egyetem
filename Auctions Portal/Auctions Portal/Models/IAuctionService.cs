using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    public interface IAuctionService
    {
        /// <summary>
        /// Get categories
        /// </summary>
        IEnumerable<Category> Categories { get; }

        /// <summary>
        /// Get biddings
        /// </summary>
        IEnumerable<Bidding> Biddings { get; }

        /// <summary>
        /// Get Biddings
        /// </summary>
        /// <param name="cityId">Identification of category.</param>
        IEnumerable<Bidding> GetBiddings(Int32? catgoryId);

        /// <summary>
        /// Get bidding
        /// </summary>
        /// <param name="biddingId">Identification of bidding.</param>
        Bidding GetBidding(Int32? biddingId);

        /// <summary>
        /// Get identifications of bidding images.
        /// </summary>
        /// <param name="biddingId">Identification of bidding</param>
        IEnumerable<Int32> GetItemImageIds(Int32? biddingId);

        /// <summary>
        /// Get bidding image.
        /// </summary>
        /// <param name="imageId">Identification of image.</param>
        Byte[] GetBuildingImage(Int32? imageId);


        BiddingViewModel NewBidding(Int32? biddingId);

        Boolean SaveBidding(Int32? biddingId, String userName, BiddingViewModel biddingModel);



    }
}