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

            ViewBag.Categories = _entities.Catgories.ToArray();


        }

        // GET: Home
        public ActionResult Index()
        {
            return View("Index", _entities.Catgories.ToList());
        }

        /// <summary>
        /// Listing bidding
        /// </summary>
        /// <param name="catrgoyId">Identification of catgory</param>
        /// <returns>View of biddings.</returns>
        public ActionResult List(Int32? catrgoyId)
        {
            if (catrgoyId == null || !_entities.Biddings.Any(b => b.Item.CagoryID == catrgoyId))
                return RedirectToAction("Index"); 

     
            return View("Index", _entities.Biddings.Include("Item").Include("Catgory").Where(i => i.Item.CagoryID== catrgoyId).ToList());
        }

        public ActionResult Details(Int32? biddingID)
        {
            if (biddingID == null)
            {
                return RedirectToAction("Index");
            }
                

            Bidding bidding = _entities.Biddings.Include("Item").Include("User").FirstOrDefault( i => i.BiddingID == biddingID);

            if(bidding == null)
            {
                return RedirectToAction("Index");
            }

            ViewBag.Title = "Ajánlat és a tárgy részletei: " + bidding.Item.Name; // az oldal címe

            return View("Details", bidding);


        }
    }
}