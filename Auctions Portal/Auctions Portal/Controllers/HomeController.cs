using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using Auctions_Portal.Models;

namespace Auctions_Portal.Controllers
{
    public class HomeController : Controller
    {

        private AuctionsPortalEntities _entities;

        public HomeController()
        {
            _entities = new AuctionsPortalEntities();

            ViewBag.Categories = _entities.Catgory.ToArray();


        }

        // GET: Home
        public ActionResult Index()
        {
            return View("Index", _entities.Bidding.Include("Item").ToList());
        }

        /// <summary>
        /// Listing bidding
        /// </summary>
        /// <param name="categoryID">Identification of catgory</param>
        /// <returns>View of biddings.</returns>
        public ActionResult List(Int32? categoryID)
        {
            if (categoryID == null || !_entities.Bidding.Any(b => b.Item.CagoryID == categoryID))
                return RedirectToAction("Index"); 

     
            return View("Index", _entities.Bidding.Include("Item").Where(b => b.Item.CagoryID == categoryID).ToList());
        }


        /// <summary>
        /// Details of a bidding
        /// </summary>
        /// <param name="biddingID">Identification of bidding</param>
        /// <returns>View of details.</returns>
        public ActionResult Details(Int32? biddingID)
        {
            if (biddingID == null)
            {
                return RedirectToAction("Index");
            }
                

            Bidding bidding = _entities.Bidding.Include("Item").FirstOrDefault( i => i.BiddingID == biddingID);

            if(bidding == null)
            {
                return RedirectToAction("Index");
            }

            ViewBag.Title = "Ajánlat és a tárgy részletei: " + bidding.Item.Name; // az oldal címe
            ViewBag.Images = _entities.ItemImage.Where(image => image.ItemID == bidding.Item.ItemID).Select(image => image.ImageID).ToList();

            return View("Details", bidding);


        }

        /// <summary>
        /// Query an item image.
        /// </summary>
        /// <param name="imageId">Identification of image.</param>
        /// <returns>Image for an item or a defualt image.</returns>
        public FileResult Image(Int32? imageId)
        {
            if (imageId == null) // nem adtak meg azonosítót
                return File("~/Content/no_image.png", "image/png");

            // lekérjük a megadott azonosítóval rendelkező képet
            Byte[] imageContent = _entities.ItemImage.Where(image => image.ImageID == imageId).Select(image => image.ImageS).FirstOrDefault();

            if (imageContent == null) // amennyiben nem sikerült betölteni, egy alapértelmezett képet adunk vissza
                return File("~/Content/no_image.png", "image/png");

            return File(imageContent, "image/png");
        }
    }
}