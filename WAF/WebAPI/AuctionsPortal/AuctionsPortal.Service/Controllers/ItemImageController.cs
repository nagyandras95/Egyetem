using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using AuctionsPortal.Service.Models;
using AuctionsPortal.Data;

namespace AuctionsPortal.Service.Controllers
{
    

    public class ItemImageController : ApiController
    {
        private AuctionsPortalEntities _entities;

        public ItemImageController()
        {
            _entities = new AuctionsPortalEntities();
        }

        public ItemImageController(AuctionsPortalEntities entities_)
        {
            _entities = entities_;
        }

        ~ItemImageController()
        {
            Dispose(false);
        }

        /// <summary>
        /// Egy épület képeinek lekérdezése.
        /// </summary>
        /// <param name="itemId">Épület azonosító.</param>
        [Route("building/{buildingId}")]
        public IHttpActionResult GetImages(Int32 itemId)
        {
            // a megfelelő képeket betöltjük és átalakítjuk (csak a kis képeket)
            return Ok(_entities.ItemImage.Where(image => image.ItemId == itemId).Select(image => new ImageDTO { Id = image.ImageId }));
        }

        /// <summary>
        /// Egy kép lekérdezése.
        /// </summary>
        [Route("{id}")]
        public IHttpActionResult GetImage(Int32 id)
        {
            ItemImage image = _entities.ItemImage.FirstOrDefault(img => img.ImageId == id);

            if (image == null)
                return NotFound();

            // a képe átalakítjuk (kis és nagyképet egyaránt)
            return Ok(new ImageDTO
            {
                Id = image.ImageId,
                ItemId = image.ImageId,
                Image = image.Image
            });
        }

        /// <summary>
        /// Kép feltöltése.
        /// </summary>
        /// <param name="buildingId">Épület azonosító.</param>
        /// <param name="size">Képméret.</param>
        /// <param name="content">Képi tartalom.</param>
        [Route] // itt nem kell paramétereznünk, csak jelezzük, hogy az egyedi útvonalat vesszük igénybe
        [Authorize(Roles = "administrator")] // csak bejelentkezett adminisztrátoroknak
        public IHttpActionResult PostImage([FromBody] ImageDTO image)
        {
            if (image == null || !_entities.Item.Any(item => image.ItemId == item.ItemId))
                return NotFound();

            ItemImage itemImage = new ItemImage
            {
                ItemId = image.ItemId,
                Image = image.Image
            };

            _entities.ItemImage.Add(itemImage);

            try
            {
                _entities.SaveChanges();
                return Created(Request.RequestUri + image.Id.ToString(), image.Id); // csak az azonosítót küldjük vissza
            }
            catch
            {
                return InternalServerError();
            }
        }

        /// <summary>
        /// Kép törlése.
        /// </summary>
        /// <param name="id">A kép azonosítója.</param>
        [Route("{id}")]
        [Authorize(Roles = "administrator")]
        public IHttpActionResult DeleteImage(Int32 id)
        {
            ItemImage image = _entities.ItemImage.FirstOrDefault(im => im.ItemId == id);

            if (image == null)
                return NotFound();

            try
            {
                _entities.ItemImage.Remove(image);
                _entities.SaveChanges();
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
