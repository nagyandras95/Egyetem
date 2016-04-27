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
                return _entities.Item.Where(item => item.CloseDate > DateTime.Today).OrderBy(item => item.StartDate);
            }
        }
		
		public IEnumerable<Item> GetActiveAdvertisements(Int32 from, Int32 how, IEnumerable<Item> categorizedItems = null)
		{
			List<Item> itemList = new List<Item>();
            
            List<Item> allItem = ActiveAdvertisements.ToList();

            int count = categorizedItems == null ? allItem.Count() : categorizedItems.Count();

            for (int i = from; i < Math.Min(count, from + how); i++)
			{
                if (categorizedItems == null)
                    itemList.Add(allItem[i]);
                else
                    itemList.Add(categorizedItems.ToList()[i]);

            }

            return itemList;
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

            return _entities.Bidding.Include("Item").
                Where(bidding => bidding.ItemId == itemId).Max(bidding=> bidding.Amount);


        }

        public IEnumerable<UserItemViewModel> GetUserBiddings(String userName)
        {
            List<UserItemViewModel> userItems = new List<UserItemViewModel>();
            foreach (int itemId in GetUserItemIds(userName))
            {
                
                
                DateTime lastDate = _entities.Bidding.Where
                    (b => b.ItemId == itemId && b.Users.UserName == userName).Max(b => b.CallDate);
                Item item = _entities.Bidding.Where(b => b.ItemId == itemId && b.CallDate == lastDate
                && b.Users.UserName == userName).
                    FirstOrDefault().Item;

                UserItemViewModel userItem = new UserItemViewModel();
                userItem.UserItem = item;
                Int32 maxAmount = (Int32) _entities.Bidding.Where(b => b.ItemId == item.ItemId).Max(b => b.Amount);
                String lastUserName = _entities.Bidding.Where(b => b.ItemId == item.ItemId && b.Users.UserName == userName
                && b.Amount == maxAmount).Select(b => b.Users.UserName).FirstOrDefault();

                userItem.First = (lastUserName == userName);
                userItem.Active = (item.CloseDate > DateTime.Today);
                
                if (!userItems.Contains(userItem))
                {
                    userItems.Add(userItem);
                }
                    
                   
            }
            return userItems;
        }

        public IEnumerable<int> GetUserItemIds(string userName)
        {
            List<int> allIds = _entities.Bidding.Where(b => b.Users.UserName == userName).Select(b => b.ItemId).ToList();
            return allIds.Distinct();
        }


        public IEnumerable<int> GetItemImageIds(int? itemId)
        {
            if (itemId == null)
                return null;

            return _entities.ItemImage.Where(image => image.ItemId == itemId).Select(image => image.ImageId);
        }

        public ItemListViewModel GetItems(ItemListViewModel oldItemList)
        {
            if (oldItemList == null)
                return null;
            ItemListViewModel newItemList = new ItemListViewModel
            {
                Category = oldItemList.Category,
                ScrollIndex = oldItemList.ScrollIndex,
                Filter = oldItemList.Filter,
                ItemName = oldItemList.ItemName,
                HowMany = oldItemList.HowMany

            };

            if (newItemList.Category == null)
                newItemList.ListedItems = ActiveAdvertisements.ToList();
            else
                newItemList.ListedItems = GetAdvertisements(newItemList.Category).ToList();

            if (!String.IsNullOrEmpty(newItemList.ItemName))
                newItemList.ListedItems = Filter
                    (newItemList.ItemName, newItemList.ListedItems).ToList();

            newItemList.ListedItems = GetActiveAdvertisements
                (newItemList.ScrollIndex*20,20,newItemList.ListedItems).ToList();

            return newItemList;

                
        }

        public ItemListViewModel CreateCategorizedItemList(int? categoryId, int index)
        {
            ItemListViewModel itemList = new ItemListViewModel
            {
                Category = categoryId,
                ScrollIndex = index
            };

            if (categoryId != null)
            {
                itemList.ListedItems = GetAdvertisements(categoryId).ToList();
                
            }
            else
            {
                itemList.ListedItems = ActiveAdvertisements.ToList();
            }
            itemList.HowMany = itemList.ListedItems.Count() / 20;
            itemList.ListedItems = GetActiveAdvertisements
                (itemList.ScrollIndex * 20, 20, itemList.ListedItems).ToList();

            return itemList;
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

        public BiddingViewModel NewBidding(int? itemId)
        {
            Item item = GetItem(itemId);
            Int32? lastAmount = GetLastAmount(itemId);
            if (item == null || lastAmount == null)
                return null;

            BiddingViewModel biddingAmount = new BiddingViewModel();
            if (biddingAmount == null)
                return null;

            if (lastAmount == null || lastAmount == 0)
            {
                biddingAmount.Amount = item.StartingCall;
            }
            else
            {
                biddingAmount.Amount = (Int32)lastAmount + 500;
            }
            return biddingAmount;
        }

        public bool SaveBidding(int? itemId, String userName, BiddingViewModel biddingModel)
        {
            if (itemId == null)
                return false;
            Users user = _entities.Users.FirstOrDefault(u => u.UserName == userName);
            if (user == null)
                return false;

            _entities.Bidding.Add(new Bidding
            {
                UserId = user.UserId,
                Users = user,
                ItemId = (Int32) itemId,
                Item = biddingModel.Item,
                CallDate = DateTime.Today,
                Amount = biddingModel.Amount
                  
            });

            try
            {
                _entities.SaveChanges();
            }
            catch (Exception)
            {

                return false;
            }
           

            return true;
        }

        public int GetTimesOfAdvertisments(int times)
        {
            return ActiveAdvertisements.Count()/times + 1;
        }

        public IEnumerable<Item> Filter(String itemName, List<Item> itemList)
        {
            return itemList.Where(item => item.Name.Contains(itemName));
        }


    }
}