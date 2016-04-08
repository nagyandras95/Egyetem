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

            ViewBag.Categories = _entities.Category.ToArray();


        }

        // GET: Home
        public ActionResult Index()
        {
            return View("Index", _entities.Bidding.Include("Item").ToList());
        }

        /// <summary>
        /// Listing bidding
        /// </summary>
        /// <param name="categoryId">Identification of catgory</param>
        /// <returns>View of biddings.</returns>
        public ActionResult List(Int32? categoryId)
        {
            if (categoryId == null || !_entities.Bidding.Any(b => b.Item.CategoryId == categoryId))
                return RedirectToAction("Index"); 

     
            return View("Index", _entities.Bidding.Include("Item").Where(b => b.Item.CategoryId == categoryId).ToList());
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
                

            Bidding bidding = _entities.Bidding.Include("Item").FirstOrDefault( i => i.ItemId == biddingId);

            if(bidding == null)
            {
                return RedirectToAction("Index");
            }

            ViewBag.Title = "Ajánlat és a tárgy részletei: " + bidding.Item.Name; // az oldal címe
            ViewBag.Images = _entities.ItemImage.Where(image => image.ItemId == bidding.Item.ItemId).Select(image => image.ImageId).ToList();

            return View("Details", bidding);


        }

        [HttpGet]
        public ActionResult Bidding(Int32? biddingId)
        {
            if(biddingId == null)
            {
                return RedirectToAction("Index");
            }

            Bidding bidding = _entities.Bidding.Include("Item").FirstOrDefault(i => i.ItemId == biddingId);

            BiddingViewModel biddingAmount = new BiddingViewModel();
            biddingAmount.BiddingId = (Int32) biddingId;
            if (biddingAmount == null)
            {
                biddingAmount.Amount = bidding.Item.StartingCall;
            }
            else
            {
                biddingAmount.Amount = (Int32) bidding.Amount + 500;
            }
            return View("Bidding", biddingAmount);

        }

        [HttpPost]
        public ActionResult Bidding(BiddingViewModel biddingAmount)
        {
            if(biddingAmount == null || Session["user"] == null)
            {
                return RedirectToAction("Index");
            }

            Bidding bidding = _entities.Bidding.Include("Item").FirstOrDefault(i => i.ItemId == biddingAmount.BiddingId);
            if(bidding == null)
            {
                return RedirectToAction("Index");
            }

            if(bidding.Amount == null && biddingAmount.Amount < bidding.Item.StartingCall ||
                bidding.Amount != null && biddingAmount.Amount < bidding.Amount)
            {
                ViewBag.Error = "Túl alcsony összeg";
                return View("Bidding", biddingAmount);
            }

            if(Session["user"] != null)
            {
                Users user = _entities.Users.FirstOrDefault(u => u.UserName == (String) Session["user"]);

                bidding.UserId = user.UserId;
                bidding.Users = user;

                _entities.Bidding.Attach(bidding);
                var entry = _entities.Entry(bidding);
                entry.Property(e => e.UserId).IsModified = true;
                entry.Property(e => e.Users).IsModified = true;
                _entities.SaveChanges();
            }

            return View("Index", "Home");
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
            Byte[] imageContent = _entities.ItemImage.Where(image => image.ItemId == imageId).Select(image => image.Image).FirstOrDefault();

            if (imageContent == null) // amennyiben nem sikerült betölteni, egy alapértelmezett képet adunk vissza
                return File("~/Content/no_image.png", "image/png");

            return File(imageContent, "image/png");
        }

       
    }
}