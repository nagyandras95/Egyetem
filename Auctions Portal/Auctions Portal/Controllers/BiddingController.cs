using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Auctions_Portal.Models;

namespace Auctions_Portal.Controllers
{
    public class BiddingController : BaseController
    {
        // GET: Bidding
        public ActionResult Index()
        {
            return View();
        }

        [HttpGet]
        public ActionResult Index(Int32? biddingId)
        {
            if (biddingId == null)
            {
                return RedirectToAction("Index");
            }

            BiddingViewModel biddingAmount = _auctionService.NewBidding(biddingId);
            if (biddingAmount == null)
            {
                return RedirectToAction("Index");
            }

            return View("Index", biddingAmount);
            

        }

        [HttpPost]
        public ActionResult Index(Int32? biddingId, BiddingViewModel biddingAmount)
        {
            if (biddingAmount == null || biddingAmount == null)
            {
                return RedirectToAction("Index");
            }

            biddingAmount.Bidding = _auctionService.GetBidding(biddingId);
            if (biddingAmount.Bidding == null)
            {
                return RedirectToAction("Index","Home");
            }

            switch(BiddingAmountValidator.Validate((Int32)biddingId, biddingAmount.Bidding.Amount, biddingAmount.Amount,
                biddingAmount.Bidding.Item.StartingCall))
            {
                case BiddingAmountError.TooFew :
                    ModelState.AddModelError("BiddingAmount", "Túl alacsony ajálat!");   
                    break;
                
            }

            if (!ModelState.IsValid)
                return View("Index", biddingAmount);

            if(_accountService.CurrentUserName == null)
            {
                return RedirectToAction("Index","Home");
                
            }

            String userName = _accountService.CurrentUserName;

            if (!_auctionService.SaveBidding(biddingId, userName, biddingAmount))
            {
                ModelState.AddModelError("", "A ajánlattétel sikertelen volt, kérem, próbálja újra!");
                return View("Index", biddingAmount);
            }

            ViewBag.Message = "Aaz ajánlatot sikeresen megtettük!";
            return View("Index", "Home");
        }
    }
}