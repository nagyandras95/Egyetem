using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using Auctions_Portal.Models;

namespace Auctions_Portal.Controllers
{
    public class HomeController : Controller
    {

        private AuctionsPortalEntityModel _entities;

        public HomeController()
        {
            _entities = new AuctionsPortalEntityModel();

            ViewBag.Categories = _entities.Catgory.ToArray();


        }

        // GET: Home
        public ActionResult Index()
        {
            return View("Index", _entities.Catgory.ToList());
        }
    }
}