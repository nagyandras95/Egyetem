using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Auctions_Portal.Models;

namespace Auctions_Portal.Models
{
    public class AuctionService : IAuctionService
    {

        private AuctionsPortalEntities _entities;

        public AuctionService()
        {
            _entities = new AuctionsPortalEntities();
        }

        public IEnumerable<Category> Categories
        {
            get
            {
                return _entities.Category;
            }
        }

        public IEnumerable<Bidding> Biddings
        {
            get
            {
                return _entities.Bidding.Include("Item");
            }
        }


        public Bidding GetBidding(Int32? biddingId)
        {
            if (biddingId == null || !_entities.Bidding.Any(bidding => bidding.ItemId == biddingId))
                return null;

            return _entities.Bidding.Include("Item").FirstOrDefault(bidding => bidding.ItemId == biddingId);
        }

        public IEnumerable<int> GetItemImageIds(int? itemId)
        {
            if (itemId == null)
                return null;

            return _entities.ItemImage.Where(image => image.ItemId == itemId).Select(image => image.ImageId);
        }

        public IEnumerable<Bidding> GetBiddings(Int32? catgoryId)
        {
            if (catgoryId == null || !_entities.Bidding.Any(bidding => bidding.Item.CategoryId == catgoryId))
                return null;

            return _entities.Bidding.Where( b => b.Item.CategoryId == catgoryId);
        }

        public byte[] GetBuildingImage(int? imageId)
        {
            if (imageId == null)
                return null;

            return _entities.ItemImage.Where(image => image.ItemId == imageId).Select(image => image.Image).FirstOrDefault();
        }

        public BiddingViewModel NewBidding(int? biddingId)
        {
            Bidding bidding = GetBidding(biddingId);
            if (bidding == null)
                return null;

            BiddingViewModel biddingAmount = new BiddingViewModel();
            if (biddingAmount == null)
                return null;

            if (bidding.Amount == null)
            {
                biddingAmount.Amount = bidding.Item.StartingCall;
            }
            else
            {
                biddingAmount.Amount = (Int32)bidding.Amount + 500;
            }
            return biddingAmount;
        }

        public bool SaveBidding(int? biddingId, String userName, BiddingViewModel biddingModel)
        {
            if (biddingId == null)
                return false;
            Users user = _entities.Users.FirstOrDefault(u => u.UserName == userName);
            if (user == null)
                return false;

            biddingModel.Bidding.UserId = user.UserId;
            biddingModel.Bidding.Users = user;
            _entities.Bidding.Attach(biddingModel.Bidding);
            var entry = _entities.Entry(biddingModel.Bidding);
            entry.Property(e => e.UserId).IsModified = true;
            entry.Property(e => e.Users).IsModified = true;
            _entities.SaveChanges();

            return true;
        }
    }
}