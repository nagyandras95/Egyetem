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
            return View("Index", _auctionService.Biddings.ToList());
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

            List<Bidding> biddings = _auctionService.GetBiddings(categoryId).ToList();
            if(biddings == null)
            {
                return RedirectToAction("Index");
            }

     
            return View("Index", biddings);
        }


        /// <summary>
        /// Details of a bidding
        /// </summary>
        /// <param name="biddingId">Identification of bidding</param>
        /// <returns>View of details.</returns>
        public ActionResult Details(Int32? biddingId)
        {
            if (biddingId == null)
            {
                return RedirectToAction("Index");
            }

            Bidding bidding = _auctionService.GetBidding(biddingId);

            if(bidding == null)
            {
                return RedirectToAction("Index");
            }

            ViewBag.Title = "Ajánlat és a tárgy részletei: " + bidding.Item.Name; // az oldal címe
            ViewBag.Images = _auctionService.GetItemImageIds(bidding.Item.ItemId).ToList();

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
            Byte[] imageContent = _auctionService.GetBuildingImage(imageId);

            if (imageContent == null) // amennyiben nem sikerült betölteni, egy alapértelmezett képet adunk vissza
                return File("~/Content/no_image.png", "image/png");

            return File(imageContent, "image/png");
        }

       
    }
}