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
        /// Get active advartisements
        /// </summary>
        IEnumerable<Item> ActiveAdvertisements { get; }

        /// <summary>
        /// Get Biddings
        /// </summary>
        /// <param name="cityId">Identification of category.</param>
        IEnumerable<Item> GetAdvertisements(Int32? catgoryId);

        Int32? GetLastAmount(Int32? itemId);


        /// <summary>
        /// Get biddings
        /// </summary>
        IEnumerable<Bidding> Biddings { get; }
   

        /// <summary>
        /// Get bidding
        /// </summary>
        /// <param name="biddingId">Identification of bidding.</param>
        Bidding GetBidding(Int32? biddingId);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="userName"></param>
        /// <returns></returns>
        IEnumerable<Item> GetUserBiddings(String userName);

        /// <summary>
        /// Get identifications of bidding images.
        /// </summary>
        /// <param name="biddingId">Identification of bidding</param>
        IEnumerable<Int32> GetItemImageIds(Int32? biddingId);


        Item GetItem(int? itemId);

        /// <summary>
        /// Get bidding image.
        /// </summary>
        /// <param name="imageId">Identification of image.</param>
        Byte[] GetBuildingImage(Int32? imageId);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="biddingId"></param>
        /// <returns></returns>
        BiddingViewModel NewBidding(Int32? biddingId);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="biddingId"></param>
        /// <param name="userName"></param>
        /// <param name="biddingModel"></param>
        /// <returns></returns>
        Boolean SaveBidding(Int32? biddingId, String userName, BiddingViewModel biddingModel);



    }
}