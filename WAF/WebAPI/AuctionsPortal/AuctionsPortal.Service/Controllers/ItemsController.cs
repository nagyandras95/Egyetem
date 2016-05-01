using System;
using System.Linq;
using System.Web.Http;
using AuctionsPortal.Service.Models;
using AuctionsPortal.Data;

namespace AuctionsPortal.Service.Controllers
{
    [RoutePrefix("api/items")]
    class ItemsController : ApiController
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
        public IHttpActionResult Advertiesements()
        {
            try
            {
                return Ok(_entities.Item.Include("Category").ToList().Select(item => new ItemDTO
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
        /// <param name="id">Kategória azonosító.</param>
        [Route("category_items")]
        [System.Web.Http.HttpGet]
        public IHttpActionResult ItemsForcategory(Int32 id)
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
        /// Új tárgy létrehozása.
        /// </summary>
        /// <param name="buildingDTO">Tárgy.</param>
        public IHttpActionResult PostItem([FromBody] ItemDTO itemDTO)
        {
            try
            {
                Item addeditem= _entities.Item.Add(new Item
                {
                    ItemId = itemDTO.Id,
                    Name = itemDTO.Name,
                    CategoryId = itemDTO.Category.Id,
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
        public IHttpActionResult PutBuilding([FromBody] ItemDTO itemDTO)
        {
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
