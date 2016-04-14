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

        public IEnumerable<Item> ActiveAdvertisements
        {
            get
            {
                return _entities.Item.Where(item => item.CloseDate > DateTime.Today);
            }
        }

        public Bidding GetBidding(Int32? biddingId)
        {
            if (biddingId == null || !_entities.Bidding.Any(bidding => bidding.ItemId == biddingId))
                return null;

            return _entities.Bidding.Include("Item").FirstOrDefault(bidding => bidding.ItemId == biddingId);
        }

        public Item GetItem(int? itemId)
        {
            if (itemId == null || !_entities.Item.Any(item => item.ItemId == itemId))
                return null;

            return _entities.Item.FirstOrDefault(item => item.ItemId == itemId);
        }

        public Int32? GetLastAmount(Int32? itemId)
        {
            if(itemId == null || !_entities.Item.Any(item => item.ItemId == itemId))
                return null;

            if(!_entities.Bidding.Include("Item").Any(bidding => bidding.ItemId == itemId))
                return 0;

            return _entities.Bidding.Include("Item").OrderBy(bidding => bidding.CallDate).
                Where(bidding => bidding.ItemId == itemId).LastOrDefault().Amount;


        }

        public IEnumerable<Item> GetUserBiddings(String userName)
        {
            List<Item> userItems = new List<Item>();
            foreach (int itemId in GetUserItemIds(userName))
            {
                userItems.Add(_entities.Bidding.Where(b => b.ItemId == itemId).
                    OrderBy(b => b.CallDate).LastOrDefault().Item);
            }
            return userItems;
        }

        public IEnumerable<int> GetUserItemIds(string userName)
        {
            return _entities.Bidding.Where(b => b.Users.UserName == userName).Select(b => b.ItemId);
        }

        public IEnumerable<int> GetItemImageIds(int? itemId)
        {
            if (itemId == null)
                return null;

            return _entities.ItemImage.Where(image => image.ItemId == itemId).Select(image => image.ImageId);
        }

        public IEnumerable<Item> GetAdvertisements(Int32? catgoryId)
        {
            if (catgoryId == null || !_entities.Item.Any(item => item.CategoryId == catgoryId))
                return null;

            return ActiveAdvertisements.Where( item => item.CategoryId == catgoryId);
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