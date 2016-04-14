using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using Auctions_Portal.Models;

namespace Auctions_Portal.Controllers
{
    public class HomeController : BaseController
    {


        // GET: Home
        public ActionResult Index()
        {
            return View("Index", _auctionService.ActiveAdvertisements.ToList());
        }

        /// <summary>
        /// Listing bidding
        /// </summary>
        /// <param name="categoryId">Identification of catgory</param>
        /// <returns>View of biddings.</returns>
        public ActionResult List(Int32? categoryId)
        {
            if (categoryId == null)
                return RedirectToAction("Index");

            List<Item> items = _auctionService.GetAdvertisements(categoryId).ToList();
            if(items == null)
            {
                return RedirectToAction("Index");
            }

     
            return View("Index", items);
        }


        /// <summary>
        /// Details of a bidding
        /// </summary>
        /// <param name="biddingId">Identification of bidding</param>
        /// <returns>View of details.</returns>
        public ActionResult Details(Int32? itemId)
        {
            if (itemId == null)
            {
                return RedirectToAction("Index");
            }

            
            Item item = _auctionService.GetItem(itemId);

            if(item == null)
            {
                return RedirectToAction("Index");
            }

            Int32? biggestAmount = _auctionService.GetLastAmount(itemId);
            if(biggestAmount == null)
                return RedirectToAction("Index");

            ViewBag.Title = "Ajánlat és a tárgy részletei: " + item.Name; // az oldal címe
            ViewBag.Images = _auctionService.GetItemImageIds(item.ItemId).ToList();

            return View("Details", new Tuple<Item,Int32>(item, (Int32)biggestAmount));


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
            Byte[] imageContent = _auctionService.GetBuildingImage(imageId);

            if (imageContent == null) // amennyiben nem sikerült betölteni, egy alapértelmezett képet adunk vissza
                return File("~/Content/no_image.png", "image/png");

            return File(imageContent, "image/png");
        }

       
    }
}