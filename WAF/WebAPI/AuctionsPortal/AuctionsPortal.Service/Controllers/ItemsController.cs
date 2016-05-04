using System;
using System.Linq;
using System.Web.Http;
using AuctionsPortal.Service.Models;
using AuctionsPortal.Data;
using System.Diagnostics;
using System.Web;


namespace AuctionsPortal.Service.Controllers
{
    [RoutePrefix("api/items")]
    public class ItemsController : ApiController
    {
        private AuctionsPortalEntities _entities;

        /// <summary>
        /// Vezérlő példányosítása.
        /// </summary>       
        public ItemsController()
        {
            _entities = new AuctionsPortalEntities();
        }

        /// <summary>
        /// Vezérlő példányosítása.
        /// </summary>
        /// <param name="entities">Entitásmodell.</param>
        public ItemsController(AuctionsPortalEntities entities_)
        {
            _entities = entities_;
        }

        /// <summary>
        /// Vezérlő megsemmisítése.
        /// </summary>
        ~ItemsController()
        {
            Dispose(false);
        }

        /// <summary>
        /// Tárgyak lekérdezése.
        /// </summary>
        /// 
        [Route("advertisements")]
        [System.Web.Http.HttpGet]
        public IHttpActionResult Advertisements()
        {
            if(HttpContext.Current.Session["user"] == null)
                return Unauthorized();
            
            try
            {
                String userName = (String) HttpContext.Current.Session["user"];
                return Ok(_entities.Item.Include("Category").Where(item => item.Advetiser.UserName == userName).
                    ToList().Select(item => new ItemDTO
                {
                    Id = item.ItemId,
                    Name = item.Name,
                    Advatiser = new AdvatiserDTO {Name = item.Advetiser.Name, UserName = item.Advetiser.UserName},
                    Category = new CategoryDTO { Id = item.Category.CategoryId, Name = item.Category.CatgoryName },
                    StartingCall = item.StartingCall,
                    StartDate = item.StartDate,
                    CloseDate = item.CloseDate,
                    Description = item.Description
                }));
            }
            catch
            {
                return InternalServerError();
            }
        }

        /// <summary>
        /// Tárgyak lekérdezése.
        /// </summary>
        /// <param name="id">Kategória azonosító.</param>
        [Route("advertisements/{id}")]
        [System.Web.Http.HttpGet]
        public IHttpActionResult Advertisements(Int32 id)
        {

            try
            {
                return Ok(_entities.Item.Include("Category").Where(i => i.CategoryId == id).ToList().Select(item => new ItemDTO
                {
                    Id = item.ItemId,
                    Name = item.Name,
                    Category = new CategoryDTO { Id = item.Category.CategoryId, Name = item.Category.CatgoryName },
                    StartingCall = item.StartingCall,
                    StartDate = item.StartDate,
                    CloseDate = item.CloseDate,
                    Description = item.Description
                }));
            }
            catch
            {
                return InternalServerError();
            }
        }

        /// <summary>
        /// Tárgyak lekérdezése.
        /// </summary>
        /// 
        [Route("biddings/{itemId}")]
        [System.Web.Http.HttpGet]
        public IHttpActionResult Biddings(Int32 itemId)
        {
            if (HttpContext.Current.Session["user"] == null)
                return Unauthorized();

            

            try
            {
                
                return Ok(_entities.Bidding.Include("Item").Where(bidding => bidding.ItemId == itemId).
                    ToList().Select(bidding => new BiddingDTO
                    {
                        BiddingId = bidding.BiddingId,
                        ItemId = bidding.ItemId,
                        UserId = (Int32) bidding.UserId,
                        User = new UserDTO { UserName = bidding.Users.UserName,
                            UserId = (Int32)bidding.UserId, Name = bidding.Users.Name},
                        Amount = (Int32) bidding.Amount,
                        CallDate = bidding.CallDate
                        
                    }));
            }
            catch
            {
                return InternalServerError();
            }
        }

        [Route("max_amount/{itemId}")]
        [System.Web.Http.HttpGet]
        public IHttpActionResult MaxAmount(Int32 itemId)
        {
            int max;
            if(_entities.Bidding.Where(b=>b.ItemId == itemId).ToList().Count == 0 )
            {

                max = 0;
            }
            else
            {
                max = (int)_entities.Bidding.Include("Item").Where(b => b.ItemId == itemId).Max(b => b.Amount);
            }
            try
            {
                return Ok(max);
            } catch
            {
                return InternalServerError();
            }

        }

        /// <summary>
        /// Új tárgy létrehozása.
        /// </summary>
        /// <param name="buildingDTO">Tárgy.</param>
        [System.Web.Http.HttpPost]
        public IHttpActionResult PostItem([FromBody] ItemDTO itemDTO)
        {
            if (HttpContext.Current.Session["user"] == null)
                return Unauthorized();
            String currentUserName = (String)HttpContext.Current.Session["user"];
            Int32 currentUserId = _entities.Advetiser.Where(a => a.UserName == a.UserName).FirstOrDefault().AdvetiserId;
            try
            {
                Item addeditem= _entities.Item.Add(new Item
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

                // visszaküldjük a létrehozott tárgyat
                return Created(Request.RequestUri + itemDTO.Id.ToString(), itemDTO);
            }
            catch
            {
                return InternalServerError();
            }
        }

        /// <summary>
        /// Tárgy módosítása.
        /// </summary>
        /// <param name="buildingDTO">Tárgy.</param>
        /// 
        [System.Web.Http.HttpPut]
        public IHttpActionResult PutItem([FromBody] ItemDTO itemDTO)
        {
            if (HttpContext.Current.Session["user"] == null)
                return Unauthorized();
            try
            {

                Item item = _entities.Item.FirstOrDefault(i => i.ItemId == itemDTO.Id);

                if (item == null) // ha nincs ilyen azonosító, akkor hibajelzést küldünk
                    return NotFound();

                item.ItemId = itemDTO.Id;
                item.Name = itemDTO.Name;
                item.CategoryId = itemDTO.Category.Id;
                item.StartingCall = itemDTO.StartingCall;
                item.StartDate = itemDTO.StartDate;
                item.CloseDate = itemDTO.CloseDate;
                item.Description = itemDTO.Description;

                _entities.SaveChanges(); // elmentjük a módosított tárgyat

                return Ok();
            }
            catch
            {
                return InternalServerError();
            }
        }

        /// <summary>
        /// Megsemmisítés.
        /// </summary>
        protected override void Dispose(Boolean disposing)
        {
            if (disposing)
            {
                _entities.Dispose();
            }

            base.Dispose(disposing);
        }
    }
}
