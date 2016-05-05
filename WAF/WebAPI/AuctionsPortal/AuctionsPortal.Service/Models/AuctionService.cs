using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using AuctionsPortal.Data;
using System.Security.Cryptography;
using System.Text;

namespace AuctionsPortal.Service.Models
{
    public class AuctionService
    {
        private AuctionsPortalEntities _entities;

        /// <summary>
        /// Vezérlő példányosítása.
        /// </summary>       
        public AuctionService()
        {
            _entities = new AuctionsPortalEntities();
        }

        /// <summary>
        /// Vezérlő példányosítása.
        /// </summary>
        /// <param name="entities">Entitásmodell.</param>
        public AuctionService(AuctionsPortalEntities entities_)
        {
            _entities = entities_;
        }

        /// <summary>
        /// Tárgyak lekérdezése.
        /// </summary>
        /// 
        [System.Web.Http.HttpGet]
        public IEnumerable<ItemDTO> Advertisements()
        { 

            String userName = (String)HttpContext.Current.Session["user"];
            return _entities.Item.Include("Category").Where(item => item.Advetiser.UserName == userName).
                ToList().Select(item => new ItemDTO
                {
                    Id = item.ItemId,
                    Name = item.Name,
                    Advatiser = new AdvatiserDTO { Name = item.Advetiser.Name, UserName = item.Advetiser.UserName },
                    Category = new CategoryDTO { Id = item.Category.CategoryId, Name = item.Category.CatgoryName },
                    StartingCall = item.StartingCall,
                    StartDate = item.StartDate,
                    CloseDate = item.CloseDate,
                    Description = item.Description
                });
           
        }

        /// <summary>
        /// Tárgyak lekérdezése.
        /// </summary>
        /// ]
        public IEnumerable<BiddingDTO> Biddings(Int32 itemId)
        {


            return _entities.Bidding.Include("Item").Where(bidding => bidding.ItemId == itemId).
            ToList().Select(bidding => new BiddingDTO
            {
                BiddingId = bidding.BiddingId,
                ItemId = bidding.ItemId,
                UserId = (Int32)bidding.UserId,
                User = new UserDTO
                {
                    UserName = bidding.Users.UserName,
                    UserId = (Int32)bidding.UserId,
                    Name = bidding.Users.Name
                },
                Amount = (Int32)bidding.Amount,
                CallDate = bidding.CallDate
            });

        }

        public Int32 MaxAmount(Int32 itemId)
        {
            int max;
            if (_entities.Bidding.Where(b => b.ItemId == itemId).ToList().Count == 0)
            {

                max = 0;
            }
            else
            {
                max = (int)_entities.Bidding.Include("Item").Where(b => b.ItemId == itemId).Max(b => b.Amount);
            }
            return max;


        }

        /// <summary>
        /// Új tárgy létrehozása.
        /// </summary>
        /// <param name="buildingDTO">Tárgy.</param>
        public void PostItem(ItemDTO itemDTO)
        {
            if (HttpContext.Current.Session["user"] == null)
                return;

            String currentUserName = (String)HttpContext.Current.Session["user"];
            Int32 currentUserId = _entities.Advetiser.Where(a => a.UserName == currentUserName).FirstOrDefault().AdvetiserId;
            Item addeditem = _entities.Item.Add(new Item
                {

                    Name = itemDTO.Name,
                    CategoryId = itemDTO.Category.Id,
                    AdvetiserId = currentUserId,
                    StartingCall = itemDTO.StartingCall,
                    StartDate = itemDTO.StartDate,
                    CloseDate = itemDTO.CloseDate,
                    Description = itemDTO.Description
                });

                _entities.SaveChanges(); // elmentjük az új tárgyat
        }

        /// <summary>
        /// Tárgy módosítása.
        /// </summary>
        /// <param name="buildingDTO">Tárgy.</param>
        /// 
        [System.Web.Http.HttpPut]
        public void PutItem(ItemDTO itemDTO)
        {
            if (HttpContext.Current.Session["user"] == null)
                return;

                Item item = _entities.Item.FirstOrDefault(i => i.ItemId == itemDTO.Id);

                item.ItemId = itemDTO.Id;
                item.Name = itemDTO.Name;
                item.CategoryId = itemDTO.Category.Id;
                item.StartingCall = itemDTO.StartingCall;
                item.StartDate = itemDTO.StartDate;
                item.CloseDate = itemDTO.CloseDate;
                item.Description = itemDTO.Description;

                _entities.SaveChanges(); // elmentjük a módosított tárgyat
            
        }


        public void Login(String userName, String password)
        {

            Advetiser advitiser = _entities.Advetiser.FirstOrDefault(a => a.UserName == userName); // megkeressük a felhasználót


            // ellenőrizzük a jelszót (ehhez a kapott jelszót hash-eljük)
            Byte[] passwordBytes = null;
            using (SHA512CryptoServiceProvider provider = new SHA512CryptoServiceProvider())
            {
                passwordBytes = provider.ComputeHash(Encoding.UTF8.GetBytes(password));
            }

            if (!passwordBytes.SequenceEqual(advitiser.Password))
                return;

            if (HttpContext.Current.Session["user"] != null)
                HttpContext.Current.Session["user"] = null;

            // ha sikeres volt az ellenőrzés
            HttpContext.Current.Session["user"] = advitiser.UserName; // felvesszük a felhasználó nevét a munkamenetbe
        }

        public void Logout()
        {
            if (HttpContext.Current.Session["user"] == null)
                return;

            HttpContext.Current.Session["user"] = null;
        }

        /// <summary>
        /// Új hírdető hozzáadása
        /// </summary>
        /// <param name="advatiserDTO"></param>
        /// <returns></returns>
        public void Register(AdvatiserDTO advatiserDTO)
        {
            Advetiser advitiser = _entities.Advetiser.FirstOrDefault(a => a.UserName == advatiserDTO.UserName);

            if (advitiser != null)
                return;

            SHA512CryptoServiceProvider provider = new SHA512CryptoServiceProvider();
            Advetiser addedAdvatiser = _entities.Advetiser.Add(new Advetiser
                {
                    Name = advatiserDTO.Name,
                    UserName = advatiserDTO.UserName,
                    Password = provider.ComputeHash(Encoding.UTF8.GetBytes(advatiserDTO.Password))
                });

                _entities.SaveChanges(); // elmentjük az új hírdetőt
        }
    }
}